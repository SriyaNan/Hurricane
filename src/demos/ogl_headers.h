#ifndef HURRICANE_DEMOS_OGL_HEADERS_H
#define HURRICANE_DEMOS_OGL_HEADERS_H

#if defined(__has_include)
#  if __has_include(<GL/freeglut.h>)
#    include <GL/freeglut.h>
#  elif __has_include(<GL/glut.h>)
#    include <GL/glut.h>
#  else
#    error "FreeGLUT/GLUT headers were not found. Install mingw-w64-ucrt-x86_64-freeglut with MSYS2."
#  endif
#else
#  include <GL/glut.h>
#endif

#endif
