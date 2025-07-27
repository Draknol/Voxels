#include <render/Voxel.h>

#include <GL/glew.h>

Voxel::Voxel(const glm::vec3 &position)
    : position(position) {
    glGenVertexArrays(1, &VAO);
}

void Voxel::draw(Shader &shader) {
    glBindVertexArray(VAO);
    shader.setVec3("cubePos", position);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}