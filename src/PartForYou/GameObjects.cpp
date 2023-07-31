#include "GameObjects.h"
#include "GameWorld.h"

GameObject::GameObject(int imageID, int x, int y, int direction, int layer, double size,GameWorld* w):
  ObjectBase(imageID,x,y, direction,  layer, size),in_world(w){}

bool GameObject::ismeteor() {
	return false;
}

bool GameObject::Get_destory() const{
	return is_destory;
}
void GameObject::set_die() {
	is_destory = true;
}
GameWorld* GameObject::Get_in_world() {
	return in_world;
}
GameObject::~GameObject() {}

int GameObject::Get_atk() const {
	return 0;
}

int GameObject::Get_hp() const {
	return 0;
}

void GameObject::Minus_hp(int){}
bool GameObject::isprojectile() { return false; }
