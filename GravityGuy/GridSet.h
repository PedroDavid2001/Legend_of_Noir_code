/**********************************************************************************
// Platform (Arquivo de Cabeçalho)
// 
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#ifndef _BOMBZOMBIE_GRIDSET_H_
#define _BOMBZOMBIE_GRIDSET_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "TileSet.h"                     // background é composto por sprites
#include "Animation.h" 
#include "Sprite.h"

enum posExp { DOOR = 1, MEDKIT, MORE_BOMBS, EXTEND_EXPLOSION };
/**
 * Possíveis objetos que PODEM surgir após o obstáculo ser destruídos, 
 * iniciados em 1 para que o zero seja um estado sem objeto.
**/

class GridSet : public Object
{
private:
    TileSet*    tileSet     = nullptr;      //tileset do obstáculo
    Animation*  anim        = nullptr;
    
    Sprite*     door        = nullptr;      //sprite da porta de passagem 
    
    Sprite*     extExplo    = nullptr;      //sprite do item extend explosion
    Sprite*     medkit      = nullptr;      //sprite do medkit
    Sprite*     moreBomb    = nullptr;      //sprite do item more bombs
                 
public:
    uint i;
    uint j;
    uint index;
    uint objPosExp;

    bool destroyed;
    
    GridSet(float posX, float posY, uint i, uint j, uint index, uint type);
    ~GridSet();

    void Update();                      // atualização do objeto
	void OnCollision(Object* obj);
    void Draw();                        // desenho do objeto
}; 

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void GridSet::Draw(){
    if (type == OBSTACLE)
        anim->Draw(x, y, z);
    else {
        if (objPosExp == 1)
            door->Draw(x, y, z);
        else if (objPosExp == 2)
            medkit->Draw(x, y, z);
        else if (objPosExp == 3)
            moreBomb->Draw(x, y, z);
        else if (objPosExp == 4)
            extExplo->Draw(x, y, z);
    }
}

// ---------------------------------------------------------------------------------

#endif