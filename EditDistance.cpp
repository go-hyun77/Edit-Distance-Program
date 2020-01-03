
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

enum step_direction                         //Enumeration of edit path taken
{
    STEP_DIRECTION_BOTTTOMRIGHT,
    STEP_DIRECTION_RIGHT,
    STEP_DIRECTION_DOWN
};

//function prototyping
void EditDistance(string x, string y, int a, int b);

vector<step_direction> Alignment(int *arr[], int a, int b, vector<step_direction> path);

int main()
{   
    //main function takes two inputs and runs the EditDistance function
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

    int **table = new int *[a + 1];         //create 2d array for storing ints
    for (int i = 0; i < a + 1; i++)
    {
        table[i] = new int[b + 1];
    }

    int distance = 0;

    for (int k = 0; k < a + 1; k++)     //fills out the first rows and columns of array
    {
        table[k][0] = k;
    }
    cout << endl;
    for (int j = 0; j < b + 1; j++)
    {
        table[0][j] = j;
    }

    for (int l = 1; l < b + 1; l++)     //fills out the 2D array based on previously calculated results based on each character comparisons of the strings
    {                                   
        for (int m = 1; m < a + 1; m++)
        {
            if (string1[m - 1] == string2[l - 1])   //if matches take the previous upper left from current position 
            {
                table[m][l] = table[m - 1][l - 1];
            }
            else    //if no match, take the smallest path to current node and add 1
            {
                table[m][l] = 1 + min(table[m - 1][l - 1], min(table[m - 1][l], table[m][l - 1]));
            }
        }
    }

    for (int i = 0; i < a + 1; i++)  // table print
    { 

        cout << table[i][0] << " | ";

        for (int j = 0; j < b + 1; j++)
        {
            cout << table[i][j] << "   ";
        }

        cout << endl;
    }
    //outputs edit distance and runs Alignment function
    cout << "edit distance of: " << table[a][b] << endl;   
    vector<step_direction> fixed_align = Alignment(table, a, b, fixed_align);
    string Align1 = "";
    string Align2 = "";

    int k = 0;
    int j = 0;
    for (int x = fixed_align.size() - 1; x >= 0; x--)   //aligns both strings based on matrix
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
    //outputs algined strings
    cout << "Alignment for the strings: " << endl 
         << Align1 << endl
         << Align2 << endl;
}

vector<step_direction> Alignment(int *arr[], int a, int b, vector<step_direction> path)
{
    int row = a;
    int column = b;

    if (column == 0 && row == 0)    //if at [0][0] in matrix it is finished
    {
        return path;
    }
    else if (column == 0)           //at an edge so can only go one way
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
        //checks diagonal and conditional
        if ((arr[row - 1][column - 1] <= arr[row][column]) && ((arr[row - 1][column] >= arr[row][column]) && (arr[row][column - 1] >= arr[row][column])))
        {
            path.push_back(STEP_DIRECTION_BOTTTOMRIGHT);
            row--;
            column--;

            return Alignment(arr, row, column, path);
        }
        //if diagonal is strictly less than current 
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
