/*
 * scene.h
 *
 *  Created on: 29/11/2014
 *      Author: K17K47
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <mathHelper.h>
#include <rndr/camera.h>
#include <rndr/object.h>

namespace Rndr {

	class Scene {
		public:
			unsigned int nObjects=0;
			std::vector<Object*> objects;
			unsigned int nCameras=0;
			std::vector<Camera*> cameras;
			//long unsigned int activeCamera;
			Camera* activeCamera;
		public:
			Camera* getActiveCamera();
			void setActiveCamera(Camera* camera);
			//long unsigned int getActiveCameraID();
			//void setActiveCameraByID(long unsigned int ID);
			void addObject(Object *obj);
			void addCamera(Camera *cam);
	};

} /* namespace Rndr */

#endif /* SCENE_H_ */
