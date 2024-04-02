#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

/**
 * @brief The Engine class represents the core engine of the application.
 *
 * This class is responsible for managing the main loop and handling the initialization
 * and shutdown of the application.
 */
class Engine
{
private:
  GLFWwindow *window;
  bool debug;

  void log(string message)
  {
    if (debug)
    {
      cout << "[ENGINE] " << message << endl;
    }
  }

public:
  /**
   * @brief Construct a new Engine object
   *
   * @param title The title of the window
   * @param width The width of the window
   * @param height The height of the window
   */
  Engine(string title, int width, int height, bool debug = false);

  /**
   * @brief Destroy the Engine object
   */
  ~Engine();

  /**
   * @brief Run the main loop of the application
   */
  void run();

  /**
   * @brief Initialization function called once before the main loop
   */
  virtual void init() {};

  /**
   * @brief Update the engine every frame of the main loop
   */
  virtual void update() {};

  /**
   * @brief Render the engine every frame of the main loop
   */
  virtual void render() {};

  /**
   * @brief Shutdown the engine when the main loop is finished
   */
  virtual void shutdown() {};
};

#endif // ENGINE_H