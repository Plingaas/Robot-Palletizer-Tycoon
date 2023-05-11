//
// Created by peter on 3/30/2023.
//
#include "helpers/Helper.hpp"

////////////////////////////////////////////
STLLoader stl_loader;

////////////////////////////////////////////

std::shared_ptr<BufferGeometry> loadSTL(const std::string &path) {
    return stl_loader.load(path);
}

void changeMeshColor(std::shared_ptr<Mesh> old_mesh, Color new_color) {
    auto mat = MeshPhongMaterial::create();
    mat->color = new_color;
    old_mesh->setMaterial(mat);
}

std::shared_ptr<Mesh> meshFromSTL(const std::string &path, Color color, Vector3 scaling) {
    auto geo = stl_loader.load(path);
    auto mat = MeshPhongMaterial::create();
    mat->color = color;

    auto mesh = Mesh::create(geo, mat);
    mesh->scale = scaling;

    return mesh;
};

template<typename T>
void log(T input) {
    std::cout << input << std::endl;
}