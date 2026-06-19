#ifndef CYCLONE_PCONTACTS_H
#define CYCLONE_PCONTACTS_H

#include "particle.h"

namespace Hurricane {
    class ParticleContactResolver;

    class ParticleContact
    {
        friend class ParticleContactResolver;
    public:
        Particle* particle[2]; // Holds the particles that are involved in the contact.
        real restitution; //How bouncy is the collision?
        Vector3 contactNormal; //the direction of the contact
        real penetration; // the depth of penetration
        Vector3 particleMovement[2]; // the amount each particle is moved by during interpenetration

    protected:
        /**
         * Resolves this contact, for both velocity and interpenetration.   
         */
        void resolve(real duration);

        /**
         * Calculates the separating velocity at this contact.
         */
        real calculateSeparatingVelocity() const;

    private:
        /**
         * Handles the impulse calculations for this collision.
         */
        void resolveVelocity(real duration);

        /**
         * Handles the interpenetration resolution for this contact.
         */
        void resolveInterpenetration(real duration);

    };

    /**
     * The contact resolution routine for particle contacts. One
     * resolver instance can be shared for the whole simulation.
     */
    class ParticleContactResolver
    {
    protected:
        /**
         * Holds the number of iterations allowed.
         */
        unsigned iterations;

        /**
         * This is a performance tracking value - we keep a record
         * of the actual number of iterations used.
         */
        unsigned iterationsUsed;

    public:
        /**
         * Creates a new contact resolver.
         */
        ParticleContactResolver(unsigned iterations);

        /**
         * Sets the number of iterations that can be used.
         */
        void setIterations(unsigned iterations);

        /**
         * Resolves a set of particle contacts for both penetration
         * and velocity.
         *
         * Contacts that cannot interact with each other should be
         * passed to separate calls to resolveContacts, as the
         * resolution algorithm takes much longer for lots of contacts
         * than it does for the same number of contacts in small sets.
         *
         * @param contactArray Pointer to an array of particle contact
         * objects.
         *
         * @param numContacts The number of contacts in the array to
         * resolve.
         *
         * @param numIterations The number of iterations through the
         * resolution algorithm. This should be at least the number of
         * contacts (otherwise some constraints will not be resolved -
         * although sometimes this is not noticable). If the
         * iterations are not needed they will not be used, so adding
         * more iterations may not make any difference. But in some
         * cases you would need millions of iterations. Think about
         * the number of iterations as a bound: if you specify a large
         * number, sometimes the algorithm WILL use it, and you may
         * drop frames.
         *
         * @param duration The duration of the previous integration step.
         * This is used to compensate for forces applied.
        */
        void resolveContacts(ParticleContact *contactArray,
            unsigned numContacts,
            real duration);
    };

    /**
     * This is the basic polymorphic interface for contact generators
     * applying to particles.
     */
    class ParticleContactGenerator
    {
    public:
        /**
         * Fills the given contact structure with the generated
         * contact. The contact pointer should point to the first
         * available contact in a contact array, where limit is the
         * maximum number of contacts in the array that can be written
         * to. The method returns the number of contacts that have
         * been written.
         */
        virtual unsigned addContact(ParticleContact *contact,
                                    unsigned limit) const = 0;
    };



} // namespace Hurricane

#endif // CYCLONE_CONTACTS_H
