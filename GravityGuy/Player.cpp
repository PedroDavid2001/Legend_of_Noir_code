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
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Spikes.h"
#include "Level4.h"
#include "BossLVL1.h"
#include "Bullet.h"
#include "Enemies.h"
#define PLAYER_VELOCITY	350.0f

// ---------------------------------------------------------------------------------

Player::Player(float scale)
{
	this->scale = scale;
	type = PLAYER;
	hp = 4;
    tileset = new TileSet("Resources/player.png", 70, 70, 9, 108);
    anim = new Animation(tileset, 0.16f, true);
	
	uint idle[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	uint idleInv[9] = { 9, 10, 11, 12, 13, 14, 15, 16, 17 };
	uint run[8] = { 18, 19, 20, 21, 22, 23, 24, 25 };
	uint runInv[8] = { 28, 29, 30, 31, 32, 33, 34, 35 };
	uint jump[5] = { 36, 37, 38, 39, 40 };
	uint jumpInv[5] = { 49, 48, 47, 46, 45 };
	uint atk[27] = { 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80 };
	uint atkInv[27] = { 89, 88, 87, 86, 85, 84, 83, 82, 81, 98, 97, 96, 95, 94, 93, 92, 91, 90, 107, 106, 105, 104, 103, 102, 101, 100, 99 };
	uint atkJump[7] = { 108, 109, 110, 111, 112, 113, 114 };
	uint atkJumpInv[7] = { 125, 124, 123, 122, 121, 120, 119 };

	anim->Add(MOVE, run, 8);
	anim->Add(IDLE, idle, 9);
	anim->Add(MOVE_INV, runInv, 8);
	anim->Add(IDLE_INV, idleInv, 9);
	anim->Add(ATACK, atk, 27);
	anim->Add(ATACK_INV, atkInv, 27);
	anim->Add(JUMP, jump, 5);
	anim->Add(JUMP_INV, jumpInv, 5);
	anim->Add(ATK_JMP, atkJump, 7);
	anim->Add(ATK_JMP_INV, atkJumpInv, 7);

    // cria bounding box
    BBox( new Rect(
		-1.0f * this->Width() / 3.0f,
		-1.0f * this->Height() / 2.0f,
		this->Width() / 3.0f,
		this->Height() / 2.0f
	));
    
    // inicializa estado do player
	state = IDLE;
	gravity = 0.0f;
	shooted = false;
	left = false;
	right = false;
	canJump = true;
	direction = true;	//começa virado para direita
	
    // posição inicial
    MoveTo( 200.0f * scale, ( 560.0f * scale ) - ( this->Height() / 2.0f ), Layer::MIDDLE);

	//starta a posição inicial no arquivo main
	GravityGuy::playerPos = this->X();
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
	MoveTo( 200.0f * scale, (560.0f * scale) - (this->Height() / 2.0f), Layer::MIDDLE);
	state = IDLE;
	gravity = 0.0f;
	left = false;
	right = false;
	canJump = true;
	direction = true;	//começa virado para direita
	
	//restarta a posição inicial no arquivo main
	GravityGuy::playerPos = this->X();
}


// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
	if (obj->type == PLATFORM) {
		Platform* plat = (Platform*)obj;

		if (plat->platType != SIGN) {
			float lftDiff = this->Right() - plat->Left();
			float rgtDiff = this->Left() - plat->Right();

			if (rgtDiff < 0)
				rgtDiff = -rgtDiff;

			if (lftDiff < 0)
				lftDiff = -lftDiff;

			//down (dentro das extremidades)
			if (this->Bottom() >= plat->Top() && this->Left() >= plat->Left() && this->Right() <= plat->Right()) {
				if ((state != JUMP && state != JUMP_INV)) {
					MoveTo(x, (plat->Top() - (this->Height() / 2.0f)));
					canJump = true;
				}

				if (plat->platType == PLAT_150X50_MOBILE_H && (state == IDLE || state == IDLE_INV))
					Translate(100.0f * plat->direcao * gameTime, 0);
			}
			//down (além das extremidades)
			else if (this->Y() <= plat->Top() && this->Bottom() <= plat->Y()) {
				if ((state != JUMP && state != JUMP_INV)) {
					gravity = 0.0f;
					MoveTo(x, (plat->Top() - (this->Height() / 2.0f)));
					canJump = true;
				}
				if (plat->platType == PLAT_150X50_MOBILE_H && (state == IDLE || state == IDLE_INV))
					Translate(100.0f * plat->direcao * gameTime, 0);
			}
			//right
			else if (this->Right() >= plat->Left() && this->Left() < plat->Left()) {
				if ((state != JUMP && state != JUMP_INV))
					MoveTo((plat->Left() - this->Width() / 2.0f), y);

				right = false;
			}
			//left
			else if (this->Left() <= plat->Right() && this->Right() > plat->Right()) {
				if ((state != JUMP && state != JUMP_INV))
					MoveTo((plat->Right() + this->Width() / 2.0f), y);

				left = false;
			}
		}
		else {
			showCtrls = true;
		}
		
	}
	else if (obj->type == SPIKE) {
		Spikes* spk = (Spikes*)obj;
		if (!spk->touched) {
			hp--;
			spk->touched = true;
		}
	}else if (obj->type == ENEMYS) {
		Enemies* enemies = (Enemies*)obj;
		if (!enemies->touched) {
			hp--;
			enemies->touched = true;
			enemies->time.Start();

		}
	}
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	if (hp > 0)
	{
		score += 1 * gameTime;

	}

	//controla o delay dos diferentes estados 
	if (state == IDLE || state == IDLE_INV)
		anim->Delay(0.16f);
	else if (state == MOVE || state == MOVE_INV)
		anim->Delay(0.08f);
	else if (state == JUMP || state == JUMP_INV)
		anim->Delay(0.125f);
	else if (state == ATACK || state == ATACK_INV)
		anim->Delay(0.012f);
	else if (state == ATK_JMP || state == ATK_JMP_INV)
		anim->Delay(0.08f);
	
	//impede de sair da tela
	if (this->Left() <= 0) {
		left = false;
	}
	if (this->Right() >= window->Width()) {
		right = false;
	}

	// ------------------------------------------------------------------------
	// detecção de movimento
	// ------------------------------------------------------------------------
	
	if ((state != ATACK && state != ATACK_INV) && (state != ATK_JMP && state != ATK_JMP_INV)) {
		if ((window->KeyDown(VK_RIGHT) || window->KeyDown('D')) && (window->KeyDown(VK_LEFT) || window->KeyDown('A'))) {
			//parado
			if ((state != JUMP && state != JUMP_INV)) {
				if (direction)
					state = IDLE;
				else
					state = IDLE_INV;
			}

			GravityGuy::platform_velocity = 0;
		}
		else if (right && (window->KeyDown(VK_RIGHT) || window->KeyDown('D'))) {

			if ((state != JUMP && state != JUMP_INV))
				state = MOVE;
			direction = true;

			if (GravityGuy::playerRgt)
				Translate(PLAYER_VELOCITY * scale * gameTime, 0);
			else {
				GravityGuy::platform_velocity = -200.0f * scale;
			}

			GravityGuy::playerPos += PLAYER_VELOCITY * scale * gameTime;//atualiza a posição relativa do player

		}
		else if (left && (window->KeyDown(VK_LEFT) || window->KeyDown('A'))) {

			if ((state != JUMP && state != JUMP_INV))
				state = MOVE_INV;
			direction = false;

			if (GravityGuy::playerLft)
				Translate(-PLAYER_VELOCITY * scale * gameTime, 0);
			else {
				GravityGuy::platform_velocity = 200.0f * scale;
			}

			GravityGuy::playerPos -= PLAYER_VELOCITY * scale * gameTime;//atualiza a posição relativa do player
		}
		else {
			//parado
			if ((state != JUMP && state != JUMP_INV)) {
				if (direction)
					state = IDLE;
				else
					state = IDLE_INV;
			}

			GravityGuy::platform_velocity = 0;
		}
	}
	else {
		GravityGuy::platform_velocity = 0;
	}
	
	// ------------------------------------------------------------------------
	// detecção de pulo
	// ------------------------------------------------------------------------
	
	if ((state != JUMP && state != JUMP_INV) && (state != ATACK && state != ATACK_INV) && (state != ATK_JMP && state != ATK_JMP_INV)) {

		if (window->KeyPress(VK_SPACE) && canJump) {
			canJump = false;
			
			//setta estado do player
			if (direction)
				state = JUMP;
			else
				state = JUMP_INV;

			jumpForce = 600.0f * this->scale;
			
			//inicia timer do pulo
			jumpTimer.Start();								
		}
	}
	else if ((state == ATK_JMP || state == ATK_JMP_INV || state == JUMP || state == JUMP_INV) && jumpTimer.Elapsed() < 0.4f) {
		Translate(0, -jumpForce * gameTime);
	
		//força do pulo vai decaindo a cada iteração
		jumpForce -= 300.0f * this->scale * gameTime;

	}
	else if (( state == JUMP || state == JUMP_INV ) && jumpTimer.Elapsed(0.4f)) {
		//finalizou o pulo
		if (direction)
			state = IDLE;
		else
			state = IDLE_INV;

		jumpTimer.Stop();
		jumpTimer.Reset();
	}
	
	// ------------------------------------------------------------------------
	// detecção de disparo
	// ------------------------------------------------------------------------

	if ((window->KeyPress('Z') || window->KeyPress('K')) && state != ATACK && state != ATACK_INV && state != ATK_JMP && state != ATK_JMP_INV) {
		
		if ((state != JUMP && state != JUMP_INV)) {
			
			if (direction)
				state = ATACK;
			else
				state = ATACK_INV;
		}
		else {
			if (direction)
				state = ATK_JMP;
			else
				state = ATK_JMP_INV;
		}
		
	}

    if(state != JUMP && state != JUMP_INV && (state != ATK_JMP && state != ATK_JMP_INV))
		// ação da gravidade sobre o personagem 
		Translate(0, gravity * scale * gameTime);

	right = true;
	left = true;
	gravity = 600.0f;
	showCtrls = false;

    // atualiza animação
    anim->Select(state);
    anim->NextFrame();

	if (anim->Frame() == 80 || anim->Frame() == 100 || anim->Frame() == 114 || anim->Frame() == 119) {
		if (direction)
			state = IDLE;
		else
			state = IDLE_INV;
		shooted = false;
	}
	if (!shooted && (anim->Frame() == 103 || anim->Frame() == 76 || anim->Frame() == 113 || anim->Frame() == 120)) {

		Bullet* bullet = nullptr;
		GravityGuy::audio->Play(ARROW_FX, false);

		if (direction)
			bullet = new Bullet(true, scale);
		else
			bullet = new Bullet(false, scale);

		//verifica qual o level atual para decidir qual irá receber o objeto bullet
		if (GravityGuy::currentLvl == LEVEL_1 && bullet != nullptr)
			Level1::scene->Add(bullet, MOVING);
		else if (GravityGuy::currentLvl == LEVEL_2 && bullet != nullptr)
			Level2::scene->Add(bullet, MOVING);
		else if (GravityGuy::currentLvl == LEVEL_3 && bullet != nullptr)
			Level3::scene->Add(bullet, MOVING);
		else if (GravityGuy::currentLvl == LEVEL_4 && bullet != nullptr)
			Level4::scene->Add(bullet, MOVING);
		else if (GravityGuy::currentLvl == BOSS_LEVEL && bullet != nullptr)
			BossLVL1::scene->Add(bullet, MOVING);
		shooted = true;
	}

}

// ---------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------