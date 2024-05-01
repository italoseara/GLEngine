#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <chrono>
#include <cmath>
#include <iostream>
#include <GL/freeglut.h>

using namespace std::chrono;

#define log(...) (printf("[%s:%d] ", __FILE__, __LINE__), printf(__VA_ARGS__), printf("\n"))

/*
 * Some key codes that are not defined in GLUT
 */
#define KEY_ESCAPE 0x001B
#define KEY_SPACE 0x0020
#define KEY_ENTER 0x000D
#define KEY_TAB 0x0009
#define KEY_BACKSPACE 0x0008
#define KEY_DELETE 0x007F

uint64_t getCurrentTimeMillis()
{
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

/*
 * Simple wrapper for GLUT
 */
namespace Engine
{
  /*
   * Variables
   */
  int width, height;
  int fps = 60;

  /*
   * Internal functions
   */
  int frames = 0;
  int currentFPS = 0;
  uint64_t initialTime = 0;
  uint64_t lastTime = 0;

  void (*render)();
  void (*update)(double);

  void _render()
  {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render();
    glutSwapBuffers();
  }

  void _update()
  {
    if (!update)
      return;

    uint64_t currentTime = getCurrentTimeMillis();
    double dt = (currentTime - lastTime) / 1000.0;
    lastTime = currentTime;

    update(dt);
  }

  void _calculateFPS()
  {
    uint64_t currentTime = getCurrentTimeMillis();
    double elapsed = currentTime - Engine::initialTime;
    if (elapsed >= 1000)
    {
      Engine::currentFPS = Engine::frames;
      Engine::frames = 0;
      Engine::initialTime = currentTime;
    }
  }

  void _timer(int value)
  {
    frames++;
    _calculateFPS();

    // I know i could've used glutIdleFunc, but this way i can control the update rate
    _update();
    glutTimerFunc(1000 / fps, _timer, 0);
    glutPostRedisplay();
  }

  /*
   * Initialization functions
   */
  void init(int *argc, char **argv, const char *title = "Engine", int width = 800, int height = 600)
  {
    Engine::width = width;
    Engine::height = height;

    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow(title);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutTimerFunc(1000 / fps, _timer, 0);
  }

  void onInit(void (*init)())
  {
    init();
  }

  void onUpdate(void (*update)(double))
  {
    Engine::update = update;
  }

  void onRender(void (*render)())
  {
    Engine::render = render;
    glutDisplayFunc(_render);
  }

  void onInput(void (*input)(unsigned char key, int x, int y))
  {
    glutKeyboardFunc(input);
  }

  void onShutdown(void (*shutdown)())
  {
    atexit(shutdown);
  }

  void setFPS(int fps)
  {
    Engine::fps = fps;
  }

  void run()
  {
    Engine::initialTime = getCurrentTimeMillis();
    glutMainLoop();
  }

  /*
   * Untility functions
   */
  int getFPS()
  {
    return Engine::currentFPS;
  }

  bool isOnScreen(int x, int y)
  {
    return x >= 0 && x <= width && y >= 0 && y <= height;
  }

  std::pair<float, float> toScreen(int x, int y)
  {
    return std::make_pair((float)x / (float)width - 1.0f, 1.0f - (float)y / (float)height);
  }

  void drawPoint(int x, int y)
  {
    if (!isOnScreen(x, y))
      return;

    std::pair<float, float> p = toScreen(x, y);
    glBegin(GL_POINTS);
    glVertex2f(p.first, p.second);
    glEnd();
  }

  void drawLine(int x1, int y1, int x2, int y2)
  {
    if (!isOnScreen(x1, y1) || !isOnScreen(x2, y2))
      return;

    std::pair<float, float> p1 = toScreen(x1, y1);
    std::pair<float, float> p2 = toScreen(x2, y2);
    glBegin(GL_LINES);
    {
      glVertex2f(p1.first, p1.second);
      glVertex2f(p2.first, p2.second);
    }
    glEnd();
  }

  void drawCircle(int x, int y, int radius, bool fill = false)
  {
    if (!isOnScreen(x, y))
      return;

    std::pair<float, float> p = toScreen(x, y);
    glBegin(fill ? GL_POLYGON : GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
      float angle = i * M_PI / 180.0f;
      glVertex2f(p.first + cos(angle) * radius / width, p.second + sin(angle) * radius / height);
    }
    glEnd();
  }

  void drawRectangle(int x, int y, int width, int height, bool fill = false)
  {
    if (!isOnScreen(x, y) || !isOnScreen(x + width, y + height))
      return;

    std::pair<float, float> p1 = toScreen(x, y);
    std::pair<float, float> p2 = toScreen(x + width, y);
    std::pair<float, float> p3 = toScreen(x + width, y + height);
    std::pair<float, float> p4 = toScreen(x, y + height);
    glBegin(fill ? GL_QUADS : GL_LINE_LOOP);
    {
      glVertex2f(p1.first, p1.second);
      glVertex2f(p2.first, p2.second);
      glVertex2f(p3.first, p3.second);
      glVertex2f(p4.first, p4.second);
    }
    glEnd();
  }

  void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, bool fill = false)
  {
    if (!isOnScreen(x1, y1) || !isOnScreen(x2, y2) || !isOnScreen(x3, y3))
      return;

    std::pair<float, float> p1 = toScreen(x1, y1);
    std::pair<float, float> p2 = toScreen(x2, y2);
    std::pair<float, float> p3 = toScreen(x3, y3);
    glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
    {
      glVertex2f(p1.first, p1.second);
      glVertex2f(p2.first, p2.second);
      glVertex2f(p3.first, p3.second);
    }
    glEnd();
  }

  void drawText(int x, int y, const char *text, void *font = GLUT_BITMAP_HELVETICA_12)
  {
    if (!isOnScreen(x, y))
      return;

    glPushMatrix();

    std::pair<float, float> p = toScreen(x, y + (glutBitmapHeight(font) * 1.5));
    glRasterPos2f(p.first, p.second);
    for (const char *c = text; *c != '\0'; c++)
      glutBitmapCharacter(font, *c);

    glPopMatrix();
  }

  void drawText(int x, int y, std::string text, void *font = GLUT_BITMAP_HELVETICA_12)
  {
    drawText(x, y, text.c_str(), font);
  }
}

#endif // ENGINE_HPP