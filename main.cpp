#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "math/maths_funcs.h"
#include "math/maths_funcs.c"
#include "console.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "model.hpp"

int main () {
    
  initConsole();
  
  Model model = Model("ostrich.obj");
  //Model model2 = Model("tree.obj");
  
  // start GL context and O/S window using the GLFW helper library
  if (!glfwInit ()) {
    fprintf (stderr, "ERROR: could not start GLFW3\n");
    getch();
    return 1;
  } 

  int width = 640, height = 480;
  GLFWwindow* window = glfwCreateWindow (width, height, "Engine", NULL, NULL);
  if (!window) {
    fprintf (stderr, "ERROR: could not open window with GLFW3\n");
    getch();
    
    glfwTerminate();
    return 1;
  }
  
  glfwMakeContextCurrent (window);
                                  
  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  glewInit ();

  // get version info
  const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString (GL_VERSION); // version as a string
  printf ("Renderer: %s\n", renderer);
  printf ("OpenGL version supported %s\n", version);

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable (GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

  float cam_pos[] = {0.0f, 0.0f, 2.0f};
  Camera camera = Camera(1.0f, 10.0f, cam_pos, 0.0f);
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  
  Scene scene = Scene();
  scene.add(model);
  //scene.add(model2);
  scene.prepare();
  camera.roll(width, height);  
  
  float speed = 3.0f; // move at 1 unit per second
  float last_position = 0.0f;
  while (!glfwWindowShouldClose (window)) {
    // add a timer for doing animation
    static double previous_seconds = glfwGetTime ();
    double current_seconds = glfwGetTime ();
    double elapsed_seconds = current_seconds - previous_seconds;
    previous_seconds = current_seconds;
  
    // reverse direction when going to far left or right
    if (fabs(last_position) > 1.0f) {
      speed = -speed;
    }

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
    camera.action(scene);
    
    glfwPollEvents ();
    glfwSwapBuffers (window);
  
    if (glfwGetKey (window, GLFW_KEY_A)) {
      camera.moveLeft(elapsed_seconds);
    }
  
    if (glfwGetKey (window, GLFW_KEY_D)) {
      camera.moveRight(elapsed_seconds);
    }
  
    if (glfwGetKey (window, GLFW_KEY_PAGE_UP)) {
      camera.moveUp(elapsed_seconds);
    }

    if (glfwGetKey (window, GLFW_KEY_PAGE_DOWN)) {
      camera.moveDown(elapsed_seconds);
    }

    if (glfwGetKey (window, GLFW_KEY_W)) {
      camera.moveForward(elapsed_seconds);
    }

    if (glfwGetKey (window, GLFW_KEY_S)) {
      camera.moveBack(elapsed_seconds);
    }

    if (glfwGetKey (window, GLFW_KEY_Q)) {
      camera.lookLeft(elapsed_seconds);
    }
  
    if (glfwGetKey (window, GLFW_KEY_E)) {
      camera.lookRight(elapsed_seconds);
    }

    camera.nextFrame();

  }
  
  // close GL context and any other GLFW resources
  glfwTerminate();
  
  return 0;
}
