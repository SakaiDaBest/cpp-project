#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Define the number of pairs
    int n = 6;

    // Declare the pairs of integers (a_i, b_i)
    vector<pair<int, int>> pairs(n);
    for(int i =0; i < n;i++){
        cin >> pairs[i].first >> pairs[i].second;
    }

    // Sort the pairs based on the sum of (a_i + b_i) in descending order
    sort(pairs.begin(), pairs.end(), [](const pair<int, int>& p1, const pair<int, int>& p2) {
        return (p1.first + p1.second) > (p2.first + p2.second);
    });

    // Initialize the scores for Evirir (X) and Rhae (Y)
    int X = 0, Y = 0;

    // Simulate the turns
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            // Evirir's turn (add a_i to X)
            X += pairs[i].first;
        } else {
            // Rhae's turn (add b_i to Y)
            Y += pairs[i].second;
        }
    }

    // Calculate the final value of X - Y
    int final_score = X - Y;

    // Output the result
    cout << "Final score (X - Y): " << final_score << endl;

    return 0;
}
