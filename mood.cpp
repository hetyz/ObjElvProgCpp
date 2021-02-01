#include "mood.h"
#include "creature.h"
#include <vector>

using namespace std;

vector<Creature*> creatures;

Happy* Happy::_instance = nullptr;
Happy* Happy::instance()
{
    if(_instance == nullptr) {
        _instance = new Happy();
    }
    return _instance;
}
void Happy::destroy()
{
    if ( nullptr!=_instance ) delete _instance;
}

Mood* Happy::transmute(Tarantula *p)
{
    p->changeHealth(1);
    creatures.push_back(p);
    return Happy::changeMood();
}

Mood* Happy::transmute(Hamster *p)
{
    p->changeHealth(2);
    creatures.push_back(p);
    return Happy::changeMood();
}

Mood* Happy::transmute(Cat *p)
{
    p->changeHealth(3);
    creatures.push_back(p);
    return Happy::changeMood();
}

Mood* Happy::changeMood()
{
    if(!Happy::changeMoodSearch())
    {
        return Average::instance();
    }
    return this;
}

// implementation of class Grass
Average* Average::_instance = nullptr;
Average* Average::instance()
{
    if(_instance == nullptr) {
        _instance = new Average();
    }
    return _instance;
}
void Average::destroy()
{
    if ( nullptr!=_instance ) delete _instance;
}

Mood* Average::transmute(Tarantula *p)
{
    p->changeHealth(-2);
    creatures.push_back(p);
    return Average::changeMood();
}

Mood* Average::transmute(Hamster *p)
{
    p->changeHealth(-3);
    creatures.push_back(p);
    return Average::changeMood();
}

Mood* Average::transmute(Cat *p)
{
    p->changeHealth(3);
    creatures.push_back(p);
    return Average::changeMood();
}

Mood* Average::changeMood()
{
    if(Average::changeMoodSearch())
    {
        return Happy::instance();
    }
    return this;
}

// implementation of class Marsh
Sad* Sad::_instance = nullptr;
Sad* Sad::instance()
{
    if(_instance == nullptr) {
        _instance = new Sad();
    }
    return _instance;
}
void Sad::destroy()
{
    if ( nullptr!=_instance ) delete _instance;
}

Mood* Sad::transmute(Tarantula *p)
{
    p->changeHealth(-3);
    creatures.push_back(p);
    return Sad::changeMood();
}

Mood* Sad::transmute(Hamster *p)
{
    p->changeHealth(-5);
        creatures.push_back(p);
    return Sad::changeMood();
}

Mood* Sad::transmute(Cat *p)
{
    p->changeHealth(-7);
        creatures.push_back(p);
    return Sad::changeMood();
}

Mood* Sad::changeMood()
{
    if(Sad::changeMoodSearch())
    {
        return Average::instance();
    }
    return this;
}

bool Sad::changeMoodSearch()
{
    bool l = true;

    for(int i=0; i<(int)creatures.size() && creatures[i]->alive(); ++i) {
        if(creatures[i]->getHealth() < 5)
        {
            l = false; break;
        }
    }

    creatures.clear();
    return l;
}

bool Happy::changeMoodSearch()
{
    bool l = true;

    for(int i=0; i<(int)creatures.size() && creatures[i]->alive(); ++i) {
        if(creatures[i]->getHealth() < 5)
        {
            l = false; break;
        }
    }

    creatures.clear();
    return l;
}

bool Average::changeMoodSearch()
{
    bool l = true;

    for(int i=0; i<(int)creatures.size() && creatures[i]->alive(); ++i) {
        if(creatures[i]->getHealth() < 5)
        {
            l = false; break;
        }
    }

    creatures.clear();
    return l;
}

