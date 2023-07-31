#include "Ship.h"
#include "GameWorld.h"
#include "Projectile.h"
///Ship
Ship::Ship(int imageID, int x, int y, int direction, int hp ,int energy,GameWorld* w)
		:GameObject(imageID,  x,  y,  direction, 0,1.0,w),hp(hp),energy(energy){}


bool Ship::isprojectile()  {
	return false;
}
int Ship::Get_energy() const {
	return energy;
}

void Ship::Minus_energy(int cos) {
	energy -= cos;
}

int Ship::Get_hp() const {
	return hp;
}

void Ship::Set_hp(int t) {
	hp = t;
}

void Ship::Minus_hp(int hurt) {
	hp -= hurt;
	if(hp <=0) {
		set_die();
		after_die();
	}	
}

void Ship::after_die(){}


//player
Player::Player(GameWorld* id):
  Ship(IMGID_DAWNBREAKER,300,100,0,100,10,id){}

int Player::Get_up() const {
	return up;
}

int Player::Get_meteor()  {
	return meteor;
}

void Player::add_hp(int add) {
	Get_hp() + add > 100 ? Set_hp(100) : Set_hp(Get_hp()+add);
}

void Player::add_up(int add) {
	up += add;
}

void Player::add_meteor(int add) {
	meteor += add;
}

bool Player::isenemy() {
	return false;
}

void Player::Update() {
	if(Get_destory()==true) // whether to die 
		return;
	int y = GetY(),x = GetX();
	GameWorld *world = Get_in_world();
	world->player_enemy(this);
	if(Get_destory())
		return;
	if(world->GetKey(KeyCode::UP)&&(y + 4) <= WINDOW_HEIGHT - 1) 
		MoveTo(x,y+4);
	y = GetY(),x = GetX();
	if(world->GetKey(KeyCode::DOWN)&&(y - 4) >= 50) 
		MoveTo(x,y-4);
	y = GetY(),x = GetX();
	if(world->GetKey(KeyCode::LEFT)&&(x - 4) >= 0) 
		MoveTo(x-4,y);
	y = GetY(),x = GetX();
	if(world->GetKey(KeyCode::RIGHT)&&(x + 4) <= WINDOW_WIDTH - 1) 
		MoveTo(x+4,y);
	y = GetY(),x = GetX();
	if(world->GetKey(KeyCode::FIRE1) && Get_energy() >= 10) {
		Minus_energy(10);
		world->append_projectile(new blue(up,x, y+50,world));
	}
	if(world->GetKeyDown(KeyCode::FIRE2)&&meteor>=1) {
		add_meteor(-1);
		world->append_projectile(new Meteor_flying(x, y+100, world));
	}
	if(Get_energy()<10)
		Minus_energy(-1);
}
