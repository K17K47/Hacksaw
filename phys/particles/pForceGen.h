/*
 * pForceGen.h
 *
 *  Created on: 29/05/2014
 *      Author: K17K47
 */

#ifndef PFORCEGEN_H_
#define PFORCEGEN_H_

#include "pWorld.h"

namespace Phys{
	class pWorld;
	class pForceGen{
		public:
			virtual void updateForce(pWorld *pointer, real dt, unsigned int pOne, unsigned int pTwo = 0) = 0;
	};

	class pFGenReg{
		protected:
			struct pFGRegister{
				unsigned int pOne;
				pForceGen *fg;
				unsigned int pTwo=0;
			};
			typedef std::vector<pFGRegister> pFGRegistry;
			pFGRegistry registry;
		public:
			void add(pForceGen *fg, unsigned int pOne, unsigned int pTwo=0);
			/*void remove()*/ //TODO:Implement remove from registry
			void clear();
			void updateForces(real dt, pWorld *pointer);
	};

	class pGrav : public pForceGen{
		private:
			Vector3 grav;
		public:
			pGrav(const Vector3 &gravity) : grav(gravity) {};
			virtual void updateForce(pWorld *pointer, real dt, unsigned int pOne, unsigned int pTwo=0);
	};

	class pDrag : public pForceGen{
		private:
			real k1;
			real k2;
		public:
			pDrag(real k1, real k2) : k1(k1), k2(k2) {};
			virtual void updateForce(pWorld *pointer, real dt, unsigned int pOne, unsigned int pTwo=0);
	};

	class pSpring : public pForceGen{
		private:
			real k;
			real restLen;
		public:
			pSpring(real k, real restLen) : k(k), restLen(restLen) {};
			virtual void updateForce(pWorld *pointer, real dt, unsigned int pOne, unsigned int pTwo);
	};

	/*class pDampedSpring : public pForceGen{};*/ //TODO: Implementar pDampedSpring

	class pAnchoredSpring : public pForceGen{
		private:
			real k;
			Vector3 *anchor;
			real restLen;
		public:
			pAnchoredSpring(Vector3 *anchor, real k, real restLen) : k(k), restLen(restLen), anchor(anchor) {};
			virtual void updateForce(pWorld *pointer, real dt, unsigned int pOne, unsigned int pTwo=0);
	};

	class pBuoyancy : public pForceGen{
		private:
			real maxDepth;
			real volume;
			real liquidHeight;
			real liquidDensity;
		public:
			pBuoyancy(real maxDepth, real volume, real liquidHeight, real liquidDensity = 1000)				 \
			: maxDepth(maxDepth), volume(volume), liquidHeight(liquidHeight), liquidDensity(liquidDensity){};\
			virtual void updateForce(pWorld *pointer, real dt, unsigned int pOne, unsigned int pTwo=0);
	};

	class pAnchoredFakeSpring : public pForceGen{
		private:
			Vector3 *anchor;
			real k;
			real damping;
		public:
			pAnchoredFakeSpring(Vector3 *anchor, real k, real damping) : anchor(anchor), k(k), damping(damping) {};
			virtual void updateForce(pWorld *pointer, real dt, unsigned int pOne, unsigned int pTwo=0);
	};

	class pLinearMotor : public pForceGen{
		private:
			Vector3 *dir;
			real force;
			real maxVel;
		public:
			pLinearMotor(Vector3 *dir, real force, real maxVel) : dir(dir), force(force), maxVel(maxVel) {};
			virtual void updateForce(pWorld *pointer, real dt, unsigned int pOne, unsigned int pTwo=0);
	};
};



#endif /* PFORCEGEN_H_ */
