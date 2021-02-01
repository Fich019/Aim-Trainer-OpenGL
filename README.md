# 2020-COMP3016-Coursework2
This is the repo readme for coursework 2 of COMP3016.
This repo will contain the projects files for my aim trainer designed and built in openGL.


# User Interactions
The user interacts with software by using mouse and keyboard controls.  
  
**Controls:**  
**W, A, S, D** - Move the player around the scene  
**Mouse Look** - Alows the user to look around inside of the scene  
**Left Mouse Button** - Lets the user interact and "shoot" at the targets in the scene  
**Scroll Wheel** - Lets the user change the fov of the camera (zoom in and out) as they see fit.  
 
The program can be opened by running the .exe located in the release folder in the github(as of right now the build doesn't work as intended and doesn't run properly) **OR** by opening the .sln file and running it through visual studio.
  
# Project Layout
  My project is a aim trainer built inside of OPENGL. I started with a camera and player movement script from learnOpenGL and a shader and built up from there. I started by creating walls, a floor and a ceiling to enclose the player in a box. From there I stopped the player leaving said box so they would remain in the playable area. There is a different coloured wall on the back which draws the players eyes to it. This is the main wall where the targets are located. The player can then aim at the targets with the crosshair provided on screen and use left click on their mouse to "shoot" at them and destroy them. The target is then randomly placed somewhere else on the wall. I got the idea from playing first person games myself, I want somewhere to warm up my aim and to practice before playing. Granted this has already been done before many times but I wanted to have a go at as it is something that I am interested in and enjoy. It combines my interests into one. 

# How does it work?
  The code runs through a loop which renders the scene and all of the walls and objects. On top of this, it uses event handlers to check where the players mouse is, what keys they have pressed and for how long. This allows for the scripts to track and update the scene to display what should be displayed to them at that given time. Each of the walls is in its own method and rendered one after the other. This, although not the most efficent allows for me as the developer to track where each element is and if something should go wrong, it is easily identifiable and fixable. When the user interacts with one of the targets, a method is called on the key press for the left mouse button and it will check the colour value of the colour that is currently in the middle of the screen when they click the button. This compares it to a value that I have set to identify the colour of the targets. This allows me to know when the target has been hit and the code can then create another one (move the one they just hit to another random location on the target wall). This goes on indefinitely until the user is warmed up enough, they can then press ESC to close the software.

# Technology Used
  The primary software used is Visual studio and OpenGL. The language C++ was used as this is one of the primary languages used for OpenGL rendering. Inside of OpenGL libraries such as: Glew, Freeglut, Glut, glm and glad were used throughout this project.

# Link to developer walkthough and images
