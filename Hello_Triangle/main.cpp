/* Be sure to include GLAD before GLFW. */

// clang-format off
#include <glad/glad.h>
// clang-format on
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Vertex shader.
const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// Fragment shader.
const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

/* Create the main function where we will instantiate the GLFW window. */
int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* create a window object. This window object holds all the windowing data. */
  /* The arguments: width, height, name of the window. Ignore the last 2. */
  GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  /* Makes the window created above, the main one. */
  glfwMakeContextCurrent(window);

  // Tell GLFW we want to call this function on every window resize
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers.
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // build and compile our shader program
  // ------------------------------------
  // Create a Vertex shader object.
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  /* Attach the shader source code to the shader object abd compile the shader*/
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  /* integer to indicate success and a storage
  container for the error messages(if any).*/
  int success_vertex;
  char infoLog_vertex[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success_vertex);

  // Check if compilation was sucessful.
  if (!success_vertex) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog_vertex);
    std::cout << "SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog_vertex << std::endl;
  }

  // Create a Fragment shader object.
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  /* Attach the shader source code to the shader object abd compile the shader*/
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  /* integer to indicate success and a storage
container for the error messages(if any).*/
  int success_fragment;
  char infoLog_fragment[512];
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success_fragment);

  // Check if compilation was sucessful.
  if (!success_fragment) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog_fragment);
    std::cout << "SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog_fragment << std::endl;
  }

  // A shader program object to combine multiple shaders (vertex + fragment).
  unsigned int shaderProgram = glCreateProgram();

  /* Attach the previously compiled shaders to the program object. */
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram); // Then we link them.

  /* integer to indicate success and a storage
   container for the error messages(if any).*/
  int success_program;
  char infoLog_program[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success_program);

  // Check if linking was sucessful.
  if (!success_program) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog_program);
    std::cout << "SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog_program << std::endl;
  }

  // Delete the shader objects after linking them into one program.
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  // Triangle vertices. (x, y, z)
  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

  // A VAO to make switching easier.
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);

  // A VBO to store vertices on the GPU's memory.
  unsigned int VBO;
  glGenBuffers(1, &VBO);

  // 1. bind Vertex Array Object
  glBindVertexArray(VAO);

  // 2. copy our vertices array in a buffer for OpenGL to use
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // 3.(set the vertex attributes pointers)
  // Interpret the vertex data before rendering
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  /* note that this is allowed, the call to glVertexAttribPointer registered VBO
  as the vertex attribute's bound vertex buffer object so afterwards we can
  safely unbind */
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  /* You can unbind the VAO afterwards so other VAO calls won't accidentally
  modify this VAO, but this rarely happens. Modifying other VAOs requires a
  call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
  VBOs) when it's not directly necessary. */
  glBindVertexArray(0);

  // Loop to keep the window running.
  while (!glfwWindowShouldClose(window)) {
    // Check for specific key presses and react accordingly every frame.
    processInput(window); // An iteration of the render loop is called a frame.

    // We specify the color that we want.
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    /* The entire buffer will have the color that we choosed above. */
    glClear(GL_COLOR_BUFFER_BIT);

    // 4. draw the object
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Swap the back buffer to the front buffer so the image can be displayed.
    glfwSwapBuffers(window);
    // Checks if any events are triggered: keyboard or mouse input.
    glfwPollEvents();
  }

  // De-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate(); // Clean up all the resources and exit the application.
  return 0;
}

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
