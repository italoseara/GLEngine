#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <GL/freeglut.h>

#include "Keys.hpp"
#include "Internal.hpp"
#include "Util.hpp"
#include "Drawable.hpp"

#define log(...) printf("[%s:%d] ", __FILE__, __LINE__), printf(__VA_ARGS__), printf("\n")

void Engine::Internal::drawDebugInfo()
{
  if (Internal::debug)
  {
    glColor3ub(0, 255, 0);
    Text({0, 0}, "FPS: " + std::to_string(Internal::currentFPS)).draw();
    Text({(float)mouseX, (float)mouseY + 10}, Vector2(mouseX, mouseY).toString()).draw();
  }
}

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

  void InputCallbacks(void (*keyDown)(int), void (*keyUp)(int) = nullptr)
  {
    Internal::keyDown = keyDown;
    Internal::keyUp = keyUp;
  }

  void MouseCallbacks(void (*mouseAction)(int, int, int, int), void (*mouseMove)(int, int))
  {
    Internal::mouseAction = mouseAction;
    Internal::mouseMove = mouseMove;
  }

  void MouseCallbacks(void (*mouseAction)(int, int, int, int))
  {
    MouseCallbacks(mouseAction, nullptr);
  }

  void MouseCallbacks(void (*mouseMove)(int, int))
  {
    MouseCallbacks(nullptr, mouseMove);
  }

  void Run(int *argc, char **argv)
  {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(Internal::width, Internal::height);
    glutCreateWindow(Internal::title.c_str());

    glutTimerFunc(1000 / Internal::fps, Internal::timer, 0);
    glutDisplayFunc(Internal::renderWrapper);
    glutKeyboardFunc(Internal::keyDownWrapper);
    glutKeyboardUpFunc(Internal::keyUpWrapper);
    glutMouseFunc(Internal::mouseActionWrapper);
    glutPassiveMotionFunc(Internal::mouseMoveWrapper);
    glutMotionFunc(Internal::mouseMoveWrapper);
    glutReshapeFunc(Internal::windowReshape);

    Internal::init();
    glutMainLoop();
  }

  void Debug(bool debug = true)
  {
    Internal::debug = debug;
  }

  void Clear(Color color = {0, 0, 0})
  {
    glClearColor(color.r / 255.0, color.g / 255.0, color.b / 255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void Draw(Drawable &drawable, Color color = {255, 255, 255}, int lineWidth = 1)
  {
    glLineWidth(lineWidth);
    glColor4ub(color.r, color.g, color.b, color.a);
    drawable.draw(Internal::debug);
    glColor4ub(255, 255, 255, 255);
    glLineWidth(1);
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