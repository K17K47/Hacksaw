/*
 * pForceGen.cpp
 *
 *  Created on: 31/10/2014
 *      Author: K17K47
 */


#include "pForceGen.h"
namespace phys{
	void pFGenReg::add(Particle * pOne, pForceGen * fg, Particle * pTwo){
		pFGenReg::pFGRegister registration;
		registration.pOne = pOne;
		registration.fg = fg;
		registration.pTwo = pTwo;
		registry.push_back(registration);
	}

	void pFGenReg::clear(){
		registry.clear();
	}

	void pFGenReg::updateForces(real dt){
		for (pFGRegistry::iterator it = registry.begin(); it != registry.end(); it++){
			it->fg->updateForce(it->pOne, dt, it->pTwo);
		}
	}

	void pGrav::updateForce(Particle * pOne, real dt, Particle * pTwo){
		if(!pOne->hasFiniteMass()) return;
		pOne->addForce(grav * pOne->getMass());
	}

	void pDrag::updateForce(Particle * pOne, real dt, Particle * pTwo){
		Vector3 force;
		pOne->getVel(&force);
		real dragK = force.norm();
		dragK=k1*dragK+k2*dragK*dragK;
		force.normalize();
		force*=-dragK;
		pOne->addForce(force);
	}

	void pSpring::updateForce(Particle * pOne, real dt, Particle * pTwo){
		Vector3 force;
		pOne->getPos(&force);
		force-=pTwo->getPos();

		real mag = force.norm();
		mag=real_abs(mag-restLen);
		mag*=k;

		force.normalize();
		force*=-mag;
		pOne->addForce(force);
	}

	void pAnchoredSpring::updateForce(Particle * pOne, real dt, Particle * pTwo){
		Vector3 force;
		pOne->getPos(&force);
		force-= *anchor;

		real mag=force.norm();
		mag=real_abs(mag-restLen);
		mag*=k;

		force.normalize();
		force*=mag;
		pOne->addForce(force);
	}

	void pBuoyancy::updateForce(Particle * pOne, real dt, Particle * pTwo){
		real depth=pOne->getPos()[2];

		if(depth >= liquidHeight + maxDepth) return;

		Vector3 force(0,0,0);

		if(depth <= liquidHeight - maxDepth){
			force[2]=liquidDensity * volume;
			pOne->addForce(force);
			return;
		}

		force[2]=liquidDensity * volume *(depth - maxDepth - liquidHeight)/2 * maxDepth;
		pOne->addForce(force);
	}

	void pAnchoredFakeSpring::updateForce(Particle * pOne, real dt, Particle * pTwo){
		if(pOne->hasFiniteMass()) return;

		Vector3 pos;
		pOne->getPos(&pos);
		pos-= *anchor;

		real gamma=0.5 * real_sqrt(4*k-damping*damping);
		if(gamma==0) return;

		Vector3 c=pos*(damping/(2.0*gamma))+pOne->getVel()*(1.0/gamma);

		Vector3 target=pos*real_cos(gamma*dt)+c*real_sin(gamma*dt);
		target*=real_exp(-0.5*dt*damping);

		Vector3 accel=(target-pos)*(1.0/dt*dt)-pOne->getVel()*dt;
		pOne->addForce(accel*pOne->getMass());
	}

	void pLinearMotor::updateForce(Particle * pOne, real dt, Particle * pTwo){
		if((maxVel==0) || (maxVel<pOne->getVel().norm())){
			pOne->addForce(dir->normalized()*force);
		}
	}
};

