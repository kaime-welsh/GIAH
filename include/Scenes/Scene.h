#pragma once
class Scene
{
public:
	virtual void Load() {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual void Unload() {}
	virtual ~Scene() {}
};