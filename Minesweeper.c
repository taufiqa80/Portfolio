#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int board[100][100]; //can be set to dynamic
int open[100][100];
int count = 0;
/*
Note:
Bomb = 9
Empty Space = 0
Unopened Space = 10
Numbers of nearby bombs = Numbers
*/

//X Y data type to store bomb location
struct coordinate
{
    int x;
    int y;
};

//X Y array to store all bomb location
struct coordinate bomb[10000];

//Function to generate nu,ber around bombs
void add_num (int x, int y, int N)
{
    //all spaces around bomb increment by 1 (except for bomb spaces and edges, ignore those)
    if ((board[x-1][y-1] != 9) && (x!=0) && (y!=0))
    {
        board[x-1][y-1]++;
    }
    if ((board[x-1][y] != 9) && (x!=0))
    {
        board[x-1][y]++;
    }
    if ((board[x-1][y+1] != 9) && (x!=0) && (y!=N))
    {
        board[x-1][y+1]++;
    }
    if ((board[x][y-1] != 9) && (y!=0))
    {
        board[x][y-1]++;
    }
    if ((board[x][y+1] != 9) && (y!=N))
    {
        board[x][y+1]++;
    }
    if ((board[x+1][y-1] != 9) && (x!=N) && (y!=0))
    {
        board[x+1][y-1]++;
    }
    if ((board[x+1][y] != 9) && (x!=N))
    {
        board[x+1][y]++;
    }
    if ((board[x+1][y+1] != 9) && (x!=N) && (y!=N))
    {
        board[x+1][y+1]++;
    }
}

void Initialize (int N, int B)
{
    int i, j, x, y;

    //initialize board with number 0 (empty space)
    //and initialize opened matrix with 10 (unopened spaces)
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            board[i][j] = 0;
            open[i][j] = 10;
        }
    }

    //generate bomb placement (9 digit is bomb) and generate number around bomb and also insert bomb coordinate to bomb list
    for(i=0;i<B;i++)
    {
        do
        {
            x = rand()%N;
            y = rand()%N;
        }while (board[x][y] == 9);
        board[x][y] = 9;
        bomb[i].x = x;
        bomb[i].y = y;
        add_num(x,y,N);
    }
}

//print initial board for test purposes (can be omitted if playing for real)
void print_board (int N)
{
    int i, j;
    printf("\n");
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            printf("%d", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//open all spaces until no empty spaces nearby
void buka(int x, int y, int N)
{
    if ((x>0) && (y>0))
    {
        open[x-1][y-1] = board[x-1][y-1];
        if (board[x-1][y-1] == 0)
        {
            count++;
            board[x-1][y-1] = 11;
            buka(x-1,y-1, N);
        }
    }
    if (x>0)
    {
        open[x-1][y] = board[x-1][y];
        if (board[x-1][y] == 0)
        {
            count++;
            board[x-1][y] = 11;
            buka(x-1,y, N);
        }
    }
    if ((x>0) && (y<N))
    {
        open[x-1][y+1] = board[x-1][y+1];
        if (board[x-1][y+1] == 0)
        {
            count++;
            board[x-1][y+1] = 11;
            buka(x-1,y+1, N);
        }
    }
    if (y>0)
    {
        open[x][y-1] = board[x][y-1];
        if (board[x][y-1] == 0)
        {
            count++;
            board[x][y-1] = 11;
            buka(x,y-1, N);
        }
    }
    if (y<N)
    {
        open[x][y+1] = board[x][y+1];
        if (board[x][y+1] == 0)
        {
            count++;
            board[x][y+1] = 11;
            buka(x,y+1, N);
        }
    }
    if ((x<N) && (y>0))
    {
        open[x+1][y-1] = board[x+1][y-1];
        if (board[x+1][y-1] == 0)
        {
            count++;
            board[x+1][y-1] = 11;
            buka(x+1,y-1, N);
        }
    }
    if (x<N)
    {
        open[x+1][y] = board[x+1][y];
        if (board[x+1][y] == 0)
        {
            count++;
            board[x+1][y] = 11;
            buka(x+1,y, N);
        }
    }
    if ((x<N) && (y<N))
    {
        open[x+1][y+1] = board[x+1][y+1];
        if (board[x+1][y+1] == 0)
        {
            count++;
            board[x+1][y+1] = 11;
            buka(x+1,y+1, N);
        }
    }
}

void print_open (int N)
{
    int i, j;
    printf("\n");
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if (open[i][j] == 10)
            {
                printf(".");
            }
            else if (open[i][j] == 9)
            {
                printf("B");
            }
            else if ((open[i][j] == 0) || (open[i][j] == 11))
            {
                printf(" ");
            }
            else
            {
                printf("%d", open[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void play (int N, int B)
{
    int x, y, i;
    int done = 0;
    do
    {
        scanf("%d %d", &x, &y);
        open[x][y] = board[x][y];
        count++;
        if (board[x][y] == 0) //empty space
        {
            count--;
            buka(x,y, N);
        }
        else if (board[x][y] == 9) //bomb space game over
        {
            done = 1;
            for(i=0;i<B;i++)
            {
                open[bomb[i].x][bomb[i].y] = board[bomb[i].x][bomb[i].y];
            }
            printf("!GAME OVER!\n");
        }
        if ((board[x][y] != 9) && (count >= ((N*N)-B)))
        {
            done = 1;
            printf("\n!!!YOU WIN!!!");
        }
        print_open(N);
    }while (done == 0);
}

int main()
{
    srand(time(NULL));
    int N, B;

    scanf("%d", &N);
    scanf("%d", &B);

    Initialize(N, B);

    //print initial board for test purposes (can be omitted if playing for real)
    print_board(N);

    play(N, B);

    return 0;
}
