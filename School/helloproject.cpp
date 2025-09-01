#include <bits/stdc++.h>
using namespace std;

class Card {
public:
    string name;
    int health;
    int attack;
    Card(string n, int h, int a) : name(n), health(h), attack(a) {}
};

class Player {
public:
    int hp = 3;
    vector<Card> deck;
    vector<Card> hand;
    Card* activeCard = nullptr;
    
    void drawInitialCards() {
        random_shuffle(deck.begin(), deck.end());
        for (int i = 0; i < 5; i++) {
            hand.push_back(deck.back());
            deck.pop_back();
        }
    }
    
    bool hasAttackCard() {
        for (auto& card : hand) {
            if (card.attack > 0) return true;
        }
        return false;
    }
};

void battle(Player &player, Player &enemy) {
    if (!player.activeCard || !enemy.activeCard) return;
    
    if (player.activeCard->attack >= enemy.activeCard->health) {
        enemy.hp--;
    }
    
    if (enemy.activeCard->attack >= player.activeCard->health) {
        player.activeCard = nullptr;
    }
}

int main() {
    vector<Card> cardPool = {
        {"Chicken", 1, 3}, {"Sheep", 2, 2}, {"Cow", 3, 2}, {"Pig", 3, 2}, {"Dragon", 4, 4}
    };
    
    Player player, enemy;
    player.deck = cardPool;
    enemy.deck = cardPool;
    player.drawInitialCards();
    enemy.drawInitialCards();
    
    while (player.hp > 0 && enemy.hp > 0) {
        // Player chooses attack card
        if (player.hasAttackCard()) {
            player.activeCard = &player.hand[0]; // Simplified selection
            player.hand.erase(player.hand.begin());
        }
        
        // Enemy plays attack card (basic AI)
        if (enemy.hasAttackCard()) {
            enemy.activeCard = &enemy.hand[0];
            enemy.hand.erase(enemy.hand.begin());
        }
        
        // Battle phase
        battle(player, enemy);
        
        cout << "Player HP: " << player.hp << " Enemy HP: " << enemy.hp << endl;
    }
    
    cout << (player.hp > 0 ? "Player Wins!" : "Enemy Wins!") << endl;
}
