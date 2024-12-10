#ifndef MESH_H
#define MESH_H

#include <cstddef>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "../shaders/shader.h"

struct Vertex {
    glm::vec3 pos;
    glm::vec3 norm;
    glm::vec2 uvCoord;
    glm::vec3 tan;
    glm::vec3 bitan;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader &shader);
private:
    //  render data
    GLuint vao, vbo, ebo;

    void setupMesh();
};

#endif