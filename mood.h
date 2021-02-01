#pragma once

#include <string>

class Hamster;
class Tarantula;
class Cat;



class Mood{
public:
    virtual Mood* transmute(Hamster *p) = 0;
    virtual Mood* transmute(Tarantula *p) = 0;
    virtual Mood* transmute(Cat *p) = 0;
    virtual Mood* changeMood() = 0;
    virtual bool changeMoodSearch() = 0;
    virtual ~Mood() {}
};

class Happy : public Mood
{
public:
    static Happy* instance();
    Mood* transmute(Hamster *p) override;
    Mood* transmute(Tarantula *p) override;
    Mood* transmute(Cat *p) override;
    Mood* changeMood() override;
    bool changeMoodSearch() override;
    static void destroy() ;
protected:
    Happy(){}
private:
    static Happy* _instance;
};

class Average : public Mood
{
public:
    static Average* instance();
    Mood* transmute(Hamster *p) override;
    Mood* transmute(Tarantula *p) override;
    Mood* transmute(Cat *p) override;
    Mood* changeMood() override;
    bool changeMoodSearch() override;
    static void destroy() ;
protected:
    Average(){}
private:
    static Average* _instance;
};

class Sad : public Mood
{
public:
    static Sad* instance();
    Mood* transmute(Hamster *p) override;
    Mood* transmute(Tarantula *p) override;
    Mood* transmute(Cat *p) override;
    Mood* changeMood() override;
    bool changeMoodSearch() override;
    static void destroy() ;
protected:
    Sad(){}
private:
    static Sad* _instance;
};

