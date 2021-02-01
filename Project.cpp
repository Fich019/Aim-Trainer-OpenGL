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


//Width and height of the window ( Aspect ratio 16:9 )
const int SRC_width = 16 * 50;
const int SRC_height = 9 * 50;

//Camera variables
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SRC_width / 2.0f;
float lastY = SRC_height / 2.0f;
bool firstMouse = true;

//Pre-declared spawn point for the target.
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





//  Main loop for the program, calls all of the required methods and the ones 
//that are required to be inside of a while loop are
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
        

        //Spawns all of the walls into the scene
        spawnWallBack(shaders);
        spawnWallFront(shaders);
        spawnWallLeft(shaders);
        spawnWallRight(shaders);
        spawnFloor(shaders);
        spawnCeiling(shaders);

        //Spawns the starting crosshair
        spawnTarget(shaders, spawnpoint);

        //Creates the crosshair
        crosshair1(hud);
        crosshair2(hud);
        crosshair3(hud);
        crosshair4(hud);

       
        
        //gets the current matrix view for the camera
        glm::mat4 view = camera.GetViewMatrix();
        shaders.setMat4("view", view);





        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    
}

//  These series of methods are used to create the crosshair that the player 
//can use inside the scene. Each of the methods creates and draws one section
//of the crosshair. All of them combined are needed to complete the crosshair.
//In order to render it as a hud rather than a 3D object, different shaders are
//used that are specifically for hud elements that are currently used and that 
//can be added at a later date.
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


//  These next 4 methods are related to the camera movement and player movement that 
//I outsourced. Due to this I have a vague understanding of how they work. Scroll
//callback is for the zoom function that is bound to the scroll wheel, it is an event
//handler. Frame buffer size makes sure that the viewport matches the diamensions of
//the window. Process input is where all of the inputs are collected and fed back to
//the camera.h class. It checks to see if W,A,S,D or ESC have been pressed and acts
//accordingly. W,A,S,D pass through to the camera class and ESC closes the window.
//  Mouse_callback tracks the current where abouts of the player's mouse in the window
//and sends the data back to the camera class, once there it updates the scene to match
//the new view that they should be seeing.
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


//  These 6 methods are used to create and render each of the walls for the scene. This is
//done by using a shader to apply a colour to the vertices and in turn indices that are
//created by each of these methods. The data for each is then collected and stored in 
//buffers. Once the data has been stored, it then can be accessed for use in the mat4.
//This is a much easier way to rotate, change the colour of and translate the object
//once it has been created. This is also required to render the object in a 3D space.
//  Once the model ahs been assigned, the rotation, scale and translation of the model
//can be edited. Once this final changes have been made, the vertex array can be 
//bound and the object drawn in the scene.
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

    //Binds the Vertex Array Object first, it then binds and sets vertex buffers. 
    //Finally, the vertex attributes are then configured.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Position attributes
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


//This is a event handler to check if the mouse has been clicked (specifically the
//left mouse button). If the button has been pressed and is pressed down, the 
//method "FetchColour" is called.
void MouseClick(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
        FetchColour();
    }
}

//  This method is used to calculate the colour of the pixel that is currently
//located in the middle of the window. This is done by halving the width and
//height of the window by 2. The function read pixels is then called to 
//calculate the colour that is currently being selected in the middle of 
//window. Once the colour has been read, it then gets converted back into
//and integer which gets used as an ID for the code to read. If the ID read
//by the function matches that of the colour that I have specified as the 
//colour of the target, it then follows through with the next section of code.
//  This creates a new vector 3 for a spawnpoint of a target. Using the rand
//function it gets new values for the x and y of the vector 3 within certain
//bounds. Once it has these, along with a preset value for z (we never want
//the z value to change) it sets this new vector 3 as the global vector 3 that
//the spawnTarget method uses. It them calls the spawnTarget method to 
//create/move the current target to its new, pseudo-randomly decided position.
void FetchColour() {

    unsigned char data[4];
    glReadPixels(SRC_width / 2, SRC_height / 2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // Convert the color back to an integer ID
    int getID =
        data[0] +
        data[1] * 256 +
        data[2] * 256 * 256;

    if (getID == 10027059)  //If colour hit
    {
        vec3 newSpawn = vec3(0.0f);

        newSpawn.x = -6 + rand() % (6 - -1 + 1);
        newSpawn.y = -2 + rand() % (6 - -1 + 1);
        newSpawn.z = -14.8f;

        spawnpoint = newSpawn;

        Shader shaders("media/triangles.vert", "media/triangles.frag");
        spawnTarget(shaders, spawnpoint);
    }
}

//  This last method is used to create the targets that the player can "shoot" at.
//This is done by using the same method as creating the walls before. We are
//setting scale to 0.5 to make it more target like rather than a wall. The colour
//for the target also has to be different than any other colour used in the scene
//as not to confused the method that gets and checks the colour against the 
//centre of the window. The major difference with this method is that the vector 3
//is declared at the top of the program. This is so that we can change it in our
//FetchColour method without causing any issues with it spawning.
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




