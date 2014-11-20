/*
 * pLink.h
 *
 *  Created on: 01/11/2014
 *      Author: K17K47
 */

#ifndef PLINK_H_
#define PLINK_H_

#include "pContacts.h"

namespace phys {

	class pLink : public pContactGen{
		public:
			Particle* particle[2];
		protected:
			real currentLength() const;
		public:
			virtual unsigned addContact(pContact *contact, unsigned limit) const=0;
	};

	class pCable : public pLink{
		public:
			real maxLength;
			real restituicao;
			virtual unsigned addContact(pContact *contact, unsigned limit) const;
	};

	class pRod : public pLink{
		public:
			real length;
			virtual unsigned addContact(pContact *contact, unsigned limit) const;
	};

}; /* namespace phys */

#endif /* PLINK_H_ */
