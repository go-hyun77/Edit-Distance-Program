#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

enum step_direction
{
    STEP_DIRECTION_BOTTTOMRIGHT,
    STEP_DIRECTION_RIGHT,
    STEP_DIRECTION_DOWN
};

void EditDistance(string x, string y, int a, int b);

vector<step_direction> Alignment(int *arr[], int a, int b, vector<step_direction> path);

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

        cout << table[i][0] << " | ";

        for (int j = 0; j < b + 1; j++)
        {
            cout << table[i][j] << "   ";
        }

        cout << endl;
    }

    cout << "edit distance of: " << table[a][b] << endl;
    vector<step_direction> fixed_align = Alignment(table, a, b, fixed_align);
    string Align1 = "";
    string Align2 = "";

    int k = 0;
    int j = 0;
    for (int x = fixed_align.size() - 1; x >= 0; x--)
    {
        if (fixed_align[x] == STEP_DIRECTION_BOTTTOMRIGHT || fixed_align[x] == STEP_DIRECTION_DOWN)
        {
            Align1 += string1[k];
            k++;
        }
        else if (fixed_align[x] == STEP_DIRECTION_RIGHT)
        {
            Align1 += "_";
        }
    }

    for (int y = fixed_align.size() - 1; y >= 0; y--)
    {
        if (fixed_align[y] == STEP_DIRECTION_BOTTTOMRIGHT || fixed_align[y] == STEP_DIRECTION_RIGHT)
        {
            Align2 += string2[j];
            j++;
        }
        else if (fixed_align[y] == STEP_DIRECTION_DOWN)
        {
            Align2 += "_";
        }
    }

    cout << "Alignment for the strings: " << endl
         << Align1 << endl
         << Align2 << endl;
}

vector<step_direction> Alignment(int *arr[], int a, int b, vector<step_direction> path)
{
    int row = a;
    int column = b;
    if (column == 0 && row == 0)
    {
        return path;
    }
    else if (column == 0)
    {
        path.push_back(STEP_DIRECTION_DOWN);
        row--;
        return Alignment(arr, row, column, path);
    }
    else if (row == 0)
    {
        path.push_back(STEP_DIRECTION_RIGHT);
        column--;
        return Alignment(arr, row, column, path);
    }
    else
    {
        if ((arr[row - 1][column - 1] <= arr[row][column]) && ((arr[row - 1][column] >= arr[row][column]) && (arr[row][column - 1] >= arr[row][column])))
        {
            path.push_back(STEP_DIRECTION_BOTTTOMRIGHT);
            row--;
            column--;

            return Alignment(arr, row, column, path);
        }
        else if (arr[row - 1][column - 1] < arr[row][column])
        {
            path.push_back(STEP_DIRECTION_BOTTTOMRIGHT);
            row--;
            column--;

            return Alignment(arr, row, column, path);
        }
        else if ((arr[row - 1][column] < arr[row][column]) && (arr[row - 1][column] <= arr[row][column - 1]))
        {
            path.push_back(STEP_DIRECTION_DOWN);
            row--;

            return Alignment(arr, row, column, path);
        }
        else if ((arr[row][column - 1] < arr[row][column]) && (arr[row][column - 1] <= arr[row - 1][column]))
        {
            path.push_back(STEP_DIRECTION_RIGHT);
            column--;

            return Alignment(arr, row, column, path);
        }
        else
        {
            cout << "Unexpected Check" << endl;
            return path;
        }
    }

    return path;
}
