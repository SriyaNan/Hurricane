# Hurricane

This is a C++ physics-engine study project based on the code structure from
*Game Physics Engine Development*. The original book engine is called Cyclone;
this repo is being renamed to `Hurricane`.

## Current Status

The particle core now builds and runs. The OpenGL demo files under `src/demos`
now have minimal GLUT support files.

The graphical demo requires FreeGLUT. If the compiler says `GL/freeglut.h`
or `GL/glut.h` is missing, install it from the MSYS2 UCRT64 shell:

```bash
pacman -S mingw-w64-ucrt-x86_64-freeglut
```

## Build The Console Demo

From PowerShell in the repo root:

```powershell
New-Item -ItemType Directory -Force build
C:\msys64\ucrt64\bin\g++.exe -std=c++17 -Iinclude src\particle.cpp examples\ballistic_console.cpp -o build\ballistic_console.exe
```

## Run

```powershell
.\build\ballistic_console.exe
```

## Build The Graphical Ballistic Demo

After installing FreeGLUT, build the book-style windowed demo from PowerShell:

```powershell
C:\msys64\ucrt64\bin\g++.exe -std=c++17 -Iinclude -Isrc\demos src\particle.cpp src\demos\timing.cpp src\demos\app.cpp src\demos\main.cpp src\demos\ballistic\ballistic.cpp -o build\ballistic_demo.exe -lfreeglut -lopengl32 -lglu32
```

Run it:

```powershell
.\build\ballistic_demo.exe
```

Controls:

```text
Click: fire
1: pistol
2: artillery
3: fireball
4: laser
```

It prints a simple CSV trajectory:

```text
time,x,y,z
0.00,0.00,1.50,0.00
0.10,0.00,1.50,3.50
...
```

## VS Code IntelliSense

Open VS Code at the repo root:

```text
C:\Users\sriya\Documents\Hurricane
```

The workspace include folder is:

```text
${workspaceFolder}/include
```

So includes like this should resolve:

```cpp
#include <hurricane/hurricane.h>
```
