/**********************************************************************************
// Platform (Código Fonte)
// 
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#include "GridSet.h"
#include "BombZombie.h"

// ---------------------------------------------------------------------------------

GridSet::GridSet(float posX, float posY, uint i, uint j, uint index, uint type)
{ 
    tileSet = new TileSet("Resources/box.png", 40, 40, 8, 8);
    anim = new Animation(tileSet, 0.05f, false);

    door = new Sprite("Resources/door.png");
    
    medkit = new Sprite("Resources/medkit.png");
    extExplo = new Sprite("Resources/explosion-plus.png");
    moreBomb = new Sprite("Resources/bomb-plus.png");
    
    objPosExp = 0;
    
    uint normal[1] = { 0 };
    uint exploded[7] = { 1,2,3,4,5,6,7 };
    
    anim->Add(0, normal, 1);
    anim->Add(1, exploded, 7);

    this->i = i;
    this->j = j;
    this->type = type;
	this->index = index;
    destroyed = false;

    BBox(new Rect(-20, -20, 20, 20));
    MoveTo(posX, posY,Layer::LOWER);
}

// ---------------------------------------------------------------------------------

void GridSet::OnCollision(Object* obj) {

    float xDiff = x - obj->X();
    float yDiff = y - obj->Y();

    if (xDiff < 0)
        xDiff = -xDiff;
    if (yDiff < 0)
        yDiff = -yDiff;

	if (type == OBSTACLE) 
		if (obj->Type() == EXPLOSION) 
            if (yDiff < 38.0f && xDiff < 38.0f)
                destroyed = true;

    //destrói o item caso colida com uma explosão
    if (type == GRID && objPosExp > 1)
        if (obj->Type() == EXPLOSION)
            if (yDiff < 38.0f && xDiff < 38.0f)
                objPosExp = 0;
}

// ---------------------------------------------------------------------------------

GridSet::~GridSet()
{
    delete anim;
    delete tileSet;
    delete door;
    delete medkit;
    delete extExplo;
    delete moreBomb;
}

// ---------------------------------------------------------------------------------

void GridSet::Update() {
    if (anim->Frame() == 7)
        this->type = GRID;

    if (!destroyed)
        anim->Select(0);
    else {
        anim->Select(1);
    }
    anim->NextFrame();
}