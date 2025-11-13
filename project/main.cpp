#include <iostream>
#include <windows.h>
#include <conio.h> // for _kbhit()
#include <fstream>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26

#define ROAD_WIDTH 30
#define LEFT_BOUNDARY 30
#define RIGHT_BOUNDARY (LEFT_BOUNDARY + ROAD_WIDTH)

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // To get access to handle the output of current console , HANDLE -> Special type to access resources
COORD CursorPosition;                             // Access to Co-ordinates (x,y)

void gotoXY(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;

    SetConsoleCursorPosition(console, CursorPosition);
}

void setCursor(bool visible, DWORD size)
{ // DWORD (Double Word) = 32-bit unsigned integer
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor; // Cursor info to make the cursor visible/invisible
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void drawBoundary()
{
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {

        gotoXY(LEFT_BOUNDARY, y);
        cout << "|";

        gotoXY(RIGHT_BOUNDARY, y);
        cout << "|";
    }
}

// Car Shape
char car[4][4] = {
    {' ', '#', '#', ' '},
    {'#', '#', '#', '#'},
    {' ', '#', '#', ' '},
    {'#', '#', '#', '#'}};

int carPosX = (LEFT_BOUNDARY + (ROAD_WIDTH / 2)) - 2; // Car size is 4 , so to cneter it -> -2
int carPosY = SCREEN_HEIGHT - 5;

void drawCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoXY(carPosX + j, carPosY + i); // X -> Column , Y -> Row
            cout << car[i][j];
        }
    }
}

void eraseCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoXY(carPosX + j, carPosY + i);
            cout << ' ';
        }
    }
}

char enemyCar[4][4] = {
    {' ', '#', '#', ' '},
    {'#', '#', '#', '#'},
    {' ', '#', '#', ' '},
    {'#', '#', '#', '#'}};

int enemyX[3];
int enemyY[3];
bool enemyFlag[3]; // To check enemy is there or not

void getEnemy(int i)
{
    enemyX[i] = (LEFT_BOUNDARY + 1) + rand() % (ROAD_WIDTH - 4);
    enemyY[i] = 0; // At the top
    enemyFlag[i] = true;
}

void drawEnemy(int i)
{
    if (!enemyFlag[i])
        return;
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            gotoXY(enemyX[i] + c, enemyY[i] + r);
            cout << enemyCar[r][c];
        }
    }
}

void eraseEnemy(int i)
{
    if (!enemyFlag[i])
        return;
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            gotoXY(enemyX[i] + c, enemyY[i] + r);
            cout << ' ';
        }
    }
}

void resetEnemy(int i)
{
    eraseEnemy(i);
    getEnemy(i);
}

bool isCollision(int enemyX, int enemyY)
{
    if (carPosY + 3 < enemyY)
        return false;
    if (carPosY > enemyY + 3)
        return false;
    if (carPosX + 3 < enemyX)
        return false;
    if (carPosX > enemyX + 3)
        return false;
    return true;
}

void drawExplosion(int x, int y) {
    string explosion[] = {
        " * * * ",
        "  ***  ",
        " * * * "
    };

    for (int i = 0; i < 3; i++) {
        gotoXY(x - 3, y + i);
        cout << explosion[i];
    }
}


int highScore = 0;
void loadHighScore()
{
    ifstream file("highscore.txt");
    if (file.is_open())
    {
        file >> highScore;
        file.close();
    }
}

void saveHighScore()
{
    ofstream file("highscore.txt");
    if (file.is_open())
    {
        file << highScore;
        file.close();
    }
}

int score = 0;
void drawScore()
{
    gotoXY(2, 1);
    cout << "Score: " << score;
    gotoXY(70, 2);
    cout << "High Score: " << highScore;
}

void showStartScreen()
{
    system("cls");
    gotoXY(35, 10);
    cout << "== CAR DODGE GAME ==";
    gotoXY(30, 12);
    cout << "Use A / D or Left / Right arrow to move.";
    gotoXY(30, 13);
    cout << "Avoid enemy cars!";
    gotoXY(30, 14);
    cout << "Press P to Pause/Resume during game.";
    gotoXY(30, 15);
    cout << "Press any key to start...";
    while (!_kbhit())
        ; // waits for keypress
    system("cls");
}

int baseDelay = 50;
int minDelay = 20; // Minimum delay to avoid zero Sleep

void play()
{

    carPosX = (LEFT_BOUNDARY + (ROAD_WIDTH / 2)) - 2;
    carPosY = SCREEN_HEIGHT - 5;

    for (int i = 0; i < 3; i++)
    {
        getEnemy(i);
        enemyY[i] = rand() % 2; // Staggered Start
    }

    int frame = 0;

    DWORD lastScoreTime = GetTickCount(); // GetTickCount -> Windows API function which tells milliseconds since the Window started

    bool paused = false;

    while (true)
    {

        /*
        GetAsyncKeyState -> Windows API function to check whether the key is pressed asynchronously
        0x8000 -> hex representation of 1000 0000 0000 0000
        & 0x8000 is used to detect the sign(Most significant) bit
        When any key is pressed sign bit is set 1 by GetAsyncKeyState
        */

        if (GetAsyncKeyState('P') & 0x8000)
        {
            paused = !paused;

            if (paused)
            {
                gotoXY(38, 15);
                cout << "-- Game Paused -- Press P to Resume --";
            }
            else
            {
                gotoXY(38, 15);
                cout << "                                      "; // Clear pause message
                drawBoundary();
            }

            // Debounce the key press to avoid rapid toggling
            while (GetAsyncKeyState('P') & 0x8000)
                Sleep(50);
        }

        if (paused)
        {
            Beep(600, 200);
            Sleep(100);
            continue;
        }

        if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000)
        {
            if (carPosX > LEFT_BOUNDARY + 1)
            {
                eraseCar();
                carPosX -= 2;
            }
            else
            {
                Beep(300, 10);
            }
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000)
        {
            if (carPosX < RIGHT_BOUNDARY - 5)
            {
                eraseCar();
                carPosX += 2;
            }
            else
            {
                Beep(300, 10);
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            break;
        }

        drawCar();

        for (int i = 0; i < 3; i++)
        {
            if (!enemyFlag[i])
                continue;

            eraseEnemy(i);
            enemyY[i]++;

            if (isCollision(enemyX[i], enemyY[i]))
            {
                drawExplosion(carPosX + 1, carPosY);
                Beep(700, 150);
                Sleep(300);

                Beep(500, 300);
                Beep(300, 300);
                
                gotoXY(40, 12);
                cout << "--XX GAME OVER XX--";
                gotoXY(38, 13);
                cout << "Press R to Restart or ESC to exit...";

                if (score > highScore)
                {
                    highScore = score;
                    saveHighScore();
                }

                while (true)
                {

                    if (GetAsyncKeyState('R') & 0x8000)
                    {
                        score = 0;
                        system("cls");
                        drawBoundary();
                        return play();
                    }
                    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
                    {
                        exit(0);
                    }
                    Sleep(100);
                }
            }

            if (enemyY[i] > SCREEN_HEIGHT - 4)
            {
                resetEnemy(i);
                enemyY[i] = 0;
            }
            drawEnemy(i);
        }

        if (GetTickCount() - lastScoreTime >= 1000)
        {
            score++;
            drawScore();
            lastScoreTime = GetTickCount();
        }

        int delay = max(minDelay, (baseDelay - score / 5));
        Sleep(delay);
    }
}

int main()
{
    system("mode con: cols=100 lines=30");
    setCursor(false, 0);

    showStartScreen();

    system("cls");
    drawBoundary();
    drawCar();
    loadHighScore();
    drawScore();

    play();

    return 0;
}