/*
 * engine.h
 * Created on: Mar 26, 2024
 * Author: Italo Santana Seara
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <chrono>
#include <string>
#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

/**
 * @class Engine
 * @brief The Engine class represents the main engine for the application.
 *
 * The Engine class is responsible for initializing the GLFW library, creating and managing the window,
 * handling the main loop, and providing utility functions for measuring frames per second (FPS) and delta time.
 */
class Engine
{
private:
  GLFWwindow *window;

  bool debug = false;

  string title;
  int width, height;

  int fps = 0;
  int frames = 0;
  int64_t lastSecond = 0;
  int64_t lastFrame = 0;

  /**
   * Logs the given message.
   *
   * @param message The message to be logged.
   */
  void log(string message)
  {
    if (debug)
    {
      cout << "[ENGINE] " << message << "\n";
    }
  }

public:
  /**
   * @brief Constructs an Engine object with the specified title, width, and height.
   *
   * @param title The title of the engine window.
   * @param width The width of the engine window.
   * @param height The height of the engine window.
   */
  Engine(string title, int width, int height) : title(title), width(width), height(height)
  {
    if (!glfwInit())
    {
      cerr << "Failed to initialize GLFW\n";
      exit(EXIT_FAILURE);
    }
  }

  /**
   * @brief Destructor for the Engine class.
   */
  ~Engine()
  {
    glfwTerminate();
  }

  /**
   * Sets the debug mode.
   *
   * @param debug The debug mode.
   */
  void setDebug(bool debug)
  {
    this->debug = debug;
  }

  /**
   * Gets the debug mode.
   *
   * @return The debug mode.
   */
  bool getDebug()
  {
    return debug;
  }

  /**
   * Gets the frames per second (FPS).
   *
   * @return The frames per second (FPS).
   */
  int getFps()
  {
    return fps;
  }

  /**
   * Calculates the time elapsed since the last frame in seconds.
   *
   * @return The time elapsed since the last frame in seconds.
   */
  double getDeltaTime()
  {
    return (getTimestamp() - lastFrame) / 1000.0;
  }

  /**
   * Returns the current timestamp in milliseconds.
   *
   * @return The current timestamp in milliseconds.
   */
  int64_t getTimestamp()
  {
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
  }

  /**
   * @brief Initializes the engine.
   *
   * This function is called to initialize the engine before it starts running.
   * It can be overridden by derived classes to perform any necessary initialization tasks.
   */
  virtual void init() {}

  /**
   * @brief Updates the engine.
   *
   * This function is called to update the engine's state.
   * It should be overridden by derived classes to implement
   * the specific update logic.
   */
  virtual void update() {}

  /**
   * @brief This function is responsible for rendering the objects on the screen.
   *
   * This function should be overridden by derived classes to implement the rendering logic.
   */
  virtual void render() {}

  /**
   * @brief This function is called after the engine has finished running.
   *
   * This function is called to destroy the engine after it has finished running.
   * It can be overridden by derived classes to perform any necessary cleanup tasks.
   */
  virtual void destroy() {}

  /**
   * Runs the engine.
   */
  void run()
  {
    log("Creating window...");
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window)
    {
      cerr << "Failed to create window\n";
      glfwTerminate();
      exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    log("Running...");

    init();
    while (!glfwWindowShouldClose(window))
    {
      glfwSwapBuffers(window);
      glfwPollEvents();

      update();
      render();

      // FPS Counter
      frames++;
      if (getTimestamp() - lastSecond >= 1000)
      {
        fps = frames;
        frames = 0;
        lastSecond = getTimestamp();
      }

      // DeltaTime
      lastFrame = getTimestamp();
    }

    log("Destroying window...");
    glfwDestroyWindow(window);
  }
};

#endif // ENGINE_H