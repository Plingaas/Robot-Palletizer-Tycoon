//
// Created by peter on 2/26/2023.
//

#include "Listener.h"

namespace {

    struct Listener: KeyListener {

        float &t;
        Vector3 *target;
        bool shift = false;
        bool ctrl= false;
        float r = 1.0f;

        explicit Listener(float &t, Vector3 *_target) : t(t) {target = _target;}

        void onKeyPressed(KeyEvent evt) override {

            if (evt.key == 340)
            {   // left shift key
                shift = true;
                r = 10.0f;
            }

            if (evt.key == 341)
            {   // left ctrl key
                ctrl = true;

            }

            if (ctrl)
            {
                if (evt.key == 265) { // Up
                    target->z += 1 * r;
                }
                if (evt.key == 264) { // Down
                    target->z -= 1 * r;
                }
            } else
            {
                if (evt.key == 265) { // Up
                    target->x -= 1 * r;
                }
                if (evt.key == 264) { // Down
                    target->x += 1 * r;
                }
                if (evt.key == 263) { // Left
                    target->y -= 1 * r;
                }
                if (evt.key == 262) { // Right
                    target->y += 1 * r;
                }
            }



        }

        void onKeyReleased(KeyEvent evt) override {
            if (evt.key == 340) {
                shift = false;
                r = 1.0f;
            }

            if (evt.key == 341)
            {   // left ctrl key
                ctrl = false;

            }

        }

        void onKeyRepeat(KeyEvent evt) override {
            if (ctrl)
            {
                if (evt.key == 265) { // Up
                    target->z += 1 * r;
                }
                if (evt.key == 264) { // Down
                    target->z -= 1 * r;
                }
            } else
            {
                if (evt.key == 265) { // Up
                    target->x -= 1 * r;
                }
                if (evt.key == 264) { // Down
                    target->x += 1 * r;
                }
                if (evt.key == 263) { // Left
                    target->y -= 1 * r;
                }
                if (evt.key == 262) { // Right
                    target->y += 1 * r;
                }
            }
        }
    };

}