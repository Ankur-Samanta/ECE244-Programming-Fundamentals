#include <iostream>
using namespace std;

void readInts() {
	int input;
	cin >> input;
	if (cin.fail()) {
		char input1;
        cin >> input1;
        if (input1 == '.') {
            cout << "Done" << endl;
            return;
        }
        else {
            cout << "error" << endl;
        }
	}
	else {
		cout << input << endl;
	}
}
