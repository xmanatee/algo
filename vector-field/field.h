//
// Created by manatee on 06.11.16.
//

#ifndef RAIC_2016_FIELD_H
#define RAIC_2016_FIELD_H

#include <functional>

#include "vec2.h"

template<class R, class T>
class FieldProducer {
public:
    virtual R get(const T& v) const = 0;
};


template<class R, class T, class F = std::function<R(const T&, const T&)>>
class CentralFieldProducer : public FieldProducer<R, T> {
public:
    CentralFieldProducer(T _center, F _field): center(_center),
                                                                              field(_field) {}
    R get(const T& v) const override {
        return field(center, v);
    }
private:
    T center;
    std::function<R(T, T)> field;
};


template<class R, class T>
class Field : public FieldProducer<R, T> {
public:
    R get(const T& v) const override {
        R value;
        for (const auto& producer : producers) {
            value += producer->get(v);
        }
        return value;
    }

    Field& operator+=(FieldProducer<R, T>& producer) {
        producers.push_back(&producer);
        return *this;
    }

    void clear() {
        for (const auto& producer : producers) {
            delete producer;
        }
        producers.clear();
    }
private:
    std::vector<FieldProducer<R, T>*> producers;

};

typedef FieldProducer<double, Vec2d> PotentialFieldProducer;
typedef CentralFieldProducer<double, Vec2d> PotentialCentralFieldProducer;
typedef Field<double, Vec2d> PotentialField;

typedef FieldProducer<Vec2d, Vec2d> VectorFieldProducer;
typedef CentralFieldProducer<Vec2d, Vec2d> VectorCentralFieldProducer;
typedef Field<Vec2d, Vec2d> VectorField;

#endif //RAIC_2016_FIELD_H
