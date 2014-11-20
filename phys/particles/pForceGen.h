/*
 * pForceGen.h
 *
 *  Created on: 29/05/2014
 *      Author: K17K47
 */

#ifndef PFORCEGEN_H_
#define PFORCEGEN_H_

#include "particle.h"

namespace phys{
	class pForceGen{
		public:
			virtual void updateForce(phys::Particle *pOne, real dt, phys::Particle *pTwo = 0) = 0;
	};

	class pFGenReg{
		protected:
			struct pFGRegister{
				phys::Particle *pOne;
				pForceGen *fg;
				phys::Particle *pTwo=0;
			};
			typedef std::vector<pFGRegister> pFGRegistry;
			pFGRegistry registry;
		public:
			void add(phys::Particle *pOne, pForceGen *fg, phys::Particle *pTwo=0);
			/*void remove()*/ //TODO:Implement remove from registry
			void clear();
			void updateForces(real dt);
	};

	class pGrav : public pForceGen{
		private:
			Vector3 grav;
		public:
			pGrav(const Vector3 &gravity) : grav(gravity) {};
			virtual void updateForce(phys::Particle *pOne, real dt, phys::Particle *pTwo=0);
	};

	class pDrag : public pForceGen{
		private:
			real k1;
			real k2;
		public:
			pDrag(real k1, real k2) : k1(k1), k2(k2) {};
			virtual void updateForce(phys::Particle *pOne, real dt, phys::Particle *pTwo=0);
	};

	class pSpring : public pForceGen{
		private:
			real k;
			real restLen;
		public:
			pSpring(real k, real restLen) : k(k), restLen(restLen) {};
			virtual void updateForce(phys::Particle *pOne, real dt, phys::Particle *pTwo);
	};

	/*class pDampedSpring : public pForceGen{};*/ //TODO: Implementar pDampedSpring

	class pAnchoredSpring : public pForceGen{
		private:
			real k;
			Vector3 *anchor;
			real restLen;
		public:
			pAnchoredSpring(Vector3 *anchor, real k, real restLen) : k(k), restLen(restLen), anchor(anchor) {};
			virtual void updateForce(phys::Particle *pOne, real dt, phys::Particle *pTwo=0);
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
			virtual void updateForce(phys::Particle *pOne, real dt, phys::Particle *pTwo=0);
	};

	class pAnchoredFakeSpring : public pForceGen{
		private:
			Vector3 *anchor;
			real k;
			real damping;
		public:
			pAnchoredFakeSpring(Vector3 *anchor, real k, real damping) : anchor(anchor), k(k), damping(damping) {};
			virtual void updateForce(phys::Particle *pOne, real dt, phys::Particle *pTwo=0);
	};

	class pLinearMotor : public pForceGen{
		private:
			Vector3 *dir;
			real force;
			real maxVel;
		public:
			pLinearMotor(Vector3 *dir, real force, real maxVel) : dir(dir), force(force), maxVel(maxVel) {};
			virtual void updateForce(phys::Particle *pOne, real dt, phys::Particle *pTwo=0);
	};
};



#endif /* PFORCEGEN_H_ */
