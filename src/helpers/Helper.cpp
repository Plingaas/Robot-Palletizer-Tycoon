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
    mesh->receiveShadow = true;

    return mesh;
};


void changeMeshColor(const std::shared_ptr<Mesh> &mesh, Color color) {
    auto mat = MeshPhongMaterial::create();
    mat->color = color;
    mesh->setMaterial(mat);

}

template<typename T>
void log(T input) {
    if constexpr (decltype(test_streaming_operator(std::declval<T>()))::value) {
        std::cout << input << std::endl;
    }
}