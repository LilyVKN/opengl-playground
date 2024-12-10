#ifndef SHADER_H
#define SHADER_H

#include <iostream>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

class Shader {
public:
    GLuint shader_id;

    void loadShader();

    void use() { glUseProgram(shader_id); }

    void setBool(const std::string &name, bool value) const
        { glUniform1i(glGetUniformLocation(shader_id, name.c_str()), (int)value); }
    void setInt(const std::string &name, int value) const
        { glUniform1i(glGetUniformLocation(shader_id, name.c_str()), value); }
    void setFloat(const std::string &name, float value) const
        { glUniform1f(glGetUniformLocation(shader_id, name.c_str()), value); }
};

#endif