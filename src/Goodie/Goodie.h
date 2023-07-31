#ifndef GOODIE_H
#define GOODIE_H
//Goodie
#include "GameObjects.h"

class GameWorld;

class Goodie : public GameObject {
public:
    Goodie(int, int, int, GameWorld*);
    virtual void Update() override;
    virtual bool isenemy() override;
    virtual void do_function() = 0;
    bool eaten();

};

//HP restore
class Restore : public Goodie {
public:
    Restore(int, int, GameWorld*);
    virtual void do_function() override;
};

//Powerup
class Powerup : public Goodie {
public:
    Powerup(int, int, GameWorld*);
    virtual void do_function() override;
};

//Meteor
class Meteor : public Goodie {
public:
    Meteor(int, int, GameWorld*);
    virtual void do_function() override;
};

class Explosion: public GameObject {
  public:
    Explosion(int, int,GameWorld*);
    virtual void Update() override;
    virtual bool isenemy() override;
  private:
    int tick;
};

//stars
class Star: public GameObject {
  public:
    Star(int,GameWorld*);
    virtual void Update() override;
    virtual bool isenemy() override;
    virtual bool isprojectile() override;
    virtual void Minus_hp(int) override;
};

#endif