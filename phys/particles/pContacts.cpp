/*
 * pContacts.cpp
 *
 *  Created on: 31/10/2014
 *      Author: K17K47
 */

#include "pContacts.h"

namespace phys{
	void pContact::resolve(real dt){
		resolveVelocity(dt);
		resolveInterpenetration(dt);
	}

	void pContact::resolveVelocity(real dt){
		real sepVel = calculateSeparatingVelocity();
		if(sepVel>0) return;

		real newSepVel = -sepVel * restituicao;

		Vector3 accCausedVel = particle[0]->getAcc();
		if(particle[1]) accCausedVel-=particle[1]->getAcc();

		real accCausedSepVel=normContact.dot(accCausedVel)*dt;
		if(accCausedSepVel<0){
			newSepVel+=restituicao*accCausedSepVel;
			if(newSepVel<0) newSepVel=0;
		}

		real deltaV = newSepVel - sepVel;
		real totalInvMass=particle[0]->getInvMass();
		if(particle[1]) totalInvMass+=particle[1]->getInvMass();
		if(totalInvMass <= 0) return;

		real impulse=deltaV/totalInvMass;
		Vector3 impPerInvMass = normContact*impulse;
		particle[0]->setVel(particle[0]->getVel()+impPerInvMass*particle[0]->getInvMass());
		if(particle[1])
			particle[1]->setVel(particle[1]->getVel()+impPerInvMass* -particle[1]->getInvMass());
	}

	real pContact::calculateSeparatingVelocity() const{
		Vector3 velRelativa = particle[0]->getVel();
		if(particle[1]) velRelativa -= particle[1]->getVel();
		return normContact.dot(velRelativa);
	}

	void pContact::resolveInterpenetration(real dt){
		if(penetracao<=0) return;

		real totalInvMass=particle[0]->getInvMass();
		if(particle[1]) totalInvMass+=particle[1]->getInvMass();
		if(totalInvMass<=0) return;

		Vector3 movePerInvMass = normContact*(penetracao/totalInvMass);
		Vector3 movParticle[2];
		movParticle[0]=movePerInvMass*particle[0]->getInvMass();
		if(particle[1]){
			movParticle[1]=movePerInvMass* -particle[1]->getInvMass();
		}else{
			movParticle[1].setZero();
		}

		particle[0]->setPos(particle[0]->getPos()+movParticle[0]);
		if(particle[1])
			particle[1]->setPos(particle[1]->getPos()+movParticle[1]);
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

