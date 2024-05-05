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
#define OFFSET        0x0100
#define KEY_F1        (OFFSET + GLUT_KEY_F1)
#define KEY_F2        (OFFSET + GLUT_KEY_F2)
#define KEY_F3        (OFFSET + GLUT_KEY_F3)
#define KEY_F4        (OFFSET + GLUT_KEY_F4)
#define KEY_F5        (OFFSET + GLUT_KEY_F5)
#define KEY_F6        (OFFSET + GLUT_KEY_F6)
#define KEY_F7        (OFFSET + GLUT_KEY_F7)
#define KEY_F8        (OFFSET + GLUT_KEY_F8)
#define KEY_F9        (OFFSET + GLUT_KEY_F9)
#define KEY_F10       (OFFSET + GLUT_KEY_F10)
#define KEY_F11       (OFFSET + GLUT_KEY_F11)
#define KEY_F12       (OFFSET + GLUT_KEY_F12)
#define KEY_LEFT      (OFFSET + GLUT_KEY_LEFT)
#define KEY_UP        (OFFSET + GLUT_KEY_UP)
#define KEY_RIGHT     (OFFSET + GLUT_KEY_RIGHT)
#define KEY_DOWN      (OFFSET + GLUT_KEY_DOWN)
#define KEY_PAGE_UP   (OFFSET + GLUT_KEY_PAGE_UP)
#define KEY_PAGE_DOWN (OFFSET + GLUT_KEY_PAGE_DOWN)
#define KEY_HOME      (OFFSET + GLUT_KEY_HOME)
#define KEY_END       (OFFSET + GLUT_KEY_END)
#define KEY_INSERT    (OFFSET + GLUT_KEY_INSERT)
#define KEY_SHIFT_L   (OFFSET + GLUT_KEY_SHIFT_L)
#define KEY_SHIFT_R   (OFFSET + GLUT_KEY_SHIFT_R)
#define KEY_CTRL_L    (OFFSET + GLUT_KEY_CTRL_L)
#define KEY_CTRL_R    (OFFSET + GLUT_KEY_CTRL_R)
#define KEY_ALT_L     (OFFSET + GLUT_KEY_ALT_L)
#define KEY_ALT_R     (OFFSET + GLUT_KEY_ALT_R)

#endif // KEYS_HPP