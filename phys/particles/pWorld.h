/*
 * pWorld.h
 *
 *  Created on: 01/11/2014
 *      Author: K17K47
 */

#ifndef PWORLD_H_
#define PWORLD_H_

#include "mathHelper.h"
#include "pForceGen.h"
#include "pContacts.h"

namespace Phys {
	class pContactGen;
	class pCResolver;
	class pContact;
	class pFGenReg;
	class pWorld {
		public:
			typedef std::vector<pContactGen*> pContactGens;

			std::vector<Vector3> pos;
			std::vector<Vector3> vel;
			std::vector<Vector3> acc;
			std::vector<Vector3> forceAcc;
			std::vector<real> invMass;

			pFGenReg* pFGRegistry;
			pCResolver* resolver;
			pContactGens pCGens;
			pContact *contacts;

			unsigned maxContacts;
			unsigned iterations;

			pWorld();
			~pWorld();

			unsigned generateContacts();
			void runPhysics(real dt);
			void startFrame();

			unsigned int addParticle(real mass, Vector3 position=Vector3::Zero(), Vector3 velocity=Vector3::Zero(), Vector3 acceleration=Vector3::Zero());
			//void remove(Particle* particle); TODO: Implement remove from world
			void clear();

			void addForce(unsigned int index, const Vector3 &force);
			void setPos(unsigned int index, const Vector3 &p);
			void setVel(unsigned int index, const Vector3 &v);
			void setAcc(unsigned int index, const Vector3 &a);
			void setMass(unsigned int index, const real &m);
			Vector3 getPos(unsigned int index);
			Vector3 getVel(unsigned int index);
			Vector3 getAcc(unsigned int index);
			real getMass(unsigned int index) const;
			real getInvMass(unsigned int index) const;
			void getPos(unsigned int index, Vector3 *p) const;
			void getVel(unsigned int index, Vector3 *v) const;
			void getAcc(unsigned int index, Vector3 *a) const;
			bool hasFiniteMass(unsigned int index) const;
			void integrate(real dt);
	};

} /* namespace phys */

#endif /* PWORLD_H_ */
