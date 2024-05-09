#ifndef INTERNAL_HPP
#define INTERNAL_HPP

#include <chrono>

#include "Engine.hpp"

namespace Engine
{
  uint64_t getCurrentTimeMillis()
  {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  }

  namespace Internal
  {
    bool debug = false;

    int fps = 60;
    int width, height;
    std::string title;

    int mouseX, mouseY;
    bool mouseButtons[3];

    bool keys[512];
    int elapsedFrames = 0, currentFPS = 0;
    uint64_t initialTime = 0, lastTime = 0;

    void (*init)();
    void (*update)(double);
    void (*render)();
    void (*keyDown)(int);
    void (*keyUp)(int);
    void (*mouseAction)(int, int, int, int);
    void (*mouseMove)(int, int);

    void drawDebugInfo();

    void renderWrapper()
    {
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      render();
      drawDebugInfo();
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

    void specialKeyDownWrapper(int key, int, int)
    {
      if (keyDown)
        keyDown(key + 256);
      keys[key + 256] = true;
    }

    void specialKeyUpWrapper(int key, int, int)
    {
      if (keyUp)
        keyUp(key + 256);
      keys[key + 256] = false;
    }

    void mouseActionWrapper(int button, int state, int x, int y)
    {
      if (mouseAction)
        mouseAction(button, state, x, y);
      mouseButtons[button] = state == GLUT_DOWN;
    }

    void mouseMoveWrapper(int x, int y)
    {
      if (mouseMove)
        mouseMove(x, y);
      mouseX = x;
      mouseY = y;
    }

    void windowReshape(int w, int h)
    {
      width = w;
      height = h;
      glViewport(0, 0, w, h);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, w, h, 0);
    }
  }
}

#endif // INTERNAL_HPP