#include "GameWorld.h"
#include "GameObjects.h"
#include "Goodie.h"
#include "Enemy.h"
#include "Ship.h"
#include "Projectile.h"
#include "Others.h"
#include<algorithm>

GameWorld::GameWorld():WorldBase(),
          maxOnscreen((5+GetLevel())>>1),
          destroyed(0),live(3),required(3*GetLevel()),onscreen(0),
          p1(6),p2(2*std::max(GetLevel()-1,0)),p3(3*std::max(GetLevel()-2,0)),p(p1+p2+p3) {

}
GameWorld::~GameWorld() {

}

void GameWorld::Minus_onscreen(){
  --onscreen;
}

void GameWorld::append_goodie(GameObject* obj) {
  gameobjects.push_front(obj);
}

void GameWorld::append_star(GameObject* obj) {
  gameobjects.push_front(obj);
}

void GameWorld::append_explosion(GameObject* obj) {
  gameobjects.push_front(obj);
}

void GameWorld::append_projectile(GameObject* obj) {
  gameobjects.push_back(obj);
}
void GameWorld::append_enemy(GameObject* obj) {
  gameobjects.push_back(obj);
  ++onscreen;
}

std::list<GameObject *>::iterator GameWorld::Get_Begin() {
  return gameobjects.begin();
}
std::list<GameObject *>::iterator GameWorld::Get_End() {
  return gameobjects.end();
}

void GameWorld::attack_blue(GameObject* blue) {
  for (auto it = gameobjects.begin(); it !=gameobjects.end();++it) {
    if(!Check_collision(blue,*it)||(*it)->Get_destory()||!(*it)->isenemy()||(*it)->isprojectile())
      continue;
    (*it)->Minus_hp(blue->Get_atk());
    blue->set_die();
  }
}

void GameWorld::meteor_enemy(Meteor_flying* meteor) {
  for (auto it = gameobjects.begin(); it !=gameobjects.end();++it) {
    if(!Check_collision(meteor,*it)||(*it)->Get_destory()||!(*it)->isenemy())
      continue;
    (*it)->Minus_hp((*it)->Get_hp()+10);
  }
}

void GameWorld::Collision_Handling(Enemy* enemy,int hurt) {
  for (auto it = Get_Begin(); it != Get_End();++it) {
    if(!Check_collision(enemy,*it)||(*it)->isenemy()||(*it)->Get_destory()) continue;

    if((*it)->isprojectile()&&!(*it)->isenemy()) {
      //blue projectile
      if((*it)->ismeteor()) {
        enemy->Minus_hp((enemy->Get_hp()) + 10);
      }
      else {
        enemy->Minus_hp((*it)->Get_atk());
        (*it)->set_die();
      }
    }

	}
	//Check if the player	world->collison_player(this,20);
  if(Check_collision(enemy,player)) {
		player->Minus_hp(hurt);
		enemy->Minus_hp(enemy->Get_hp() + 10);
	}
}

void GameWorld::player_enemy(Player *player) {
  for (auto it = Get_Begin(); it != Get_End();++it) {
    if((*it)->Get_destory()||!Check_collision(player,*it))continue;
    if((*it)->isenemy()&&(*it)->isprojectile()) {
      player->Minus_hp((*it)->Get_atk());
      (*it)->set_die();
    }
    else if((*it)->isenemy()&&!(*it)->isenemy()) {
      player->Minus_hp(20);
      (*it)->Minus_hp((*it)->Get_hp() + 10);
    }
  }
}

bool GameWorld::Goodie_player(Goodie* good) {
  return Check_collision(good, player);
}

void GameWorld::Increase_hp(int add) {
  player->add_hp(add);
}

void GameWorld::Increase_up(int add) {
  player->add_up(add);
}

void GameWorld::Increase_meteor(int add) {
  player->add_meteor(add);
}

void GameWorld::red_player(projectile* red) {
  if(Check_collision(red,player)) {
    player->Minus_hp(red->Get_atk());
    red->set_die();
  }
}

int GameWorld::Get_playerX() {
  return player->GetX();
}

int GameWorld::Get_playerY() {
  return player->GetY();
}

void GameWorld::add_destroyed() {
  ++destroyed;
}

void GameWorld::Init() {
  maxOnscreen=(5+GetLevel())>>1,
  destroyed=0;
  required=3 * GetLevel();
  onscreen=0;
  p1 = 6;
  p2 = 2 * std::max(GetLevel() - 1, 0);
  p3 = 3 * std::max(GetLevel() - 2, 0);
  p = p1 + p2 + p3;
  player = new Player(this); // place the player
  for (int i = 1; i <= 30;i++)
    append_star(new Star(randInt(0, WINDOW_HEIGHT - 1), this)); // genenrate 30 stars 
}

LevelStatus GameWorld::Update() {
  if(randInt(1,30)==1)
    append_star(new Star(randInt(0, WINDOW_HEIGHT - 1), this)); // generate random star

    //generate enemy
  int allowed = maxOnscreen<required - destroyed?maxOnscreen:required-destroyed;
  if(onscreen<allowed) {
    if(randInt(1,100)<=allowed-onscreen) {
      //determine what kind of enemy to generate
      int rand = randInt(1, p);
      if(rand<=p1)
        append_enemy(new Alpha(this));
      else if(rand<=p1+p2)
        append_enemy(new Sigma(this));
      else
        append_enemy(new Omega(this));
    }
  }

  player->Update();
  for(auto object:gameobjects) {//update every gameobject
    if(object->Get_destory())
      continue;
    object->Update();
  }
  if(player->Get_destory()) {
    --live;
    return LevelStatus::DAWNBREAKER_DESTROYED;   //judge the status of game 
  }
  else if(destroyed>=required)
    return LevelStatus::LEVEL_CLEARED;
  for (auto it = gameobjects.begin(); it != gameobjects.end();) {
    if((*it)->Get_destory()) {
      delete *it;
      it = gameobjects.erase(it);// why erase don't call deconstructor????
    }
    else
      ++it;
  }
  
  //HP: X/100 Meteors: X Lives: X Level: X Enemies: X/X Score: X
  std::string s = "HP: " + std::to_string(player->Get_hp())+"/100";
  s += "   Meteors: " + std::to_string(player->Get_meteor());
  s += "   Lives: " + std::to_string(live);
  s += "   Level: " + std::to_string(GetLevel());
  s += "   Enemies: " + std::to_string(destroyed) + "/" + std::to_string(required);
  s += "   Score: " + std::to_string(GetScore());
  SetStatusBarMessage(s);
  return LevelStatus::ONGOING;
}      

void GameWorld::CleanUp() {
  delete player;
  for(auto x:gameobjects)
    delete x;
  gameobjects.clear();
}


bool GameWorld::IsGameOver() const {
  if(live==0)
    return true;
  else return false;
}

bool Check_collision(const GameObject*lhs,const GameObject*rhs) {
  double dis = sqrt((lhs->GetX() - rhs->GetX()) * (lhs->GetX() - rhs->GetX()) +
                    (lhs->GetY() - rhs->GetY()) * (lhs->GetY() - rhs->GetY()));
  return dis <(30.0 * (lhs->GetSize() + rhs->GetSize()));
}