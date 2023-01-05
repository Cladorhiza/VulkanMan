#include "Scene.h"

Scene::Scene()
	:nextID(0), transformSystem{}, spriteSystem(&transformSystem)
{






}

Entity& Scene::GetEntity(uint32_t id) {
	if (entities.find(id) != entities.end()) {
		return entities.at(id);
	}
	std::cout << "Attempted to retrieve entity " << id << " from scene, DOESN'T EXIST.\n";
	Entity e{ 666666 };
	return e;
}

uint32_t Scene::AddEntity() {
	
	if (entities.find(nextID) == entities.end()) {
		entities[nextID] = Entity{ nextID };
	}
	nextID++;

	return nextID - 1;

}

void Scene::Init(Renderer* renderer) {

	spriteSystem.SetRenderer(renderer);

}

void Scene::MainLoop() {


}