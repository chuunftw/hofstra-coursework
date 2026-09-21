#include <iostream>
using namespace std;

int main(){
        cout<< "Please enter an int" << endl;
        int x;
        cin >> x;

        if(cin.fail()) {
        cout << "There was an error" << endl;
        }

        else {
        cout << "Your int was: " << x << endl;
	}

	bool y = true;
	cout << boolalpha<< y << endl;
	float n = 0.3;
	cout << scientific<<n << endl;
return 0;
}


