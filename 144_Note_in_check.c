/*
«Задача 114: Тетрадь в клеточку
Все мы в школе рисовали в тетрадке в клеточку. На этот раз вы нарисовали круг и вам нужно определить кол-во точек с целочисленными координатами, ктр наход¤тс¤ внутри круга, а также точки на окружности круга. Центр круга задан целочисленными координатами.

Входные данные: r - радиус круга, где r - целое число от 1 до 10^4.

Вывод: кол-во точек, ктр заданы целочисленными координатами.

ѕример: r = 1
Answer = 5
*/
#include <stdio.h>
#include <math.h>

int main()
{
    //radius
    int R;
    int max_R = pow(10, 4);

    printf("Enter Radius = ");
    scanf("%d", &R);
   if (R > max_R){
        printf("Too big radius(try less then %d)", max_R);
        return 1;
    }

    int counter = 0;
    //iterate through all points in square area
    for(int x = -R; x <= R; x++){
        for(int y = -R; y <= R; y++){
            //check is point satisfies circle circle equation
            if(sqrt(x * x + y * y) <= R){
                counter++;
            }
        } 
    }
    printf("Number of dots(int coordinates) =%d \n", counter);
    
    return 0;
}

