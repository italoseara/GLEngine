#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <GL/freeglut.h>

#include "Keys.hpp"
#include "Internal.hpp"
#include "Util.hpp"
#include "Drawable.hpp"

#define log(...) printf("[%s:%d] ", __FILE__, __LINE__), printf(__VA_ARGS__), printf("\n")

namespace Engine
{
  void Init(std::string title, int width, int height, int fps = 60)
  {
    Internal::title = title;
    Internal::width = width;
    Internal::height = height;
    Internal::fps = fps;
  }

  void Callbacks(void (*init)(), void (*update)(double), void (*render)())
  {
    Internal::init = init;
    Internal::update = update;
    Internal::render = render;
  }

  void InputCallbacks(void (*keyDown)(int), void (*keyUp)(int))
  {
    Internal::keyDown = keyDown;
    Internal::keyUp = keyUp;
  }

  void MouseCallbacks(void (*mouseDown)(int, int, int, int), void (*mouseMove)(int, int))
  {
    Internal::mouseDown = mouseDown;
    Internal::mouseMove = mouseMove;
  }

  void Run(int *argc, char **argv)
  {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(Internal::width, Internal::height);
    glutCreateWindow(Internal::title.c_str());

    glutDisplayFunc(Internal::renderWrapper);
    glutTimerFunc(1000 / Internal::fps, Internal::timer, 0);
    glutKeyboardFunc(Internal::keyDownWrapper);
    glutKeyboardUpFunc(Internal::keyUpWrapper);
    glutMouseFunc(Internal::mouseDownWrapper);
    glutPassiveMotionFunc(Internal::mouseMoveWrapper);
    glutMotionFunc(Internal::mouseMoveWrapper);
    glutReshapeFunc(Internal::windowReshape);

    Internal::init();
    glutMainLoop();
  }

  void Draw(Drawable &drawable, Color color = {255, 255, 255}, int lineWidth = 1)
  {
    glColor3ub(color.r, color.g, color.b);
    glLineWidth(lineWidth);
    drawable.draw();
    glLineWidth(1);
    glColor3ub(255, 255, 255);
  }

  void Draw(std::vector<Drawable> &drawables, Color color = {255, 255, 255}, int lineWidth = 1)
  {
    for (Drawable &drawable : drawables)
      Draw(drawable, color, lineWidth);
  }

  bool isKeyPressed(int key)
  {
    return Internal::keys[toupper(key)];
  }

  bool isMousePressed(int button)
  {
    return Internal::mouseButtons[button];
  }

  Vector2 getMousePos()
  {
    return {(float)Internal::mouseX, (float)Internal::mouseY};
  }

  int getMouseX()
  {
    return Internal::mouseX;
  }

  int getMouseY()
  {
    return Internal::mouseY;
  }

  int getWidth()
  {
    return Internal::width;
  }

  int getHeight()
  {
    return Internal::height;
  }

  int getFPS()
  {
    return Internal::currentFPS;
  }

  void setTitle(std::string title)
  {
    Internal::title = title;
    glutSetWindowTitle(title.c_str());
  }
}

#endif // ENGINE_HPP