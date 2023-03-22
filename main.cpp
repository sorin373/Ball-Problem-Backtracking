#include <iostream>
#include <fstream>

using namespace std;

int Board[20][20], n, m, istart, jstart, maxim;
bool Path[20][20], PathMax[20][20];

void input()
{
    ifstream fin("board.txt");
    fin >> n >> m;
    for (unsigned int i = 1; i <= n; i++)
        for (unsigned int j = 1; j <= m; j++)
            fin >> Board[i][j];
    fin >> istart >> jstart;
    fin.close();
}

void displayInitialData()
{
    cout << "Start coordinates: (" << istart << ", " << jstart << ")\n";
    for (unsigned int i = 1; i <= n; i++)
    {
        for (unsigned int j = 1; j <= m; j++)
            cout << Board[i][j] << " ";
        cout << '\n';
    }
    cout << '\n';
}

void resetPathFile()
{
    ofstream fout;
    fout.open("path.txt", ofstream::out | ofstream::trunc);
    fout.close();
}

void displaySolution(int k)
{
    ofstream fout;
    fout.open("path.txt", ios::app);
    fout << "Number of areas passed: " << k << '\n'
         << "Path:"
         << "\n\n";
    for (unsigned int i = 1; i <= n; i++)
    {
        for (unsigned int j = 1; j <= m; j++)
            fout << Path[i][j] << " ";
        fout << '\n';
    }
    fout << '\n';
    fout.close();
}

bool solution(int i, int j)
{
    if (i == n || i == 1 || j == m || j == 1) // check if the ball has reached the edge
        return true;
    return false;
}

void back(int i, int j, int k)
{
    if (solution(i, j)) // if we reached the edge -> solution -> calculate maximum number of moves
    {
        if (k == 1)
            Path[i][j] = true;

        displaySolution(k);

        if (k > maxim)
        {
            maxim = k;
            for (unsigned int i = 1; i <= n; i++)
                for (unsigned int j = 1; j <= m; j++)
                    PathMax[i][j] = Path[i][j];
        }
    }
    else
    {
        // the back function is called recursively with the new coordinates and updated number of steps if the position is valid
        Path[i][j] = true;
        if (Board[i + 1][j] < Board[i][j])
        {
            Path[i + 1][j] = true;    // mark the position
            back(i + 1, j, k + 1);
            Path[i + 1][j] = false;   // reset position
        }

        if (Board[i - 1][j] < Board[i][j])
        {
            Path[i - 1][j] = true;
            back(i - 1, j, k + 1);
            Path[i - 1][j] = false;
        }

        if (Board[i][j + 1] < Board[i][j])
        {
            Path[i][j + 1] = true;
            back(i, j + 1, k + 1);
            Path[i][j + 1] = false;
        }

        if (Board[i][j - 1] < Board[i][j])
        {
            Path[i][j - 1] = true;
            back(i, j - 1, k + 1);
            Path[i][j - 1] = false;
        }
    }
}

int main()
{
    input();
    displayInitialData();
    resetPathFile();

    back(istart, jstart, 1);

    if (maxim > 0)
    {
        cout << "The maximum no. of areas passed by the ball is: " << maxim << '\n'
             << "Path: "
             << "\n\n";

        for (unsigned int i = 1; i <= n; i++)
        {
            for (unsigned int j = 1; j <= m; j++)
                cout << PathMax[i][j] << " ";
            cout << '\n';
        }
    }
    else
        cout << "There are no possible paths!";
    return 0;
}