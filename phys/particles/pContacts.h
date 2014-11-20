/*
 * pContacts.h
 *
 *  Created on: 31/10/2014
 *      Author: K17K47
 */

#ifndef PCONTACTS_H_
#define PCONTACTS_H_

#include "particle.h"

namespace phys{
	class pContact {
		public:
			Particle* particle[2];
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
			unsigned iterations;
			unsigned iterationsUsed;
		public:
			pCResolver(unsigned iterations): iterations(iterations), iterationsUsed(0) {}
			void setIterations(unsigned iterations);
			void resolveContacts(pContact *contactArray, unsigned nContacts, real dt);
	};

	class pContactGen{
		public:
			virtual unsigned addContact(pContact *contact, unsigned limit) const=0;
	};
};

#endif /* PCONTACTS_H_ */
