#include <iostream>
#include <fstream>

using namespace std;

int Board[25][25], n, m, istart, jstart, maxim;
bool Path[25][25], PathMax[25][25];

void citireDate()
{
    ifstream fin("board.txt");
    fin >> n >> m;
    for (unsigned int i = 1; i <= n; i++)
        for (unsigned int j = 1; j <= m; j++)
            fin >> Board[i][j];
    fin >> istart >> jstart;
    fin.close();
}

void afisareDateInitiale()
{
    cout << "Coordonate inceput: (" << istart << ", " << jstart << ")\n";
    for (unsigned int i = 1; i <= n; i++)
    {
        for (unsigned int j = 1; j <= m; j++)
            cout << Board[i][j] << " ";
        cout << '\n';
    }
    cout << '\n';
}

void resetFisierTraseu()
{
    ofstream fout;
    fout.open("path.txt", ofstream::out | ofstream::trunc);
    fout.close();
}

void tiparSolutie(int k)
{
    ofstream fout;
    fout.open("path.txt", ios::app);
    fout << "Numarul zonelor trecute: " << k << '\n'
         << "Traseu:"
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

bool solutie(int i, int j)
{
    if (i == n || i == 1 || j == m || j == 1) // verifica daca bila a ajuns pe margine
        return true;
    return false;
}

void back(int i, int j, int k)
{
    if (solutie(i, j)) // daca am ajuns la margine -> soltutie -> calculam nr. maxim de mutari
    {
        if (k == 1)
            Path[i][j] = true;

        tiparSolutie(k);

        if (k > maxim)
        {
            maxim = k;
            for (unsigned int i = 1; i <= n; i++)
                for (unsigned int j = 1; j <= m; j++)
                    PathMax[i][j] = Path[i][j];
        }

        Path[i][j] = false;
    }
    else
    {
        // se apeleaza recursiv functia back cu noile coordonate si nr de pasi actualizat
        // daca pozitia este valida
        Path[i][j] = true;
        if (Board[i + 1][j] < Board[i][j])
        {
            Path[i + 1][j] = true;    // marcam pozitia pe unde am trecut
            back(i + 1, j, k + 1);
            Path[i + 1][j] = false;   // resetam pozitia
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
    citireDate();
    afisareDateInitiale();
    resetFisierTraseu();

    back(istart, jstart, 1);

    if (maxim > 0)
    {
        cout << "Numarul maxim de zone trecute este: " << maxim << '\n'
             << "Traseu: "
             << "\n\n";

        for (unsigned int i = 1; i <= n; i++)
        {
            for (unsigned int j = 1; j <= m; j++)
                cout << PathMax[i][j] << " ";
            cout << '\n';
        }
    }
    else
        cout << "Nu exista trasee posibile!";
    return 0;
}