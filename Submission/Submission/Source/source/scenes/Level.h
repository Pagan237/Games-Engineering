#pragma once

#include "engine.h"

class Level : public Scene
{
public:
	void Load() override;
	void Update(const double& dt)override;
	void Unload()override;
	void Render()override;
};