#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "utils/vec3d.h"
#include "screen/rgb.h"
#include "lights/light.h"
#include "scene.h"
#include "screen/screen.h"
#include "threadpool.h"

class Camera {
public:
    class CameraTaskGenerator : public TaskGenerator {
    public:
        int i = 0, j = 0;
        int height, width;

        const Scene *scene;
        ScreenBuffer *screen;
        const Camera *camera;
        CameraTaskGenerator(const Scene* _scene, ScreenBuffer* _screen, const Camera* _camera) {
            scene = _scene;
            screen = _screen;
            camera = _camera;
            height = screen->size();
            width = screen->front().size();
        }
        Executor operator()() override ;

        void inc();

        bool isEmpty() override ;
    };
    Vec3d origin, topLeft, bottomLeft, topRight;
    Vec3d uniW, uniH;
    int screenHeight, screenWidth;
    Camera(const Vec3d& _origin,
           const Vec3d& _topLeft,
           const Vec3d& _bottomLeft,
           const Vec3d& _topRight):
            origin(_origin),
            topLeft(_topLeft),
            bottomLeft(_bottomLeft),
            topRight(_bottomLeft) { }
    Camera() {}

    RGB light2RGB(const Light& light) const;

    void setScreenSize(const Settings &settings);

    void setScreenSize(int _screenHeignt, int _screenWidth);

    RGB calcPixel(const Scene& scene, int w_coord, int h_coord) const;

    void shot(const Scene& scene, ScreenBuffer &screenBuffer, bool parallel = true) const;
};

#endif // _CAMERA_H_