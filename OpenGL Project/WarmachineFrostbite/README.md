This is a basic game using openGL.
This game was implemented to show some basic functions of opengl such as Cameras, Ilumination, 
Texture and others.

In order to run this, first check all libraries and the main.c file in order to add right 
paths to the images. The functions are called loadTexture or carregaTextura.

To compile this in a OS X terminal use gcc -o name main.c -framework OpenGL -framework GLUT
You can always search for other ways to compile it at other platforms.

Below are the instructions translated to english:

Objective : Capture the small prisoners

Controls: M - Changes Camera
Control Camera (Behind character) - W,A,S,D to control the war machine
Upper Camera (Upper) - W,A,S,D to move the map

Developer Functions: 
X,Y,Z - rotate the camera
R - Reset the camera rotations
I - Turns light when on Upper Camera
B - Teleports close to the enemy
O - Teleports Back to origin

0 - Use Warmachine - KIWI
1 - Use Warmachine - BLD
