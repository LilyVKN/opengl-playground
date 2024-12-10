#include "./shader.h"

void Shader::loadShader() {
    const char* vert_shader_src = 
    #include "./test.vs"
    ;
    const char* frag_shader_src =
    #include "./test.frag"
    ;

    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glCompileShader(vert_shader);
    glShaderSource(vert_shader, 1, &vert_shader_src, NULL);
    glCompileShader(vert_shader);
    int success;
    char infoLog[512];
    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vert_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glCompileShader(frag_shader);
    glShaderSource(frag_shader, 1, &frag_shader_src, NULL);
    glCompileShader(frag_shader);
    // check for shader compile errors
    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(frag_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    this->shader_id = glCreateProgram();
    glAttachShader(this->shader_id, vert_shader);
    glAttachShader(this->shader_id, frag_shader);
    
    // insert location binding code here
    glBindAttribLocation(this->shader_id, 0, "vertex_position");
    glBindAttribLocation(this->shader_id, 1, "vertex_color");

    glLinkProgram(this->shader_id);
    // check for linking errors
    glGetProgramiv(this->shader_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->shader_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
}