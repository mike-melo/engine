#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "math/maths_funcs.h"
#include "math/maths_funcs.c"

int main () {
  // start GL context and O/S window using the GLFW helper library
  if (!glfwInit ()) {
    fprintf (stderr, "ERROR: could not start GLFW3\n");
    getch();
    return 1;
  } 

	// uncomment these lines if on Apple OS X
  /*glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

  int width = 640, height = 480;
  GLFWwindow* window = glfwCreateWindow (width, height, "Hello Triangle", NULL, NULL);
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

  float points[] = {
   0.0f,  0.5f,  0.0f,
   0.5f, -0.5f,  0.0f,
  -0.5f, -0.5f,  0.0f
  };
  
  unsigned int vbo = 0;
  glGenBuffers (1, &vbo);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glBufferData (GL_ARRAY_BUFFER, 9 * sizeof (float), points, GL_STATIC_DRAW);
  
  unsigned int vao = 0;
  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);
  glEnableVertexAttribArray (0);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  const char* vertex_shader =
  "#version 400\n"
  "in vec3 vp;"
  "uniform mat4 view, proj;"
  "void main () {"
  "  gl_Position = proj * view * vec4 (vp, 1.0);"
  "}";

  const char* fragment_shader =
  "#version 400\n"
  "out vec4 frag_colour;"
  "void main () {"
  "  frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
  "}";
  
  unsigned int vs = glCreateShader (GL_VERTEX_SHADER);
  glShaderSource (vs, 1, &vertex_shader, NULL);
  glCompileShader (vs);
  unsigned int fs = glCreateShader (GL_FRAGMENT_SHADER);
  glShaderSource (fs, 1, &fragment_shader, NULL);
  glCompileShader (fs);

  unsigned int shader_programme = glCreateProgram ();
  glAttachShader (shader_programme, fs);
  glAttachShader (shader_programme, vs);
  glLinkProgram (shader_programme);
  
  float cam_speed = 1.0f; // 1 unit per second
  float cam_yaw_speed = 10.0f; // 10 degrees per second
  float cam_pos[] = {0.0f, 0.0f, 2.0f}; // don't start at zero, or we will be too close
  float cam_yaw = 0.0f; // y-rotation in degrees
  
  mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2]));
  mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw);
  mat4 view_mat = R * T;
  
  #define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444
  // input variables
  float near = 0.1f; // clipping plane
  float far = 100.0f; // clipping plane
  float fov = 67.0f * ONE_DEG_IN_RAD; // convert 67 degrees to radians
  float aspect = (float)width / (float)height; // aspect ratio
  // matrix components
  float range = tan (fov * 0.5f) * near;
  float Sx = (2.0f * near) / (range * aspect + range * aspect);
  float Sy = near / range;
  float Sz = -(far + near) / (far - near);
  float Pz = -(2.0f * far * near) / (far - near);  
  
  float proj_mat[] = {
  Sx, 0.0f, 0.0f, 0.0f,
  0.0f, Sy, 0.0f, 0.0f,
  0.0f, 0.0f, Sz, -1.0f,
  0.0f, 0.0f, Pz, 0.0f
  };
  
  int view_mat_location = glGetUniformLocation (shader_programme, "view");
  glUseProgram (shader_programme);
  glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
  int proj_mat_location = glGetUniformLocation (shader_programme, "proj");
  glUseProgram (shader_programme);
  glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, proj_mat);
  
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
  glUseProgram (shader_programme);
  glBindVertexArray (vao);
  glDrawArrays (GL_TRIANGLES, 0, 3);
  glfwPollEvents ();
  glfwSwapBuffers (window);
  // control keys
bool cam_moved = false;
if (glfwGetKey (window, GLFW_KEY_A)) {
  cam_pos[0] -= cam_speed * elapsed_seconds;
  cam_moved = true;
}
if (glfwGetKey (window, GLFW_KEY_D)) {
  cam_pos[0] += cam_speed * elapsed_seconds;
  cam_moved = true;
}
if (glfwGetKey (window, GLFW_KEY_PAGE_UP)) {
  cam_pos[1] += cam_speed * elapsed_seconds;
  cam_moved = true;
}
if (glfwGetKey (window, GLFW_KEY_PAGE_DOWN)) {
  cam_pos[1] -= cam_speed * elapsed_seconds;
  cam_moved = true;
}
if (glfwGetKey (window, GLFW_KEY_W)) {
  cam_pos[2] -= cam_speed * elapsed_seconds;
  cam_moved = true;
}
if (glfwGetKey (window, GLFW_KEY_S)) {
  cam_pos[2] += cam_speed * elapsed_seconds;
  cam_moved = true;
}
if (glfwGetKey (window, GLFW_KEY_LEFT)) {
  cam_yaw += cam_yaw_speed * elapsed_seconds;
  cam_moved = true;
}
if (glfwGetKey (window, GLFW_KEY_RIGHT)) {
  cam_yaw -= cam_yaw_speed * elapsed_seconds;
  cam_moved = true;
}
// update view matrix
if (cam_moved) {
  mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2])); // cam translation
  mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw); // 
  mat4 view_mat = R * T;
  glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
}
}
  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}
