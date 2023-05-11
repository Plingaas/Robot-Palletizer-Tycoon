//
// Created by peter on 3/30/2023.
//

#ifndef ROBOTCONTROLLER_HELPER_H
#define ROBOTCONTROLLER_HELPER_H

#include "LinkedList.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

/**
 * @brief Loads the geometry of an STL file.
 *
 * This function loads the geometry data from an STL file located at the specified path and returns it
 * as a shared pointer to a BufferGeometry object.
 *
 * @param path The path to the STL file to be loaded.
 * @return A std::shared_ptr<BufferGeometry> pointing to the loaded geometry.
 *
 * @note The caller of this function should manage the lifespan of the returned BufferGeometry object
 *       by holding onto the shared pointer or transferring its ownership appropriately.
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
void changeMeshColor(std::shared_ptr<Mesh> mesh, Color color);

/**
 * @brief Creates a mesh from an STL file
 *
 * This function loads the STL file as a geometry and creates a material for it
 * before it then creates a new mesh and returns a shared pointer to it.
 *
 * @param path The path to the STL file to be loaded.
 * @return A std::shared_ptr<Mesh> pointing to the created Mesh.
 *
 * @note The caller of this function should manage the lifespan of the returned Mesh object
 *       by holding onto the shared pointer or transferring its ownership appropriately.
 */
std::shared_ptr<Mesh> meshFromSTL(const std::string &path, Color color = Color::white, Vector3 scaling = {1.0f, 1.0f, 1.0f});

/**
 * @brief Logs information in the terminal.
 *
 * This function prints the input to the terminal with a new line at the end.
 * If the input is invalid it won't print.
 *
 * @param path The input to be printed.
 * @return void.
 *
 */
template<typename T>
void log(T input);

enum Axis {
    x, y, z
};
#endif //ROBOTCONTROLLER_HELPER_H
