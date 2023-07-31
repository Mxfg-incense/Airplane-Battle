#include "Projectile.h"
#include "GameWorld.h"
//projectlie
projectile::projectile(int imageID, int x, int y, int direction, int layer, double size,GameWorld* w,int atk)
	:GameObject( imageID,  x,  y,  direction,  layer,  size, w),atk(atk){}
bool projectile::isenemy() {
	return false;
}
bool projectile::isprojectile() {
	return true;
}
void projectile::Minus_hp(int) {}
int projectile::Get_atk() const {
	return atk;
}



blue::blue(int up,int x,int y,GameWorld* w):
	projectile(IMGID_BLUE_BULLET,x,y,0,1,0.5+0.1*up,w,5+3*up){}

bool blue::isenemy() {
	return false;
}

void blue::Update() {
	if(Get_destory()) 
		return;
	int y = GetY();
	GameWorld *world = Get_in_world();
	if(y>=WINDOW_HEIGHT) {
		set_die();
		return;
	}
	//attack the enemy
	world->attack_blue(this);
	if(Get_destory())
		return;
	//move
	MoveTo(GetX(), y + 6);
	world->attack_blue(this);
}


//red
red::red(int x,int y,int dir,int atk,GameWorld* w):
	projectile(IMGID_RED_BULLET,x,y,dir,1,0.5,w,atk){}

void red::Update() {
	if(Get_destory()) 
		return;
	int x=GetX(),y = GetY();
	GameWorld *world = Get_in_world();
	if(y<0) {
		set_die();
		return;
	}

	//attack player
	world->red_player(this);
	if(Get_destory())
		return;
	//move
	switch (GetDirection())
	{
		case 180:
			MoveTo(x, y - 6);
			break;
		case 162:
			MoveTo(x + 2, y - 6);
			break;
		case 198:
			MoveTo(x - 2, y - 6);
			break;
	}
	world->red_player(this);
}

bool red::isenemy() { return true; }

//Meteor_flying
Meteor_flying::Meteor_flying(int x,int y,GameWorld*w):
	projectile(IMGID_METEOR,x,y,0,1,2.0,w,0){}

bool Meteor_flying::isenemy(){
	return false;
}

bool Meteor_flying::ismeteor(){
	return true;
}

void Meteor_flying::Update() {
	if(Get_destory()) 
		return;
	int x=GetX(),y = GetY();
	GameWorld *world = Get_in_world();
	if(y>=WINDOW_HEIGHT) {
		set_die();
		return;
	}
	//attack enemy
	world->meteor_enemy(this);
	//move
	MoveTo(x,y+2);
	SetDirection(GetDirection() + 5);

	world->meteor_enemy(this);
}
