//
// Created by manatee on 24.04.16.
//

#include <iostream>

#include "beamtracer.h"
#include "settings.h"

BeamTracer defaultTracer;

BeamTracer::BeamTracer() { }

Light BeamTracer::operator()(const Beam &beam, const Scene &scene) const {
    return trace(beam, scene, 0);
}

Light BeamTracer::trace(const Beam& beam, const Scene& scene, signed_small depth) const {
    if (depth == settings.tracingDepth) return LIGHT_BLACK;
    Intersection intersection = findFirstIntersection(beam, scene.figures);

    if (isInf(intersection.first)) {
        return LIGHT_BLACK;
    }

    Vec3d point = beam(intersection.first);
    Vec3d normal = intersection.second->getNormalIn(point);
    std::pair<Vec3d, Vec3d> ref = reflectAndRefract(-beam.dir,
                                                    normal,
                                                    beam.attribute,
                                                    intersection.second->traits.refractiveId);

    Beam reflectedBeam = make_beam(point, ref.first);
    reflectedBeam.attribute = beam.attribute;
    Light reflectedLight = trace(reflectedBeam, scene, depth + 1);
    reflectedLight = reflectedLight * intersection.second->traits.reflectionRate;

    Beam refractedBeam = make_beam(point, ref.second);
    refractedBeam.attribute = intersection.second->traits.refractiveId;
    if (normal * beam.dir > 0)
        refractedBeam.attribute = 1;
    Light refractedLight = trace(refractedBeam, scene, depth + 1);
    refractedLight = refractedLight * intersection.second->traits.refractionRate;

    real dispersedLightPower = 0;
    real phongsLightPower = 0;
    for (const auto& lightSource : scene.lights) {
        Vec3d rvec = lightSource.loc - point;
        real distToLight = rvec.len();
        Beam beamToLight = make_beam(point, rvec);
        Intersection i = findFirstIntersection(beamToLight, scene.figures);

        if (i.first + real_epsilon < distToLight) {
            continue;
        }

        real crossFactor = rvec.normalized() * normal * sign(-beam.dir * normal);
        if (crossFactor > 0)
            dispersedLightPower += crossFactor * lightSource.power / sqr(distToLight);
        crossFactor = beamToLight.dir * beam.dir;
        if (crossFactor > 0)
            phongsLightPower += lightSource.power * pow(crossFactor, intersection.second->traits.alpha);
    }

    Light dispersedLight = dispersedLightPower * intersection.second->traits.color;
    Light phongsLight = phongsLightPower * intersection.second->traits.reflectionRate * intersection.second->traits.color;


    Light light = reflectedLight + refractedLight + dispersedLight + phongsLight;

    return light;
}





