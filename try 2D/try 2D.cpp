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
int layers[1000][HEIGHT][WIDTH] = { 0 };
bool n_layers[1000] = {0};

struct Object {
    int x = 0, y = 0;
    int width = 0, height = 0, radius = 0;
    int angle_deg = 0, visibility = 100;
    int layer[HEIGHT][WIDTH] = { 0 };
    int slot = -1;

    void layer_to_draw() {
        if (slot == -1) {
            for (int n = 0; n < 1000; n++) {
                if (n_layers[n] == 0) {
                    n_layers[n] = 1;
                    slot = n;
                    break;
                }
            }
        }
        if (slot != -1) {
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    layers[slot][i][j] = layer[i][j];
                }
            }
        }
    }

    void clear_layer() {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                layer[i][j] = 0;
            }
        }
    }

    void quad() {
        clear_layer();
        int half_w = width / 2;
        int half_h = height / 2;
        if (angle_deg == 0) {
            for (int i = -half_h; i < half_h; i++) {
                for (int j = -half_w; j < half_w; j++) {
                    int screen_x = x + j;
                    int screen_y = y + i;
                    if (screen_x >= 0 && screen_y >= 0 && screen_x < WIDTH && screen_y < HEIGHT) {
                        if (rand() % 100 > (100 - visibility))
                            layer[screen_y][screen_x] = 1;
                    }
                }
            }
        }
        else {
            double angle = angle_deg * M_PI / 180.0;
            double cos_a = cos(angle);
            double sin_a = sin(angle);
            int half_w = width / 2;
            int half_h = height / 2;

            for (int i = -half_h; i <= half_h; i++) {
                for (int j = -half_w; j <= half_w; j++) {
                    int x_rot = round(j * cos_a - i * sin_a);
                    int y_rot = round(j * sin_a + i * cos_a);
                    int screen_x = x + x_rot;
                    int screen_y = y + y_rot;

                    if (screen_x >= 0 && screen_x < WIDTH &&
                        screen_y >= 0 && screen_y < HEIGHT) {
                        if (rand() % 100 > (100 - visibility))
                            layer[screen_y][screen_x] = 1;
                    }
                }
            }
        }
        layer_to_draw();
    }

    void circle() {
        clear_layer();
        for (int i = y - radius; i < y + radius; i++) {
            for (int j = x - radius; j < x + radius; j++) {
                if (j < 0 or i < 0 or j >= WIDTH or i >= HEIGHT) {
                    continue;
                }
                if (pow(j - x, 2) + pow(i - y, 2)*3 <= pow(radius, 2)) {
                    if (rand() % 100 > (100 - visibility))
                        layer[i][j] = 1;
                }
            }
        }
        layer_to_draw();
    }
};

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
    for (int n = 0; n < 1000; n++) {
        if (n_layers[n]) {
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    if (screen[i][j] == 0) {
                        screen[i][j] = layers[n][i][j];
                    }
                }
            }
        }
    }
                

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (text_buffer[i][j]) {
                *ptr++ = text_buffer[i][j];
            }
            else if (screen[i][j]) {
                *ptr++ = '*';
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
            text_buffer[i][j] = 0;
        }
    }
}

int main()
{
    system("mode con cols=200 lines=41");
    srand(time(0));
    int time_screen = 0;
    int time_sec = 0;
    int time_rate = 0;
    bool f_sec, f_rate;
    int rate = 10;
    int x, y;
    x = 10; y = 10;
    bool run = true;
    //переменные тела цикла
    Object obj;
    string text1, text2;
    
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
        text1 = "Visibility:" + to_string(obj.visibility);
        draw_text(text1.c_str(), 0, 0);
        for (int n = 0; n < 1000; n++) {
            if (n_layers[n])
                text2 = "Layers:" + to_string(n);
        }
        draw_text(text2.c_str(), 0, 1);
        //тело программы
        if (f_rate) {
            obj.x = 5 + time_rate*20 % 200 ; obj.y = 20; obj.width = 30; obj.height = 15;
            obj.quad();
        }
        obj.visibility = time_rate*10 % 100;

        //конец
        draw();
        Sleep(1000 / FPS);
        
    }

}
