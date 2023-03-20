#include <iostream>
#include <fstream>

using namespace std;

int tabla[25][25], n, m, istart, jstart, maxim;
bool traseu[25][25], traseuMax[25][25];

void citireDate(void)
{
    ifstream fin("tabla.txt");
    fin >> n >> m;
    for (unsigned int i = 1; i <= n; i++)
        for (unsigned int j = 1; j <= m; j++)
            fin >> tabla[i][j];
    fin >> istart >> jstart;
    fin.close();
}

void afisareDateInitiale(void)
{
    cout << "Coordonate inceput: (" << istart << ", " << jstart << ")\n";
    for (unsigned int i = 1; i <= n; i++)
    {
        for (unsigned int j = 1; j <= m; j++)
            cout << tabla[i][j] << " ";
        cout << '\n';
    }
    cout << '\n';
}

bool solutie(int i, int j)
{
    if (i == n || i == 1 || j == m || j == 1)  // verifica daca bila a ajuns pe margine
        return true;
    return false;
}

void tiparSolutie(int k)
{
    ofstream fout("traseu.txt");
    fout << "Numarul zonelor trecute: " << k << '\n' << "Traseu:" << "\n\n";
    for (unsigned int i = 1; i <= n; i++)
    {
        for (unsigned int j = 1; j <= m; j++)
            fout << traseu[i][j] << " ";
        fout << '\n';
    }
    fout << '\n';
    fout.close();
}

void back(int i, int j, int k)
{
    if (solutie(i,j)) // daca am ajuns la margine -> soltutie -> calculam nr. maxim de mutari
    {
        tiparSolutie(k);

        if (k > maxim)
        {
            maxim = k;
            for (unsigned int i = 1; i <= n; i++)
                for (unsigned int j = 1; j <= m; j++)
                    traseuMax[i][j] = traseu[i][j];
        }

        traseu[i][j] = false;
    }
    else
    {
        // se apeleaza recursiv functia back cu noile coordonate si nr de pasi actualizat
        // daca pozitia este valida
        traseu[i][j] = true;
        if (tabla[i + 1][j] < tabla[i][j])
        {
            traseu[i + 1][j] = true; // marcam pozitia pe unde am trecut
            back(i + 1, j, k + 1);
            traseu[i + 1][j] = false; // resetam pozitia
        }

        if (tabla[i - 1][j] < tabla[i][j])
        {
            traseu[i - 1][j] = true;
            back(i - 1, j, k + 1);
            traseu[i - 1][j] = false;
        }

        if (tabla[i][j + 1] < tabla[i][j])
        {
            traseu[i][j + 1] = true;
            back(i, j + 1, k + 1);
            traseu[i][j + 1] = false;
        }

        if (tabla[i][j - 1] < tabla[i][j])
        {
            traseu[i][j - 1] = true;
            back(i, j - 1, k + 1);
            traseu[i][j - 1] = false;
        }
    }
}

int main(void)
{
    citireDate();
    afisareDateInitiale();

    back(istart, jstart, 1);

    cout  << "_____________________________________" << "\n\n"
          << "Numarul maxim de zone trecute este: " << maxim << '\n' << "Traseu: " << "\n\n";
    for (unsigned int i = 1; i <= n; i++)
    {
        for (unsigned int j = 1; j <= m; j++)
            cout << traseuMax[i][j] << " ";
        cout << '\n';
    }
    return 0;
}