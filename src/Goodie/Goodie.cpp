#include "Goodie.h"
#include "GameWorld.h"
//Goodie
Goodie::Goodie(int id,int x,int y,GameWorld* w) :
	GameObject(id,x,y,0,2,0.5,w){}

bool Goodie::isenemy() {
	return false;
}

bool Goodie::eaten() {
	GameWorld *world = Get_in_world();
	if (world->Goodie_player(this)) {
		do_function();
		world->IncreaseScore(20);
		set_die();
		return true;
	}
	else return false;
}

void Goodie::Update() {
	if(Get_destory())
		return;
	int y=GetY();
	GameWorld *world = Get_in_world();
	if(y<0) {
		set_die();
		return;
	}
	// play its function
	if(eaten())
		return;
	//Move
	MoveTo(GetX(),y-2);

	if(eaten())
		return;
}


//Restore HP
Restore::Restore(int x,int y,GameWorld* w):
	Goodie(IMGID_HP_RESTORE_GOODIE,x,y,w){}

void Restore::do_function() {
	Get_in_world()->Increase_hp(50);
}

//Power up
Powerup::Powerup(int x,int y,GameWorld* w):
	Goodie(IMGID_POWERUP_GOODIE,x,y,w){}

void Powerup::do_function() {
	Get_in_world()->Increase_up(1);
}

//Meteor
Meteor::Meteor(int x,int y,GameWorld* w):
	Goodie(IMGID_METEOR_GOODIE,x,y,w){}

void Meteor::do_function() {
	Get_in_world()->Increase_meteor(1);
}

Explosion::Explosion(int x, int y, GameWorld *w) : 
	GameObject(IMGID_EXPLOSION, x, y, 0, 3, 4.5, w), tick(20){}

bool Explosion::isenemy() { return false; }

void Explosion::Update() {
	SetSize(GetSize() - 0.2);
	if(!(--tick))
		set_die();
}

//stars
Star::Star(int y,GameWorld* id):
  GameObject(IMGID_STAR,randInt(0,WINDOW_WIDTH-1),
  y,0,4,randInt(10,40)/100.0,id){}
void Star::Update() {
	if(Get_destory())
		return;
	if(GetY()<0) {
		set_die();
		return;
	}
	MoveTo(GetX(), GetY() - 1);
	if(GetY()<0) {
		set_die();
	}
}
bool Star::isenemy() {
	return false;
}
bool Star::isprojectile() {
	return false;
}
void Star::Minus_hp(int){}