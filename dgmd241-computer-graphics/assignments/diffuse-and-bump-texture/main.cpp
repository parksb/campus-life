#define GLFW_INCLUDE_NONE
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "toys.h"
#include "j3a.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
GLuint textureCoordinateBuffer = 0;

using namespace glm;
using namespace std;

vec3 lightPosition = vec3(3, 10, 5);
vec3 lightColor = vec3(100);
vec3 ambientLight = vec3(0.1);
GLuint diffTex = 0;
GLuint bumpTex = 0;

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
    loadJ3A("dwarf.j3a");
    program.loadShaders("shader.vert", "shader.frag");

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, nVertices[0] * sizeof(glm::vec3), vertices[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, nVertices[0] * sizeof(glm::vec3), normals[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, 0);

    glGenBuffers(1, &textureCoordinateBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, textureCoordinateBuffer);
    glBufferData(GL_ARRAY_BUFFER, nVertices[0] * sizeof(glm::vec2), texCoords[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, 0, 0, 0);

    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nTriangles[0] * sizeof(glm::u32vec3), triangles[0], GL_STATIC_DRAW);

    int w, h, n;
    stbi_set_flip_vertically_on_load(true);

    void* d = stbi_load(diffuseMap[0].c_str(), &w, &h, &n, 4);
    glGenTextures(1, &diffTex);
    glBindTexture(GL_TEXTURE_2D, diffTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, d);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(d);

    d = stbi_load(bumpMap[0].c_str(), &w, &h, &n, 4);
    glGenTextures(1, &bumpTex);
    glBindTexture(GL_TEXTURE_2D, bumpTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, d);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(d);
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
    glUniform4fv(colorLocation, 1, value_ptr(diffuseColor[0]));

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

    GLuint lightColorLocation = glGetUniformLocation(program.programID, "lightColor");
    glUniform3fv(lightColorLocation, 1, value_ptr(lightColor));

    GLint shininessLocation = glGetUniformLocation(program.programID, "shininess");
    glUniform1f(shininessLocation, shininess[0]);

    GLuint ambientLightLocation = glGetUniformLocation(program.programID, "ambientLight");
    glUniform3fv(ambientLightLocation, 1, value_ptr(ambientLight));

    GLuint cameraPositionLocation = glGetUniformLocation(program.programID, "cameraPosition");
    glUniform3fv(cameraPositionLocation, 1, value_ptr(cameraPosition));

    GLuint modelMatLocation = glGetUniformLocation(program.programID, "modelMat");
    glUniformMatrix4fv(modelMatLocation, 1, GL_FALSE, value_ptr(mat4(1)));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffTex);
    GLuint diffTexLocation = glGetUniformLocation(program.programID, "diffTex");
    glUniform1i(diffTexLocation, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, bumpTex);
    GLuint bumpTexLocation = glGetUniformLocation(program.programID, "bumpTex");
    glUniform1i(bumpTexLocation, 1);

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

        const float MIN_CAMERA_PHI = -PI / 2 + 0.01f;
        const float MAX_CAMERA_PHI = PI / 2 - 0.01f;
        cameraPhi -= dy / height * PI;
        if (cameraPhi < MIN_CAMERA_PHI) {
            cameraPhi = MIN_CAMERA_PHI;
        } else if (cameraPhi > MAX_CAMERA_PHI) {
            cameraPhi = MAX_CAMERA_PHI;
        }

        cameraTheta -= dx / width * PI;
    }

    lastX = xpos;
    lastY = ypos;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    const float MIN_FOVY = 0.01f;
    const float MAX_FOVY = PI - 0.05f;

    fovy += yoffset / 30;
    if (fovy < MIN_FOVY) {
        fovy = MIN_FOVY;
    } else if (fovy > MAX_FOVY) {
        fovy = MAX_FOVY;
    }
}

