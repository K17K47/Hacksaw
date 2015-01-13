/*
 * scene.cpp
 *
 *  Created on: 29/11/2014
 *      Author: K17K47
 */

#include <rndr/scene.h>

namespace Rndr {

	void Scene::addCamera(Camera* cam){
		Scene::cameras.push_back(cam);
		Scene::nCameras++;
	}

	void Scene::addObject(Object* obj){
		Scene::objects.push_back(obj);
		Scene::nObjects++;
	}

	Camera* Scene::getActiveCamera(){ return activeCamera;}
	void Scene::setActiveCamera(Camera* camera){ activeCamera=camera;}

} /* namespace Rndr */
