#ifndef ROBOTCONTROLLER_HELPER_H
#define ROBOTCONTROLLER_HELPER_H

#include "LinkedList.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

// How much the cost is multiplied with when upgrading
inline float upgradeCostMultiplier = 1.15f;

/**
 * @brief Loads an image into a texture
 *
 * This function loads the image data from an image file located at the specified path.
 *
 * @param path The path to the .png file to be loaded.
 *
 * @return A std::shared_ptr<Texture> pointing to the loaded texture.
 *
 */
std::shared_ptr<Texture> loadTexture(const std::string& path);

/**
 * @brief Loads the geometry of an STL file.
 *
 * This function loads the geometry data from an STL file located at the specified path.
 *
 * @param path The path to the STL file to be loaded.
 * @return A std::shared_ptr<BufferGeometry> pointing to the loaded geometry.
 *
 */
std::shared_ptr<BufferGeometry> loadSTL(const std::string& path);

/**
 * @brief Changes the color of a mesh.
 *
 * @param mesh The mesh that will change color.
 * @param color The new color.
 *
 * @return void.
 *
 */
void changeMeshColor(const std::shared_ptr<Mesh> &mesh, Color color);

/**
 * @brief Creates a mesh from an STL file
 *
 * This function loads the STL file as a geometry and creates a material for it
 * before it then creates a new mesh and returns a shared pointer to it.
 *
 * @param path The path to the STL file to be loaded.
 * @return A std::shared_ptr<Mesh> pointing to the created Mesh.
 *
 */
std::shared_ptr<Mesh> meshFromSTL(const std::string &path, Color color = Color::white, Vector3 scaling = {1.0f, 1.0f, 1.0f});

/**
 * @brief Logs information in the terminal.
 *
 * This function prints the input to the terminal with a new line at the end.
 *
 * @param T The input to be printed.
 * @return void.
 *
 * @note Will crash if given invalid inputs.
 */
template<typename T>
void log(T input);

enum Axis {
    x, y, z
};
#endif //ROBOTCONTROLLER_HELPER_H
