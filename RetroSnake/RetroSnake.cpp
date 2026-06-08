#include <graphics.h>
#include <conio.h>
#include <stdio.h>

int origin_x = 20;
int origin_y = 10;
int block_width = 20;

int ga_width = 27;
int ga_height = 20;

int length = 12;

int snake[100][2] = {
    {14, 11},
    {13, 11},
    {13, 10},
    {12, 10},
    {11, 10},
    {11, 9},
    {11, 8},
    {11, 7},
    {10, 7},
    {9, 7},
    {8, 7},
    {7, 7}
};

int food_x = 0;
int food_y = 0;
int score = 0;

void DrawBorder(void)
{
    int left = origin_x - 1;
    int top = origin_y - 1;
    int right = origin_x + ga_width * block_width + 1;
    int bottom = origin_y + ga_height * block_width + 1;
    rectangle(left, top, right, bottom);
    rectangle(left - 2, top - 2, right + 2, bottom + 2);
}

void DrawUnitBlock(int x, int y, int color)
{
    int left = origin_x + block_width * x;
    int top = origin_y + block_width * y;
    int right = left + block_width;
    int bottom = top + block_width;

    setcolor(color);
    rectangle(left, top, right, bottom);
}

void PrintPositions(void)
{
    for ( int i = 0 ; i < length ; i ++ )
    {
        printf("(%d,%d)", snake[i][0], snake[i][1]);
    }
    printf("\n");
}

int CanMoveLeft()
{
    int new_x = snake[0][0] - 1;
    int new_y = snake[0][1];

    for ( int i = 0 ; i < length ; i ++ )
    {
        if ( new_x == snake[i][0] && new_y == snake[i][1] )
        {
            return -1;
        }
    }

    if ( new_x < 0)
    {
        return -1;
    }

    if ( new_x == food_x && new_y == food_y )
    {
        return 2;
    }

    return 1;
}

int CanMoveRight()
{
    int new_x = snake[0][0] + 1;
    int new_y = snake[0][1];

    for ( int i = 0 ; i < length ; i ++ )
    {
        if ( new_x == snake[i][0] && new_y == snake[i][1] )
        {
            return -1;
        }
    }

    if ( new_x >= ga_width)
    {
        return -1;
    }

    if ( new_x == food_x && new_y == food_y )
    {
        return 2;
    }

    return 1;
}

int CanMoveUp()
{
    int new_x = snake[0][0];
    int new_y = snake[0][1] - 1;

    for ( int i = 0 ; i < length ; i ++ )
    {
        if ( new_x == snake[i][0] && new_y == snake[i][1] )
        {
            return -1;
        }
    }

    if ( new_y < 0)
    {
        return -1;
    }

    if ( new_x == food_x && new_y == food_y )
    {
        return 2;
    }

    return 1;
}

int CanMoveDown()
{
    int new_x = snake[0][0];
    int new_y = snake[0][1] + 1;

    for ( int i = 0 ; i < length ; i ++ )
    {
        if ( new_x == snake[i][0] && new_y == snake[i][1] )
        {
            return -1;
        }
    }

    if ( new_y >= ga_height)
    {
        return -1;
    }

    if ( new_x == food_x && new_y == food_y )
    {
        return 2;
    }

    return 1;
}


bool IsInSnake(int x, int y)
{
    for ( int i = 0 ; i < length ; i ++ )
    {
        if ( x == snake[i][0] && y == snake[i][1] )
        {
            return true;
        }
    }

    return false;
}

void GenerateFood()
{
    while(true)
    {
        food_x = rand() % ga_width;
        food_y = rand() % ga_height;

        if ( IsInSnake(food_x, food_y) == false)
        {
            break;
        }
    }
}

void DrawFood()
{
    DrawUnitBlock(food_x, food_y, GREEN);
}

void MoveRemainingPart()
{
    // 1. Move the remaining part of snake
    for ( int i = length - 1 ; i >= 1 ; i -- )
    {
        snake[i][0] = snake[i - 1][0];
        snake[i][1] = snake[i - 1][1];
    }
}

void MoveSnake(char dir)
{
    int MoveRslt = 0;
    // 2. Move the head of snake
    if ( dir == 'a' )
    {// LEFT
        MoveRslt = CanMoveLeft();
        if ( MoveRslt == 1 || MoveRslt == 2 )
        {
            MoveRemainingPart();
            snake[0][0] = snake[0][0] - 1;
        }
        if ( MoveRslt == 2 )
        {
            score = score + 100;
            printf("SCORE : %d\n", score);

            DrawUnitBlock(food_x, food_y, BLACK);
            GenerateFood();
            DrawFood();
        }
    }
    else if ( dir == 'd' )
    {// RIGHT
        MoveRslt = CanMoveRight();
        if ( MoveRslt == 1 || MoveRslt == 2 )
        {
            MoveRemainingPart();
            snake[0][0] = snake[0][0] + 1;
        }
        if ( MoveRslt == 2 )
        {
            score = score + 100;
            printf("SCORE : %d\n", score);

            DrawUnitBlock(food_x, food_y, BLACK);
            GenerateFood();
            DrawFood();
        }
    }
    else if ( dir == 'w' )
    {// UP
        MoveRslt = CanMoveUp();
        if ( MoveRslt == 1 || MoveRslt == 2 )
        {
            MoveRemainingPart();
            snake[0][1] = snake[0][1] - 1;
        }
        if ( MoveRslt == 2 )
        {
            score = score + 100;
            printf("SCORE : %d\n", score);

            DrawUnitBlock(food_x, food_y, BLACK);
            GenerateFood();
            DrawFood();
        }
    }
    else if ( dir == 's' )
    {// DOWN
        MoveRslt = CanMoveDown();
        if ( MoveRslt == 1 || MoveRslt == 2 )
        {
            MoveRemainingPart();
            snake[0][1] = snake[0][1] + 1;
        }
        if ( MoveRslt == 2 )
        {
            score = score + 100;
            printf("SCORE : %d\n", score);
            DrawUnitBlock(food_x, food_y, BLACK);
            GenerateFood();
            DrawFood();
        }
    }
}

void DrawSnake(int color)
{
    for ( int i = 0 ; i < length ; i ++ )
    {
        int ub_x = snake[i][0];
        int ub_y = snake[i][1];
        DrawUnitBlock(ub_x, ub_y, color);
    }
}

int main(void)
{
    initwindow(640, 480, "My RetroSnake Game!");

    DrawBorder();
    DrawSnake(WHITE);

    GenerateFood();
    DrawFood();

    while(true)
    {
        char Input = getch();
        if ( Input == 'q' )
        {
            break;
        }

        if ( Input == 'a' || Input == 'd' || Input == 's' || Input == 'w' )
        {
            DrawSnake(BLACK);
            MoveSnake(Input);
            DrawSnake(WHITE);
        }

        if ( Input == 'g' )
        {
            DrawUnitBlock(food_x, food_y, BLACK);
            GenerateFood();
            DrawFood();
        }

        if ( Input == 'i' )
        {
            length = length + 1;
        }
    }


    getch();
    closegraph();
}
