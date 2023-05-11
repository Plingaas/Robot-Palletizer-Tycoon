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

// Code below is from ChatGPT 4.0
template<typename T>
auto test_streaming_operator(T&& t) -> decltype(std::cout << std::forward<T>(t), std::true_type{});

std::false_type test_streaming_operator(...);
template<typename T>
void log(T input) {
    if constexpr (decltype(test_streaming_operator(std::declval<T>()))::value) {
        std::cout << input << std::endl;
    } else
    {
        std::cout << "Invalid input, could not print." << std::endl;
    }
}