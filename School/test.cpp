
#include <iostream>
using namespace std;

int main() {
    int totalMatch = 0;
    int Takahashi = 0, Aoki = 0, TakahashiScore = 0, AokiScore = 0;
    cout << "Match:";
    cin >> totalMatch;
    for (int i = 0; i < totalMatch; i++){
        if(totalMatch >= i){
            cout << "Round " << i + 1 << endl;
            cout << "Takahashi's Score:";
            cin >> Takahashi;
            cout << "Aoki's Score:";
            cin >> Aoki;
            if(Takahashi > Aoki){
                TakahashiScore += 1;
            }
            if(Takahashi < Aoki){
                AokiScore += 1;
            }
            if(Takahashi == Aoki){
                continue;
            }
        if(totalMatch < i){
            break;
        }
        }}
    if(TakahashiScore > AokiScore){
        cout << "Takahashi Win";
    } else if(AokiScore > TakahashiScore){
        cout << "Aoki Win";
    } else{
        cout << "Draw";
    }
    return 0;}
