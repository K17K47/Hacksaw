/*
 * particle.h
 *
 *  Created on: 29/05/2014
 *      Author: K17K47
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "mathHelper.h"

namespace phys{
	class Particle{
		protected:
			Vector3 pos=Vector3::Zero(); 		//Posição
			Vector3 vel=Vector3::Zero(); 		//Velocidade
			Vector3 acc=Vector3::Zero(); 		//Aceleração
			Vector3 forceB=Vector3::Zero();	    //Acumulador de força
			bool grav=false; 					//sujeito à gravidade
			real dampingConst=1; 				//FixMe: Por tudo que é sagrado, tira isso aqui K17!
			real msInv; 						//Melhor armazenar o inverso da massa e economizar ciclos
		public:
			Particle();

		    Particle(Vector3 posicao, real amortecimento, real massa, bool gravity )
		    : pos(posicao), dampingConst(amortecimento), msInv(1/massa),grav(gravity) {}

            void addForce(const Vector3 &force);
		    void setPos(const Vector3 &p);
		    void setVel(const Vector3 &v);
		    void setAcc(const Vector3 &a);
		    void setMass(const real &m);
		    Vector3 getPos();
		    Vector3 getVel();
		    Vector3 getAcc();
		    real getMass() const;
		    real getInvMass() const;
		    void getPos(Vector3 *p) const;
		    void getVel(Vector3 *v) const;
		    void getAcc(Vector3 *a) const;
		    bool hasFiniteMass() const;
		    void clearForceBuffer();
		    dbVector3 evaluate (const dbVector3 &inicio, real dt, const dbVector3 &d);
		    void integrate(real dt);
	};
};


#endif /* PARTICLE_H_ */
