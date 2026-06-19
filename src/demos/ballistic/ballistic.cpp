#include <hurricane/hurricane.h>
#include "../ogl_headers.h"
#include "../app.h"
#include "../timing.h"

#include <stdio.h>

class BallisticDemo : public Application //application class in balldemo
{
    enum ShotType
    {
        UNUSED = 0,
        PISTOL,
        ARTILLERY,
        FIREBALL,
        LASER
    };
    struct AmmoRound
    {
        Hurricane::Particle particle;
        ShotType type;
        unsigned startTime;

        void render()
        {
            Hurricane::Vector3 position;
            particle.getPosition(&position);

            glColor3f(0, 0, 0);
            glPushMatrix();
            glTranslatef(position.x, position.y, position.z);
            glutSolidSphere(1.0f, 5, 4);
            glPopMatrix();
            //shadow
            glColor3f(0.10, 0.097, 0.097);
            glPushMatrix();
            glTranslatef(position.x, 0, position.z);
            glScalef(1.0f, 0.1f, 1.0f);
            glutSolidSphere(0.6f, 5, 4);
            glPopMatrix();
        }
    };

    const static unsigned ammoRounds = 16;
    AmmoRound ammo[ammoRounds];
    ShotType currentShotType;
    void fire();

    public:
        BallisticDemo();
        virtual const char* getTitle();
        virtual void update();
        virtual void display();
        virtual void mouse(int button, int state, int x, int y);
        virtual void key(unsigned char key);
};

BallisticDemo::BallisticDemo(): currentShotType(LASER)
{
    for (AmmoRound *shot = ammo; shot < ammo+ammoRounds; shot++)
    {
        shot->type = UNUSED;
    }
}

const char* BallisticDemo::getTitle()
{
    return "Hurricane engine";
}

void BallisticDemo::fire()
{
    AmmoRound *shot;
    for (shot = ammo; shot < ammo+ammoRounds; shot++)
    {
        if (shot->type == UNUSED) break;
    }
    if (shot >= ammo+ammoRounds) return;
    switch(currentShotType)
    {
    case PISTOL:
        shot->particle.setMass(2.0f); 
        shot->particle.setVelocity(0.0f, 0.0f, 35.0f); 
        shot->particle.setAcceleration(0.0f, -1.0f, 0.0f);
        shot->particle.setDamping(0.99f);
        break;

    case ARTILLERY:
        shot->particle.setMass(200.0f); // 200.0kg
        shot->particle.setVelocity(0.0f, 30.0f, 40.0f); // 50m/s
        shot->particle.setAcceleration(0.0f, -20.0f, 0.0f);
        shot->particle.setDamping(0.99f);
        break;

    case FIREBALL:
        shot->particle.setMass(1.0f); // 1.0kg - mostly blast damage
        shot->particle.setVelocity(0.0f, 0.0f, 10.0f); // 5m/s
        shot->particle.setAcceleration(0.0f, 0.6f, 0.0f); // Floats up
        shot->particle.setDamping(0.9f);
        break;

    case LASER:
        shot->particle.setMass(0.1f); // 0.1kg - almost no weight
        shot->particle.setVelocity(0.0f, 0.0f, 100.0f); // 100m/s
        shot->particle.setAcceleration(0.0f, 0.0f, 0.0f); // No gravity
        shot->particle.setDamping(0.99f);
        break;
    }

    shot->particle.setPosition(0.0f, 0.9f, 0.0f);
    shot->startTime = TimingData::get().lastFrameTimestamp;
    shot->type = currentShotType;
    shot->particle.clearAccumulator();
}

void BallisticDemo::update()
{
    float duration = (float)TimingData::get().lastFrameDuration * 0.001f;
    if (duration <= 0.0f) return;

    for (AmmoRound *shot = ammo; shot < ammo+ammoRounds; shot++)
    {
        if (shot->type != UNUSED)
        {
            shot->particle.integrate(duration);

            if (shot->particle.getPosition().y < 0.0f ||
                shot->startTime+5000 < TimingData::get().lastFrameTimestamp ||
                shot->particle.getPosition().z > 200.0f)
            {
                shot->type = UNUSED;
            }
        }
    }

    Application::update();
}

void BallisticDemo::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(-25.0, 8.0, 5.0,  0.0, 5.0, 22.0,  0.0, 1.0, 0.0);

    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, 0.0f);
    glutSolidCube(1.0f);
    glTranslatef(0.0f, -1.5f, 0.0f);
    glColor3f(0.75f, 0.75f, 0.75f);
    glScalef(1.0f, 0.1f, 1.0f);
    glutSolidSphere(0.1f, 5, 5);
    glPopMatrix();

    glColor3f(0.75f, 0.75f, 0.75f);
    glBegin(GL_LINES);
    for (unsigned i = 0; i < 200; i += 10)
    {
        glVertex3f(-5.0f, 0.0f, i);
        glVertex3f(5.0f, 0.0f, i);
    }
    glEnd();

    for (AmmoRound *shot = ammo; shot < ammo+ammoRounds; shot++)
    {
        if (shot->type != UNUSED)
        {
            shot->render();
        }
    }

    glColor3f(0.0f, 0.0f, 0.0f);
    renderText(10.0f, 34.0f, "Click to Fire\n1-4: Select Ammo");

    // Render the name of the current shot type
    switch(currentShotType)
    {
    case PISTOL: renderText(10.0f, 10.0f, "Current Ammo: Pistol"); break;
    case ARTILLERY: renderText(10.0f, 10.0f, "Current Ammo: Artillery"); break;
    case FIREBALL: renderText(10.0f, 10.0f, "Current Ammo: Fireball"); break;
    case LASER: renderText(10.0f, 10.0f, "Current Ammo: Laser"); break;
    }
}

void BallisticDemo::mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) fire();
}

void BallisticDemo::key(unsigned char key)
{
    switch(key)
    {
    case '1': currentShotType = PISTOL; break;
    case '2': currentShotType = ARTILLERY; break;
    case '3': currentShotType = FIREBALL; break;
    case '4': currentShotType = LASER; break;
    }
}

Application* getApplication()
{
    return new BallisticDemo();
}
