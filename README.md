# gl_loader

An easy-to-use OpenGL Procedure Loader for win32 applications.

## Usage

Include `opengl.h` and `win32_opengl.c` at the start of your project or wherever you want to use OpenGL functions.
```
#include "gl_loader/opengl.h"
#include "gl_loader/win32_opengl.c"
```

If you need a functions that are not included by default, you can add them at the top of the `opengl.h` file by using the following format:
```
GLProc(glTexImage3D, GLTEXIMAGE3D) \
GLProc(glGenerateMipmap, GLGENERATEMIPMAP) \
...
```

## Examples

For further usage explanation you can have a look at the [example_app.c](example_app.c) file.
