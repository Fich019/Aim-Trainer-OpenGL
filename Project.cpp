#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <math.h>
#include "GLFW/glfw3.h"
#include "Camera.h"
#include "Shaders.h"

using namespace std;
using namespace glm;

//width and height of the window ( Aspect ratio 16:9 )
const int SRC_width = 16 * 50;
const int SRC_height = 9 * 50;


Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SRC_width / 2.0f;
float lastY = SRC_height / 2.0f;
bool firstMouse = true;

int onMouse = 0;

vec3 spawnpoint = vec3(0.0f, 0.15f, -14.8f);




float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

void crosshair1(Shader &hud);
void crosshair2(Shader &hud);
void crosshair3(Shader &hud);
void crosshair4(Shader &hud);

void FetchColour();
void MouseClick(GLFWwindow* window, int button, int action, int mods);
void spawnTarget(Shader &shaders, vec3 spawn);

void spawnFloor(Shader &shaders);
void spawnWallBack(Shader &shaders);
void spawnWallFront(Shader& shaders);
void spawnWallLeft(Shader& shaders);
void spawnWallRight(Shader& shaders);
void spawnCeiling(Shader &shaders);

bool test = false;






int main(int argc, char** argv)
{

    glfwInit();


    GLFWwindow* window = glfwCreateWindow(SRC_width, SRC_height, "3D Shooting Range", NULL, NULL);

    

    glfwMakeContextCurrent(window);

    glewInit();
    
    glutInit(&argc, argv);

    


    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, MouseClick);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    Shader shaders("media/triangles.vert", "media/triangles.frag");
    
    Shader hud("media/HUD.vert", "media/HUD.frag");
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        processInput(window);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        
        spawnWallBack(shaders);
        spawnWallFront(shaders);
        spawnWallLeft(shaders);
        spawnWallRight(shaders);
        spawnFloor(shaders);
        spawnCeiling(shaders);


        spawnTarget(shaders, spawnpoint);


        crosshair1(hud);
        crosshair2(hud);
        crosshair3(hud);
        crosshair4(hud);

       
        

        glm::mat4 view = camera.GetViewMatrix();
        shaders.setMat4("view", view);





        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    
}


void crosshair1(Shader& hud) {

    float vertices[] = {
         0.05f,  0.01f, 0.0f,  // top right
         0.05f, -0.01f, 0.0f,  // bottom right
         0.02f, -0.01f, 0.0f,  // bottom left
         0.02f,  0.01f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);




    hud.use();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void crosshair2(Shader& hud) {

    float vertices[] = {
         -0.05f,  0.01f, 0.0f,  // top right
         -0.05f, -0.01f, 0.0f,  // bottom right
         -0.02f, -0.01f, 0.0f,  // bottom left
         -0.02f,  0.01f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);




    hud.use();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void crosshair3(Shader& hud) {

    float vertices[] = {
         0.005f,  0.09f, 0.0f,  // top right
         0.005f,  0.03f, 0.0f,  // bottom right
         -0.005f,  0.03f, 0.0f,  // bottom left
         -0.005f,  0.09f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);




    hud.use();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void crosshair4(Shader& hud) {

    float vertices[] = {
         0.005f,  -0.09f, 0.0f,  // top right
         0.005f,  -0.03f, 0.0f,  // bottom right
         -0.005f,  -0.03f, 0.0f,  // bottom left
         -0.005f,  -0.09f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);




    hud.use();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}



void spawnWallBack(Shader& shade) {

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);




    shade.use();

    mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SRC_width / (float)SRC_height, 0.1f, 100.0f);
    mat4 view = camera.GetViewMatrix();
    shade.setMat4("projection", projection);
    shade.setMat4("view", view);
    shade.setVec3("objectColor", vec3(0.5f, 0.0f, 0.5f));
    mat4 model = mat4(1.0);

    model = scale(model, vec3(10.0f, 7.0f, 7.0f));
    model = rotate(model, radians(0.0f), vec3(1.0f, 0.0f, 0.0f));
    model = translate(model, vec3(0.0f, 0.15f, 1.07f));
    shade.setMat4("model", model);


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void spawnWallFront(Shader& shade) {

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);




    shade.use();

    mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SRC_width / (float)SRC_height, 0.1f, 100.0f);
    mat4 view = camera.GetViewMatrix();
    shade.setMat4("projection", projection);
    shade.setMat4("view", view);
    shade.setVec3("objectColor", vec3(0.2f, 0.2f, 0.2f));
    mat4 model = mat4(1.0);

    model = scale(model, vec3(10.0f, 7.0f, 7.0f));
    model = rotate(model, radians(0.0f), vec3(1.0f, 0.0f, 0.0f));
    model = translate(model, vec3(0.0f, 0.15f, -1.07f));
    shade.setMat4("model", model);


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void spawnWallLeft(Shader& shade) {

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);




    shade.use();

    mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SRC_width / (float)SRC_height, 0.1f, 100.0f);
    mat4 view = camera.GetViewMatrix();
    shade.setMat4("projection", projection);
    shade.setMat4("view", view);
    shade.setVec3("objectColor", vec3(0.5f, 0.0f, 0.5f));
    mat4 model = mat4(1.0);

    model = scale(model, vec3(10.0f, 7.0f, 15.0f));
    model = rotate(model, radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = translate(model, vec3(0.0f, 0.15f, 0.5f));
    shade.setMat4("model", model);


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void spawnWallRight(Shader& shade) {

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);




    shade.use();

    mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SRC_width / (float)SRC_height, 0.1f, 100.0f);
    mat4 view = camera.GetViewMatrix();
    shade.setMat4("projection", projection);
    shade.setMat4("view", view);
    shade.setVec3("objectColor", vec3(0.5f, 0.0f, 0.5f));
    mat4 model = mat4(1.0);

    model = scale(model, vec3(10.0f, 7.0f, 15.0f));
    model = rotate(model, radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    model = translate(model, vec3(0.0f, 0.15f, -0.5f));
    shade.setMat4("model", model);


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void spawnCeiling(Shader& shade) {

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);




    shade.use();

    mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SRC_width / (float)SRC_height, 0.1f, 100.0f);
    mat4 view = camera.GetViewMatrix();
    shade.setMat4("projection", projection);
    shade.setMat4("view", view);
    shade.setVec3("objectColor", vec3(1.0f, 1.0f, 1.0f));
    mat4 model = mat4(1.0);

    model = scale(model, vec3(10.0f, 15.0f, 15.0f));
    model = rotate(model, radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
    model = translate(model, vec3(0.0f, 0.0f, -0.3f));
    shade.setMat4("model", model);


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
void spawnFloor(Shader& shade) {
    
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    

    shade.use();

    mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SRC_width / (float)SRC_height, 0.1f, 100.0f);
    mat4 view = camera.GetViewMatrix();
    shade.setMat4("projection", projection);
    shade.setMat4("view", view);
    shade.setVec3("objectColor", vec3(0.5f, 0.5f, 0.5f));
    mat4 model = mat4(1.0);

    model = scale(model, vec3(10.0f, 15.0f, 15.0f));
    model = rotate(model, radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
    model = translate(model, vec3(0.0f, 0.0f, 0.1f));
    shade.setMat4("model", model);
    

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
}


void MouseClick(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
        FetchColour();
    }
}

void FetchColour() {

    unsigned char data[4];
    glReadPixels(SRC_width / 2, SRC_height / 2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // Convert the color back to an integer ID
    int getID =
        data[0] +
        data[1] * 256 +
        data[2] * 256 * 256;
    //cout << pickedID << endl;

    if (getID == 10027059)  //If colour hit
    {
        vec3 newSpawn = vec3(0.0f);

        newSpawn.x = -6 + rand() % (6 - -1 + 1);
        newSpawn.y = -2 + rand() % (6 - -1 + 1);
        newSpawn.z = -14.8f;

        spawnpoint = newSpawn;

        Shader shaders("media/triangles.vert", "media/triangles.frag");
        spawnTarget(shaders, spawnpoint);
        cout << "HIT" << endl;
    }
}

void spawnTarget(Shader& shade, vec3 spawn) {

    

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindVertexArray(0);




    shade.use();

    mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SRC_width / (float)SRC_height, 0.1f, 100.0f);
    mat4 view = camera.GetViewMatrix();
    shade.setMat4("projection", projection);
    shade.setMat4("view", view);
    shade.setVec3("objectColor", vec3(0.2f, 0.0f, 0.6f));
    mat4 model = mat4(1.0);
    
    model = scale(model, vec3(0.5f, 0.5f, 0.5f));
    model = translate(model, spawn);
    shade.setMat4("model", model);


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}




