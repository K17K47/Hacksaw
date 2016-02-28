/*
 * hsGame.h
 *
 *  Created on: 15/01/2015
 *      Author: K17K47
 */

#ifndef HSGAME_H_
#define HSGAME_H_

#include<hacksaw.h>

namespace Game {

	class hsGame {
		public:
			Phys::pWorld particleWorld;
			hsGame();
			~hsGame();
	};

} /* namespace Game */

#endif /* HSGAME_H_ */
