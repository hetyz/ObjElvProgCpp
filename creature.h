#pragma once

#include <string>
#include "mood.h"

// class of abstract creatures
class Creature{
protected:
    std::string _name;
    int _health;
    Creature (const std::string &str, int e = 0) :_name(str), _health(e) {}
public:
    std::string name() const { return _name; }
    int getHealth() {return _health;}
    bool alive() const { return _health > 0; }
    void changeHealth(int e) { _health += e; }
    virtual void transmute(Mood* &court) = 0;
    virtual ~Creature () {}
};

// class of green finches
class Tarantula : public Creature {
public:
    Tarantula(const std::string &str, int e = 0) : Creature(str, e){}
    void transmute(Mood* &court) override {
        court = court->transmute(this);
    }
};

// class of dune beetles
class Hamster : public Creature {
public:
    Hamster(const std::string &str, int e = 0) : Creature(str, e){}
    void transmute(Mood* &court) override {
        court = court->transmute(this);
    }
};

// class of squelchies
class Cat : public Creature {
public:
    Cat(const std::string &str, int e = 0) : Creature(str, e){}
    void transmute(Mood* &court) override{
        court = court->transmute(this);
    }
};

