#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>

int origin_x = 40;
int origin_y = 40;
int block_width = 25;

int ga_width = 16;
int ga_height = 16;

int color[8] = {BLUE, GREEN, RED, CYAN, LIGHTBLUE, LIGHTGREEN, YELLOW, LIGHTRED};

int count_mines = 40;

#define MAP_EMPTY       0
#define MAP_MINE        1

#define STATUS_INIT     0
#define STATUS_CLICKED  1
#define STATUS_MARKED   2

int Map[16][16];
int Status[16][16];

void DrawBorder(void)
{
    // 1. Left : Game area
    int left = origin_x - 1;
    int top = origin_y - 1;
    int right = origin_x + ga_width * block_width + 1;
    int bottom = origin_y + ga_height * block_width + 1;
    rectangle(left, top, right, bottom);
    rectangle(left - 2, top - 2, right + 2, bottom + 2);

    // 2. Right-Top : Next Tetris
    int left2 = right + 50;
    int top2 = top;
    int right2 = left2 + 160;
    int bottom2 = top2 + 120;
    rectangle(left2, top2, right2, bottom2);
    rectangle(left2 - 2, top2 - 2, right2 + 2, bottom2 + 2);

    // 3. Right-Middle : Score
    int left3 = left2;
    int top3 = bottom2 + 20;
    int right3 = left3 + 160;
    int bottom3 = top3 + 60;
    rectangle(left3, top3, right3, bottom3);
    rectangle(left3 - 2, top3 - 2, right3 + 2, bottom3 + 2);

    // 4. Right-Bottom : Help Info.
    int left4 = left2;
    int top4 = bottom3 + 20;
    int right4 = left4 + 160;
    int bottom4 = bottom;
    rectangle(left4, top4, right4, bottom4);
    rectangle(left4 - 2, top4 - 2, right4 + 2, bottom4 + 2);

    char buffer[256];
    for ( int i = 0 ; i < ga_width ; i ++ )
    {
        sprintf(buffer, "%d", i);
        setcolor(WHITE);
        setbkcolor(BLACK);
        outtextxy(left + i * block_width + 9
                , top - block_width
                , buffer);
        outtextxy(left - block_width
                , top + i * block_width + 2
                , buffer);
        outtextxy(left + i * block_width + 9
                , bottom + 5
                , buffer);
        outtextxy(right + 9
                , top + i * block_width + 2
                , buffer);

    }
}

void EraseBlock(int x, int y)
{
    int left = origin_x + block_width * x;
    int top = origin_y + block_width * y;
    int right = left + block_width - 1;
    int bottom = top + block_width - 1;
    setcolor(BLACK);
    rectangle(left, top, right, bottom);

    setfillstyle(SOLID_FILL, BLACK);
    floodfill(left + 2, top + 2, BLACK);
}

void DrawInitBlock(int x, int y)
{
    int left = origin_x + block_width * x;
    int top = origin_y + block_width * y;
    int right = left + block_width - 1;
    int bottom = top + block_width - 1;

    setcolor(LIGHTGRAY);
    rectangle(left, top, right, bottom);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    floodfill(left + 2, top + 2, LIGHTGRAY);

    setcolor(WHITE);
    line(left, top, right, top);
    line(left, top, left, bottom);

    setcolor(DARKGRAY);
    line(right, top, right, bottom);
    line(left, bottom, right, bottom);
}


void DrawClickedBlock(int x, int y)
{

    int left = origin_x + block_width * x;
    int top = origin_y + block_width * y;
    int right = left + block_width - 1;
    int bottom = top + block_width - 1;

    setcolor(DARKGRAY);
    rectangle(left, top, right, bottom);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    floodfill(left + 2, top + 2, DARKGRAY);
}

void GenMines()
{
    for ( int i = 0 ; i < count_mines ; i ++ )
    {
        int x = rand() % ga_width;
        int y = rand() % ga_height;
        if ( Map[x][y] == MAP_MINE )
        {
            i = i - 1;
        }
        else
        {
            Map[x][y] = MAP_MINE;
        }
    }
}

void PaintMine(int x, int y)
{
    int left = origin_x + block_width * x;
    int top = origin_y + block_width * y;
    int right = left + block_width - 1;
    int bottom = top + block_width - 1;

    setcolor(RED);
    setbkcolor(LIGHTGRAY);
    outtextxy(left + 10, top + 5, "*");
}

void PaintNumber(int x, int y, int number)
{
    int left = origin_x + block_width * x;
    int top = origin_y + block_width * y;
    int right = left + block_width - 1;
    int bottom = top + block_width - 1;

    setcolor(color[number - 1]);
    setbkcolor(LIGHTGRAY);

    char Buffer[256];
    sprintf(Buffer, "%d", number);
    outtextxy(left + 9, top + 5, Buffer);
}

void PaintRedFlag(int x, int y)
{
    int left = origin_x + block_width * x;
    int top = origin_y + block_width * y;
    int right = left + block_width - 1;
    int bottom = top + block_width - 1;

    int center_x = (left + right) / 2;
    int center_y = (top + bottom) / 2;

    int top_x = center_x;
    int top_y = top + 3;

    int right_x = right - 3;
    int right_y = center_y;

    int bottom_x = center_x;
    int bottom_y = bottom - 3;

    setcolor(BLACK);
    line(center_x, center_y, bottom_x, bottom_y);

    setcolor(RED);
    line(center_x, center_y, top_x, top_y);
    line(top_x, top_y, right_x, right_y);
    line(right_x, right_y, center_x, center_y);

    setfillstyle(SOLID_FILL, RED);
    floodfill(center_x + 2, center_y - 2, RED);
}

int GetCountOfMines(int x, int y)
{
    int count = 0;
    for ( int i = x - 1 ; i <= x + 1 ; i ++ )
    {
        if ( i < 0 || i >= ga_width )
        {
            continue;
        }
        for ( int j = y - 1 ; j <= y + 1 ; j ++ )
        {
            if ( j < 0 || j >= ga_height )
            {
                continue;
            }
            if ( Map[i][j] == MAP_MINE )
            {
                count ++;
            }
        }
    }
    return count;
}

void AutoClickNeighbors(int x, int y)
{
    for ( int i = x - 1 ; i <= x + 1 ; i ++ )
    {
        for ( int j = y - 1 ; j <= y + 1 ; j ++ )
        {
            if ( i < 0 || i >= ga_width || j < 0 || j >= ga_height )
            {
                continue;
            }
            if ( i == x && j == y )
            {
                continue;
            }
            if ( Status[i][j] == STATUS_INIT )
            {
                Status[i][j] = STATUS_CLICKED;
                DrawClickedBlock(i, j);

                int CntOfMines = GetCountOfMines(i, j);
                if ( CntOfMines > 0 )
                {
                    PaintNumber(i, j, CntOfMines);
                }
                if ( CntOfMines == 0 )
                {
                    AutoClickNeighbors(i, j);
                }
            }
        }
    }
}

void LeftButtonClicked(int mouse_x, int mouse_y)
{
    char Buffer[256];
    int left = origin_x;
    int top = origin_y + block_width * (ga_height + 2);

    // 1. Position of clicked pixel is tranformed to game pos.
    int x = (mouse_x - origin_x) / block_width;
    int y = (mouse_y - origin_y) / block_width;

    if ( Map[x][y] == MAP_MINE )
    {
        setcolor(WHITE);
        setbkcolor(BLACK);
        outtextxy(left, top + block_width, "Bomb!!!");
    }
    else
    {
        DrawClickedBlock(x, y);
        Status[x][y] = STATUS_CLICKED;
        int CntOfMines = GetCountOfMines(x, y);
        if (CntOfMines > 0)
        {
            PaintNumber(x, y, CntOfMines);
        }
        if (CntOfMines == 0)
        {
            AutoClickNeighbors(x, y);
        }
    }

    sprintf(Buffer, "Left button is clicked at (%d, %d)-(%d, %d)"
            , mouse_x, mouse_y, x, y);
    setcolor(WHITE);
    setbkcolor(BLACK);
    outtextxy(left, top, Buffer);
}

void RightButtonClicked(int mouse_x, int mouse_y)
{
    int x = ( mouse_x - origin_x ) / block_width;
    int y = ( mouse_y - origin_y ) / block_width;

    if ( Status[x][y] == STATUS_INIT )
    {
        PaintRedFlag(x, y);
        Status[x][y] = STATUS_MARKED;
    }
    else if ( Status[x][y] == STATUS_MARKED )
    {
        EraseBlock(x, y);
        DrawInitBlock(x, y);
        Status[x][y] = STATUS_INIT;
    }
}


int main(void)
{
    time_t t;
    time(&t);
    srand((unsigned int)t);

    GenMines();

    initwindow(800, 600, "Tetris", 160, 180);
    DrawBorder();
    registermousehandler(WM_LBUTTONDOWN, LeftButtonClicked);
    registermousehandler(WM_RBUTTONDOWN, RightButtonClicked);



    for ( int i = 0 ; i < ga_width ; i ++ )
    {
        for ( int j =0 ; j < ga_height ; j ++ )
        {
            DrawInitBlock(i, j);
            if ( Map[i][j] == MAP_MINE )
            {
                PaintMine(i, j);
            }
        }
    }

    getch();
    closegraph();
}
