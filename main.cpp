#include<iostream>
#include<string>
#include<vector>
#include<thread>
#include <chrono>
#include <limits>

#include "Player.h"
#include "Monster.h"
#include "Skill.h"
#include "Item.h"

//---
//tool function
//---

void pause(int ms = 600){
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void printBanner(const std::string& text){
    std::cout<<"\n==========================\n";
    std::cout<<" "<<text<<"\n";
    std::cout<<"==========================\n\n";
}


int getInput(int minVal, int maxVal){
    int choice = -1;
    while (true){
        std::cout<<"Enter ("<<minVal<<"~"<<maxVal<<"): ";
        std::cin>>choice;
        if(std::cin.fail() || choice < minVal || choice > maxVal){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<" Invalid input. Please try again.";
        }
        else{
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
    
}
void addItem(Player& player, const Item& newitem){
    for (auto& it : player.items){
        if(it.getName() == newitem.getName()){
            it.setQuantity(it.getQuantity() + newitem.getQuantity());
            return;
        }
    }
    player.items.push_back(newitem);
}



//---
//fighting system
//---
bool battle(Player& player, Monster monster){
    printBanner("Encounter the enemy!  " + monster.getName());
    monster.showInfo();
    pause();

    int round  = 1;
    while (player.isAlive() && monster.isAilve()){
        std::cout<<"\n--------Round "<<round<<"---------\n";
        player.showStatus();
        std::cout<<" Enemy: "<<monster.getName()<<" HP: "<<monster.getMaxHp()<<"/"<<monster.getHp()<<"\n\n";
        
        //player
        std::cout<<"Choose action:\n"<<" 1. normal attack\n"<<" 2. Use Skill\n"<<" 3. Use Item\n"<<" 4. Enemy's Info\n";
        int action = getInput(1,4);

        if(action == 1){
            // normal attack
            int dmg = player.attack();
            monster.takeDamage(dmg);
            std::cout<<"\n"<<player.getName()<<" normal attack deal "<<dmg<<" damage to"<<monster.getName()<<"\n";
        }
        else if(action == 2){
            //use skill
            player.showSkills();
            if(player.skills.empty()){
                std::cout<<" no skills can use\n";
                pause();
                continue;
            }
            std::cout<<" Choose skill (0 to cancel): ";
            int idx = getInput(0, (int)player.skills.size());
            if(idx == 0) continue;
            int dmg = player.useSkill(idx - 1);
            if(dmg > 0){
                monster.takeDamage(dmg);
                std::cout<<"\n"<<player.getName()<<" use skill ["<< player.skills[idx-1].getName()<<"] deal "<<dmg<<" damage!\n";
            }
            else continue; //mp not enough
        }
        else if(action == 3){
            //use item
            player.showItems();
            bool hasItem = false;
            for (auto& it : player.items) if(it.isAvaliable()) {hasItem = true; break;}
            if(!hasItem){
                std::cout<<" The backpack was empty.\n";
                pause();
                continue;
            }
            std::cout<<" Choose Item(0 to cancel): ";
            int idx = getInput(0, (int)player.items.size());
            if(idx == 0) continue;
            bool ok = player.useItem(idx - 1);
            if(!ok) continue;
                        
        }
        else{
            //watch enemy info
            monster.showInfo();
            pause();
            continue;
        }

        pause();
        
        //monster attack
        if(monster.isAilve()){
            int dmg = monster.attack();
            player.takeDamage(dmg);
            std::cout<<" enemy "<<monster.getName()<<" counterattack deal "<<dmg<<" damage!\n";
        }
        else{
            std::cout<<"\n"<<monster.getName() <<" defeated!\n";
        }
        player.onTurnEnd();
        round++;
        pause();
        
    }
    if(player.isAlive()){
        player.addGold(monster.getRewarGold());
        std::cout<<"\nVICTORY! you get "<<monster.getRewarGold()<<"G!\n";
        return true;
    }
    else{
        std::cout<<"\n "<<player.getName()<<" falls...\n";
        std::cout<<"\ngame over\n";
        return false;
    }
     
}



//random event
void ramdomEvent(Player& player){
    int r = rand() % 4;
    std::cout<<"\n [There is something!!!]\n";
    pause();
    switch (r){
        case 0:
            std::cout<<"You find a ancient well, Drinking the water restores 30 HP and 20 MP!\n";
            player.setHp(player.getHp() + 30);
            player.setMp(player.getMp() + 20);
            break;
        case 1:
            std::cout<<"You find a abandoned backpack, there is a MP potion!\n";
            addItem(player, Item("MP potion", ItemType::MANA, 30, 1));
            break;
        case 2:
            std::cout<<" you stepped on a trap, hurting 10 HP!\n";
            player.takeDamage(10);
            break;
        case 3:
            std::cout<<"You enconter a traveling merchant, he give you a HP potion!\n";
            addItem(player,Item("HP potion", ItemType::HEAL, 40, 1));
            break;
    }
    pause();
}

//shop
void shop(Player& player){
    printBanner("===mystery shop===");
    while (true){
        std::cout<<" Gold: "<<player.getGold()<<"G\n\n";
        std::cout<<" shopItem list:\n"<<" 1. Big HP potion (+80 HP) ---50G\n"
                <<" 2. Big MP potion (+60 MP) ---40G\n"
                <<" 3. strength potion (ATK +20, last 3 round) ---60G\n"
                <<" 4. left\n";
        int c = getInput(1,4);
        if(c==4) break;

        struct ShopItem{
            std::string name;
            ItemType type;
            int val;
            int price;
        };
        ShopItem catalog[] = {
            {"Big MP potion", ItemType::HEAL, 80, 50},
            {"Big MP potion", ItemType::MANA, 60, 40},
            {"strength potion", ItemType::ATTACK_UP, 20,60},

        };
        auto& s1 = catalog[c-1];
        if(player.getGold() >= s1.price){
            player.addGold(-s1.price);
            player.items.push_back(Item(s1.name, s1.type, s1.val));
            std::cout<<" Purchase successful, you get ["<<s1.name<<"]\n";
        }
        else{
            std::cout<<"you have not enuogh money!\n";
        }
        pause();
    }
}



//character creater
Player createrPlayer(){
    printBanner("<Text RPG>");
    std::cout<<" welcome player! plaese Enter your name: ";
    std::string name;
    std::getline(std::cin, name);
    if(name.empty()) name = "Nameless Hero";
    // choose Profession
    Player p;
    std::cout<<"\n Choose profession:\n"
            <<" 1. Warrior(HP:150  MP:50  ATK:24)\n"
            <<" 2. Mage(HP: 100  MP:120  ATK:15)\n"
            <<" 3. Thief(HP:120  MP:70  ATK:18)\n";
    int cls = getInput(1,3);
    switch (cls){
        case 1:
            p = Player(name, 150, 50, 24);
            p.skills.push_back(Skill("Heavy chop", 40, 20));
            p.skills.push_back(Skill("Storm Slash", 60, 35));
            break;
        case 2:
            p = Player(name, 100,120,15);
            p.skills.push_back(Skill("fire ball", 55, 25));
            p.skills.push_back(Skill("thunder", 70, 40));
            break;
        case 3:
            p = Player(name, 120, 70, 18);
            p.skills.push_back(Skill("backstab", 50, 30));
            p.skills.push_back(Skill("Fuma Shuriken", 90, 50));
            break;
    }

    

    //item
    p.items.push_back(Item("HP potion", ItemType::HEAL, 40, 2));
    p.items.push_back(Item("MP potion", ItemType::MANA, 30, 1));
    std::cout<<"\ngame start!\n";
    pause(800);
    return p;

}

//stage struct


//main function
int main(){

    srand(static_cast<unsigned>(time(nullptr)));

    std::cout<<" press Enter to start game...";
    std::cin.ignore();

    Player player = createrPlayer();

    bool won = false;
    
    Monster monster1("Griffin",80, 14, 30);

    
    if(!battle(player,monster1)){
        return 0;
    }
    player.setHp(player.getHp() + 30);
    player.setMp(player.getMp() + 20);
    std::cout<<"restore 30HP and 20MP\n";
    pause(800);
    ramdomEvent(player);

    Monster monster2("Cyclops", 100, 20, 40);
    if(!battle(player,monster2)){
        return 0;
    }
    player.setHp(player.getHp() + 30);
    player.setMp(player.getMp() + 20);
    std::cout<<"restore 30HP and 20MP\n";

    shop(player);
    Monster final("Dragon", 150, 25, 50);
    if(!battle(player,final)){
        return 0;
    }
    std::cout<<"Congraduation!\nThank you for playing!\n";

    return 0;


}
