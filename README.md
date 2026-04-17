# gl-debug-draw

A lightweight OpenGL **debug line drawing** utility for rendering simple line primitives (for example axis lines, rays, bounds, and helpers) at runtime.

This repository contains:

- A reusable `DebugDraw` module (`Init`, `BeginFrame`, `DrawLine`, `EndFrame`, `Shutdown`)
- A sample app (`gl-debug-draw/Main.cpp`) that creates a GLFW window and renders a test line
- A CMake build for portable builds across generators and platforms

## Features

- OpenGL 3.3 core profile setup (GLFW + GLAD)
- Dynamic CPU-side line list per frame
- Per-vertex RGB color support for lines
- MVP-style `viewProj` matrix uniform in the debug shader
- Minimal API surface for easy integration into existing render loops

## Project Layout

- `CMakeLists.txt` - CMake build entry point
- `gl-debug-draw/` - demo executable project
  - `Main.cpp` - sample usage of the debug draw module
  - `glad.c` - GLAD OpenGL loader implementation
- `DebugDraw/` - debug draw library project
  - `include/DebugDraw.h` - public API
  - `DebugDraw.cpp` - implementation

## Requirements

- CMake 3.15+
- C++ compiler with C++11 support
- OpenGL 3.3 capable GPU/driver
- Git and internet access if CMake needs to download GLFW

GLM and GLAD are vendored as source/headers. GLFW is found from the system first; if it is not installed, CMake downloads GLFW source with `FetchContent`.

## Build and Run (CMake)

Configure and build:

```sh
cmake -S . -B build
cmake --build build
```

On Windows with the Visual Studio generator:

```sh
cmake -S . -B build -A x64
cmake --build build --config Debug
```

Run the sample app:

```powershell
# Windows Visual Studio generator
.\build\Debug\ExampleApp.exe

# Single-config generators such as Ninja or Unix Makefiles
.\build\ExampleApp.exe
```

On Linux/macOS:

```sh
cmake -S . -B build
cmake --build build
./build/ExampleApp
```

Ubuntu/Debian packages commonly needed before configuring:

```sh
sudo apt install cmake g++ git libgl1-mesa-dev xorg-dev
```

If you want CMake to use an already installed GLFW instead of downloading it:

```sh
# Ubuntu/Debian
sudo apt install libglfw3-dev
cmake -S . -B build -DGL_DEBUG_DRAW_FETCH_GLFW=OFF

# macOS with Homebrew
brew install glfw
cmake -S . -B build -DGL_DEBUG_DRAW_FETCH_GLFW=OFF
```

To check only the reusable library without GLFW or the sample app:

```sh
cmake -S . -B build -DGL_DEBUG_DRAW_BUILD_EXAMPLE=OFF
cmake --build build
```

You should see an 800x600 window with a single red horizontal line in the center.

## Usage

Public API (`DebugDraw/include/DebugDraw.h`):

- `DebugDraw::Init()`
- `DebugDraw::Shutdown()`
- `DebugDraw::BeginFrame()`
- `DebugDraw::DrawLine(start, end, color)`
- `DebugDraw::EndFrame(viewProj)`

Typical frame flow:

```cpp
DebugDraw::Init();

while (running)
{
    DebugDraw::BeginFrame();

    DebugDraw::DrawLine({0,0,0}, {1,0,0}, {1,0,0});
    DebugDraw::DrawLine({0,0,0}, {0,1,0}, {0,1,0});

    DebugDraw::EndFrame(viewProj);
}

DebugDraw::Shutdown();
```

## Notes

- `BeginFrame()` clears queued line vertices.
- `EndFrame()` uploads queued lines to a dynamic VBO and draws with `GL_LINES`.
- If no lines are queued, `EndFrame()` returns early.

## Future Improvements

- Add line thickness support (screen-space or world-space)
- Add persistent debug primitives with lifetime
- Add batch limits / ring buffers for large debug workloads
- Add camera + projection example with movement controls

## License

MIT License

