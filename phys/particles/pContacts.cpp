/*
 * pContacts.cpp
 *
 *  Created on: 31/10/2014
 *      Author: K17K47
 */

#include "pContacts.h"

namespace Phys{
	void pContact::resolve(real dt){
		resolveVelocity(dt);
		resolveInterpenetration(dt);
	}

	void pContact::resolveVelocity(real dt){
		real sepVel = calculateSeparatingVelocity();
		if(sepVel>0) return;

		real newSepVel = -sepVel * restituicao;

		Vector3 accCausedVel = world->getAcc(particle[0]);
		if(particle[1]) accCausedVel-=world->getAcc(particle[1]);

		real accCausedSepVel=normContact.dot(accCausedVel)*dt;
		if(accCausedSepVel<0){
			newSepVel+=restituicao*accCausedSepVel;
			if(newSepVel<0) newSepVel=0;
		}

		real deltaV = newSepVel - sepVel;
		real totalInvMass=world->getInvMass(particle[0]);
		if(particle[1]) totalInvMass+=world->getInvMass(particle[1]);
		if(totalInvMass <= 0) return;

		real impulse=deltaV/totalInvMass;
		Vector3 impPerInvMass = normContact*impulse;
		world->setVel(particle[0], world->getVel(particle[0])+impPerInvMass*world->getInvMass(particle[0]));
		if(particle[1])
			world->setVel(particle[1], world->getVel(particle[1])+impPerInvMass* -world->getInvMass(particle[1]));
	}

	real pContact::calculateSeparatingVelocity() const{
		Vector3 velRelativa = world->getVel(particle[0]);
		if(particle[1]) velRelativa -= world->getVel(particle[1]);
		return normContact.dot(velRelativa);
	}

	void pContact::resolveInterpenetration(real dt){
		if(penetracao<=0) return;

		real totalInvMass=world->getInvMass(particle[0]);
		if(particle[1]) totalInvMass+=world->getInvMass(particle[1]);
		if(totalInvMass<=0) return;

		Vector3 movePerInvMass = normContact*(penetracao/totalInvMass);
		Vector3 movParticle[2];
		movParticle[0]=movePerInvMass*world->getInvMass(particle[0]);
		if(particle[1]){
			movParticle[1]=movePerInvMass* -world->getInvMass(particle[1]);
		}else{
			movParticle[1].setZero();
		}

		world->setPos(particle[0], world->getPos(particle[0])+movParticle[0]);
		if(particle[1])
			world->setPos(particle[1], world->getPos(particle[1])+movParticle[1]);
	}

	void pCResolver::resolveContacts(pContact *contactArray, unsigned nContacts, real dt){
		unsigned i;

		for(iterationsUsed=0; iterationsUsed<iterations; iterationsUsed++){
			real max=REAL_MAX;
			unsigned maxIndex=nContacts;

			for(i=0; i<nContacts; i++){
				real sepVel=contactArray[i].calculateSeparatingVelocity();

				if(sepVel<max && (sepVel<0 || contactArray[i].penetracao>0)){
					max=sepVel;
					maxIndex=i;
				}
			}
			if(maxIndex==nContacts) break;
			contactArray[maxIndex].resolve(dt);
		}
	}

	void pCResolver::setIterations(unsigned iterations){this->iterations=iterations;}
};

