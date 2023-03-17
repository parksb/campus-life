#define GLFW_INCLUDE_NONE
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "toys.h"

void init();
void render(GLFWwindow* window);

int main(void) {
    if (!glfwInit()) exit(EXIT_FAILURE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    GLFWwindow* window = glfwCreateWindow(640, 480, "Title", NULL, NULL);
    glfwMakeContextCurrent(window);

    init();

    while (!glfwWindowShouldClose(window)) {
        render(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

GLuint vertexBuffer = 0;
GLuint vertexArray = 0;
GLuint elementBuffer = 0;
Program program;

using namespace glm;
using namespace std;

void init() {
    program.loadShaders("shader.vert", "shader.frag");

    vector<vec3> vertices = {
        {-1, -1, 0}, // lower left
        {-0.5, 0, 0}, // middle left
        {1, -1, 0}, // lower right
        {0.5, 0, 0}, // middle right
        {0, 1, 0}, // upper middle
        {0, -1, 0} // lower center
    };

    vector<u16vec3> triangles = {{0, 5, 1}, {5, 2, 3}, {1, 3, 4}};

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u16vec3) * triangles.size(), triangles.data(), GL_STATIC_DRAW);
}

void render(GLFWwindow* window) {
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0, 0, .5, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program.programID);
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_SHORT, 0);

    glfwSwapBuffers(window);
}

