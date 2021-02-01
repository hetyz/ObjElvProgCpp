#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "creature.h"
#include "mood.h"

using namespace std;

void create(const string &str, vector<Creature*> &creatures, vector<Mood*> &courts)
{
    ifstream f(str);
    if(f.fail()) { cout << "Wrong file name!\n"; exit(1);}

    int n; f >> n;
    creatures.resize(n);
    for( int i=0; i<n; ++i ){
        char ch; string name; int p;
        f >> ch >> name >> p;
        switch(ch){
            case 'T' : creatures[i] = new Tarantula(name, p); break;
            case 'H' : creatures[i] = new Hamster(name, p); break;
            case 'C' : creatures[i] = new Cat(name, p);   break;
        }
    }

    int m; f >> m;
    courts.resize(m);
    for( int j=0; j<m; ++j ) {
        char k; f >> k;
        switch(k){
            case 'v' : courts[j] = Happy::instance();  break;
            case 'a' : courts[j] = Average::instance(); break;
            case 's' : courts[j] = Sad::instance(); break;
        }
    }
}

void writeOut(int j, string name, int maxi)
{
    if(name == "") name = "They are on a better place where they have caring";
    switch(j) {
        case 0: cout << j+1 << "st day: " << name << " " << maxi << endl; break;
        case 1: cout << j+1 << "nd day: " << name << " " << maxi << endl; break;
        case 2: cout << j+1 << "rd day: " << name << " " << maxi << endl; break;
        default: break;
    }

    if(j > 2)
    {
        if(j % 10 == 1 && j != 11)
        {
            cout << j+1 << "st day: " << name << " " << maxi << endl;
        } else if(j % 10 == 2 && j != 12)
        {
            cout << j+1 << "nd day: " << name << " " << maxi << endl;
        } else if(j % 10 == 3 && j > 10)
        {
            cout << j+1 << "rd day: " << name << " " << maxi << endl;
        } else {
            cout << j+1 << "th day: " << name << " " << maxi << endl;
        }
    }
}

void ifYouRHappyAndYouKnowIt(vector<Creature*> &creatures, vector<Mood*> &courts, vector<string>& alives)
{
    alives.clear();
    int maxi = 0;
    string name = "";
    try{
        for( unsigned int j=0; j < courts.size(); ++j ) {
            alives.clear();
            maxi = 0;
            name = "";
            for( unsigned int i=0; i < creatures.size(); ++i ){
                if(creatures[i]->alive()){
                    creatures[i]->transmute(courts[j]);
                    if(maxi < creatures[i]->getHealth())
                    {
                        maxi = creatures[i]->getHealth();
                        name = creatures[i]->name();
                    }
                }
                if ( creatures[i]->alive() ) alives.push_back(creatures[i]->name());
            }
            writeOut(j, name, maxi);
        }
    }catch(exception e){
        cout << e.what() << endl;
    }
}

void destroy(vector<Creature*> &creatures)
{
    for(int i=0; i<(int)creatures.size(); ++i) delete creatures[i];
}

void destroyMood()
{
    Happy::destroy();
    Average::destroy();
    Sad::destroy();
}
#define NORMAL_MODE
#ifdef NORMAL_MODE
int main()
{
    vector<Creature*> creatures;
    vector<Mood*> courts;
    create("inp22.txt", creatures, courts );

    vector<string> alives;
    ifYouRHappyAndYouKnowIt(creatures, courts, alives);
    for(unsigned int i=0; i<alives.size(); ++i) cout << alives[i] << endl;

    destroy(creatures);
    destroyMood();
    return 0;
}


#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1", "")
{
    vector<Creature*> creatures;
    vector<Mood*> courts;
    vector<string> alives;

    create("inp11.txt", creatures, courts);
    ifYouRHappyAndYouKnowIt(creatures, courts, alives);
    CHECK(alives.size() == 0);
    destroy(creatures);

    create("inp12.txt", creatures, courts );
    ifYouRHappyAndYouKnowIt(creatures, courts, alives);
    CHECK(alives.size() == 1);
    destroy(creatures);

    create("inp13.txt", creatures, courts );
    ifYouRHappyAndYouKnowIt(creatures, courts, alives);
    CHECK(alives.size() == 4);
    destroy(creatures);

    create("inp22.txt", creatures, courts );
    ifYouRHappyAndYouKnowIt(creatures, courts, alives);
    CHECK(alives.size() == 0);
    destroy(creatures);

    creatures.clear();
    courts.clear();
    creatures.push_back(new Hamster("bug", 1));
    courts.push_back(Sad::instance()); courts.push_back(Average::instance());
    ifYouRHappyAndYouKnowIt(creatures, courts, alives);

    CHECK(creatures[0]->alive() == false);
    CHECK(courts[0] == Average::instance());
    CHECK(courts[1] == Average::instance());

    destroy(creatures);

    creatures.clear();
    courts.clear();
    creatures.push_back(new Tarantula("bug", 3));
    courts.push_back(Happy::instance()); courts.push_back(Happy::instance());
    ifYouRHappyAndYouKnowIt(creatures, courts, alives);

    CHECK(creatures[0]->alive() == true);
    CHECK(courts[0] == Average::instance());
    CHECK(courts[1] == Happy::instance());

    destroy(creatures);

    creatures.clear();
    courts.clear();
    creatures.push_back(new Hamster("bug", 8));
    courts.push_back(Average::instance()); courts.push_back(Sad::instance());
    ifYouRHappyAndYouKnowIt(creatures, courts, alives);

    CHECK(creatures[0]->alive() == false);
    CHECK(courts[0] == Happy::instance());
    CHECK(courts[1] == Average::instance());

    destroy(creatures);
    destroyMood();
}

#endif // NORMAL_MODE
