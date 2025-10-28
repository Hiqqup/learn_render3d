//
// Created by ju on 10/28/25.
//

#pragma once

#include <cstddef>
#include <map>
#include <vector>
#include <string>
#include <filesystem>
#include "tiny_gltf.h"

class Mesh3d {
    struct Primitive {
    int mode;
    size_t count;
    int type;
    };
    unsigned int VAO = 0;
    std::map<int, unsigned int> buffers;
    std::map<std::string, unsigned int> vaa = {
            {"POSITION", 0},
            {"NORMAL", 1}
    };
    std::vector<Primitive> primitives;
    tinygltf::Model loadGltf(const std::filesystem::path &gltfAssetPath);
public:
    explicit Mesh3d(const std::filesystem::path &gltfAssetPath, int meshIndex = 0);
    void draw() const ;
    ~Mesh3d();


};
