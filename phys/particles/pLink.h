/*
 * pLink.h
 *
 *  Created on: 01/11/2014
 *      Author: K17K47
 */

#ifndef PLINK_H_
#define PLINK_H_

#include "pContacts.h"

namespace Phys {

	class pLink : public pContactGen{
		public:
			pWorld* world;
			unsigned int particle[2];
		protected:
			real currentLength() const;
		public:
			virtual unsigned addContact(pContact *contact, unsigned limit) const=0;
	};

	class pCable : public pLink{
		public:
			pWorld* world;
			real maxLength;
			real restituicao;
			virtual unsigned addContact(pContact *contact, unsigned limit) const;
	};

	class pRod : public pLink{
		public:
			pWorld* world;
			real length;
			virtual unsigned addContact(pContact *contact, unsigned limit) const;
	};

}; /* namespace phys */

#endif /* PLINK_H_ */
