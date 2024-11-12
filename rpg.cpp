#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#define DEF_HEALTH 100
#define DEF_FORCE 25
#define DEF_FORCE_MODIFIER 5
#define DEF_DEFENCE 5
#define DEF_LENGTH 10

using namespace std;

class Entity{
    private :
    static const string defaultName[DEF_LENGTH];
    static const string defaultType[DEF_LENGTH];
    string name;
    string type;
    int health;
    int force;
    int forceModifier;
    int defence;

    public :
    Entity (string name) {
        if (name != "") {
            this->name = name;
            this->type = "Warrior";
            this->health = DEF_HEALTH;
            this->force = DEF_FORCE;
            this->forceModifier = DEF_FORCE_MODIFIER;
            this->defence = DEF_DEFENCE;
        }
        else {
            this->name = getRandomName();
            this->type = getRandomType();
            this->health = (int)(80 + (static_cast<double>(rand()) / RAND_MAX)*2*20);
            this->force = (int)(20 + (static_cast<double>(rand()) / RAND_MAX)*2*10);
            this->forceModifier = (int)(5 + (static_cast<double>(rand()) / RAND_MAX)*2*3);
            this->defence = (int)(5 + (static_cast<double>(rand()) / RAND_MAX)*2*3);
        }
    }

    string getName() {
        return name;
    }

    string getType() {
        return type;
    }

    string getFullTitle() {
        return name + " the " + type;
    }

    int getHealth() {
        return health;
    }

    void getDamaged(int value) {
        int damage = defence - value;
        if (damage < 0) {
            health -= value;
        }
    }

    bool isAlive() {
        return health > 0;
    }

    void attack(Entity enemy) {
        enemy.getDamaged(force - forceModifier + (static_cast<double>(rand()) / RAND_MAX)*2*forceModifier);
    }

    static string getRandomName() {
        return defaultName[(int)((static_cast<double>(rand()) / RAND_MAX)*DEF_LENGTH)];
    }

    static string getRandomType() {
        return defaultType[(int)((static_cast<double>(rand()) / RAND_MAX)*DEF_LENGTH)];
    }
};

class Player : public Entity {
    private :

    public :
    Player (string name) : Entity (name) {}

};

const string Entity::defaultName[10] = {"David", "Lysandre", "Albator", "Reinhardt", "Condoriano", "Eustache", "Lystérine", "Elowenn", "Aldaric", "Zéphyrion"};
const string Entity::defaultType[10] = {"Dark Elf", "Corrupted Dwarf", "Thief", "Orc", "Pirate", "Technomancer", "Ghoul", "Dark Mage", "Vampire", "Werewolf"};

Player setup() {
    cout << "********************\n** RPG BATTLE SIM **\n********************\n";
    cout << "Enter your name :\n";
    string s;
    cin >> s;
    Player res = Player(s);
    cout << "--> You are now " << res.getFullTitle() << "\n";
    return res;
}

bool choice() {
    cout << "Do you want to :\n\t>> Fight ? Press [F]\n\t>> Run ? Press [R]\n";
    char c;
    cin >> c;
    while (c != 'f' && c != 'F' && c != 'r' && c != 'R'){
        cout << "Invalid input !\nPress [F] to fight or [R] to run\n";
        cin >> c;
    }
    return (c == 'f' || c == 'F');
}

bool fight(Player player) {
    Entity enemy = Entity("");
    int i = 0;
    while (player.isAlive() && enemy.isAlive()){
        if (i%2 == 0){
            
        }
    }
    return true;
}

int main() {
    srand(time(NULL));
    Player player = setup();
    choice();

    return 0;
}