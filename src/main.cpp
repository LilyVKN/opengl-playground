#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <X11/X.h>
#include <X11/Xlib.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

Display                 *dpy;
Window                  root;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;

GLuint createTri() {
    GLuint points_vbo = 0;
    float points[] = {
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
    };
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    float colors[] = {
        1.0f, 0.0f,  0.0f,
        0.0f, 1.0f,  0.0f,
        0.0f, 0.0f,  1.0f
    };
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colors, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    return vao;
}

GLuint defineShaders() {
    const char* vert_shader_src = 
    #include "./shaders/test.vs"
    ;
    const char* frag_shader_src =
    #include "./shaders/test.frag"
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

    GLuint shader_prog = glCreateProgram();
    glAttachShader(shader_prog, vert_shader);
    glAttachShader(shader_prog, frag_shader);
    
    // insert location binding code here
    glBindAttribLocation(shader_prog, 0, "vertex_position");
    glBindAttribLocation(shader_prog, 1, "vertex_color");

    glLinkProgram(shader_prog);
    // check for linking errors
    glGetProgramiv(shader_prog, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_prog, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    return shader_prog;
}

void draw(GLuint shader_prog, GLuint vao, double time) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // projection matrix
    glm::mat4 proj_mat = glm::perspective(
        glm::radians(45.0f), 1.0f, 0.1f, 100.0f
    );

    // view matrix
    glm::mat4 view_mat = glm::lookAt(
        glm::vec3(0.0f, 2.0f, -2.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
    
    // model matrix
    float angle = time * 5.0;
    glm::mat4 trans = glm::mat4(1.0);
    trans = glm::rotate(trans, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

    glUseProgram(shader_prog);

    glm::mat4 mvp = proj_mat * view_mat * trans;
    GLint mvpLoc = glGetUniformLocation(shader_prog, "MVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(int argc, char *argv[]) {
    dpy = XOpenDisplay(NULL);

    if (dpy == NULL) {
    printf("\n\tcannot connect to X server\n\n");
        exit(0);
    }

    root = DefaultRootWindow(dpy);

    vi = glXChooseVisual(dpy, 0, att);

    if (vi == NULL) {
        printf("\n\tno appropriate visual found\n\n");
        exit(0);
    } else {
        printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
    }

    cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;

    win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

    XMapWindow(dpy, win);
    XStoreName(dpy, win, "VERY SIMPLE APPLICATION");

    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);

    GLuint shader_prog = defineShaders();
    GLuint vao = createTri();

    glEnable(GL_DEPTH_TEST); 

    auto program_start = std::chrono::high_resolution_clock::now();
    double delT = 0.0;

    // render first frame
    XGetWindowAttributes(dpy, win, &gwa);
    glViewport(0, 0, gwa.width, gwa.height);
    draw(shader_prog, vao, 0.0); 

    while(1) {        
        auto frame_start = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> program_age = frame_start - program_start;

        // TODO: read user input

        // swap frame while computing
        glXSwapBuffers(dpy, win);

        // TODO: pass data to physics thread

        // render next frame
        XGetWindowAttributes(dpy, win, &gwa);
        glViewport(0, 0, gwa.width, gwa.height);
        draw(shader_prog, vao, program_age.count());

        // TODO: wait for the physics thread to complete

        auto frame_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = frame_end - frame_start;
        delT = elapsed_seconds.count();
    }
}