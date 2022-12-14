#pragma once
#include "Scene.h"
#include "../components/AIControllerPaddleComponent.h"

#include <cstdint>
class AIControllerPaddleSystem
{

private:

	Scene* scene;
	std::vector<std::pair<uint32_t, AIControllerPaddleComponent>> components;
	TransformComponent* ballTransform;
public:

	void AddComponent(uint32_t id, float paddleSpeed, float topBound, float bottomBound);

	void Init(Scene* scene);
	void SetBallTransform(TransformComponent* ball) { ballTransform = ball; }
	void Update(float deltaTime);
};