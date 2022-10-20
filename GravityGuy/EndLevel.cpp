#include "EndLevel.h"

EndLevel::EndLevel(float x, float y) {

	tileset = new TileSet("Resources/level_end.png", 50, 60, 5, 5);
	anim = new Animation(tileset, 0.1f, true);

	// cria bounding box
	BBox(new Rect(
		-1.0f * this->Width() / 2.0f,
		-1.0f * this->Height() / 2.0f,
		this->Width() / 2.0f,
		this->Height() / 2.0f
	));

	MoveTo(x, y);
}

EndLevel::~EndLevel() {
	delete tileset;
	delete anim;
}							// destrutor

void EndLevel::Update() {
	if (!GravityGuy::playerRgt)
		Translate(GravityGuy::platform_velocity * gameTime, 0);
	if (!GravityGuy::playerLft)
		Translate(GravityGuy::platform_velocity * gameTime, 0);

	anim->NextFrame();
}