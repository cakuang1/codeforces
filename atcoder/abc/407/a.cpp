#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int A, B;
    cin >> A >> B;
    // Print A / B, rounded off to an integer.
    cout << round(static_cast<double>(A) / B) << endl;
    return 0;
}