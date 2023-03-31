//
// Created by peter on 3/30/2023.
//

#include "Box.h"

Box::Box(Color color_)
{
    color_ = 0xffffff * math::randomInRange(0, 0xffffff);
    size = {90.0f, 120.0f, 96.0f};
    auto geo = BoxGeometry::create(size.x, size.y, size.z);
    auto mat = MeshPhongMaterial::create();
    mat->color = color_;

    mesh = Mesh::create(geo, mat);
}
