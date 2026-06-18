#include "Monster.h"
#include<iostream>
#include<cstdlib>

Monster::Monster() : name(""), hp(0), maxHp(0), attackPower(0), rewardGold(0){}
Monster::Monster(const std::string& n, int h, int a, int g) 
    : name(n), hp(h), maxHp(h), attackPower(a), rewardGold(g){}

std::string Monster::getName() const {return name;}
int Monster::getHp() const {return hp;}
int Monster::getMaxHp() const {return maxHp;}
int Monster::getAttackPower() const {return attackPower;}
int Monster::getRewarGold() const {return rewardGold;}

void Monster::setName(const std::string& n) {name = n;}
void Monster::setHp(int h) {hp = h;}
void Monster::setMaxHp(int h) {maxHp = h;}
void Monster::seyAttackPower(int a) {attackPower = a;}
void Monster::setRewarGold(int g) {rewardGold = g;}


int Monster::attack() const{
    int variation = attackPower / 5;
    int dmg = attackPower - variation + (rand() % (variation * 2 + 1));
    if(dmg > 0) {return dmg;}
    else {return 1;}
}
void Monster::takeDamage(int dmg){
    hp -= dmg;
    if(hp < 0) hp = 0;
}
bool Monster::isAilve() const{
    return hp > 0;
}
void Monster::showInfo() const{
    std::cout<<" ["<<name<<"] \nHP: "<<maxHp<<"/"<<hp<<"\nattack power: "<<attackPower<<"\nDefeat reward: "
        <<rewardGold<<"G\n";
}
