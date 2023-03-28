//
// Created by peter on 2/26/2023.
//

#ifndef ROBOTCONTROLLER_LISTENER_H
#define ROBOTCONTROLLER_LISTENER_H
#include "threepp/threepp.hpp"
using namespace threepp;

namespace {

    struct Listener: KeyListener {

        enum KEY {a_ = 65,b_,c_,d_,e_,f_,g_,h_,i_,j_,k_,l_,m_,n_,o_,p_,q_,r_,s_,t_,u_,v_,w_,x_,y_,z_,
            lshift_ = 340, lctrl_ = 341
        };

        float &t;
        Vector3 target{0,0,0};
        bool shift = false;
        bool ctrl= false;
        int current = 0;

        float r = 1.0f;
        explicit Listener(float &t) : t(t) {}

        void onKeyPressed(KeyEvent evt) override {

            //std::cout << evt.key << std::endl;


            if (evt.key == lshift_)
            {
                shift = true;
            }
            else if (evt.key == lctrl_)
            {
                ctrl = true;
            }
            else if (evt.key == current)
            {
                current = 0;
            }
            else
            {
                current = evt.key;
            }

        }

        void onKeyReleased(KeyEvent evt) override {


            if (evt.key == lshift_)
            {
                shift = false;
                r = 1.0f;
            }

            else if (evt.key == lctrl_)
            {   // left ctrl key
                ctrl = false;
            }

            else
            {
            }

        }

        void onKeyRepeat(KeyEvent evt) override {

        }
    };

    struct MListener: MouseListener {

        float &t;

        bool LEFTCLICK = false;
        bool RIGHTCLICK = false;

        explicit MListener(float &t) : t(t) {}

        void onMouseDown(int button, const Vector2& pos) override {
            if (button == 0) LEFTCLICK = true;
            if (button == 1) RIGHTCLICK = true;
        }

        void onMouseUp(int button, const Vector2& pos) override {
            LEFTCLICK = false;
            RIGHTCLICK = false;
        }

    };

}


#endif //ROBOTCONTROLLER_LISTENER_H
