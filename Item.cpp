#include "Item.h"
#include "Player.h"
#include<iostream>

Item::Item() : name(""), type(), effectValue(0), quantity(0){}
Item::Item(const std::string& n, ItemType t, int e, int q) : name{n}, type(t), effectValue(e), quantity(q){}

std::string Item::getName() const{return name;}
ItemType Item::getType() const{return type;}
int Item::getEffectValue() const{return effectValue;}
int Item::getQuantity() const{return quantity;}

void Item::setName(const std::string& n) {name = n;}
void Item::setType(ItemType t) {type = t;}
void Item::setEffectValue(int e) {effectValue = e;}
void Item::setQuantity(int q) {quantity = q;}


bool Item::isAvaliable() const{
    return quantity > 0;
}
int Item::use(){
    if(!isAvaliable()){
        std::cout<<" ["<<name<<"] have been used up!\n";
        return 0;
    }
    quantity--;
    return effectValue;
}
void Item::showInfo() const{
    std::string typeStr;
    switch (type)
    {
    case ItemType::HEAL:
        typeStr = "Restore HP";
        break;
    case ItemType::MANA:
        typeStr = "Restore MP";
        break;
    case ItemType::ATTACK_UP:
        typeStr = "Attack power up";
        break;
    case ItemType::REVIVE:
        typeStr = "Revive";
    }
    std::cout<<" ["<<name<<"] "<<typeStr<<"   Effect: "<<effectValue<<"   Quantity: "<<quantity<<"\n";
}



