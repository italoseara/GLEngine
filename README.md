# OpenGL Project

This is a project that utilizes the OpenGL library to create a simple game engine.

## Prerequisites

Before running this project, make sure you have the following installed:

- [OpenGL](https://www.opengl.org/)
- [FreeGLUT](http://freeglut.sourceforge.net/)

## Getting Started

To get started with this project, follow these steps:

1. Clone this repository: `git clone https://github.com/italoseara/GLEngine.git`
2. Open the project in your favorite IDE
3. Build using `make` or `make all`
4. Run the project using `./build/main`

## Features

- [x] Delta time calculation
- [x] Frame rate calculation
- [x] init(), update(), render() and shutdown() functions
- [x] Input handling
- [x] Debug mode
- [ ] Camera
- [ ] Movement
- [ ] Textures
- [x] 2D rendering
- [ ] 3D rendering

## Usage

```cpp
#include <iostream>
#include "GLEngine/Engine.hpp"

using namespace std;

// Implement the following functions
void init();
void update(double dt);
void render();
void keyDown(int keyCode);
void keyUp(int keyCode);

int main(int argc, char **argv)
{
  Engine::Init("Engine", 800, 600);
  Engine::Callbacks(init, update, render);
  Engine::InputCallbacks(keyDown, keyUp);
  Engine::Run(&argc, argv);
  return 0;
}
```

## Contributing

Contributions are welcome! If you'd like to contribute to this project, please follow these guidelines:

1. Fork the repository
2. Create a new branch: `git checkout -b feat/your-feature`
3. Make your changes and commit them: `git commit -m 'Add your feature'`
4. Push to the branch: `git push origin feat/your-feature`
5. Submit a pull request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Contact

If you want to contact me you can reach me at [italo.sseara@gmail.com](mailto:italo.sseara@gmail.com)
