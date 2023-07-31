#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__

#include<cmath>
#include "ObjectBase.h"


class GameWorld;

class GameObject : public ObjectBase {
  public:
    GameObject(int imageID, int x, int y, int direction, int layer, double size,GameWorld* w);
    virtual ~GameObject() override;
    virtual bool isenemy()= 0;
    virtual bool ismeteor();
    virtual bool isprojectile();
    virtual void Minus_hp(int);
    virtual int Get_atk() const;
    virtual int Get_hp() const;
    bool Get_destory() const;
    void set_die();
    GameWorld *Get_in_world();
  private:
    bool is_destory = false;
    GameWorld *in_world;
};



#endif // GAMEOBJECTS_H__