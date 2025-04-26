#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<string>
#include<sstream>
#include <typeinfo>
using namespace std;

/*
Classes Animal, Fish, Bird, Mouse, BetterFish,
BetterMouse, BetterBird, Monster were made by UML diagram.
Added classes and methods will be explained in comments.
*/

class Animal{
    private:
        const string name;
        int daysLived;
    public:
        Animal() : name(""), daysLived(0) {};
        Animal(const string name, int daysLived) : name(name), daysLived(daysLived) {};
        Animal(Animal& other) = default;
        virtual ~Animal() = default;
        int getDaysLived() const { return daysLived;}
        string getName() const { return name;}
        void sayName(){
            cout << "My name is " << name << ", days lived: " << daysLived << endl;
        }
        virtual void attack(Animal& other) = 0;
        void setDaysLived(int newValue){
            daysLived = newValue;
        }
};

class Fish : public virtual Animal{
    public:
        Fish(const string name, int daysLived) : Animal(name, daysLived) {};
        void attack(Animal& other) override{
            cout << "Fish is attacking" << endl;
        }
};

class Bird : public virtual Animal{
    public:
        Bird(const string name, int daysLived) : Animal(name, daysLived) {};
        void attack(Animal& other) override{
            cout << "Bird is attacking" << endl;
        }
};

class Mouse : public virtual Animal{
    public:
        Mouse(const string name, int daysLived) : Animal(name, daysLived) {};
        void attack(Animal& other) override{
            cout << "Mouse is attacking" << endl;
        }
};

class BetterFish : public Fish{
    public:
        BetterFish(string name, int daysLived) : Animal(name, daysLived), Fish(name, daysLived) {};
        BetterFish(Fish& fish) : Animal(fish), Fish(fish) {};
        void attack(Animal& other) override{
            cout << "BetterFish is attacking" << endl;
        }
};

class BetterBird : public Bird{
    public:
        BetterBird(string name, int daysLived) : Animal(name, daysLived), Bird(name, daysLived) {};
        BetterBird(Bird& bird) : Animal(bird), Bird(bird) {};
        void attack(Animal& other) override{
            cout << "BetterBird is attacking" << endl;
        }
};

class BetterMouse : public Mouse{
    public:
        BetterMouse(string name, int daysLived) : Animal(name, daysLived), Mouse(name, daysLived) {};
        BetterMouse(Mouse& mouse) : Animal(mouse), Mouse(mouse) {};
        void attack(Animal& other) override{
            cout << "BetterMouse is attacking" << endl;
        }
};

class Monster : public virtual BetterFish,
                public virtual BetterBird,
                public virtual BetterMouse{
    public:
        Monster(string name) : Animal(name, 1),
                                BetterFish(name, 1), 
                                BetterBird(name, 1), 
                                BetterMouse(name, 1) {};
        Monster(Animal& other) : Animal(other.getName(), 1), 
                                    BetterFish(other.getName(), 1), 
                                    BetterBird(other.getName(), 1), 
                                    BetterMouse(other.getName(), 1) {};
        void attack(Animal& other) override{
            cout << "Monster is attacking" << endl;
        }
};

// It is template Container for different Cages, Aquariums, and Freedom 
template<typename T>
class Container{
    private:
        vector<T*> cont;
    public:
        ~Container() = default;
        void add(T* element){
            cont.push_back(element);
            sort(cont.begin(), cont.end(), &Container<T>::animalComparison);
        }
        bool checkExistence(int number) const {
            return (cont.size() >= (number + 1));
        }
        void del(int number){
            cont.erase(cont.begin() + number);
        }
        // This method was applied after command PERIOD
        // It increases number of days of all animals and check which animals are still alive
        void increaseDay(){
            vector<int> death;
            for (int i = 0; i < cont.size(); i++){
                cont.at(i)->setDaysLived(cont.at(i)->getDaysLived() + 1);
                if ((typeid(*cont.at(i)) != typeid(Monster) && cont.at(i)->getDaysLived() >= 11)
                    || (typeid(*cont.at(i)) == typeid(Monster) && cont.at(i)->getDaysLived() >= 2)){
                    cout << cont.at(i)->getName() << " has died of old days" << endl;
                    death.push_back(i);
                }
            }
            reverse(death.begin(), death.end());
            for (int element : death){
                cont.erase(cont.begin() + element);
            }
        }
        // animalComparison was made for proper work of Container sorting
        // after addition new Animal (or element of type T)
        static bool animalComparison(const T* one, const T* another) {
            if (one->getDaysLived() == another->getDaysLived()) {
                return one->getName() < another->getName();
            }
            return one->getDaysLived() < another->getDaysLived();
        }
        void delAll(){
            cont.clear();
        }
        T* getAnimal(int index){
            return cont.at(index);
        }
};

/*
There are template specialization for Cage<Fish> and Aquarium<Bird>
*/
template<typename P>
class Cage : public Container<P>{};

template<>
class Cage<Fish>{
public:
    Cage() = delete;
    Cage(const Cage<Fish>&) = delete;
    Cage& operator=(const Cage<Fish>&) = delete;
};

template<typename P>
class Aquarium : public Container<P>{};

template<>
class Aquarium<Bird>{
public:
    Aquarium() = delete;
    Aquarium(const Aquarium<Bird>&) = delete;
    Aquarium& operator=(const Aquarium<Bird>&) = delete;
};

template<typename P>
class Freedom : public Container<P>{};

// Creation of all possible containers for animals in advance
Cage<Bird> cageBird;
Cage<BetterBird> cageBetterBird;
Cage<Mouse> cageMouse;
Cage<BetterMouse> cageBetterMouse;
Aquarium<Fish> aquariumFish;
Aquarium<BetterFish> aquariumBetterFish;
Aquarium<Mouse> aquariumMouse;
Aquarium<BetterMouse> aquariumBetterMouse;
Freedom<Animal> freedom;

class ProcedureCommands{
    private:
        int n;
    public:
        ProcedureCommands(int number) : n(number) {};
        void runCommand(){
            //For-loop for each command from input
            for (int i = 0; i < n; i++){

                // Reading string of command and spliting it by words
                string input;
                getline(cin, input);
                vector<string> comand;
                stringstream iss(input);
                string word;
                while (iss >> word) {
                    comand.push_back(word);
                }

                if (comand.at(0) == "CREATE"){
                    // Initialization of type, name, container and day
                    // for creating animal and put it in right container
                    string type = comand.at(1);
                    string name = comand.at(2);
                    string container = comand.at(4);
                    int day= stoi(comand.at(5));

                    // Division of groups by containers
                    // Creation of animal, calling method sayName(), and adding animal in container
                    if (container == "Cage"){
                        if (type == "B"){
                            Bird* bird = new Bird(name, day);
                            bird->sayName();
                            cageBird.add(bird);
                        } else if (type == "BB"){
                            BetterBird* bird = new BetterBird(name, day);
                            bird->sayName();
                            cageBetterBird.add(bird);
                        } else if (type == "M"){
                            Mouse* mouse = new Mouse(name, day);
                            mouse->sayName();
                            cageMouse.add(mouse);
                        } else if (type == "BM"){
                            BetterMouse* mouse = new BetterMouse(name, day);
                            mouse->sayName();
                            cageBetterMouse.add(mouse);
                        }
                    } else if (container == "Aquarium"){
                        if (type == "F"){
                            Fish* fish = new Fish(name, day);
                            fish->sayName();
                            aquariumFish.add(fish);
                        } else if (type == "BF"){
                            BetterFish* fish = new BetterFish(name, day);
                            fish->sayName();
                            aquariumBetterFish.add(fish);
                        } else if (type == "M"){
                            Mouse* mouse = new Mouse(name, day);
                            mouse->sayName();
                            aquariumMouse.add(mouse);
                        } else if (type == "BM"){
                            BetterMouse* mouse = new BetterMouse(name, day);
                            mouse->sayName();
                            aquariumBetterMouse.add(mouse);
                        }
                    } else if (container == "Freedom"){
                        if (type == "B"){
                            Bird* bird = new Bird(name, day);
                            bird->sayName();
                            freedom.add(bird);
                        } else if (type == "BB"){
                            BetterBird* bird = new BetterBird(name, day);
                            bird->sayName();
                            freedom.add(bird);
                        } else if (type == "M"){
                            Mouse* mouse = new Mouse(name, day);
                            mouse->sayName();
                            freedom.add(mouse);
                        } else if (type == "BM"){
                            BetterMouse* mouse = new BetterMouse(name, day);
                            mouse->sayName();
                            freedom.add(mouse);
                        } else if (type == "F"){
                            Fish* fish = new Fish(name, day);
                            fish->sayName();
                            freedom.add(fish);
                        } else if (type == "BF"){
                            BetterFish* fish = new BetterFish(name, day);
                            fish->sayName();
                            freedom.add(fish);
                        }
                    }
                } else if (comand.at(0) == "APPLY_SUBSTANCE"){

                    //Initialization of container for applying substance
                    string container = comand.at(1);

                    // We cannot apply substance only in Freedom, therefore print the message
                    if (container == "Freedom"){
                        cout << "Substance cannot be applied in freedom" << endl;
                    } else {
                        // For all other containers initializing of type and animal position in container
                        string type = comand.at(2);
                        int pos = stoi(comand.at(3));

                        /*
                        For all other containers check the existance of animal in container, otherwise print needed message
                        Get an animal on given position, create better animal or Monster
                        Set new number of days for better animals and remove it from previous container;
                        for monster (number of days was set by constructor) remove all animals in container
                        Put better animal in container for better animals, monster - in Freedom
                        */
                        if (type == "M" && container == "Cage"){
                            if (cageMouse.checkExistence(pos)){
                                Mouse* mouse = cageMouse.getAnimal(pos);
                                BetterMouse* bMouse = new BetterMouse(*mouse);
                                bMouse->setDaysLived((bMouse->getDaysLived() - 1) / 2 + 1);
                                cageMouse.del(pos);
                                cageBetterMouse.add(bMouse);
                                // Deletion the pointer to mouse to avoid memory leakage
                                delete mouse;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "M" && container == "Aquarium"){
                            if (aquariumMouse.checkExistence(pos)){
                                Mouse* mouse = aquariumMouse.getAnimal(pos);
                                BetterMouse* bMouse = new BetterMouse(*mouse);
                                bMouse->setDaysLived((bMouse->getDaysLived() - 1) / 2 + 1);
                                aquariumMouse.del(pos);
                                aquariumBetterMouse.add(bMouse);
                                // Deletion the pointer to mouse to avoid memory leakage
                                delete mouse;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        }else if (type == "BM" && container == "Cage"){
                            if (cageBetterMouse.checkExistence(pos)){
                                BetterMouse* bMouse = cageBetterMouse.getAnimal(pos);
                                Monster* monster = new Monster(*bMouse);
                                cageBetterMouse.delAll();
                                freedom.add(monster);
                                // Deletion the pointer to bMouse to avoid memory leakage
                                delete bMouse;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        }else if (type == "BM" && container == "Aquarium"){
                            if (aquariumBetterMouse.checkExistence(pos)){
                                BetterMouse* bMouse = aquariumBetterMouse.getAnimal(pos);
                                Monster* monster = new Monster(*bMouse);
                                aquariumBetterMouse.delAll();
                                freedom.add(monster);
                                // Deletion the pointer to bMouse to avoid memory leakage
                                delete bMouse;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "F"){
                            if (aquariumFish.checkExistence(pos)){
                                Fish* fish = aquariumFish.getAnimal(pos);
                                BetterFish* bFish = new BetterFish(*fish);
                                bFish->setDaysLived((bFish->getDaysLived() - 1) / 2 + 1);
                                aquariumFish.del(pos);
                                aquariumBetterFish.add(bFish);
                                // Deletion the pointer to fish to avoid memory leakage
                                delete fish;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "BF"){
                            if (aquariumBetterFish.checkExistence(pos)){
                                BetterFish* bFish = aquariumBetterFish.getAnimal(pos);
                                Monster* monster = new Monster(*bFish);
                                aquariumBetterFish.delAll();
                                freedom.add(monster);
                                // Deletion the pointer to bFish to avoid memory leakage
                                delete bFish;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "B"){
                            if (cageBird.checkExistence(pos)){
                                Bird* bird = cageBird.getAnimal(pos);
                                BetterBird* bBird = new BetterBird(*bird);
                                bBird->setDaysLived((bBird->getDaysLived() - 1) / 2 + 1);
                                cageBird.del(pos);
                                cageBetterBird.add(bBird);
                                // Deletion the pointer to bird to avoid memory leakage
                                delete bird;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "BB"){
                            if (cageBetterBird.checkExistence(pos)){
                                BetterBird* bBird = cageBetterBird.getAnimal(pos);
                                Monster* monster = new Monster(*bBird);
                                cageBetterBird.delAll();
                                freedom.add(monster);
                                // Deletion the pointer to bBird to avoid memory leakage
                                delete bBird;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        }    
                    }
                } else if (comand.at(0) == "REMOVE_SUBSTANCE"){

                    //Initialization of container for removing substance
                    string container = comand.at(1);

                    // We cannot remove substance in Freedom, therefore print the message
                    if (container == "Freedom"){
                        cout << "Substance cannot be removed in freedom" << endl;
                    } else {

                        // For all other containers innitializing of type and animal position in container
                        string type = comand.at(2);
                        int pos = stoi(comand.at(3));

                        // We cannont remove substance for some types, when substance was not applied before
                        // Therefore print the message
                        if (type == "M" || type == "B" || type == "F"){
                            cout << "Invalid substance removal" << endl;
                        }
                        
                        /*
                        In other cases get better animal from container,
                        set the new number of days, upcast better Animal to ordinary one,
                        put ordinary animal in container and remove better animal from container for better animals
                        */
                        else if (type == "BM" && container == "Cage"){
                            if (cageBetterMouse.checkExistence(pos)){
                                BetterMouse* bMouse = cageBetterMouse.getAnimal(pos);
                                bMouse->setDaysLived(bMouse->getDaysLived() * 2);
                                Mouse* mouse = bMouse;
                                cageMouse.add(mouse);
                                cageBetterMouse.del(pos);
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        }else if (type == "BM" && container == "Aquarium"){
                            if (aquariumBetterMouse.checkExistence(pos)){
                                BetterMouse* bMouse = aquariumBetterMouse.getAnimal(pos);
                                bMouse->setDaysLived(bMouse->getDaysLived() * 2);
                                Mouse* mouse = bMouse;
                                aquariumMouse.add(mouse);
                                aquariumBetterMouse.del(pos);
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "BF"){
                            if (aquariumBetterFish.checkExistence(pos)){
                                BetterFish* bFish = aquariumBetterFish.getAnimal(pos);
                                bFish->setDaysLived(bFish->getDaysLived() * 2);
                                Fish* fish = bFish;
                                aquariumFish.add(fish);
                                aquariumBetterFish.del(pos);
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "BB"){
                            if (cageBetterBird.checkExistence(pos)){
                                BetterBird* bBird = cageBetterBird.getAnimal(pos);
                                bBird->setDaysLived(bBird->getDaysLived() * 2);
                                Bird* bird = bBird;
                                cageBird.add(bird);
                                cageBetterBird.del(pos);
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        }    
                    }
                } else if (comand.at(0) == "ATTACK"){

                    //Initialization of container for removing substance
                    string container = comand.at(1);

                    // We cannont apply attack in Freedom therefore print the message
                    if (container == "Freedom"){
                        cout << "Animals cannot attack in Freedom" << endl;
                    } else {

                        // For all other containers innitializing of type and animals' position in container
                        string type = comand.at(2);
                        int pos1 = stoi(comand.at(3));
                        int pos2 = stoi(comand.at(4));

                        /*
                        For all other containers check existance of animals on positions otherwise print the message
                        Get animals from container on positions, call method attack, and remove attacked animal from container
                        */
                        if (type == "M" && container == "Cage"){
                            if (cageMouse.checkExistence(pos1) && cageMouse.checkExistence(pos2)){
                                Mouse* mouse1 = cageMouse.getAnimal(pos1);
                                Mouse* mouse2 = cageMouse.getAnimal(pos2);
                                mouse1->attack(*mouse2);
                                cageMouse.del(pos2);
                                // Deletion pointer to mouse2 to avoid memory leackage
                                delete mouse2;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "M" && container == "Aquarium"){
                            if (aquariumMouse.checkExistence(pos1) && aquariumMouse.checkExistence(pos2)){
                                Mouse* mouse1 = aquariumMouse.getAnimal(pos1);
                                Mouse* mouse2 = aquariumMouse.getAnimal(pos2);
                                mouse1->attack(*mouse2);
                                aquariumMouse.del(pos2);
                                // Deletion pointer to mouse2 to avoid memory leackage
                                delete mouse2;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        }else if (type == "BM" && container == "Cage"){
                            if (cageBetterMouse.checkExistence(pos1) && cageBetterMouse.checkExistence(pos2)){
                                BetterMouse* bmouse1 = cageBetterMouse.getAnimal(pos1);
                                BetterMouse* bmouse2 = cageBetterMouse.getAnimal(pos2);
                                bmouse1->attack(*bmouse2);
                                cageBetterMouse.del(pos2);
                                // Deletion pointer to bmouse2 to avoid memory leackage
                                delete bmouse2;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        }else if (type == "BM" && container == "Aquarium"){
                            if (aquariumBetterMouse.checkExistence(pos1) && aquariumBetterMouse.checkExistence(pos2)){
                                BetterMouse* bmouse1 = aquariumBetterMouse.getAnimal(pos1);
                                BetterMouse* bmouse2 = aquariumBetterMouse.getAnimal(pos2);
                                bmouse1->attack(*bmouse2);
                                aquariumBetterMouse.del(pos2);
                                // Deletion pointer to bmouse2 to avoid memory leackage
                                delete bmouse2;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "F"){
                            if (aquariumFish.checkExistence(pos1) && aquariumFish.checkExistence(pos2)){
                                Fish* fish1 = aquariumFish.getAnimal(pos1);
                                Fish* fish2 = aquariumFish.getAnimal(pos2);
                                fish1->attack(*fish2);
                                aquariumFish.del(pos2);
                                // Deletion pointer to fish2 to avoid memory leackage
                                delete fish2;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "BF"){
                            if (aquariumBetterFish.checkExistence(pos1) && aquariumBetterFish.checkExistence(pos2)){
                                BetterFish* bfish1 = aquariumBetterFish.getAnimal(pos1);
                                BetterFish* bfish2 = aquariumBetterFish.getAnimal(pos2);
                                bfish1->attack(*bfish2);
                                aquariumBetterFish.del(pos2);
                                // Deletion pointer to bfish2 to avoid memory leackage
                                delete bfish2;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "B"){
                            if (cageBird.checkExistence(pos1) && cageBird.checkExistence(pos2)){
                                Bird* bird1 = cageBird.getAnimal(pos1);
                                Bird* bird2 = cageBird.getAnimal(pos2);
                                bird1->attack(*bird2);
                                cageBird.del(pos2);
                                // Deletion pointer to bird2 to avoid memory leackage
                                delete bird2;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "BB"){
                            if (cageBetterBird.checkExistence(pos1) && cageBetterBird.checkExistence(pos2)){
                                BetterBird* bbird1 = cageBetterBird.getAnimal(pos1);
                                BetterBird* bbird2 = cageBetterBird.getAnimal(pos2);
                                bbird1->attack(*bbird2);
                                cageBetterBird.del(pos2);
                                // Deletion pointer to bbird2 to avoid memory leackage
                                delete bbird2;
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        }
                    }
                } else if (comand.at(0) == "TALK"){

                    //Initialization of container for removing substance
                    string container = comand.at(1);

                    /*
                    For container Freedom we have different number of words in command string
                    therefore proceed it separetely

                    For all containers:
                    Check existance animal on position, otherwise print the message
                    Get animal from a container, call the method sayName()
                    */
                    if (container == "Freedom"){
                        int pos = stoi(comand.at(2));
                        if (freedom.checkExistence(pos)){
                            freedom.getAnimal(pos)->sayName();
                        } else {
                            cout << "Animal not found" << endl;
                        }
                    } else {
                        string type = comand.at(2);
                        int pos = stoi(comand.at(3));
                        if (type == "M" && container == "Cage"){
                            if (cageMouse.checkExistence(pos)){
                                cageMouse.getAnimal(pos)->sayName();
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "M" && container == "Aquarium"){
                            if (aquariumMouse.checkExistence(pos)){
                                aquariumMouse.getAnimal(pos)->sayName();
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        }else if (type == "BM" && container == "Cage"){
                            if (cageBetterMouse.checkExistence(pos)){
                                cageBetterMouse.getAnimal(pos)->sayName();
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        }else if (type == "BM" && container == "Aquarium"){
                            if (aquariumBetterMouse.checkExistence(pos)){
                                aquariumBetterMouse.getAnimal(pos)->sayName();
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "F"){
                            if (aquariumFish.checkExistence(pos)){
                                aquariumFish.getAnimal(pos)->sayName();
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "BF"){
                            if (aquariumBetterFish.checkExistence(pos)){
                                aquariumBetterFish.getAnimal(pos)->sayName();
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "B"){
                            if (cageBird.checkExistence(pos)){
                                cageBird.getAnimal(pos)->sayName();
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        } else if (type == "BB"){
                            if (cageBetterBird.checkExistence(pos)){
                                cageBetterBird.getAnimal(pos)->sayName();
                            } else {
                                cout << "Animal not found" << endl;
                            }
                        }
                    }
                } else if (comand.at(0) == "PERIOD"){
                    /*
                    For command PERIOD apply method increaseDay() to all containers
                    Method increaseDay() was written in template Container
                    */
                    cageBird.increaseDay();
                    cageBetterBird.increaseDay();
                    cageMouse.increaseDay();
                    cageBetterMouse.increaseDay();
                    aquariumFish.increaseDay();
                    aquariumBetterFish.increaseDay();
                    aquariumMouse.increaseDay();
                    aquariumBetterMouse.increaseDay();
                    freedom.increaseDay();
                }
            }
        }

};

int main(){

    // Reading number of commands
    int n;
    cin >> n;
    cin.ignore(); // to avoid new line after integer
    // Creation a class by constructor that proceeds all commands from input
    ProcedureCommands* program = new ProcedureCommands(n);
    // Calling method for all commands
    program->runCommand();
}