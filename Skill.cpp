#include "Skill.h"
#include<iostream>

Skill::Skill() : name(""), damage(0), mpCost(0){}
Skill::Skill(const std::string& n, int d, int m) : name(n), damage(d), mpCost(m){}

std::string Skill::getName() const {return name;}
int Skill::getDamage() const {return damage;}
int Skill::getMpCost() const {return mpCost;}

void Skill::setName(const std::string& n) {name = n;}
void Skill::setDamage(int d) {damage = d;}
void Skill::setMpCost(int m) {mpCost = m;}


int Skill::use() const{
    return damage;
}

void Skill::showinfo() const{
    std::cout<<" ["<<name<<"] damage: "<<damage<<"   MPcost: "<<mpCost<<"\n";
}
