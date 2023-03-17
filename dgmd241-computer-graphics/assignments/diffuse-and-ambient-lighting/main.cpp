#define GLFW_INCLUDE_NONE
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "toys.h"
#include "j3a.hpp"

const float PI = 3.14159265258979f;

float cameraTheta = 0;
float cameraPhi = 0;
float cameraDistance = 5;
float fovy = 80 * PI / 180;

Program program;
GLuint vertexBuffer = 0;
GLuint normalBuffer = 0;
GLuint vertexArray = 0;
GLuint elementBuffer = 0;

using namespace glm;
using namespace std;

vec3 lightPosition = vec3(3, 10, 5);
vec3 ambientLight = vec3(0.5);

void init();
void render(GLFWwindow* window);
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

int main(void) {
    if (!glfwInit()) exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_SAMPLES, 8);

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    GLFWwindow* window = glfwCreateWindow(640, 480, "Title", NULL, NULL);

    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);

    glfwMakeContextCurrent(window);

    init();

    while (!glfwWindowShouldClose(window)) {
        render(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void init() {
    loadJ3A("Hebe.j3a");
    program.loadShaders("shader.vert", "shader.frag");

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, nVertices[0] * sizeof(glm::vec3), vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, nVertices[0] * sizeof(glm::vec3), normals[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, 0);

    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nTriangles[0] * sizeof(glm::u32vec3), triangles[0], GL_STATIC_DRAW);
}

void render(GLFWwindow* window) {
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0, 0, 0.5f, 0);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program.programID);

    GLint colorLocation = glGetUniformLocation(program.programID, "color");
    glUniform4fv(colorLocation, 1, value_ptr(vec4(0.5f, 0.5f, 0.5f, 1.0f)));

    vec3 initialCameraPosition = vec3(0, 0, cameraDistance);
    mat4 cameraPhiRotationMat = rotate(cameraPhi, vec3(1, 0, 0));
    mat4 cameraThetaRotationMat = rotate(cameraTheta, vec3(0, 1, 0));
    vec3 cameraPosition = cameraThetaRotationMat * cameraPhiRotationMat * vec4(initialCameraPosition, 1);

    mat4 viewMat = glm::lookAt(cameraPosition, vec3(0, 0, 0), vec3(0, 1, 0));
    GLuint viewMatLocation = glGetUniformLocation(program.programID, "viewMat");
    glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, value_ptr(viewMat));

    mat4 projMat = glm::perspective(fovy, width / (float)height, 0.01f, 1000.0f);
    GLuint projMatLocation = glGetUniformLocation(program.programID, "projMat");
    glUniformMatrix4fv(projMatLocation, 1, GL_FALSE, value_ptr(projMat));

    GLuint lightPositionLocation = glGetUniformLocation(program.programID, "lightPosition");
    glUniform3fv(lightPositionLocation, 1, value_ptr(lightPosition));

    GLuint ambientLightLocation = glGetUniformLocation(program.programID, "ambientLight");
    glUniform3fv(ambientLightLocation, 1, value_ptr(ambientLight));

    GLuint cameraPositionLocation = glGetUniformLocation(program.programID, "cameraPosition");
    glUniform3fv(cameraPositionLocation, 1, value_ptr(cameraPosition));

    GLuint modelMatLocation = glGetUniformLocation(program.programID, "modelMat");
    glUniformMatrix4fv(modelMatLocation, 1, GL_FALSE, value_ptr(mat4(1)));

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glDrawElements(GL_TRIANGLES, nTriangles[0] * 3, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    static double lastX = 0;
    static double lastY = 0;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1)) {
        double dx = xpos - lastX;
        double dy = ypos - lastY;

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        cameraTheta -= dx / width * PI;
        cameraPhi -= dy / height * PI;
    }

    lastX = xpos;
    lastY = ypos;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    fovy += yoffset / 30;
}

