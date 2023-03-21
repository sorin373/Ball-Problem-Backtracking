# Problem Question
- Consider a rectangular game board, divided into n lines and m columns. In this way, n*m zones are obtained and the height of each zone is known. At a known position - line istart, column jstart there is a ball that can move to a neighboring position (up, down, left, right) only if the height of the neighboring position is strictly lower than the height of the current position.
- Determine the maximum number of zones the ball can pass through to reach one of the edges of the game board.


# Input
- The input file _board.txt_ contains the numbers n and m on the first line. The next n lines contain m strictly positive natural numbers representing the heights of each zone.
On line n+2 there are two numbers istart, jstart with the meaning in the statement.
~~~
4 5
4 4 3 1 5
8 7 2 1 3
9 6 3 2 1
2 5 4 3 7
2 2
~~~

# Output
- On the screen it will be shown the maximum number of zones through which the ball can pass to reach one of the edges of the game board, including the starting zone.
~~~
5
~~~

# Restrictions and clarifications
- 1 ≤ n, m ≤ 20
- rows and columns are numbered from 1
- the height of each zone is between 1 and 50
- when the ball reaches an edge of the board, it stops there. It does not continue on that edge and cannot return to the inside of the board.
- if it is not possible for the ball to reach the edge of the board, a message will be displayed

# Solution
- Me and my colleague created a reccursive backtracking algorithm which explores all possible paths in each of the four directions (up, down, left, right), if the condition is met.
~~~
{
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
~~~
- After a solution is found (the ball reached the edge of the board) we calculate _maxim_ which at the end of the program will contain the maximum number of zones through which the ball passed.
~~~
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

        Path[i][j] = false;
    }
~~~
- In addition to the problem's reqirements we also displayed all the paths created, in the file _path.txt_.
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
