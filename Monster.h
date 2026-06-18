#pragma once
#include<iostream>
#include<string>


class Monster
{
private:
    std::string name;
    int hp;
    int maxHp;
    int attackPower;
    int rewardGold;
public:
    Monster();
    Monster(const std::string& n, int h, int a, int g);    

    int attack() const;
    void takeDamage(int dmg);
    bool isAilve() const;
    void showInfo() const;

    std::string getName() const;
    int getHp() const;
    int getMaxHp() const;
    int getAttackPower() const;
    int getRewarGold() const;

    void setName(const std::string& n);
    void setHp(int h);
    void setMaxHp(int h);
    void seyAttackPower(int a);
    void setRewarGold(int g);

};











