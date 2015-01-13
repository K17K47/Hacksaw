/*
 * object.h
 *
 *  Created on: 29/11/2014
 *      Author: K17K47
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <mathHelper.h>
#include <rndr/model.h>

namespace Rndr {

	class Object {
		public:
			Vector3* pos;
			Quaternion* rot;
			Vector3* scale;
			Model* model;
			long int ID;
	};

} /* namespace Rndr */

#endif /* OBJECT_H_ */
