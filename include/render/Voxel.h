#ifndef VOXEL_H
#define VOXEL_H

#include <render/Shader.h>

#include <glm/vec3.hpp>

class Voxel {
private:
    unsigned int VAO;
    glm::vec3 position;

public:
    Voxel(const glm::vec3 &position);

    void draw(Shader &shader);
};

#endif