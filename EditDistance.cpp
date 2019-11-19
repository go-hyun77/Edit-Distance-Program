#include <iostream>
#include <string>

using namespace std;

void EditDistance(string x, string y, int a, int b);

int main() {
	string input1;
	string input2;

	cout << "Enter 1st string: ";
	cin >> input1;
	cout << "Enter 2nd string: ";
	cin >> input2;

	EditDistance(input1, input2, input1.length(), input2.length());



	system("pause");

		
	
}

void EditDistance(string x, string y, int a, int b) {

	
	
}
