#include <iostream>
#include <string>
#include <algorithm> 

using namespace std;

int EditDistance(string x, string y);

int main()
{
	string input1;
	string input2;

	cout << "Enter 1st string: ";
	cin >> input1;
	cout << "Enter 2nd string: ";
	cin >> input2;

	cout << endl << "Edit distance of: " << EditDistance(input1, input2) << endl;

	system("pause");
}

int EditDistance(string x, string y) {
	int m = x.size();
	int n = y.size();

	int** table = new int*[m + 1];					//create dynamic 2d array for edit distance table
	for (int i = 0; i < (m + 1); i++) {
		table[i] = new int[n + 1];
	}

	
	for (int i = 0; i < (m + 1); i++) {				//fill 1st row with 0 1 2 3 4...
		table[i][0] = i;
	}
	
	for (int j = 0; j < (n + 1); j++) {				//fill 1st column with 0 1 2 3 4...
		table[0][j] = j;
	}

	for (int i = 1; i < (m + 1); i++) {				//recursive edit distance 
		for (int j = 1; j < (n + 1); j++) {
			if (x[i - 1] == y[j - 1]) {
				table[i][j] = table[i - 1][j - 1];		
			}
			else {
				table[i][j] = 1 + min(table[i - 1][j - 1], min(table[i - 1][j], table[i][j - 1]));
			}
		}
	}

	int distance = table[m][n];

	//_______________table print_________________

	cout << "    ";									


	for (int i = 0; i < (n + 1); i++) {				//print first row of 0 1 2 3 4...
		cout << i << "   ";
	}
	
	cout << endl; 

	for (int i = 0; i < m + 1; i++) {				//table print
		cout << endl;
		cout << table[i][0] << "   ";				//print first column of 0 1 2 3 4..

		for (int j = 0; j < n + 1; j++) {			//fill out table
			cout << table[i][j] << "   ";
			}
		cout << endl;
	}

	for (int i = 0; i < m + 1; i++) {				//free memory	
		delete[] table[i];
	}
	delete[] table;

	return distance;
}
