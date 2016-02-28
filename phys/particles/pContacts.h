/*
 * pContacts.h
 *
 *  Created on: 31/10/2014
 *      Author: K17K47
 */

#ifndef PCONTACTS_H_
#define PCONTACTS_H_

#include "pWorld.h"

namespace Phys{
	class pWorld;
	class pContact {
		public:
			pWorld* world;
			unsigned int particle[2];
			real restituicao;
			Vector3 normContact;
			real penetracao;

			void resolve(real dt);
			real calculateSeparatingVelocity() const;
		private:
			void resolveVelocity(real dt);
			void resolveInterpenetration(real dt);
	};

	class pCResolver{
		protected:
			unsigned iterations=8;
			unsigned iterationsUsed=0;
		public:
			void setIterations(unsigned iterations);
			void resolveContacts(pContact *contactArray, unsigned nContacts, real dt);
	};

	class pContactGen{
		public:
			pWorld* world;
			virtual unsigned addContact(pContact *contact, unsigned limit) const=0;
	};
};

#endif /* PCONTACTS_H_ */
