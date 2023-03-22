# Cerinta
- Se considera o tabla de joc de forma dreptunghiulara, impartita in n lini si m coloane. Se obtin astfel n*m zone si se cunoaste inaltimea fiecarei zone. La o pozitie cunoscuta – linia istart, coloana jstart se afla o bila care se poate deplasa pe o pozitie vecina (sus, jos, stanga, dreapta) doar daca inaltimea pozitiei vecine este strict mai mica decat inaltimea pozitiei curente.
- Determinati numarul maxim de zone prin care poate sa treaca bila pentru a ajunge pe una dintre marginile tablei de joc.


# Date de intrare
- Fisierul de intrare _board.txt_ contine pe prima linie numerele n si m. Urmatoarele n linii contin cate m numere naturale strict pozitive reprezentand inaltimile fiecarei zone.
Pe linia n+2 se afla doua numere istart, jstart cu semnificatia din enunt.
~~~
4 5
4 4 3 1 5
8 7 2 1 3
9 6 3 2 1
2 5 4 3 7
2 2
~~~

# Date de iesire
- Numarul maxim de zone prin care poate sa treaca bila pentru a ajunge pe una dintre marginile tablei de joc, inclusiv zona initiala.
- Traseul cu numarul maxim de mutari
~~~
5
0 0 0 0 0 
0 1 0 0 0 
0 1 1 1 1 
0 0 0 0 0 
~~~

# Restrictii si precizari
- 1 ≤ n, m ≤ 20
- liniile si coloanele sunt numerotate de la 1
- inaltimea fiecarei zone este cuprinsa intre 1 si 50
- cand bila ajunge pe o margine a tablei, se opreste acolo. Nu mai continua pe acea margine si nu se poate intoarce in interiorul tablei.
- daca nu este posibil ca bila sa ajunga pe marginea tablei se va afisa un mesaj corespunzator.

# Solutie
- Pentru a rezolva aceasta problema, eu si colega mea, Andreea, am creat o functie de backtracking recursiva care exploreaza toate caile posibile si valide pe unde poate mingea sa se miste(sus, jos, stanga, dreapta). Cand se gaseste o solutie (bila este pe marginea tablei) sau daca nu mai sunt miscari posibile, functia se intoarce la pozitia anteriora valida si continua verificarea directiilor ramase.
- Am inceput functia verificand daca a fost gasita o solutie. In cazul afirmativ am calculat _maxim_ care la finalul programului va contine numarul maxim de zone prin care a trecut mingea. De asemenea, am facut o copie a traseului corespunzator maxim-ului curent, deoarece am vrut la sfarsitul programului sa afisam _maxim_ si drumul corespunzator acestuia.
~~~
void back(int i, int j, int k)
{
    if (solutie(i, j))
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
    }
~~~
- Daca nu a fost gasita o solutie, continuam cu celalalt caz in care validam fiecare directie (sus, jos, dreapta, stanga), in care se poate deplasa mingea. Daca se gaseste o pozitie valida, o marcam cu _true_ si apelam functia inapoi cu coordonatele actualizate ale mingii. Acest lucru va continua pana cand, fie gasim o solutie (bila ajunge pe marginea tablei), fie nu mai exista locuri valide in care sa mutam mingea. La intoarcere, fiecare instanta a functiei _back_ va continua si va reseta matricea in care drumul este salvat prin setarea pozitiilor marcate anterior de minge in matrice cu _true_ inapoi cu _false_.
~~~
    else
        {
            Path[i][j] = true;
            if (Board[i + 1][j] < Board[i][j])
            {
                Path[i + 1][j] = true;
                back(i + 1, j, k + 1);
                Path[i + 1][j] = false;
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
~~~
- Pe langa cerintele problemei, am afisat si toate caile valide create, in fisierul path.txt.
~~~
Numarul zonelor trecute: 3
Traseu:

0 0 0 0 0 
0 1 0 0 0 
0 1 0 0 0 
0 1 0 0 0 

Numarul zonelor trecute: 5
Traseu:

0 0 0 0 0 
0 1 0 0 0 
0 1 1 1 1 
0 0 0 0 0 

Numarul zonelor trecute: 2
Traseu:

0 1 0 0 0 
0 1 0 0 0 
0 0 0 0 0 
0 0 0 0 0 

~~~
