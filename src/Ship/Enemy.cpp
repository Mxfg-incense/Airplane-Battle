#include "GameObjects.h"
#include "Enemy.h"
#include "GameWorld.h"
#include "Goodie.h"
#include "Projectile.h"
#include "Others.h"
//Enenmy 


Enemy::Enemy(int imageID,GameWorld* w,int hp,int energy,int atk,int speed,int bonus):
	Ship(imageID,randInt(0,WINDOW_WIDTH-1),WINDOW_HEIGHT-1,  180 ,hp,energy, w)
	,atk(atk),speed(speed),bonus(bonus) {}

bool Enemy::isenemy() {
	return true;
}

void Enemy::after_die() {
	Get_in_world()->add_destroyed();
	Get_in_world()->Minus_onscreen();
	Get_in_world()->append_explosion(new Explosion(GetX(), GetY(), Get_in_world()));
	Get_in_world()->IncreaseScore(bonus);
	die_drop();
}

int Enemy::Get_atk() const {
	return atk;
}

void Enemy::getStrategy() {
	if(stratagy<=0) {
		stratagy_kind = randInt(1, 3);
		stratagy = randInt(10, 50);
	} 
	else if (GetX()<0) {
		stratagy_kind = 2;
		stratagy = randInt(10, 50);
	}
	else if(GetX()>=WINDOW_WIDTH){
		stratagy_kind = 3;
		stratagy = randInt(10, 50);
	}
}

void Enemy::applyStrategy() {
	--stratagy;
	int x = GetX(), y = GetY();
	switch (stratagy_kind)
	{
	case 1:
		MoveTo(x, y - speed);
		break;
	case 2:
		MoveTo(x + speed, y-speed);
		break;
	case 3:
		MoveTo(x - speed, y-speed);
		break;
	}
}

void Enemy::Update() {
	if(Get_destory())
		return;
	int x = GetX(), y = GetY();
	auto world = Get_in_world();
	if(y<0) {
		set_die();
		world->Minus_onscreen();
		return;
	}
	//Check the collison with the projectile and the player
	world->Collision_Handling(this,20);
	if(Get_destory())return;
	//try to lauch the red
	lauch_projectile();
	//sprint
	sprint();
	//move
	getStrategy(); 
	applyStrategy();
	

	world->Collision_Handling(this, 20);
}

void Enemy::lauch_projectile() {}

void Enemy::sprint() {}

void Enemy::die_drop(){}

void Enemy::setspeed(int x) {
	speed = x;
}

void Enemy::setMovedir(int x) {
	stratagy_kind = x;
}

void Enemy::setstratagy(int x) {
	stratagy = x;
}
//Alpha

Alpha::Alpha(GameWorld*w):
	Enemy(IMGID_ALPHATRON,w,
	20+(1<<(w->GetLevel())),25,4+w->GetLevel(),2+w->GetLevel()/5,50){}
	
void Alpha::lauch_projectile() {
	int x = GetX(), y = GetY();
	GameWorld *world = Get_in_world();
	if(abs(x-world->Get_playerX())<=10&&Get_energy()>=25&&randInt(1,25)<=25) {
		world->append_projectile(new red(x, y - 50, 180, Get_atk(), world));
		Minus_energy(25);
	}
	if(Get_energy()<25)
		Minus_energy(-1);
}


//Sigma
Sigma::Sigma(GameWorld*w):
	Enemy(IMGID_SIGMATRON,w,
	25+5*(w->GetLevel()),0,0,2+w->GetLevel()/5,100){}
	
void Sigma::sprint() {
	if(abs(GetX()-Get_in_world()->Get_playerX())<=10) {
		setspeed(10);
		setMovedir(1);
		setstratagy(WINDOW_HEIGHT);
	}
}

void Sigma::die_drop() {
	if(randInt(1,100)<=20) {
		Get_in_world()->append_goodie(
			new Restore(GetX(), GetY(), Get_in_world()));
	}
}

//omega
Omega::Omega(GameWorld*w):
	Enemy(IMGID_OMEGATRON,w,
	20+w->GetLevel(),50,2+(2*w->GetLevel()),3+w->GetLevel()/4,200){}

void Omega::lauch_projectile() {
	int x = GetX(), y = GetY();
	GameWorld *world = Get_in_world();
	if(Get_energy()>=50) {
		world->append_projectile(new red(x, y - 50, 162, Get_atk(), world));
		world->append_projectile(new red(x, y - 50, 198, Get_atk(), world));
		Minus_energy(50);
	}
	if(Get_energy()<50)
		Minus_energy(-1);
}

void Omega::die_drop() {
	if(randInt(1,100)<=40) {
		if(randInt(1,100)<=80)
			Get_in_world()->append_goodie(
				new Powerup(GetX(), GetY(), Get_in_world()));
		else 
			Get_in_world()->append_goodie(
				new Meteor(GetX(), GetY(), Get_in_world()));
	}
}
