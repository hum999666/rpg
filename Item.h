#pragma once
#include<iostream>
#include<string>

enum class ItemType{
    HEAL,
    MANA,
    ATTACK_UP,
    REVIVE
};


class Item
{
private:
    std::string name;
    ItemType type;
    int effectValue;
    int quantity;    
public:
    Item();
    Item(const std::string& n, ItemType t, int e, int q = 1);
    int use();
    void showInfo() const;
    bool isAvaliable() const;

    std::string getName() const;
    ItemType getType() const;
    int getEffectValue() const;
    int getQuantity() const;

    void setName(const std::string& n);
    void setType(ItemType t);
    void setEffectValue(int e);
    void setQuantity(int q);
   
};



