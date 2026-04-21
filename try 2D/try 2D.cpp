#include <iostream>
#include <windows.h>
#include <string>
#include <cmath>

using namespace std;

const int HEIGHT = 40;
const int WIDTH = 200;
const int FPS = 144;
int screen[HEIGHT][WIDTH] = { 0 };

char text_buffer[HEIGHT][WIDTH] = { 0 };

void draw_text(const char* text, int x, int y) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (x + i < WIDTH and y < HEIGHT) {
            text_buffer[y][x + i] = text[i];
        }
    }
}

void draw() {
    static char buffer[HEIGHT * (WIDTH  + 2)];
    char* ptr = buffer;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (text_buffer[i][j]) {
                *ptr++ = text_buffer[i][j];
            }
            else if (screen[i][j]) {
                *ptr++ = '#';
            }
            else {
                *ptr++ = ' ';
            }
        }
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

void circle(int x, int y, int d) {
    int r = d / 2;
    int cx = x + r;
    int cy = y + r;
    for (int i = y; i < y + d; i++) {
        for (int j = x; j < x + d; j++) {
            if (j < 0 or i < 0 or j >= WIDTH or i >= HEIGHT) {
                continue;
            }
            if (pow(j-cx,2) + pow(i-cy, 2) <= pow(r, 2)) {
                screen[i][j] = 1;
            }
        }
    }
}

int main()
{
    long int time_screen = 0;
    long int time_sec = 0;
    long int time_rate = 0;
    bool f_sec, f_rate;
    long int rate = 2;
    bool run = true;
    int x, y;
    string text1 = "FPS:" + to_string(FPS);
    x = 10; y = 10;
    while (run) { //экран 120 x 30
        time_screen++;
        time_sec = time_screen / FPS; // изменение раз в секунду
        time_rate = time_screen / rate; // изменение раз в определенный rate
        if (time_screen % FPS == 0) f_sec = true;
        else f_sec = false;
        if (time_screen % rate == 0) f_rate = true;
        else f_rate = false;
        COORD zero = { 0, 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), zero);

        //начало
        draw_text(text1.c_str(), 0, 0);
        if (f_rate){
            if (time_sec % 28 < 14)
                x += 1;
            else x -= 1;
        }
        quad(x, y, 15, 15);        
        draw();
        Sleep(1000 / FPS);
        clear();
    }

}
