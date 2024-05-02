#ifndef INTERNAL_HPP
#define INTERNAL_HPP

#include <chrono>

#include "Engine.hpp"

namespace Engine
{
  namespace Internal
  {
    int fps = 60;
    int width, height;
    std::string title;

    bool keys[256];
    int elapsedFrames = 0, currentFPS = 0;
    uint64_t initialTime = 0, lastTime = 0;

    void (*init)();
    void (*update)(double);
    void (*render)();
    void (*keyDown)(int);
    void (*keyUp)(int);

    uint64_t getCurrentTimeMillis()
    {
      using namespace std::chrono;
      return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }

    void renderWrapper()
    {
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      render();
      glutSwapBuffers();
    }

    void calculateFPS()
    {
      uint64_t currentTime = getCurrentTimeMillis();
      double elapsed = currentTime - initialTime;
      if (elapsed >= 1000)
      {
        currentFPS = elapsedFrames;
        elapsedFrames = 0;
        initialTime = currentTime;
      }
    }

    void updateWrapper()
    {
      if (!update)
        return;

      uint64_t currentTime = getCurrentTimeMillis();
      double dt = (currentTime - lastTime) / 1000.0;
      lastTime = currentTime;

      update(dt);
    }

    void timer(int)
    {
      elapsedFrames++;
      calculateFPS();

      // I know i could've used glutIdleFunc, but this way i can control the update rate
      glutTimerFunc(1000 / fps, timer, 0);
      updateWrapper();
      glutPostRedisplay();
    }

    void keyDownWrapper(unsigned char key, int, int)
    {
      if (keyDown)
        keyDown(key);
      keys[toupper(key)] = true;
    }

    void keyUpWrapper(unsigned char key, int, int)
    {
      if (keyUp)
        keyUp(key);
      keys[toupper(key)] = false;
    }
  }
}

#endif // INTERNAL_HPP