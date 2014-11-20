/*
 * pWorld.cpp
 *
 *  Created on: 01/11/2014
 *      Author: K17K47
 */

#include "pWorld.h"

namespace phys {
	void pWorld::add(Particle* particle){
		particles.push_back(particle);
	}

	void pWorld::clear(){
		particles.clear();
	}

	unsigned pWorld::generateContacts(){
		unsigned limit=maxContacts;
		pContact *nextContact=contacts;

		for(pContactGens::iterator g=pCGens.begin(); g!=pCGens.end(); g++){
			unsigned used=(*g)->addContact(nextContact, limit);
			limit-=used;
			nextContact+=used;
			if(limit<=0) break;
		}
		return maxContacts-limit;
	}

	void pWorld::integrate(real dt){
		for(Particles::iterator p=particles.begin(); p!=particles.end(); p++){
			(*p)->integrate(dt);
		}
	}

	void pWorld::runPhysics(real dt){
		pFGRegistry.updateForces(dt);
		integrate(dt);

		unsigned usedContacts=generateContacts();
		if(usedContacts){
			if(!iterations) resolver.setIterations(usedContacts*2);
			resolver.resolveContacts(contacts, usedContacts, dt);
		}
	}
}; /* namespace phys */
