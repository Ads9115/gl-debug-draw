# gl-debug-draw

A lightweight OpenGL **debug line drawing** utility for rendering simple line primitives (for example axis lines, rays, bounds, and helpers) at runtime.

This repository contains:

- A reusable `DebugDraw` module (`Init`, `BeginFrame`, `DrawLine`, `EndFrame`, `Shutdown`)
- A sample app (`gl-debug-draw/Main.cpp`) that creates a GLFW window and renders a test line
- A Visual Studio solution configured for Windows development

## Features

- OpenGL 3.3 core profile setup (GLFW + GLAD)
- Dynamic CPU-side line list per frame
- Per-vertex RGB color support for lines
- MVP-style `viewProj` matrix uniform in the debug shader
- Minimal API surface for easy integration into existing render loops

## Project Layout

- `gl-debug-draw.sln` — Visual Studio solution
- `gl-debug-draw/` — demo executable project
  - `Main.cpp` — sample usage of the debug draw module
- `DebugDraw/` — debug draw library project
  - `include/DebugDraw.h` — public API
  - `DebugDraw.cpp` — implementation

## Requirements

- Windows + Visual Studio (solution and project files are included)
- OpenGL 3.3 capable GPU/driver
- C++ compiler with C++11+ support

Third-party headers/libraries are vendored under `DebugDraw/Libraries` (including GLM and GLFW headers).

## Build and Run (Visual Studio)

1. Open `gl-debug-draw.sln` in Visual Studio.
2. Select `Debug` or `Release` and `x64` (or your preferred platform).
3. Build the solution.
4. Set `gl-debug-draw` as the startup project if needed.
5. Run the project.

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
