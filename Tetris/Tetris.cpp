#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>


int origin_x = 20;
int origin_y = 10;
int block_width = 20;

int ga_width = 10;
int ga_height = 20;

int Block[7][4][4][2] =
{
	{/*Type 0 : T */
		{{0, 0}, {-1, 0}, {1, 0}, {0, -1}},
		{{0, 0}, {1, 0}, {0, 1}, {0, -1}},
		{{0, 0}, {-1, 0}, {1, 0}, {0, 1}},
		{{0, 0}, {-1, 0}, {0, 1}, {0, -1}}
	},
	{/*Type 1 : S */
		{{0, 0},{0,-1},{1,-1},{-1,0}},
		{{0, 0},{0,-1},{1,0},{1,1}},
		{{0, 0},{-1,0},{0,-1},{1,-1}},
		{{0, 0},{0,-1},{1,0},{1,1}}
	},
	{/*Type 2 : Z */
		{{0, 0},{-1,-1},{0,-1},{1,0}},
		{{0, 0},{1,0},{0,1},{1,-1}},
		{{0, 0},{-1,-1},{0,-1},{1,0}},
		{{0, 0},{1,-1},{1,0},{0,1}}
	},
	{/*Type 3 : I */
		{{0, 0},{-2,0},{-1,0},{1,0}},
		{{0, 0},{0,-2},{0,-1},{0,1}},
		{{0, 0},{-2,0},{-1,0},{1,0}},
		{{0, 0},{0,-2},{0,-1},{0,1}}
	},
	{/*Type 4: O */
		{{0,0},{-1,-1},{0,-1},{-1,0}},
		{{0,0},{-1,-1},{0,-1},{-1,0}},
		{{0,0},{-1,-1},{0,-1},{-1,0}},
		{{0,0},{-1,-1},{0,-1},{-1,0}}
	},
	{/*Type 5: L */
		{{0,0},{1,-1},{-1,0},{1,0}},
		{{1,1},{0,0},{0,-1},{0,1}},
		{{-1,1},{0,0},{-1,0},{1,0}},
		{{-1,-1},{0,0},{0,1},{0,-1}}
	},
	{/*Type 6: J*/
		{{0,0},{-1,0},{1,0},{1,1}},
		{{0,0},{0,1},{0,-1},{-1,1}},
		{{0,0},{-1,0},{1,0},{-1,-1}},
		{{0,0},{0,1},{0,-1},{1,-1}}
	}
};
int color[7] = {BLUE, GREEN, YELLOW, RED, CYAN, LIGHTBLUE, LIGHTGREEN};

int x;
int y;
int Type;
int Rotate;

int next_x = 14;
int next_y = 2;
int NextType;
int NextRotate;

int LandedBlock[10][20];

int score = 100;

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
    int left2 = right + 20;
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

    printf("%d, %d", right4, bottom4);
}

void DrawUnitBlock(int x, int y, int icolor)
{
    int left = origin_x + block_width * x;
    int top = origin_y + block_width * y;
    int right = left + block_width - 1;
    int bottom = top + block_width - 1;

    setcolor(WHITE);
    rectangle(left, top, right, bottom);

    setfillstyle(SOLID_FILL, icolor);
    floodfill(left + 2, top + 2, WHITE);
}

void EraseUnitBlock(int x, int y)
{
    int left = origin_x + block_width * x;
    int top = origin_y + block_width * y;
    int right = left + block_width - 1;
    int bottom = top + block_width - 1;

    setcolor(WHITE);
    rectangle(left, top, right, bottom);

    setfillstyle(SOLID_FILL, BLACK);
    floodfill(left + 2, top + 2, WHITE);

    setcolor(BLACK);
    rectangle(left, top, right, bottom);
}

void DrawTetris(int ix, int iy, int it, int ir)
{
    for ( int i = 0 ; i < 4 ; i ++ )
    {
        int ub_x = ix + Block[it][ir][i][0];
        int ub_y = iy + Block[it][ir][i][1];
        DrawUnitBlock(ub_x, ub_y, color[it]);
    }
}

void EraseTetris(int ix, int iy, int it, int ir)
{
    for ( int i = 0 ; i < 4 ; i ++ )
    {
        int ub_x = ix + Block[it][ir][i][0];
        int ub_y = iy + Block[it][ir][i][1];
        EraseUnitBlock(ub_x, ub_y);
    }
}

void GenTetris()
{
    x = 5;
    y = 3;
    Type = NextType;
    Rotate = NextRotate;
    NextType = rand() % 7;
    NextRotate = rand() % 4;
}

bool CanMoveLeft(void)
{
    for ( int i = 0 ; i < 4 ; i ++ )
    {
        int new_x = x + Block[Type][Rotate][i][0] - 1;
        int new_y = y + Block[Type][Rotate][i][1];
        if ( new_x < 0 )
        {
            return false;
        }
        if ( LandedBlock[new_x][new_y] > 0 )
        {
            return false;
        }
    }
    return true;
}

bool CanMoveRight(void)
{
    for ( int i = 0 ; i < 4 ; i ++ )
    {
        int new_x = x + Block[Type][Rotate][i][0] + 1;
        int new_y = y + Block[Type][Rotate][i][1];
        if ( new_x >= ga_width )
        {
            return false;
        }
        if ( LandedBlock[new_x][new_y] > 0 )
        {
            return false;
        }
    }
    return true;
}

bool CanFall(void)
{
    for ( int i = 0 ; i < 4 ; i ++ )
    {
        int new_x = x + Block[Type][Rotate][i][0];
        int new_y = y + Block[Type][Rotate][i][1] + 1;
        if ( new_y >= ga_height )
        {
            return false;
        }
        if ( LandedBlock[new_x][new_y] > 0 )
        {
            return false;
        }
    }
    return true;
}

bool CanRotate(void)
{
    for ( int i = 0 ; i < 4 ; i ++ )
    {
        int new_rotate = ( Rotate + 1 ) % 4;
        int new_x = x + Block[Type][new_rotate][i][0];
        int new_y = y + Block[Type][new_rotate][i][1];
        if ( new_x < 0 || new_x >= ga_width
            || new_y >= ga_height )
        {
            return false;
        }
        if ( LandedBlock[new_x][new_y] > 0 )
        {
            return false;
        }
    }
    return true;
}

void LandBlock()
{
    for ( int i = 0 ; i < 4 ; i ++ )
    {
        int CoordX = x + Block[Type][Rotate][i][0];
        int CoordY = y + Block[Type][Rotate][i][1];
        LandedBlock[CoordX][CoordY] = color[Type];
    }
}

void UpdateScore()
{
    int margin = 160;
    int left = origin_x - 1;
    int top = origin_y - 1 + margin;
    int right = origin_x + ga_width * block_width + 1;

    char Buffer[256];
    sprintf(Buffer, "Your score : %d", score);
    outtextxy(right + 35, top, Buffer);
}

void DispInfo(void)
{
    int margin = 190;
    int left = origin_x - 1;
    int top = origin_y - 1 + margin;
    int right = origin_x + ga_width * block_width + 1;
    int bottom = origin_y + ga_height * block_width + 1;

    outtextxy(right + 35, top + 50, "A : Left");
    outtextxy(right + 35, top + 75, "D : Right");
    outtextxy(right + 35, top + 100, "S : Down");
    outtextxy(right + 35, top + 125, "W : Rotate");

}

void RemoveRow(int RowId)
{
    for ( int r = RowId ; r > 0 ; r -- )
    {
        for ( int ix = 0 ; ix < ga_width ; ix ++ )
        {
            LandedBlock[ix][r] = LandedBlock[ix][r - 1];
        }
    }
}

bool IsOccupiedCompletely(int RowId)
{
    for ( int ix = 0 ; ix < ga_width ; ix ++ )
    {
        if ( LandedBlock[ix][RowId] == 0 )
        {
            return false;
        }
    }
    return true;
}

void UpdateGameArea()
{
    for ( int ix = 0 ; ix < ga_width ; ix ++ )
    {
        for ( int iy = 0 ; iy < ga_height ; iy ++ )
        {
            if ( LandedBlock[ix][iy] == 0 )
            {
                EraseUnitBlock(ix, iy);
            }
            else
            {
                //EraseUnitBlock(ix, iy);
                DrawUnitBlock(ix, iy, LandedBlock[ix][iy]);
            }
        }
    }
}


void RemoveAllOccupiedRows()
{
    for ( int iy = ga_height - 1 ; iy > 0 ; iy -- )
    {
        if ( IsOccupiedCompletely(iy) )
        {
            RemoveRow(iy);
            iy = iy + 1;
        }
    }
    UpdateGameArea();
}

int main(void)
{
    time_t t;
    time(&t);
    srand((unsigned int)t);

    x = 5;
    y = 3;
    NextType = rand() % 7;
    NextRotate = rand() % 4;

    GenTetris();

    initwindow(420, 430, "Tetris", 160, 180);
    DrawBorder();
    DispInfo();

    DrawTetris(next_x, next_y , NextType, NextRotate);
    DrawTetris(x, y , Type, Rotate);

    UpdateScore();



    while(true)
    {
        char Input = getch();
        EraseTetris(x, y , Type, Rotate);
        if (Input == 'a' && CanMoveLeft() == true)
        {
            x = x - 1;
        }
        else if (Input == 'd' && CanMoveRight() == true)
        {
            x = x + 1;
        }
        else if ( Input == 's' )
        {
            if ( CanFall() )
            {
                y = y + 1;
            }
            else
            {
                LandBlock();
                DrawTetris(x, y, Type, Rotate);

                RemoveAllOccupiedRows();

                EraseTetris(next_x, next_y, NextType, NextRotate);
                GenTetris();
                DrawTetris(next_x, next_y, NextType, NextRotate);
            }
        }
        else if ( Input == 'w' && CanRotate())
        {
            Rotate = (Rotate + 1) % 4;
        }
        else if ( Input == 'l' )
        {
            LandBlock();
        }
        else if ( Input == 'c' )
        {
            DrawTetris(x, y, Type, Rotate);
            GenTetris();
            DrawTetris(x, y, Type, Rotate);
        }
        else if ( Input == 'q' )
        {
            break;
        }
        else if ( Input == 'r' )
        {
            RemoveRow(19);
            UpdateGameArea();
        }
        else if ( Input >= '0' && Input < '7' )
        {
            Type = Input - '0';
        }

        DrawTetris(x, y , Type, Rotate);
    }

    getch();
    closegraph();
}


/*


    for ( int t = 0 ; t < 7 ; t ++)
    {
        x = t * 5 + 3;
        Type = t;
        for ( int r = 0 ; r < 4 ; r ++ )
        {
            y = r * 5 + 3;
            Rotate = r;
            DrawTetris();
        }
    }


    for ( int t = 0 ; t < 7 ; t ++)
    {
        Type = t;
        for ( int r = 0 ; r < 4 ; r ++ )
        {
            Rotate = r;
            DrawTetris();
            getch();
            EraseTetris();
        }
    }

*/
