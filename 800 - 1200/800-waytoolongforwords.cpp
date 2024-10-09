 #include <iostream>
 #include <string>
using namespace std;
int main() {
    int count; 
    cin >> count;
    cin.ignore();
    

    for (int i = 0 ; i < count  ; ++ i ) {
        string word;
        getline(cin , word); 

        int len = word.length(); 
        if (len > 10) {
            cout << word[0] << (len - 2) << word[len - 1]  << endl; 
        } else {
            cout << word << endl; 
        } 
    }
    return 0; 
}
