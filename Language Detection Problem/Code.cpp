#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int maxNumberWords = 0;
    vector<int> languages;
    languages.assign(n+1, 0);
    unordered_map<string, int> dict;
    for (int i = 1; i < n+1; i++){
        int numb;
        cin >> numb;
        for (int j = 0; j < numb; j++){
            string word;
            cin >> word;
            dict[word] = i;
        }
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++){
        string word;
        cin >> word;
        if (!(dict.find(word) == dict.end())){
            int lang = dict[word];
            languages.at(lang) += 1;
            maxNumberWords = max(maxNumberWords, languages.at(lang));
        }
    }
    for (int i = 1; i < n+1; i++){
        if (languages.at(i) == maxNumberWords){
            cout << i << " ";
        }
    }
}