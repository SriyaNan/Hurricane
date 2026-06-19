#include <hurricane/hurricane.h>

#include <iomanip>
#include <iostream>

using namespace Hurricane;

namespace {
    Particle makeProjectile()
    {
        Particle projectile;
        projectile.setMass(2.0);
        projectile.setPosition(0.0, 1.5, 0.0);
        projectile.setVelocity(0.0, 0.0, 35.0);
        projectile.setAcceleration(0.0, -9.8, 0.0);
        projectile.setDamping(0.99);
        projectile.clearAccumulator();
        return projectile;
    }
}

int main()
{
    Particle projectile = makeProjectile();
    const real duration = 0.1;

    std::cout << "time,x,y,z\n";

    for (unsigned step = 0; step <= 50; ++step)
    {
        Vector3 position = projectile.getPosition();
        real time = step * duration;

        std::cout << std::fixed << std::setprecision(2)
                  << time << ','
                  << position.x << ','
                  << position.y << ','
                  << position.z << '\n';

        if (position.y < 0.0) break;
        projectile.integrate(duration);
    }
}
