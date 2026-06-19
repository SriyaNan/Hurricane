#include <assert.h>
#include <hurricane/particle.h>

using namespace Hurricane;

Particle::Particle()
    : inverseMass(1.0),
      damping(0.99),
      position(),
      velocity(),
      forceAccum(),
      acceleration()
{
}

void Particle::integrate(real duration)
{
    assert(duration > 0.0);

    if (inverseMass <= 0.0) return;

    position.addScaledVector(velocity, duration);

    Vector3 resultingAcceleration = acceleration;
    resultingAcceleration.addScaledVector(forceAccum, inverseMass);

    velocity.addScaledVector(resultingAcceleration, duration);
    velocity *= real_pow(damping, duration);

    clearAccumulator();
}

void Particle::setMass(const real mass)
{
    assert(mass != 0);
    inverseMass = ((real)1.0) / mass;
}

real Particle::getMass() const
{
    if (inverseMass == 0) return REAL_MAX;
    return ((real)1.0) / inverseMass;
}

void Particle::setInverseMass(const real inverseMass)
{
    Particle::inverseMass = inverseMass;
}

real Particle::getInverseMass() const
{
    return inverseMass;
}

bool Particle::hasFiniteMass() const
{
    return inverseMass > 0.0;
}

void Particle::setDamping(const real damping)
{
    Particle::damping = damping;
}

real Particle::getDamping() const
{
    return damping;
}

void Particle::setPosition(const Vector3 &position)
{
    Particle::position = position;
}

void Particle::setPosition(const real x, const real y, const real z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

void Particle::getPosition(Vector3 *position) const
{
    *position = Particle::position;
}

Vector3 Particle::getPosition() const
{
    return position;
}

void Particle::setVelocity(const Vector3 &velocity)
{
    Particle::velocity = velocity;
}

void Particle::setVelocity(const real x, const real y, const real z)
{
    velocity.x = x;
    velocity.y = y;
    velocity.z = z;
}

void Particle::getVelocity(Vector3 *velocity) const
{
    *velocity = Particle::velocity;
}

Vector3 Particle::getVelocity() const
{
    return velocity;
}

void Particle::setAcceleration(const Vector3 &acceleration)
{
    Particle::acceleration = acceleration;
}

void Particle::setAcceleration(const real x, const real y, const real z)
{
    acceleration.x = x;
    acceleration.y = y;
    acceleration.z = z;
}

void Particle::getAcceleration(Vector3 *acceleration) const
{
    *acceleration = Particle::acceleration;
}

Vector3 Particle::getAcceleration() const
{
    return acceleration;
}

void Particle::clearAccumulator()
{
    forceAccum.clear();
}

void Particle::addForce(const Vector3 &force)
{
    forceAccum += force;
}
