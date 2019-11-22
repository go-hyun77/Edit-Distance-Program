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

vector<step_direction> Alignment(int *arr[], int a, int b);

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

    int **table = new int *[a + 1]; //create 2d array for storing words
    for (int i = 0; i < a + 1; i++)
    {
        table[i] = new int[b + 1];
    }

    int distance = 0;

    for (int k = 0; k < a + 1; k++)
    {
        table[k][0] = k;
    }
    cout << endl;
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
                table[m][l] = 1 + min(table[m - 1][l - 1], min(table[m - 1][l], table[m][l - 1]));
            }
        }
    }

    for (int i = 0; i < a + 1; i++)
    { // table print
        cout << endl;

        cout << table[i][0] << "   ";

        for (int j = 0; j < b + 1; j++)
        {
            cout << table[i][j] << "   ";
        }

        cout << endl;
    }

    cout << "edit distance of: " << table[a][b] << endl;
    vector<step_direction> fixed_align = Alignment(table, a, b);
    if (!fixed_align.empty())
    {
        cout << fixed_align[0] << endl;
    }
    else
        cout << "empty!" << endl;
}

vector<step_direction> Alignment(int *arr[], int a, int b)
{
    vector<step_direction> temp;
    int row = a;
    int column = b;
    //cout <<a <<"   "  <<b <<endl;
    cout << "column:" << column << endl
         << "row: " << row << endl;
    if (column == 0 && row == 0)
    {
        return temp;
    }
    else if (column == 0)
    {
        temp.push_back(STEP_DIRECTION_DOWN);
        row--;
        return Alignment(arr, row, column);
    }
    else if (row == 0)
    {
        temp.push_back(STEP_DIRECTION_RIGHT);
        column--;
        return Alignment(arr, row, column);
    }
    else
    {
        if ((arr[row - 1][column - 1] <= arr[row][column]) && ((arr[row - 1][column] >= arr[row][column]) && (arr[row][column - 1] >= arr[row][column])))
        {
            temp.push_back(STEP_DIRECTION_BOTTTOMRIGHT);
            row--;
            column--;
            cout << "diag?" << endl;
            return Alignment(arr, row, column);
        }
        else if ((arr[row - 1][column] < arr[row][column]) && (arr[row - 1][column] <= arr[row][column - 1]))
        {
            temp.push_back(STEP_DIRECTION_DOWN);
            row--;
            cout << "right?" << endl;
            return Alignment(arr, row, column);
        }
        else if ((arr[row][column - 1] < arr[row][column]) && (arr[row][column - 1] <= arr[row - 1][column]))
        {
            temp.push_back(STEP_DIRECTION_RIGHT);
            column--;
            cout << "down" << endl;
            return Alignment(arr, row, column);
        }
        else
        {
            cout << "Unexpected Check" << endl;
            return temp;
        }
    }

    return temp;
}
