#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "Skill.h"
#include "Item.h"

class Player
{
private:
    std::string name;
    int hp;
    int maxHp;
    int mp;
    int maxMp;
    int attackPower;
    int gold;
    int attackUpTurns;
    int attackUpvalue;
public:
    std::vector<Skill> skills;
    std::vector<Item> items;

    Player();
    Player(const std::string& n, int h, int m, int a);


    int attack() const;
    void takeDamage(int dmg);
    int useSkill(int index);
    bool useItem(int index);
    bool isAlive() const;
    void onTurnEnd();

    std::string getName() const;
    int getHp() const;
    int getMaxHp() const;
    int getMp() const;
    int getMaxMp() const;
    int getAttackPower() const;
    int getGold() const;

    void setName(const std::string& n);
    void setHp(int h);
    void setMp(int m);
    void setAttackPower(int a);
    void addGold(int g);

    void showStatus() const;
    void showSkills() const;
    void showItems() const;

};




