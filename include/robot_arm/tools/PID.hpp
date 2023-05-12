//
// Created by peter on 3/6/2023.
//
// Code from https://github.com/markaren/threepp/blob/master/examples/libs/utility/PID.hpp
// This has been used in order to save time as PID control is a very trivial
// concept. Slightly modified.

#ifndef ROBOTCONTROLLER_PID_HPP
#define ROBOTCONTROLLER_PID_HPP

#include <limits>
#include <optional>

#include "threepp/threepp.hpp"

using namespace threepp;

struct PIDParameters {
    float kp;
    float ti;
    float td;

    void set_params(float _kp, float _ti, float _td) {
        kp = _kp;
        ti = _ti;
        td = _td;
    };
};

class PID {

public:

    PID() : PID(1.0f, 0.01f, 0.0f) {}

    PID(float kp, float ti, float td) : params_{kp, ti, td} {}

    Vector3 regulate(Vector3 setPoint, Vector3 measuredValue, float dt) {
        if (dt == 0) dt = std::numeric_limits<float>::min();

        Vector3 currentError = (setPoint - measuredValue);

        integral_ += (currentError * dt);

        Vector3 diff = ((currentError - prevError_) / dt);

        // Windup guard for integral
        if (windupGuard_) {
            for (int i = 0; i < 3; i++) {
                integral_[i] = std::clamp(integral_[i], -windupGuard_.value(), windupGuard_.value());
            }
        }

        // Save current error as previous error for next iteration
        prevError_ = currentError;

        // Scale
        Vector3 P = (currentError * params_.kp);
        Vector3 I = (integral_ * params_.ti);
        Vector3 D = (diff * params_.td);

        //Vector3 sum = P + I + D - error because D = infinity?
        Vector3 sum = P + I;

        return sum;
    }

    void setWindupGuard(const std::optional<float> &windupGuard) {
        windupGuard_ = windupGuard;
    }

    [[nodiscard]] Vector3 error() const {
        return prevError_;
    }

    [[nodiscard]] PIDParameters &params() {
        return params_;
    }

    [[nodiscard]] const PIDParameters &params() const {
        return params_;
    }

private:

    Vector3 integral_{};
    Vector3 prevError_{};
    PIDParameters params_;
    std::optional<float> windupGuard_;
};

#endif //ROBOTCONTROLLER_PID_HPP
