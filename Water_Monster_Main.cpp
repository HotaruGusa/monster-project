#include "Lake_Monster.h"
#include "Sea_Monster.h"
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

int get_int_input(string prompt, string invalid, int low, int high);
void monster_mode();
void player_mode();

int main() {
    int choice = get_int_input("Enter 1 to play as a water monster or 2 to play as a person: ",
                             "Invalid choice. Enter 1 or 2: ",
                             1,
                             2);

    if (choice == 1) {
        cout << "You monster!" << endl;
        monster_mode();
    } else {
        cout << "Get ready to face the water monsters!" << endl;
        player_mode();
    }
    return 0;
}

int get_int_input(string prompt, string invalid, int low, int high) {
    cout << prompt;
    int choice = 0;
    string junk;
    while (!(cin >> choice) || choice < low || choice > high) {
        cout << invalid;
        cin.clear();
        getline(cin, junk);
    }
    return choice;
}

void monster_mode() {
    Lake_Monster champ(0);
    // Print welcome message that includes the name Champ the Lake Monster
    cout << "Lake Monster is Here!" << endl;
    // Create vector of unique pointers to Water Monsters called friends
    vector<unique_ptr<Water_Monster>> W_Monster;
    // Populate vector with 10 monsters, choosing Lake vs Sea randomly
    srand(time(NULL));
    for (int i = 0; i < 10; ++i) {
        int k = rand() % 2;
        if (k == 1) {
            W_Monster.push_back(make_unique<Lake_Monster>());
        } else{
            W_Monster.push_back(make_unique<Sea_Monster>());
        }
    }
    // Call get_int_input to prompt the user to choose 1 for meal time, 2 for scare time, or 3 to exit.
    int choice = get_int_input("Choose 1 for meal time, 2 for scare time, or 3 to exit: ",
                               "Error happened, please retype your number: ",
                               1,
                               3);
    //Create a loop that runs until the user chooses option 3:
    //      - If 1 is chosen, loop through populated vector and call eat_person on each.
    //          - This is NOT an example of polymorphism. Why? Answer in your README file.
    //      - If 2 is chosen, print message saying "This is how my friends scare:"
    //          - Loop through populated vector and call scare method on each pointer, printing return value to console
    //          - This IS an example of polymorphism. Why? Answer in your README file.
    //          - Print message saying how Champ scares, then call and print scare method on champ.
    //      - Call get_int_input again with the same options as before.
    while (choice != 3){
        if (choice == 1) {
            for (int i = 0; i < W_Monster.size(); i++) {
                W_Monster[i]->eat_person();
            }
        }
        else if (choice == 2) {
            cout << "This is how my friends scare:" << endl;
            for (int i = 0; i < W_Monster.size(); i++) {
                cout<<W_Monster[i]->scare() << endl;
            }
            cout << "This is how champ scares: ";
            cout<<champ.scare()<<endl;
        }

        choice = get_int_input("Choose 1 for meal time, 2 for scare time, or 3 to exit: ",
                               "Error happened, please retype your number: ",
                               1,
                               3);
    }
}

void player_mode() {
    vector<unique_ptr<Water_Monster>> monsters;
    srand(time(NULL));
    for (int i = 0; i < 10; ++i) {
        if (rand() % 2) {
            monsters.push_back(make_unique<Lake_Monster>());
        } else {
            monsters.push_back(make_unique<Sea_Monster>());
        }
    }
    int index = get_int_input("Enter a number from 0 to " + to_string(monsters.size()-1) + ": ",
                            "Invalid input. Try again: ",
                            0,
                            monsters.size()-1);
    cout << "The monster approaches: " << monsters[index]->scare() << endl;
    int choice = get_int_input("Choose a number between 1 and 3: ",
                             "Invalid input. Pick a number from 1 to 3: ",
                             1,
                             3);
    if (rand() % 3 + 1 == choice) {
        cout << "You were lucky and beat the monster!" << endl;
        monsters.erase(monsters.begin() + index);
    } else {
        cout << "The monster ate you!" << endl;
        monsters[index]->eat_person();
    }
}