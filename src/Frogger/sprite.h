
#pragma once
#include "ID.hh"
#include "Renderer.hh"
#include "Transform.hh"

// model (struct), per fer els sprites.
struct Sprite {
	Transform transform;
	ObjectID objectID;
	void Draw() { R.Push(objectID, transform); };
};