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

#include "glad/glad.h"
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
   * @brief Called once before the engine starts running.
   *
   * This function is called to initialize the engine before it starts running.
   * Can be called again to reset the state of the engine.
   * It can be overridden by derived classes to perform any necessary initialization tasks.
   */
  virtual void init() {}

  /**
   * @brief Called every frame to update the engine's state.
   *
   * This function is called to update the engine's state.
   * It should be overridden by derived classes to implement
   * the specific update logic.
   */
  virtual void update() {}

  /**
   * @brief Called every frame to render the engine's state.
   *
   * This function should be overridden by derived classes to implement the rendering logic.
   */
  virtual void render() {}

  /**
   * @brief Called once after the engine has finished running.
   *
   * This function is called to cleanup the engine after it has finished running.
   * It can be overridden by derived classes to perform any necessary cleanup tasks.
   */
  virtual void cleanup() {}

  /**
   * Runs the engine.
   */
  void run()
  {
    // Log the OpenGL version
    log("OpenGL Version: " + string((char *)glfwGetVersionString()));

    // Create window and thows an error if it fails
    log("Creating window...");
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window)
    {
      cerr << "Failed to create window\n";
      glfwTerminate();
      exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, width, height);

    // Starts the running loop
    log("Running...");

    init();
    while (!glfwWindowShouldClose(window))
    {
      // Update and Render the scene
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

      // Handle events and swap buffers
      glfwSwapBuffers(window);
      glfwPollEvents();
    }

    // After the program is closed
    log("Destroying window...");

    cleanup();
    glfwDestroyWindow(window);
  }
};

#endif // ENGINE_H