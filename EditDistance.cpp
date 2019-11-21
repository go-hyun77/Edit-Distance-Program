#include <iostream>
#include <string>
#include <algorithm> 

using namespace std;

void EditDistance(string x, string y, int a, int b);



int main()
{
    string input1;
    string input2;

    cout << "Enter 1st string: ";
    cin >> input1;
    cout << "Enter 2nd string: ";
    cin >> input2;

    return 0; 
}

void EditDistance(string x, string y, int a, int b)
{
    string1 = x; 
    string2 = y; 
    int** table = new int*[a];        //create 2d array for storing words
    for (int i = 0; i < a; i++) {
        table[i] = new int[b];

    }

    int distance = 0; 

    for (int k = 0; k < a+1; k++)
    {
        table[k]][0] = k;
    }

    for (int j = 0; k < b+1; j++)
    {
        table[0][j] = j;

    }

    for (int l = 1; l < b+1; l++)
    {
        for(int m = 1; m <a+1; m++)
        {
            if(string1[m-1] == string2[l-1])
            {
                table[m][l] = table[m-1][l-1]; 
            }
            else
            {
                table[m][l] = min(table[m-1][l-1], min(table[m-1][l], table[m][l-1])); 
            }
        }
        cout <<"edit distance of: " <<table[m+1][l+1]; 
    }

    

}
