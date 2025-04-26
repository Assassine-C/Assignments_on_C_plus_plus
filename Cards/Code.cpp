#include <iostream>
#include <vector>
using namespace std;

// Member function find_game_result find the win cards of both players and the print the game's result
void find_game_result(vector<int>& Ahmed_card,  vector<int>& Karim_card){
    vector<int> Ahmed_win(Ahmed_card.size(), -1);
    vector<int> Karim_win(Karim_card.size(), -1);
    int A_win = 0;
    int K_win = 0;

    // In these two for-loops values of players' cards are considered, finds win cards and mark them as "used" by -1
    for (int i = 0; i < Ahmed_card.size(); i++){
        for (int j = 0; j < Karim_card.size(); j++){
            if (Ahmed_card.at(i) == Karim_card.at(j)){
                if(i < j){
                    Ahmed_win.at(i) = Ahmed_card.at(i);
                    A_win ++;
                } else if(j < i){
                    Karim_win.at(j) = Karim_card.at(j);
                    K_win ++;
                }
                Ahmed_card.at(i) = -1;
                Karim_card.at(j) = -1;
                break;
            }
        }
    }
    // Print of Ahmed's win cards
    if (A_win != 0){
        for (int card : Ahmed_win){
            if (card != -1){
                cout << card << " ";
            }
        }
    } else {
        cout << "-";
    }
    cout << endl;
    // Print of Karim's win cards
    if (K_win != 0){
        for (int card : Karim_win){
            if (card != -1){
                cout << card << " ";
            }
        }
    } else {
        cout << "-";
    }
    cout << endl;
    // Print the result of game
    if (A_win > K_win){
        cout << "Ahmed" << endl;
    } else if (K_win > A_win){
        cout << "Karim" << endl;
    } else{
        cout << "Tie" << endl;
    }
}
// Member function main create two vectors and read Ahmed's and Karim's cards to it
// Then it calls the member function find_game_result
int main(){
    vector<int> Ahmed_card;
    vector<int> Karim_card;
    int number;
    cin >> number;
    while (number != 0){
        Ahmed_card.push_back(number);
        cin >> number;
    }
    cin >> number;
    while (number != 0){
        Karim_card.push_back(number);
        cin >> number;
    }
    find_game_result(Ahmed_card, Karim_card);
    return 0;
}