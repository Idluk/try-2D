#include <iostream>
#include <windows.h>
#include <string>
#include <cmath>

using namespace std;
const double M_PI = 3.14;
const int HEIGHT = 40;
const int WIDTH = 200;
const int FPS = 60;
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
                *ptr++ = '1';
            }
            else {
                *ptr++ = '0';
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
            text_buffer[i][j] = 0;
        }
    }
}

void quad(int x, int y, int width, int height, double angle_deg = 0) {
    if (angle_deg == 0) {
        for (int i = y; i < y + height; i++) {
            for (int j = x; j < x + width; j++) {
                if (j >= 0 && i >= 0 && j < WIDTH && i < HEIGHT) {
                    screen[i][j] = 1;
                }
            }
        }
    }
    else {
        double angle = angle_deg * M_PI / 180.0;
        double cos_a = cos(angle);
        double sin_a = sin(angle);
        int cx = x + width / 2;
        int cy = y + height / 2;
        int half_w = width / 2;
        int half_h = height / 2;

        for (int i = -half_h; i <= half_h; i++) {
            for (int j = -half_w; j <= half_w; j++) {
                int x_rot = round(j * cos_a - i * sin_a);
                int y_rot = round(j * sin_a + i * cos_a);
                int screen_x = cx + x_rot;
                int screen_y = cy + y_rot;

                if (screen_x >= 0 && screen_x < WIDTH &&
                    screen_y >= 0 && screen_y < HEIGHT) {
                    screen[screen_y][screen_x] = 1;
                }
            }
        }
    }
}



void circle(int x, int y, int d) {
    int r = d / 2;
    for (int i = y-r; i < y + r; i++) {
        for (int j = x-r; j < x + r; j++) {
            if (j < 0 or i < 0 or j >= WIDTH or i >= HEIGHT) {
                continue;
            }
            if (pow(j-x,2) + pow(i-y, 2)*3 <= pow(r, 2)) {
                screen[i][j] = 1;
            }
        }
    }
}

void particles_quad(int x, int y, int width, int height, double angle_deg = 0, int visibility = 50) {
    if (angle_deg == 0) {
        for (int i = y; i < y + height; i++) {
            for (int j = x; j < x + width; j++) {
                if (j >= 0 && i >= 0 && j < WIDTH && i < HEIGHT) {
                    screen[i][j] = 1;
                }
            }
        }
    }
    else {
        double angle = angle_deg * M_PI / 180.0;
        double cos_a = cos(angle);
        double sin_a = sin(angle);
        int cx = x + width / 2;
        int cy = y + height / 2;
        int half_w = width / 2;
        int half_h = height / 2;

        for (int i = -half_h; i <= half_h; i++) {
            for (int j = -half_w; j <= half_w; j++) {
                int x_rot = round(j * cos_a - i * sin_a);
                int y_rot = round(j * sin_a + i * cos_a);
                int screen_x = cx + x_rot;
                int screen_y = cy + y_rot;

                if (screen_x >= 0 && screen_x < WIDTH &&
                    screen_y >= 0 && screen_y < HEIGHT) {
                    if (rand()%100>(100-visibility))
                        screen[screen_y][screen_x] = 1;
                }
            }
        }
    }
}

void particles_circle(int x, int y, int d, int visibility = 50) {
    int r = d / 2;
    for (int i = y - r; i < y + r; i++) {
        for (int j = x - r; j < x + r; j++) {
            if (j < 0 or i < 0 or j >= WIDTH or i >= HEIGHT) {
                continue;
            }
            if (pow(j - x, 2) + pow(i - y, 2) * 3 <= pow(r, 2)) {
                if (rand()%100>(100-visibility))
                    screen[i][j] = 1;
            }
        }
    }
}



int main()
{
    system("mode con cols=200 lines=41");
    srand(time(0));
    long int time_screen = 0;
    long int time_sec = 0;
    long int time_rate = 0;
    bool f_sec, f_rate;
    long int rate = 2;
    string text1 = "FPS:" + to_string(FPS);
    int x, y;
    x = 10; y = 10;
    bool run = true;
    //переменные тела цикла
    int temp_time_rate = 0;
    int temp_time_sec = 0;
    while (run) { //экран 200 x 40
        time_screen++;
        time_sec = time_screen / FPS; // изменение раз в секунду
        time_rate = time_screen / rate; // изменение раз в определенный rate
        if (time_screen % FPS == 0) f_sec = true;
        else f_sec = false;
        if (time_screen % rate == 0) f_rate = true;
        else f_rate = false;
        system("cls");
        //начало
        clear();
        //draw_text(text1.c_str(), 0, 0); //fps

        //тело программы
        
        for(int i = 0; i<200; i=i+30) {
            particles_quad(i, HEIGHT / 2 - 10, 15, 15, 15 * time_rate + i, i/2 + 20);
        }

        //конец
        draw();
        Sleep(1000 / FPS);
        
    }

}
