#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

void EditDistance(string x, string y, int a, int b);
enum step_direction
{
    STEP_DIRECTION_BOTTTOMRIGHT,
    STEP_DIRECTION_RIGHT,
    STEP_DIRECTION_DOWN
};
vector<step_direction> Alignment(int *arr [], int a, int b);

int main()
{
    string input1;
    string input2;

    cout << "Enter 1st string: ";
    cin >> input1;
    cout << "Enter 2nd string: ";
    cin >> input2;

    EditDistance(input1, input2, input1.length(), input2.length());

    return 0;
}

void EditDistance(string x, string y, int a, int b)
{
    string string1 = x;
    string string2 = y;
    int **table = new int *[a]; //create 2d array for storing words
    for (int i = 0; i < a; i++)
    {
        table[i] = new int[b];
    }

    int distance = 0;

    for (int k = 0; k < a + 1; k++)
    {
        table[k][0] = k;
    }

    for (int j = 0; j < b + 1; j++)
    {
        table[0][j] = j;
    }

    for (int l = 1; l < b + 1; l++)
    {
        for (int m = 1; m < a + 1; m++)
        {
            if (string1[m - 1] == string2[l - 1])
            {
                table[m][l] = table[m - 1][l - 1];
            }
            else
            {
                table[m][l] = min(table[m - 1][l - 1], min(table[m - 1][l], table[m][l - 1]));
            }
        }
        cout << "edit distance of: " << table[a + 1][b + 1];
    }
    vector<step_direction> fixed_align = Alignment(table, a + 1, b + 1);
    cout << fixed_align[1]; 
}

vector<step_direction> Alignment(int *arr [], int a, int b)
{
    vector<step_direction> temp;
    int column = a;
    int row = b;

    if (column == 0 && row == 0)
    {
        return temp;
    }
    else if(column == 0)
    {
        temp.push_back(STEP_DIRECTION_DOWN);
        row--;
        return Alignment(arr, column, row);
    }
    else if (row == 0)
    {
        temp.push_back(STEP_DIRECTION_RIGHT);
        column--;
        return Alignment(arr, column, row);
    }
    else
    {
        if ((arr[row - 1][column - 1] <= arr[row][column]) && ((arr[row - 1][column] >= arr[row][column]) && (arr[row][column - 1] >= arr[row][column])))
        {
            temp.push_back(STEP_DIRECTION_BOTTTOMRIGHT);
            row--; 
            column--; 
            return Alignment(arr, column, row);
        }
        else if ((arr[row-1][column] < arr[row][column]) && (arr[row-1][column] < arr[row][column-1]) )
        {
            temp.push_back(STEP_DIRECTION_RIGHT); 
            column--; 
            return Alignment(arr, column, row);
        }
        else if( (arr[row][column-1] < arr[row][column]) && (arr[row][column-1] <= arr[row-1][column]) )
        {
            temp.push_back(STEP_DIRECTION_DOWN); 
            row--;
            return Alignment(arr, column, row);
        }
        else
        {
            cout<<"Unexpected Check" <<endl;
            return temp; 
        }
    }

    return temp;
}
