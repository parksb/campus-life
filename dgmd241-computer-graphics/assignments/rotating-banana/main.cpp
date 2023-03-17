#define GLFW_INCLUDE_NONE
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "toys.h"
#include "j3a.hpp"

const float PI = 3.14159265258979f;
float theta = 0;

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
    loadJ3A("banana.j3a");
    program.loadShaders("shader.vert", "shader.frag");

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, nVertices[0] * sizeof(glm::vec3), vertices[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nTriangles[0] * sizeof(glm::u32vec3), triangles[0], GL_STATIC_DRAW);
}

void render(GLFWwindow* window) {
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0, 0, 0.5f, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program.programID);

    GLint colorLocation = glGetUniformLocation(program.programID, "color");
    glUniform4fv(colorLocation, 1, value_ptr(vec4(1.0f, 1.0f, 0, 1.0f)));

    theta += 5.0f / 180 * PI;
    mat4 rotationMatrix = rotate(theta, vec3(0, 1.0f, 0));
    GLuint transformMatrixLocation = glGetUniformLocation(program.programID, "transformMatrix");
    glUniformMatrix4fv(transformMatrixLocation, 1, GL_FALSE, value_ptr(rotationMatrix));

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glDrawElements(GL_TRIANGLES, nTriangles[0] * 3, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
}

