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

#ifndef _GRAVITYGUY_PLAYER_H_
#define _GRAVITYGUY_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // animação de sprites

// ------------------------------------------------------------------------------

enum PlayerState { IDLE, MOVE, JUMP, ATACK, HURT };         

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet   * tileset;                // folha de sprites do personagem
    Animation * anim;                   // animação do personagem
	uint		state;
	Timer		jumpTimer;				//timer usado para definir o tempo do pulo
    float       jumpForce;
    int         level;                  // nível finalizado
	bool        canJump;				//verifica se o player está sobre uma plataforma para poder pular
    bool        falling;                //verifica se existe algo abaixo do player
    float       scale;
	
public:
    Player(float scale);                // construtor
    ~Player();                          // destrutor
    
    float currentPos;                   //posição atual baseada na quantidade de terreno que já foi percorrido
    void Reset();                       // volta ao estado inicial
    int Level();                        // último nível finalizado
    float Bottom();                     // coordenadas da base
    float Top();                        // coordenadas do topo
    float Right();
    float Left();
    float Width();
    float Height();

    void OnCollision(Object * obj);     // resolução da colisão
    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline int Player::Level()
{ return level; }

inline float Player::Height()
{
    return tileset->TileHeight() * scale;
}

inline float Player::Width()
{
    return tileset->TileWidth() * scale;
}

inline float Player::Bottom()
{ 
    return y + ( tileset->TileHeight() / 2.0f );
}

inline float Player::Top()
{ 
    return y - ( tileset->TileHeight() / 2.0f );
}

inline float Player::Right()
{
    return x + ( tileset->TileWidth() / 2.0f );
}

inline float Player::Left()
{
    return x - ( tileset->TileWidth() / 2.0f );
}

inline void Player::Draw()
{ anim->Draw(x, y, z, scale); }

// ---------------------------------------------------------------------------------

#endif