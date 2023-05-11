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

        Vector3 curr_error = (setPoint - measuredValue);

        integral_ += (curr_error * dt);

        Vector3 diff = ((curr_error - prev_error_) / dt);

        // Windup guard for integral
        if (windup_guard_) {
            for (int i = 0; i < 3; i++) {
                integral_[i] = std::clamp(integral_[i], -windup_guard_.value(), windup_guard_.value());
            }
        }

        // Save current error as previous error for next iteration
        prev_error_ = curr_error;

        // Scale
        Vector3 P = (curr_error * params_.kp);
        Vector3 I = (integral_ * params_.ti);
        Vector3 D = (diff * params_.td);

        //Vector3 sum = P + I + D - error because D = infinity?
        Vector3 sum = P + I;


        return sum;
    }

    void setWindupGuard(const std::optional<float> &windupGuard) {
        windup_guard_ = windupGuard;
    }

    [[nodiscard]] Vector3 error() const {
        return prev_error_;
    }

    [[nodiscard]] PIDParameters &params() {
        return params_;
    }

    [[nodiscard]] const PIDParameters &params() const {
        return params_;
    }

private:

    Vector3 integral_{};
    Vector3 prev_error_{};
    PIDParameters params_;
    std::optional<float> windup_guard_;
};

#endif //ROBOTCONTROLLER_PID_HPP
