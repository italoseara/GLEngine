#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <GL/freeglut.h>

#include "Keys.hpp"
#include "Internal.hpp"
#include "Util.hpp"
#include "Drawable.hpp"
#include "Log.hpp"

namespace Engine
{
  void Init(std::string title, int width, int height)
  {
    Internal::title = title;
    Internal::width = width;
    Internal::height = height;
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
    glutReshapeFunc(Internal::windowReshape);

    Internal::init();
    glutMainLoop();
  }

  int Width()
  {
    return Internal::width;
  }

  int Height()
  {
    return Internal::height;
  }

  bool isKeyPressed(int key)
  {
    return Internal::keys[toupper(key)];
  }
}

#endif // ENGINE_HPP