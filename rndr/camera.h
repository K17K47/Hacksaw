/*
 * camera.h
 *
 *  Created on: 29/11/2014
 *      Author: K17K47
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include<mathHelper.h>

namespace Rndr {

	class Camera {
		public:
			Vector3 pos;
			Quaternion rot;
		public:
			Camera(Vector3 pos, Quaternion rot): pos(pos), rot(rot) {};
	};

} /* namespace Rndr */

#endif /* CAMERA_H_ */
