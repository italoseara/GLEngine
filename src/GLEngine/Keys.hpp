#ifndef KEYS_HPP
#define KEYS_HPP

// Special keys that are not defined in GLUT
#define KEY_ESCAPE    0x001B
#define KEY_SPACE     0x0020
#define KEY_ENTER     0x000D
#define KEY_TAB       0x0009
#define KEY_BACKSPACE 0x0008
#define KEY_DELETE    0x007F

// Special keys that are defined in GLUT but need to account for the offset
#define KEY_F1        (0x0100 + GLUT_KEY_F1)
#define KEY_F2        (0x0100 + GLUT_KEY_F2)
#define KEY_F3        (0x0100 + GLUT_KEY_F3)
#define KEY_F4        (0x0100 + GLUT_KEY_F4)
#define KEY_F5        (0x0100 + GLUT_KEY_F5)
#define KEY_F6        (0x0100 + GLUT_KEY_F6)
#define KEY_F7        (0x0100 + GLUT_KEY_F7)
#define KEY_F8        (0x0100 + GLUT_KEY_F8)
#define KEY_F9        (0x0100 + GLUT_KEY_F9)
#define KEY_F10       (0x0100 + GLUT_KEY_F10)
#define KEY_F11       (0x0100 + GLUT_KEY_F11)
#define KEY_F12       (0x0100 + GLUT_KEY_F12)
#define KEY_LEFT      (0x0100 + GLUT_KEY_LEFT)
#define KEY_UP        (0x0100 + GLUT_KEY_UP)
#define KEY_RIGHT     (0x0100 + GLUT_KEY_RIGHT)
#define KEY_DOWN      (0x0100 + GLUT_KEY_DOWN)
#define KEY_PAGE_UP   (0x0100 + GLUT_KEY_PAGE_UP)
#define KEY_PAGE_DOWN (0x0100 + GLUT_KEY_PAGE_DOWN)
#define KEY_HOME      (0x0100 + GLUT_KEY_HOME)
#define KEY_END       (0x0100 + GLUT_KEY_END)
#define KEY_INSERT    (0x0100 + GLUT_KEY_INSERT)

#endif // KEYS_HPP