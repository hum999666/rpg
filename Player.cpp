#include "Player.h"
#include<iostream>
#include<cstdlib>

Player::Player() : name(""), hp(0), maxHp(0), mp(0), maxMp(0), attackPower(0), gold(0), attackUpTurns(0), attackUpvalue(0){}
Player::Player(const std::string& n, int h, int m, int a)
    : name(n), hp(h), maxHp(h), mp(m), maxMp(m), attackPower(a), gold(0), attackUpTurns(0), attackUpvalue(0){}

std::string Player::getName() const{return name;}
int Player::getHp() const {return hp;}
int Player::getMaxHp() const {return maxHp;}
int Player::getMp() const {return mp;}
int Player::getMaxMp() const{return maxMp;}
int Player::getAttackPower() const{return attackPower + attackUpvalue;}
int Player::getGold() const{return gold;}


void Player::setName(const std::string& n) {name = n;}
void Player::setHp(int h) {hp = h > maxHp ? maxHp : (h < 0 ? 0 : h);}
void Player::setMp(int m) {mp = m > maxMp ? maxMp : (m < 0 ? 0 : m);}
void Player::setAttackPower(int a) {attackPower = a;}
void Player::addGold(int g) {gold += g;}


int Player::attack() const{
    int base = getAttackPower();
    int variation = base / 5;
    int dmg = base - variation + (rand() % (variation * 2 + 1));
    return dmg > 0 ? dmg : 1;
}
void Player::takeDamage(int dmg){
    hp-=dmg;
    if(hp < 0) hp = 0;
}
int Player::useSkill(int index){
    if(index < 0 || index >= (int)skills.size()) return -1;
    Skill& sk = skills[index];
    if(mp < sk.getMpCost()){
        std::cout<<" MP not enough!\n";
        return -1;
    }
    mp -= sk.getMpCost();
    return sk.use();
}
bool Player::useItem(int index){
    if(index < 0 || index >= (int)items.size()) return false;
    Item& it = items[index];
    if(!it.isAvaliable()){
        std::cout<<" ["<<name<<"] have been used up!\n";
        return false;
    }
    int val = it.use();
    switch (it.getType()){
        case ItemType::HEAL:
            setHp(hp+val);
            std::cout<<" use ["<<it.getName()<<"] , restore "<<val<<" HP!\n";
            break;
        case ItemType::MANA:
            setMp(mp+val);
            std::cout<<" use ["<<it.getName()<<"] , restore "<<val<<" MP!\n";
            break;
        case ItemType::ATTACK_UP:
            attackUpvalue += val;
            attackUpTurns += 4;
            std::cout<<" use ["<<it.getName()<<"] , attackpower up "<<val<<" point last 3 turns\n";
            break;
        case ItemType::REVIVE:
            break;
    
    }
    if(!it.isAvaliable()){
        items.erase(items.begin() + index);
    }
    return true;
}
bool Player::isAlive() const{
    return hp > 0;
}
void Player::onTurnEnd(){
    if(attackUpTurns > 0){
        attackUpTurns--;
        if(attackUpTurns == 0){
            attackUpvalue = 0;
            std::cout<<"  Attack power up effect ends.\n";
        }
    }
}

void Player::showStatus() const{
    std::cout<<"===================\n";
    std::cout<<" ["<<name<<"] "
             <<" HP: "<<maxHp<<"/"<<hp
             <<" MP: "<<maxMp<<"/"<<mp
             <<" ATK: "<<getAttackPower()
             <<" GOLD: "<<gold<<"G\n";
    if(attackUpTurns > 0){
        std::cout<<" Attack power up (last "<<attackUpTurns<<" turns)\n";
    }
    std::cout<<"------------------\n";
}

void Player::showSkills() const{
    std::cout<<"----skills list---\n";
    for (int i = 0; i < (int)skills.size(); i++){
        std::cout<<" "<< i+1 <<". ";
        skills[i].showinfo();
    }
    
}
void Player::showItems() const{
    std::cout<<"---items list---\n";
    bool any = false;
    for (int i = 0; i < (int)items.size(); i++){
        if(items[i].isAvaliable()){
            std::cout<<" "<< i+1<<". ";
            items[i].showInfo();
            any = true;
        }
    }
    if(!any) std::cout<<" The backpack was empty.\n";
}

