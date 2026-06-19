#ifndef HURRICANE_DEMOS_APP_H
#define HURRICANE_DEMOS_APP_H

#include <hurricane/hurricane.h>

class Application
{
protected:
    int height;
    int width;

public:
    virtual const char* getTitle();
    virtual void initGraphics();
    virtual void setView();
    virtual void deinit();
    virtual void display();
    virtual void update();
    virtual void key(unsigned char key);
    virtual void resize(int width, int height);
    virtual void mouse(int button, int state, int x, int y);
    virtual void mouseDrag(int x, int y);

    void renderText(float x, float y, const char *text, void* font=0);
};

#endif
