/*
 * pForceGen.cpp
 *
 *  Created on: 31/10/2014
 *      Author: K17K47
 */


#include "pForceGen.h"
namespace Phys{
	void pFGenReg::add(pForceGen *fg, unsigned int pOne, unsigned int pTwo){
		pFGenReg::pFGRegister registration;
		registration.pOne = pOne;
		registration.fg = fg;
		registration.pTwo = pTwo;
		registry.push_back(registration);
	}

	void pFGenReg::clear(){
		registry.clear();
	}

	void pFGenReg::updateForces(real dt, pWorld *pointer){
		for (pFGRegistry::iterator it = registry.begin(); it != registry.end(); it++){
			it->fg->updateForce(pointer, dt, it->pOne, it->pTwo);
		}
	}

	void pGrav::updateForce(pWorld *pointer, real dt, unsigned int pOne, unsigned int pTwo){
		if(!pointer->hasFiniteMass(pOne)) return;
		pointer->addForce(pOne, grav * pointer->getMass(pOne));
	}

	void pDrag::updateForce(pWorld *pointer, real dt, unsigned int pOne, unsigned int pTwo){
		Vector3 force;
		pointer->getVel(pOne, &force);
		real dragK = force.norm();
		dragK=k1*dragK+k2*dragK*dragK;
		force.normalize();
		force*=-dragK;
		pointer->addForce(pOne, force);
	}

	void pSpring::updateForce(pWorld *pointer, real dt, unsigned int pOne, unsigned int pTwo){
		Vector3 force;
		pointer->getPos(pOne, &force);
		force-=pointer->getPos(pTwo);

		real mag = force.norm();
		mag=real_abs(mag-restLen);
		mag*=k;

		force.normalize();
		force*=-mag;
		pointer->addForce(pOne, force);
	}

	void pAnchoredSpring::updateForce(pWorld *pointer, real dt, unsigned int pOne, unsigned int pTwo){
		Vector3 force;
		pointer->getPos(pOne, &force);
		force-= *anchor;

		real mag=force.norm();
		mag=real_abs(mag-restLen);
		mag*=k;

		force.normalize();
		force*=mag;
		pointer->addForce(pOne, force);
	}

	void pBuoyancy::updateForce(pWorld *pointer, real dt, unsigned int pOne, unsigned int pTwo){
		real depth=pointer->getPos(pOne)[2];

		if(depth >= liquidHeight + maxDepth) return;

		Vector3 force(0,0,0);

		if(depth <= liquidHeight - maxDepth){
			force[2]=liquidDensity * volume;
			pointer->addForce(pOne, force);
			return;
		}

		force[2]=liquidDensity * volume *(depth - maxDepth - liquidHeight)/2 * maxDepth;
		pointer->addForce(pOne, force);
	}

	void pAnchoredFakeSpring::updateForce(pWorld *pointer, real dt, unsigned int pOne, unsigned int pTwo){
		if(pointer->hasFiniteMass(pOne)) return;

		Vector3 pos;
		pointer->getPos(pOne, &pos);
		pos-= *anchor;

		real gamma=0.5 * real_sqrt(4*k-damping*damping);
		if(gamma==0) return;

		Vector3 c=pos*(damping/(2.0*gamma))+pointer->getVel(pOne)*(1.0/gamma);

		Vector3 target=pos*real_cos(gamma*dt)+c*real_sin(gamma*dt);
		target*=real_exp(-0.5*dt*damping);

		Vector3 accel=(target-pos)*(1.0/dt*dt)-pointer->getVel(pOne)*dt;
		pointer->addForce(pOne, accel*pointer->getMass(pOne));
	}

	void pLinearMotor::updateForce(pWorld *pointer, real dt, unsigned int pOne, unsigned int pTwo){
		if((maxVel==0) || (maxVel<pointer->getVel(pOne).norm())){
			pointer->addForce(pOne ,dir->normalized()*force);
		}
	}
};

