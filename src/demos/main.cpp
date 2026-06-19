#include "app.h"
#include "ogl_headers.h"
#include "timing.h"

Application* getApplication();

namespace {
    Application *application = 0;

    void display()
    {
        application->display();
        glFlush();
        glutSwapBuffers();
    }

    void update()
    {
        TimingData::get().update();
        application->update();
    }

    void key(unsigned char key, int, int)
    {
        application->key(key);
    }

    void resize(int width, int height)
    {
        application->resize(width, height);
    }

    void mouse(int button, int state, int x, int y)
    {
        application->mouse(button, state, x, y);
    }

    void motion(int x, int y)
    {
        application->mouseDrag(x, y);
    }
}

int main(int argc, char **argv)
{
    application = getApplication();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 320);
    glutCreateWindow(application->getTitle());

    application->resize(640, 320);
    application->initGraphics();

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(key);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(update);

    glutMainLoop();

    application->deinit();
    delete application;
    return 0;
}
