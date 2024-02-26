# N-body simulation

This project was done for the course Numerical Algorithms and Numerical Software.

Following numerical methods have been implemented for calculating body position and velocity:

- Forward Euler method
- Semi-implicit Euler method
- Verlet integration

As for the calculation of body acceleration, two methods have been used:

- Direct method
- Barnes-Hut method

![](img/screenshot_01.png)

### Libraries

Before bulding this project, following libraries need to be installed on the system:

- [GLM v1.0.0](https://github.com/g-truc/glm)
- [GLFW v3.3.9](https://www.glfw.org/)
- [OpenGL v3.3](https://www.opengl.org/)
- [ImGui v1.90.1](https://github.com/ocornut/imgui)

**NOTE:** Installation of these libraries depends on Linux distro that you use.

### How to build on Linux

Firstly, run `init.sh` script from root directory. This will download ImGui library, extract it and copy necessary source files. It will also create `build` and `results` directories.

This project uses `cmake` for building process.

This project can be build in DEBUG and RELEASE mode. When building in RELEASE mode all necessary g++ flags
are enabled in order to achive better performance.

RELEASE mode:
```
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

DEBUG mode:
```
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### How to run on Linux

After building, application can be run by executing `SimulationGUI` program located inside of `build` directory.

### Running application in Docker

Building Docker image based on Ubuntu:
```
docker build .
```

Running Docker container from image:
```
docker run --net=host -e DISPLAY=$DISPLAY <image-id>
```

### Examples

![](gif/gif_01.gif)

![](gif/gif_02.gif)

![](gif/gif_03.gif)

![](gif/gif_04.gif)
