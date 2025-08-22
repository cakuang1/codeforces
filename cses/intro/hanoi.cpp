#include <bits/stdc++.h>

using namespace std;

// Recursive function to move 'diskNumber' disks from
// 'sourceStack' to 'destinationStack' using
// 'auxiliaryStack'
void moveDisk(int diskNumber, vector<vector<int> >& moves,
              int sourceStack, int destinationStack,
              int auxiliaryStack)
{
    // Base case: If there is only one disk, move it
    // directly from source to destination
    if (diskNumber == 1) {
        moves.push_back({ sourceStack, destinationStack });
        return;
    }

    // Recursive call 1: Move 'n-1' disks from source to
    // auxiliary, swapping roles of destination and
    // auxiliary stacks
    moveDisk(diskNumber - 1, moves, sourceStack,
             auxiliaryStack, destinationStack);

    // Add the current move to the moves vector
    moves.push_back({ sourceStack, destinationStack });

    // Recursive call 2: Move 'n-1' disks from auxiliary to
    // destination, swapping roles of source and auxiliary
    // stacks
    moveDisk(diskNumber - 1, moves, auxiliaryStack,
             destinationStack, sourceStack);
}

// Function to solve Tower of Hanoi problem
void towerOfHanoi(int numberOfDisks)
{
    vector<vector<int> >
        moves; // Vector to store the sequence of moves
    int sourceStack = 1, destinationStack = 3,
        auxiliaryStack = 2; // Initialize stack indices
    moveDisk(numberOfDisks, moves, sourceStack,
             destinationStack,
             auxiliaryStack); // Call the recursive function

    // Output the total number of moves
    cout << moves.size() << "\n";

    // Output the sequence of moves (source stack to
    // destination stack)
    for (auto move : moves) {
        cout << move[0] << " " << move[1] << "\n";
    }
}

int main()
{
    int n ; cin >> n; 
    towerOfHanoi(
        n); // Call the Tower of Hanoi function
    return 0;
}