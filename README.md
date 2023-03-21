# Cerinţa
- Se consideră o tablă de joc de formă dreptunghiulară, împărţită în n lini şi m coloane. Se obţin astfel n*m zone şi se cunoaște înălțimea fiecărei zone. La o poziție cunoscută – linia istart, coloana jstart se află o bilă care se poate deplasa pe o poziție vecină (sus, jos, stânga, dreapta) doar dacă înălțimea poziției vecine este strict mai mică decât înălțimea poziției curente.
- Determinați numărul maxim de zone prin care poate să treacă bila pentru a ajunge pe una dintre marginile tablei de joc.


# Date de intrare
- Fişierul de intrare _board.txt_ conţine pe prima linie numerele n și m. Următoarele n linii conțin câte m numere naturale strict pozitive reprezentând înălțimile fiecărei zone.
Pe linia n+2 se află două numere istart, jstart cu semnificația din enunț.
~~~
4 5
4 4 3 1 5
8 7 2 1 3
9 6 3 2 1
2 5 4 3 7
2 2
~~~

# Date de ieşire
- Pe ecran se va afisa numărul maxim de zone prin care poate să treacă bila pentru a ajunge pe una dintre marginile tablei de joc, inclusiv zona inițială.
~~~
5
~~~

# Restricţii şi precizări
- 1 ≤ n, m ≤ 20
- liniile și coloanele sunt numerotate de la 1
- înălțimea fiecărei zone este cuprinsă între 1 și 50
- când bila ajunge pe o margine a tablei, se oprește acolo. Nu mai continua pe acea margine și nu se poate întoarce în interiorul tablei.
- dacă nu este posibil ca bila să ajungă pe marginea tablei se va afișa un mesaj corespunzator.

# Solution
- Pentru a rezolva această problemă, eu și colega mea, Andreea, am creat o funcție de backtracking recursiva care explorează toate căile posibile și valide pe unde poate mingea sa se miste(sus, jos, stânga, dreapta). Când se găsește o soluție (bila este pe marginea tablei) sau dacă nu mai sunt mișcări posibile, funcția se întoarce la pozitia anteriora valida și continuă verificarea direcțiilor rămase.
- Am inceput funcția verificând dacă a fost găsită o soluție. In cazul afirmativ am calculat _maxim_ care la finalul programului va contine numarul maxim de zone prin care a trecut mingea. De asemenea, am facut o copie a traseului corespunzator maxim-ului curent, deoarece am vrut la sfârșitul programului să afișăm _maxim_ si drumul corespunzator acestuia.
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
- Dacă nu a fost găsită o soluție, continuăm cu celălalt caz în care validăm fiecare direcție (sus, jos, dreapta, stânga), în care se poate deplasa mingea. Dacă se găsește o poziție validă, o marcam cu _true_ și apelăm funcția înapoi cu coordonatele actualizate ale mingii. Acest lucru va continua până când, fie găsim o soluție (bila ajunge pe marginea tablei), fie nu mai există locuri valide în care să mutam mingea. La întoarcere, fiecare instanță a funcției _back_ va continua și va reseta matricea în care drumul este salvat prin setarea pozițiilor marcate anterior de minge în matrice cu _true_ înapoi cu _false_.
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
- Pe lângă cerințele problemei, am afișat și toate căile valide create, în fișierul path.txt.
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
