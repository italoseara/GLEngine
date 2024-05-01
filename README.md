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
3. Build and run the project

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
#include "engine.h"

// Implement the following functions
void init();
void update(float dt);
void render();
void input(unsigned char key, int x, int y);
void shutdown();

int main(int argc, char** argv) {
    Engine::init(&argc, argv, "My Game", 800, 600);
    Engine::onInit(init);
    Engine::onUpdate(update);
    Engine::onRender(render);
    Engine::onKeyDown(input);
    Engine::onShutdown(shutdown);
    Engine::run();
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
