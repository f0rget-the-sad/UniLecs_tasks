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
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define m 1000
#define n 1000

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

struct perimeter{
    int perimeterR;
    int perimeterF;
};

void calc_perimeter(char area_item, struct perimeter *p){
    if (area_item == 'R')
        p->perimeterR++;
    if (area_item == 'F')
        p->perimeterF++;
}


void front_line(char area[][m], int x, int y) {

    const int color_x = x+1;
    const int color_y = 2*y+1;

    char color_area[color_x][color_y]; //extra array for store the colors

    int front_line_length = 0;
    struct perimeter p;
    p.perimeterF = 0;
    p.perimeterR = 0;

    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            //check top line
            if (i == 0){
                color_area[0][2*j+1] = area[0][j];
                calc_perimeter(area[0][j], &p);
            }
            //check left line
            if (j == 0){
                color_area[i+1][0] = area[i][0];
                calc_perimeter(area[i][0], &p);
            }
            // check is it the last raw
            if (i == x-1){
                color_area[color_x-1][2*j+1] = area[i][j];
                calc_perimeter(area[i][j], &p);
            } else {
                // check bottom square
                if (area[i][j] != area[i+1][j]){
                    color_area[i+1][2*j+1] = 'B'; //find battle(B) line
                    front_line_length++;
                } else {
                    color_area[i+1][2*j+1] = area[i][j];
                }

            }
            // check is it the last column
            if (j == y-1){
                color_area[i+1][color_y-1] = area[i][j];
                calc_perimeter(area[i][j], &p);
            } else {
                // check right square
                if (area[i][j] != area[i][j+1]){
                    color_area[i+1][2*j+2] = 'B'; //find battle(B) line
                    front_line_length++;
                } else {
                    color_area[i+1][2*j+2] = area[i][j];
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

    p.perimeterR += front_line_length;
    p.perimeterF += front_line_length;

    printf("Front Line = %d\n", front_line_length);
    printf("PerimeterR = %d\n", p.perimeterR);
    printf("PerimeterF = %d\n", p.perimeterF);
}

int main() {

    char test_area1[n][m] = { { 'R', 'R' }, { 'R', 'F' } };

    front_line(test_area1, 2, 2);

    char test_area2[n][m] = {{'R', 'R', 'R', 'R', 'R', 'R'},
                            {'R', 'R', 'F', 'F', 'R', 'R'},
                            {'F', 'R', 'R', 'F', 'F', 'R'},
                            {'F', 'F', 'F', 'F', 'R', 'R'}};

    front_line(test_area2, 4, 6);

    char test_area3[n][m] = {{'R','R','R','R','R','R'},
                            {'F','F','F','F','F','R'},
                            {'R','R','R','R','F','R'},
                            {'R','F','F','R','F','R'},
                            {'R','F','R','R','F','R'},
                            {'R','F','F','F','F','R'},
                            {'R','R','R','R','R','R'}};

    front_line(test_area3, 7, 6);
}
