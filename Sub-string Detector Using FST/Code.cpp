#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Meshcheriakova_Anna_FST{
    private:
        string substring;
        int state = 0;
        vector<int> states;
        void transition_function(char charr) {
            for (int i = 0; i < states.size(); i++){
                if (charr == substring.at(states.at(i))){
                    states.at(i) ++;
                } else{
                    states.at(i) = -1;
                }
            }
            states.erase(remove(states.begin(), states.end(), -1), states.end());
            if (charr == substring.at(0)){
                states.push_back(1);
            }
        }
        bool output_function(){
            if (find(states.begin(), states.end(), substring.size()) != states.end()){
                states.erase(remove(states.begin(), states.end(), substring.size()), states.end());
                return true;
            } return false;
        }
    public:
        Meshcheriakova_Anna_FST(string substring){
            this->substring = substring;
        }
        bool process(char charr){
            transition_function(charr);
            return output_function();
        }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string substring;
    cin >> substring;
    Meshcheriakova_Anna_FST fst(substring);
    int tot = 0;
    cin.ignore(); //Ignore the newline in the input
    string input;
    cin >> input;
    for (char ch : input) {
        if (fst.process(ch)) {
            tot++;
        }
    }
    if (tot == 0){
        cout << "NOT DETECTED" << endl;
    } else {
        cout << tot << endl;
    }
    return 0;
}