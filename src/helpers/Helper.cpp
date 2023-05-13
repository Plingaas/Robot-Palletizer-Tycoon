#include "helpers/Helper.hpp"

STLLoader stl_loader;
TextureLoader texture_loader;

std::shared_ptr<Texture> loadTexture(const std::string &path) {
    return texture_loader.load(path);
}

std::shared_ptr<BufferGeometry> loadSTL(const std::string &path) {
    return stl_loader.load(path);
}

std::shared_ptr<Mesh> meshFromSTL(const std::string &path, Color color, Vector3 scaling) {
    auto geo = stl_loader.load(path);
    auto mat = MeshPhongMaterial::create();
    mat->color = color;

    auto mesh = Mesh::create(geo, mat);
    mesh->scale = scaling;

    return mesh;
};

void changeMeshColor(std::shared_ptr<Mesh> mesh, Color color) {
    auto mat = MeshPhongMaterial::create();
    mat->color = color;
    mesh->setMaterial(mat);
}


// test_streaming_operator is written by ChatGPT 4.0 in order to only accept printable input.
// I was considering adding operator overload << for my classes in order to be able to print
// some useful information but decided on using ChatGPT to save time. I have had originally
// just written a logger with template <typename T>. This is the only part of this project
// that has been written by ChatGPT.
template<typename T>
auto test_streaming_operator(T&& t) -> decltype(std::cout << std::forward<T>(t), std::true_type{});

std::false_type test_streaming_operator(...);

template<typename T>
void log(T input) {
    if constexpr (decltype(test_streaming_operator(std::declval<T>()))::value) {
        std::cout << input << std::endl;
    }
}