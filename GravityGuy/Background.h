/**********************************************************************************
// Background (Arquivo de Cabeçalho)
// 
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plano de fundo do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_BACKGROUND_H_
#define _GRAVITYGUY_BACKGROUND_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // background é composto por sprites

// ---------------------------------------------------------------------------------

class Background : public Object
{
private:
    float posC1, posC2;                         //posição horizontal das nuvens
	float posB11, posB12;							//posição horizontal dos primeiros predios
	float posB21, posB22;							//posição horizontal dos predios do meio
	float posB31, posB32;							//posição horizontal dos predios de tras
	

    Sprite * sky;                       // fundo estático

    Sprite * clouds1;                   // nuvens dinamicas
    Sprite * clouds2; 
	
	
	Sprite * build_11; //predios mais proximos
	Sprite * build_12;
	
	Sprite* build_21; //predios do meio
	Sprite* build_22;

	Sprite * build_31; //predios mais distantes
	Sprite * build_32;

    Color color;                        // cor do pano de fundo

public:
    Background(Color tint);             // construtor
    ~Background();                      // destrutor

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
}; 

// ---------------------------------------------------------------------------------

#endif