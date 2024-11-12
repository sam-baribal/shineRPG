#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#define DEF_HEALTH 100
#define DEF_FORCE 25
#define DEF_FORCE_MODIFIER 5
#define DEF_DEFENCE 5
#define DEF_LENGTH 10
#define RUN_AWAY_ODDS 3

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
            this->health = (int)(60 + (static_cast<double>(rand()) / RAND_MAX)*2*20);
            this->force = (int)(15 + (static_cast<double>(rand()) / RAND_MAX)*2*10);
            this->forceModifier = (int)(2 + (static_cast<double>(rand()) / RAND_MAX)*2*3);
            this->defence = (int)(2 + (static_cast<double>(rand()) / RAND_MAX)*2*3);
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
            health += damage;
            cout << name << " recieved " << damage << " damage !\n";
        }
        else {
            cout << name << " wasn't hurt by the attack\n";
        }
    }

    bool isAlive(bool display) {
        if (health <= 0) {
            if (display){
                cout << name << " was defeated !\n";
            }
            return false;
        }
        return true;
    }

    void attack(Entity &enemy) {
        int attackForce = (int)(force - forceModifier + (static_cast<double>(rand()) / RAND_MAX)*2*forceModifier);
        cout << name << " attacked " << enemy.getName() << " with a force of " << attackForce << " !\n";
        enemy.getDamaged(attackForce);
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

    bool runFrom(Entity enemy) {
        float dice = (static_cast<float>(rand()) / RAND_MAX);
        if (dice < 1.0/RUN_AWAY_ODDS) {
            cout << "You successfully run away from " << enemy.getFullTitle() << "!\n";
            return true;
        }
        cout << "You failed to escape from the fight!\n";
        return false;
    }

};

const string Entity::defaultName[10] = {"David", "Lysandre", "Albator", "Reinhardt", "Condoriano", "Eustache", "Lystérine", "Elowenn", "Aldaric", "Zéphyrion"};
const string Entity::defaultType[10] = {"Dark Elf", "Corrupted Dwarf", "Thief", "Orc", "Pirate", "Technomancer", "Ghoul", "Dark Mage", "Vampire", "Werewolf"};

Player setup() {
    cout << "********************\n** RPG BATTLE SIM **\n********************\n\n";
    cout << "Enter your name :\n";
    string s;
    cin >> s;
    Player res = Player(s);
    cout << "--> You are now " << res.getFullTitle() << "\nPrepare to enter the dungeon !\n\n";
    return res;
}

bool choice(string option1, string option2) {
    cout << "Do you want to :\n\t>> " << option1 << " ? Press [1]\n\t>> " << option2 << " ? Press [2]\n";
    char c;
    cin >> c;
    while (c != '1' && c != '2'){
        cout << "Invalid input !\nPress [1] to " << option1 << " or [1] to " << option2 << "\n";
        cin >> c;
    }
    return (c == '1');
}

bool fight(Player player) {
    Entity enemy = Entity("");
    int initEnemyHealth = enemy.getHealth();
    cout << "\n<!> You encountered " << enemy.getFullTitle() << " and they want to fight you !\n";
    int i = 0;
    while (player.isAlive(true) && enemy.isAlive(true)){
        cout << "\n" << player.getFullTitle() << " [ " << player.getHealth() << " / " << DEF_HEALTH << " HP ]\n";
        cout << enemy.getFullTitle() << " [ " << enemy.getHealth() << " / " << initEnemyHealth << " HP ]\n";
        if (i%2 == 0){
            cout << "Your turn !\n";
            if (choice("attack", "run")){
                player.attack(enemy);
            }
            else {
                if (player.runFrom(enemy)){
                    break;
                }
            }
        }
        else {
            cout << "The enemy's turn !\n";
            enemy.attack(player);
        }
        i++;
    }
    return (player.isAlive(false));
}

int main() {
    srand(time(NULL));
    do {
        Player player = setup();
        while (choice("fight", "quit")){
            if (!fight(player)){
                cout << "<!> You lost !\n";
                break;
            }
            else {
                cout << "<!> You win the encounter !\n";
            }
        }
    } while (choice("play again", "quit"));
    cout << "\n***************\n** GAME OVER **\n***************\n~~ Thanks for playing ! ~~\n";
    return 0;
}