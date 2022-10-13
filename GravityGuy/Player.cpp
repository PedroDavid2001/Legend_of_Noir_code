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
    BBox( new Rect(
		-1.0f * this->Width() / 2.0f,
		-1.0f * this->Height() / 2.0f,
		this->Width() / 2.0f,
		this->Height() / 2.0f
	));
    
    // inicializa estado do player
	state = IDLE;
    level = 0;
	falling = false;
	canJump = true;

    // posição inicial
    MoveTo(window->CenterX(), ( 570.0f * scale ) - ( this->Height() / 2.0f ), Layer::MIDDLE);
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
	MoveTo(window->CenterX(), (570.0f * scale) - (this->Height() / 2.0f), Layer::MIDDLE);
    state = IDLE;
    level = 0;
}


// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
	Platform* plat = (Platform*)obj;
	
	canJump = true;
	
	float botDiff = this->Bottom() - plat->Top();
	float rgtDiff = this->Right() - plat->Left();
	float lftDiff = this->Left() - plat->Right();

	if (rgtDiff < 0)
		rgtDiff = -rgtDiff;
	if (botDiff < 0)
		botDiff = -botDiff;
	if (lftDiff < 0)
		lftDiff = -lftDiff;


	if (plat->Type() != 11) {
		//está sobre a plataforma
		if (this->Left() >= plat->Left() && this->Right() <= plat->Right()) {
			falling = false;
			MoveTo(x, (plat->Top() - (this->Height() )) - 1.0f);
		}
	}
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	if (jumpTimer.Elapsed(0.6f)){
		state = IDLE;
	}
	else {
		canJump = false;//não pode pular novamente até finalizar o atual
	}

	// ----------------------------------------------------------
	// Processa teclas pressionadas
	// ----------------------------------------------------------

	if (state != JUMP) {
		if (window->KeyDown(VK_RIGHT) || window->KeyDown('D')) {
			
			//impede o jogador de atravessar a tela
			if (this->Right() < window->Width())
				Translate( GravityGuy::playerRgtVel * gameTime, 0 );

			state = MOVE;

		}
		else if (window->KeyDown(VK_LEFT) || window->KeyDown('A')) {
			
			//impede o jogador de atravessar a tela
			if (this->Left() > 0)
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
			jumpForce = PLAYER_VELOCITY * 2.0f;
			
			//inicia timer do pulo
			jumpTimer.Start();								
		}
	}
	else if (state == JUMP) {
		Translate(0, -jumpForce * gameTime);
		falling = true; //pode cair, quando terminar o pulo

		//força do pulo vai decaindo a cada iteração
		jumpForce -= (PLAYER_VELOCITY / 2.0f) * gameTime;						

		//se estiver pulando, e, se mover em uma direção, vai alterar apenas a posição relativa
		if (window->KeyDown(VK_RIGHT) || window->KeyDown('D')) {

			//impede o jogador de atravessar a tela
			if (this->Right() < window->Width())
				Translate(GravityGuy::playerRgtVel * gameTime, 0);
		}
		else if (window->KeyDown(VK_LEFT) || window->KeyDown('A')) {
			
			//impede o jogador de atravessar a tela
			if (this->Left() > 0)
				Translate(-GravityGuy::playerLftVel * gameTime, 0);
		}
	}

    if(state != JUMP && falling)
		// ação da gravidade sobre o personagem não afeta durante o pulo
		Translate(0, PLAYER_VELOCITY * 2.0f * gameTime);
       
    // atualiza animação
    anim->Select(state);
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------