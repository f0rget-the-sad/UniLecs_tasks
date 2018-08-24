/*
Задача: на карте боевых действий есть прямоугольный участок, где идут самые ожесточенные бои. Прямоугольник задан символьной матрицей. Элемент матрицы обозначает территорию 1х1, ктр захвачена либо армией 'R', либо 'F'. Необходимо определить линию фронта в условных единицах, а также общий периметр каждой из сторон.

Входные данные: area[] - символьная матрица, состоящая из символов 'R' и 'F'. Размер матрицы NxM, где N, M - от 1 до 1000.

Захваченные территории каждой из сторон это связные области.

Вывод: линия фронта, общие периметры каждой из сторон.

Пример: 

area = [ { 'R', 'R' }, { 'R', 'F' } ]

Answer: FrontLine = 2; PerimeterR = 8; PerimeterF = 4
*/
#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define x 4
#define y 6

#define color_x x+1
#define color_y 2*y+1


void print_hline(char* color){
    printf("%s_%s", color, ANSI_COLOR_RESET);
}
void print_vline(char* color){
    printf("%s|%s", color, ANSI_COLOR_RESET);
}

char* army_to_color(char a){
    switch (a){
        case 'R':
            return ANSI_COLOR_YELLOW;
        case 'F':
            return ANSI_COLOR_CYAN;
        case 'B':
            return ANSI_COLOR_RED;
        default:
            return ANSI_COLOR_RESET;
    }
}

int main() {
    //char area[x][y] = { { 'R', 'R' }, { 'R', 'F' } };
    char area[x][y] = {{'R', 'R', 'R', 'R', 'R', 'R'},
                      {'R', 'R', 'F', 'F', 'R', 'R'},
                      {'F', 'R', 'R', 'F', 'F', 'R'},
                      {'F', 'F', 'F', 'F', 'R', 'R'}};

    char color_area[color_x][color_y]; //extra array for store the colors
    char squre[] = "[]";
    //char squre[] = "*\n*";

    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            if (area[i][j] == 'R'){
                printf("%s%s%s", ANSI_COLOR_RED, squre, ANSI_COLOR_RESET);
            } else if (area[i][j] == 'F'){
                printf("%s%s%s", ANSI_COLOR_CYAN, squre, ANSI_COLOR_RESET);
            }
        }
        printf("\n");
    }

    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            //check top line
            if (i == 0)
                color_area[0][2*j+1] = area[0][j];
            //check left line
            if (j == 0)
                color_area[i+1][0] = area[i][0];
            // check is it the last raw
            if (i == x-1){
                color_area[color_x-1][2*j+1] = area[i][j];
            } else {
                // check bottom square
                if (area[i][j] != area[i+1][j]){
                    color_area[i+1][2*j+1] = 'B'; //find battle(B) line
                } else {
                    color_area[i+1][2*j+1] = area[i][j]; //find battle(B) line
                }

            }
            // check is it the last column
            if (j == y-1){
                color_area[i+1][color_y-1] = area[i][j];
            } else {
                // check right square
                if (area[i][j] != area[i][j+1]){
                    color_area[i+1][2*j+2] = 'B'; //find battle(B) line
                } else {
                    color_area[i+1][2*j+2] = area[i][j]; //find battle(B) line
                }
            }
        }
    }
    // draw battle area
    for (int i = 0; i < color_x; i++){
        for (int j = 0; j < color_y; j++){
            if(i == 0){
                if(j%2 != 0)
                    print_hline(army_to_color(color_area[i][j]));
                else
                    printf(" ");
            } else {
                if(j%2 != 0){
                    print_hline(army_to_color(color_area[i][j]));
                } else {
                    print_vline(army_to_color(color_area[i][j]));
                }
            }
        }
        printf("\n");
    }
}
