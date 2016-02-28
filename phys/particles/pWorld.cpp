/*
 * pWorld.cpp
 *
 *  Created on: 01/11/2014
 *      Author: K17K47
 */

#include "pForceGen.h"
#include "pContacts.h"
#include "pWorld.h"

namespace Phys {
	pWorld::pWorld(){
		resolver= new pCResolver();
		pFGRegistry=new pFGenReg();
	}

	pWorld::~pWorld(){
		delete resolver;
		delete pFGRegistry;
	}

	void pWorld::addForce(unsigned int index, const Vector3 &force){forceAcc[index] +=force;}
	void pWorld::setPos(unsigned int index, const Vector3 &p){pos[index]=p;}
	void pWorld::setVel(unsigned int index, const Vector3 &v){vel[index]=v;}
	void pWorld::setAcc(unsigned int index, const Vector3 &a){acc[index]=a;}
	void pWorld::setMass(unsigned int index, const real &m){invMass[index]=1/m;}
	Vector3 pWorld::getPos(unsigned int index){return pos[index];}
	Vector3 pWorld::getVel(unsigned int index){return vel[index];}
	Vector3 pWorld::getAcc(unsigned int index){return acc[index]+forceAcc[index]*invMass[index];}
	real pWorld::getMass(unsigned int index) const{if(invMass[index]==0){return REAL_MAX;}else{return ((real)1.0)/invMass[index];}}
	real pWorld::getInvMass(unsigned int index) const{return invMass[index];}
	void pWorld::getPos(unsigned int index, Vector3 *p) const{*p=pos[index];}
	void pWorld::getVel(unsigned int index, Vector3 *v) const{*v=vel[index];}
	void pWorld::getAcc(unsigned int index, Vector3 *a) const{*a=acc[index]+forceAcc[index]*invMass[index];}
	bool pWorld::hasFiniteMass(unsigned int index) const{return invMass[index]>=0.0;}

	unsigned int pWorld::addParticle(real mass, Vector3 position, Vector3 velocity, Vector3 acceleration){
		pos.push_back(position);
		vel.push_back(velocity);
		acc.push_back(acceleration);
		invMass.push_back(1.0f/mass);
		forceAcc.push_back(Vector3::Zero());
		return pos.size()-1;
	}

	void pWorld::clear(){
		pos.clear();
		vel.clear();
		acc.clear();
		invMass.clear();
		forceAcc.clear();
	}

	unsigned pWorld::generateContacts(){
		unsigned limit=maxContacts;
		pContact *nextContact=contacts;

		for(pContactGens::iterator g=pCGens.begin(); g!=pCGens.end(); g++){
			unsigned used=(*g)->addContact(nextContact, limit);
			limit-=used;
			nextContact+=used;
			if(limit<=0) break;
		}
		return maxContacts-limit;
	}

	void pWorld::integrate(real dt){
		/*for(int p=0; p<; p++){
			(*p)->integrate(dt);
		}
		dbVector3 estado;
		estado.p = pos;
		estado.v = vel;

		dbVector3 a = evaluate(estado, 0.0f, dbVector3());
		dbVector3 b = evaluate(estado, 0.5*dt, a);
		dbVector3 c = evaluate(estado, 0.5*dt, b);
		dbVector3 d = evaluate(estado, dt, c);

		const Vector3 dxdt = (a.p +(b.p + c.p)*2 + d.p)*(1.0f/6.0f);
		const Vector3 dvdt = (a.v +(b.v + c.v)*2 + d.p)*(1.0f/6.0f);

		pos+=dxdt * dt;
		vel+=dvdt * dt;
		*/
		//av=getAcc(i);
		//b.p=vel[i]+av*0.5*dt;
		//bv=getAcc(i);
		//c.p=vel[i]+bv*0.5*dt;
		//
		//a.p=vel[i];
		//d.p=vel[i]+cv*dt;

		//pos+=(((2*vel[i]+getAcc(i)*dt)*2+2*vel[i]+getAcc(i)*dt)*(1.0f/6.0f))*dt;
		//pos+=((6*vel[i]+3*getAcc(i)*dt)*(1.0f/6.0f))*dt;
		//pos+=((2*vel[i]+getAcc(i)*dt)*(1.0f/2.0f))*dt;

		//vel+=((getAcc+(getAcc+getAcc)*2+getAcc)*(1.0f/6.0f))*dt;
		//vel+=((4*getAcc+2*getAcc)*(1.0f/6.0f))*dt;
		//vel+=(6*getAcc*(1.0f/6.0f))*dt;
		//pos+=((a.p +(b.p + c.p)*2 + d.p)*(1.0f/6.0f))*dt;	//(dx/dt) * dt = x
		//vel+=((a.v +(b.v + c.v)*2 + d.p)*(1.0f/6.0f))*dt;	//(dv/dt) * dt = v
		unsigned int possize=pos.size();
		std::vector<Vector3> tmpAcc(possize);

		for(unsigned int i=0;i<possize;i++){
			tmpAcc[i]=forceAcc[i]*invMass[i];
			forceAcc[i]=Vector3::Zero();
		}

		for(unsigned int i=0;i<possize;i++) tmpAcc[i]=(acc[i]+tmpAcc[i])*dt;

		for(unsigned int i=0;i<possize;i++){
			pos[i]+=(2*vel[i]+tmpAcc[i])*0.5*dt;
			vel[i]+=tmpAcc[i];
		}
	}

	void pWorld::runPhysics(real dt){
		pFGRegistry->updateForces(dt, this);
		integrate(dt);

		unsigned usedContacts=generateContacts();
		if(usedContacts){
			if(!iterations) resolver->setIterations(usedContacts*2);
			resolver->resolveContacts(contacts, usedContacts, dt);
		}
	}
}; /* namespace phys */
