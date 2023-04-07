#include <iostream>

using namespace std;

int main(void) {
    string s = "";
    int i = 63636;

    cout << "\nType an integer: ";
    cin >> i;
    cout << endl;

    while (i) {
        s.insert(0,(i%2) ? "1" : "0");
        cout << i << " " << s << endl;
        i = i >> 1;
    }

    return 0;
}
