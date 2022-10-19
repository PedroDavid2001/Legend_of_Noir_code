/**********************************************************************************
// Player (Arquivo de Cabeçalho)
//
// Criação:     20 Abr 2012
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para o jogador
//
**********************************************************************************/

#ifndef _GRAVITYGUY_ENDLEVEL_H_
#define _GRAVITYGUY_ENDLEVEL_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animação de sprites
#include "TileSet.h"
#include "GravityGuy.h"

// ------------------------------------------------------------------------------

class EndLevel : public Object
{
private:
	TileSet* tileset;						// folha de sprites do personagem
	Animation* anim;						// animação do personagem

public:

	EndLevel(float x, float y);								// construtor
	~EndLevel();							// destrutor

	void Update();							// atualização do objeto
	void Draw();							// desenho do objeto
	float Width();
	float Height();
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void EndLevel::Draw()
{
	anim->Draw(x, y, z, GravityGuy::totalScale);
}

inline float EndLevel::Height()
{
	return tileset->TileHeight() * GravityGuy::totalScale;
}

inline float EndLevel::Width()
{
	return tileset->TileWidth() * GravityGuy::totalScale;
}

// ---------------------------------------------------------------------------------

#endif