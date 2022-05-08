/* Be sure to include GLAD before GLFW. */

// clang-format off
#include <glad/glad.h>
// clang-format on
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

/* callback function window that gets called each time the window is resized. */
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  /*  We have to tell OpenGL the size of the rendering window so OpenGL knows
  how we want to display the data and coordinates with respect to the window.
  The first two parameters of glViewport set the location of the lower left
  corner of the window. The third and fourth parameter set th width and height
  */
  glViewport(0, 0, width, height);
}

/* Function that takes the window as input together with a key. The function
returns whether this key is currently being pressed. */
void processInput(GLFWwindow *window) {
  /* Here we check whether the user has pressed the escape key. If the user did
press the escape key, we close the window.*/
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  // (if it’s not pressed, glfwGetKey returns GLFW_RELEASE).
}

/* Create the main function where we will instantiate the GLFW window. */
int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* create a window object. This window object holds all the windowing data. */
  /* The arguments: width, height, name of the window. Ignore the last 2. */
  GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  /* Makes the window created above, the main one. */
  glfwMakeContextCurrent(window);

  /* GLAD manages function pointers for OpenGL so it must be called before we
   * call any OpenGL function. */
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  /*  Tell GLFW we want to call this function on every window resize by
   * registering it. */
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Loop to keep the window running.
  while (!glfwWindowShouldClose(window)) {
    // Check for specific key presses and react accordingly every frame.
    processInput(window); // An iteration of the render loop is called a frame.

    // We specify the color that we want.
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    /* The entire buffer will have the color that we choosed above. */
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap the back buffer to the front buffer so the image can be displayed.
    glfwSwapBuffers(window);
    // Checks if any events are triggered: keyboard or mouse input.
    glfwPollEvents();
  }

  glfwTerminate(); // Clean up all the resources and exit the application.
  return 0;
}
