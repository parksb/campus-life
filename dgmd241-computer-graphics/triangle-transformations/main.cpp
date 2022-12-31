#define GLFW_INCLUDE_NONE
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "toys.h"

const float PI = 3.14159265258979f;
float theta = 0;
float scaleFactor = 0;
bool isShirinking = true;

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
        {-0.7f, -0.7f, 0},
        {0.7, -0.7, 0},
        {0, 0.7f, 0},
    };

    vector<u16vec3> triangle = {{0, 1, 2}};

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u16vec3) * triangle.size(), triangle.data(), GL_STATIC_DRAW);
}

void render(GLFWwindow* window) {
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0, 0, .5, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program.programID);

    GLint colorLocation = glGetUniformLocation(program.programID, "color");
    glUniform4fv(colorLocation, 1, value_ptr(vec4(1.0f, 0.5f, 0, 1.0f)));

    theta += 5.0f / 180 * PI;
    if (isShirinking) {
        scaleFactor -= 0.025f;
        if (scaleFactor < 0.5f) isShirinking = false;
    } else {
        scaleFactor += 0.025f;
        if (scaleFactor > 1.0f) isShirinking = true;
    }

    mat3 rotationMatrix = mat3(cos(theta), sin(theta), 0, -sin(theta), cos(theta), 0, 0, 0, 1);
    mat3 scalingMatrix = mat3(scaleFactor, 0, 0, 0, scaleFactor, 0, 0, 0, 1.0f);
    GLuint transformMatrixLocation = glGetUniformLocation(program.programID, "transformMatrix");
    glUniformMatrix3fv(transformMatrixLocation, 1, GL_FALSE, value_ptr(scalingMatrix * rotationMatrix));

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer); glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);

    glfwSwapBuffers(window);
}

