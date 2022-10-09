/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:     20 Abr 2012
// Atualização: 27 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Define uma classe para o jogador 
//
**********************************************************************************/

#include "Player.h"
#include "Platform.h"
#include "Timer.h"
#include "GravityGuy.h"

// ---------------------------------------------------------------------------------

Player::Player(float scale)
{
	this->scale = scale;
    tileset = new TileSet("Resources/GravityGuy.png", 70, 80, 5, 5);
    anim = new Animation(tileset, 0.120f, true);
	
	uint moving[4] = { 1,2,3,4 };
	uint jump[1] = { 0 };
	uint idle[1] = { 0 };

	anim->Add(MOVE, moving, 4);
	anim->Add(IDLE, idle, 1);
	anim->Add(JUMP, jump, 1);

    // cria bounding box
    BBox(new Rect(
			( - 1.0f * tileset->TileWidth() / 2.0f) * GravityGuy::totalScale,
			( -1.0f * tileset->TileHeight() / 2.0f) * GravityGuy::totalScale,
			( tileset->TileWidth() / 2.0f)          * GravityGuy::totalScale,
			( tileset->TileHeight() / 2.0f)         * GravityGuy::totalScale ));
    
    // inicializa estado do player
	state = IDLE;
    level = 0;

    // posição inicial
    MoveTo(window->CenterX(), 24.0f, Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete anim;
    delete tileset;    
}

// ---------------------------------------------------------------------------------

void Player::Reset()
{
    // volta ao estado inicial
    MoveTo(window->CenterX(), 24.0f, Layer::MIDDLE);
    state = IDLE;
    level = 0;
}


// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
    
    if (obj->Type() == FLOOR)
    {
		Platform* plat = (Platform*)obj;
		canJump = true;
		//mantém sobre o chão
		MoveTo(x, plat->Y() - ((( plat->Height() / 2.0f ) + ( this->tileset->TileHeight() / 2.0f )) * GravityGuy::totalScale));
	}
	else {

		Platform* plat = (Platform*)obj;
		canJump = true;
		//mantém sobre a plataforma
		MoveTo(x, obj->Y() - (((plat->Height() / 2.0f) + (this->tileset->TileHeight() / 2.0f)) * GravityGuy::totalScale));
	}
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	if (jumpTimer.Elapsed(0.5f))
		state = IDLE;
	else {
		canJump = false;//não pode pular novamente até finalizar o atual
	}

	// ----------------------------------------------------------
	// Processa teclas pressionadas
	// ----------------------------------------------------------

	if (state != JUMP) {
		if (window->KeyDown(VK_RIGHT) || window->KeyDown('D')) {
			
			//impede o jogador de atravessar a tela
			if (x + ((tileset->TileWidth() * GravityGuy::totalScale) / 2.0f) < window->Width())
				Translate( GravityGuy::playerRgtVel * gameTime, 0 );

			state = MOVE;

		}
		else if (window->KeyDown(VK_LEFT) || window->KeyDown('A')) {
			
			//impede o jogador de atravessar a tela
			if (x - ((tileset->TileWidth() * GravityGuy::totalScale) / 2.0f) > 0)
				Translate( -GravityGuy::playerLftVel * gameTime, 0 );
			
			state = MOVE;
		}
		else {
			state = IDLE;
		}

		//independente do estado, se o jogador apertar espaço, o boneco deve pular!!
		if (window->KeyPress(VK_SPACE) && canJump) {
			
			//setta estado do player
			state = JUMP;									
			jumpForce = PLAYER_VELOCITY * 1.5f;

			//inicia timer do pulo
			jumpTimer.Start();								
		}
	}
	else if (state == JUMP) {
		Translate(0, -jumpForce * gameTime);

		//força do pulo vai decaindo a cada iteração
		jumpForce -= (PLAYER_VELOCITY / 2.0f) * gameTime;						

		//se estiver pulando, e, se mover em uma direção, vai alterar apenas a posição relativa
		if (window->KeyDown(VK_RIGHT) || window->KeyDown('D')) {

			//impede o jogador de atravessar a tela
			if (x + ((tileset->TileWidth() * GravityGuy::totalScale) / 2.0f) < window->Width())
				Translate(GravityGuy::playerRgtVel * gameTime, 0);
		}
		else if (window->KeyDown(VK_LEFT) || window->KeyDown('A')) {
			
			//impede o jogador de atravessar a tela
			if (x - ((tileset->TileWidth() * GravityGuy::totalScale) / 2.0f) > 0)
				Translate(-GravityGuy::playerLftVel * gameTime, 0);
		}
	}

    if(state != JUMP)
		// ação da gravidade sobre o personagem não afeta durante o pulo
		Translate(0, PLAYER_VELOCITY * gameTime);
        
    // atualiza animação
    anim->Select(state);
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------