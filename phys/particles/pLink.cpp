/*
 * pLink.cpp
 *
 *  Created on: 01/11/2014
 *      Author: K17K47
 */

#include "pLink.h"

namespace phys {
	real pLink::currentLength() const{
		Vector3 relativePos=particle[0]->getPos()-particle[1]->getPos();
		return relativePos.norm();
	}

	unsigned pCable::addContact(pContact *contact, unsigned limit) const{
		real length=currentLength();
		if(length<maxLength) return 0;

		contact->particle[0]=particle[0];
		contact->particle[1]=particle[1];

		Vector3 normal=particle[1]->getPos()-particle[0]->getPos();
		normal.normalize();

		contact->normContact=normal;
		contact->penetracao=length-maxLength;
		contact->restituicao=restituicao;

		return 1;
	}

	unsigned pRod::addContact(pContact *contact, unsigned limit) const{
		real currentLen=currentLength();
		if(currentLen==length) return 0;

		contact->particle[0]=particle[0];
		contact->particle[1]=particle[1];

		Vector3 normal=particle[1]->getPos()-particle[0]->getPos();
		normal.normalize();

		if(currentLen>length){
			contact->normContact=normal;
			contact->penetracao=currentLen-length;
		}else{
			contact->normContact=normal*-1;
			contact->penetracao=length-currentLen;
		}

		contact->restituicao=0;

		return 1;
	}

}; /* namespace phys */
