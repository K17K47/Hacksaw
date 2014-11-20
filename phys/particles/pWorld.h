/*
 * pWorld.h
 *
 *  Created on: 01/11/2014
 *      Author: K17K47
 */

#ifndef PWORLD_H_
#define PWORLD_H_

#include "particle.h"
#include "pForceGen.h"
#include "pContacts.h"

namespace phys {

	class pWorld {
		public:
			typedef std::vector<Particle*> Particles;
			typedef std::vector<pContactGen*> pContactGens;
		protected:
			Particles particles;
		public:
			pFGenReg pFGRegistry;
			pCResolver resolver=pCResolver(iterations);
			pContactGens pCGens;
			pContact *contacts;

			unsigned maxContacts;
			unsigned iterations;

			pWorld(unsigned maxContacts, unsigned iterations=0):maxContacts(maxContacts), iterations(iterations) {}

			unsigned generateContacts();
			void integrate(real dt);
			void runPhysics(real dt);
			void startFrame();

			void add(Particle* particle);
			//void remove(Particle* particle); TODO: Implement remove from world
			void clear();
	};

} /* namespace phys */

#endif /* PWORLD_H_ */
