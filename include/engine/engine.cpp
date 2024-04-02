#include "engine.h"

Engine::Engine(string title, int width, int height, bool debug) : debug(debug)
{
  // Initialize GLFW
  log("Initializing GLFW");

  if (!glfwInit())
  {
    cerr << "Failed to initialize GLFW" << endl;
    exit(EXIT_FAILURE);
  }

  // Set the OpenGL version to 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a windowed mode window and its OpenGL context
  log("Creating window");

  window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (!window)
  {
    cerr << "Failed to create window" << endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // Load OpenGL functions using glad
  log("Loading OpenGL functions");

  if (!gladLoadGL())
  {
    cerr << "Failed to initialize OpenGL context" << endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Set the viewport size
  glViewport(0, 0, width, height);
}

Engine::~Engine()
{
  // Terminate GLFW
  log("Terminating GLFW");
  glfwTerminate();
}

void Engine::run()
{
  log("Running main loop");

  // Initialization function
  init();

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window))
  {
    // Updating and rendering the window
    update();
    render();

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }
}
