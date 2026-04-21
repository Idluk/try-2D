#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

const int HEIGHT = 30;
const int WIDTH = 120;
const int FPS = 24;
bool screen[HEIGHT][WIDTH] = { 0 };

void draw() {
    static char buffer[HEIGHT * (WIDTH + 2)];
    char* ptr = buffer;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++)
            *ptr++ = screen[i][j] ? '*' : ' ';
        *ptr++ = '\n';
    }
    *ptr = '\0';
    printf("%s", buffer);
}

void clear() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            screen[i][j] = 0;
        }
    }
}

void quad(int x, int y, int height, int width) {
    for (int i = y; i < y + height; i++) {
        for (int j = x; j < x + width; j++) {
            if (j < 0 or i < 0 or j >= WIDTH or i >= HEIGHT) {
                continue;
            }
            else {
                screen[i][j] = 1;
            }
        }
    }
}

int main()
{
    long int time_screen = 0;
    long int time_fps = 0;
    long int time_rate = 0;
    long int rate = 5;
    bool run = true;
    while (run) {
        time_screen++;
        time_fps = time_screen / FPS; // изменение раз в секунду
        time_rate = time_screen / rate; // изменение раз в определенный rate
        COORD zero = { 0, 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), zero);
        quad(5 - time_rate * 1, 5, 5, 5);
        quad(15 + time_rate * 1, 15, 5, 5);
        draw();
        Sleep(1000 / FPS);
        clear();
    }

}
