/*
 * particle.cpp
 *
 *  Created on: 29/05/2014
 *      Author: K17K47
 */

#include "particle.h"
namespace phys{
	void Particle::addForce(const Vector3 &force){forceB +=force;}
	void Particle::setPos(const Vector3 &p){pos=p;}
	void Particle::setVel(const Vector3 &v){vel=v;}
	void Particle::setAcc(const Vector3 &a){acc=a;}
	void Particle::setMass(const real &m){msInv=1/m;}
	Vector3 Particle::getPos(){return pos;}
	Vector3 Particle::getVel(){return vel;}
	Vector3 Particle::getAcc(){Vector3 a=acc + forceB * msInv; if(grav)a+=Vector3(0,-9.806,0); return a;}
	real Particle::getMass() const{if(msInv==0){return REAL_MAX;}else{return ((real)1.0)/msInv;}}
	real Particle::getInvMass() const{return msInv;}
	void Particle::getPos(Vector3 *p) const{*p=pos;}
	void Particle::getVel(Vector3 *v) const{*v=vel;}
	void Particle::getAcc(Vector3 *a) const{*a=acc + forceB * msInv; if(grav)*a+=Vector3(0,-9.806,0);}
	bool Particle::hasFiniteMass() const{return msInv>=0.0;}
	void Particle::clearForceBuffer(){forceB.setZero();}

	dbVector3 Particle::evaluate(const dbVector3 &inicio, real dt, const dbVector3 &d){
		dbVector3 out;
		//Vector3 x = inicio.p + d.p * dt;
		out.p = inicio.v + d.v * dt;
		out.v = getAcc();
		return out;
	}

	void Particle::integrate(real dt){ //TODO: Implement in OpenCL, to permit GPGPU sim. acceleration
		dbVector3 estado;
		estado.p = pos;
		estado.v = vel;

		dbVector3 a = evaluate(estado, 0.0f, dbVector3());
		dbVector3 b = evaluate(estado, 0.5*dt, a);
		dbVector3 c = evaluate(estado, 0.5*dt, b);
		dbVector3 d = evaluate(estado, dt, c);

		/*
		const Vector3 dxdt = (a.p +(b.p + c.p)*2 + d.p)*(1.0f/6.0f);
		const Vector3 dvdt = (a.v +(b.v + c.v)*2 + d.p)*(1.0f/6.0f);

		pos+=dxdt * dt;
		vel+=dvdt * dt;
		*/

		pos+=((a.p +(b.p + c.p)*2 + d.p)*(1.0f/6.0f))*dt;	//(dx/dt) * dt = x
		vel+=((a.v +(b.v + c.v)*2 + d.p)*(1.0f/6.0f))*dt;	//(dv/dt) * dt = v

		clearForceBuffer();
	}
};
