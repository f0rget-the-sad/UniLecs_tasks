/*
Задача: В одной области одной северной страны, где нет нормальных дорог, чтобы добраться из одного поселка до другого люди вынуждены пользоваться самодельной вагонеткой для доставки грузов. В этой области N поселков и только нектр из них соединены между собой старой железной дорогой. Для проезда по ней из одного поселка до другого нужна одна канистра горючего, но в каждом поселке своя стоимость канистры горючего. А вагонетка слишком мала, и вы не можете взять с собой доп.канистры. Необходимо довести груз из 1го поселка до N-го, при этом использовать минимальное кол-во средств на горючку.

Входные данные: OilCosts = [oilCost_1, oilCost_2, ... oilCost_N] - массив, где oilCost(i) - стоимость канистры горючего в i-м поселке. 

TrainRoads = [ (Ai, Bj) ] - массив, где (Ai, Bj) - железная дорога, ктр соединяет поселок Ai c поселком Bj.

Дороги двухсторонние, и разумеется, между любыми двумя поселками не более 1 одной дороги.

Вывод: вывести оптимальный маршрут, т.е. номера поселков на этом маршруте.

Пример: 

OilCosts = [5, 10, 1]

TrainRoads = [ (1, 3), (1, 2), (3, 2) ]

Answer: 1 -> 3
*/

#include <stdio.h>
#include <limits.h>

#define INFINITY INT_MAX

int *pred;

void printWay(int v) {
	if (v == -1) return;
	printWay(pred[v]); 
	printf("%d ", (v + 1)); 
} 

int main()
{
	//int OilCosts[] = {5, 10, 1};
	int OilCosts[] = {7, 9, 14, 15, 10, 11, 2, 6, 9};
	//int TrainRoads[][2] = {{1, 3}, {1, 2}, {3, 2}};
	int TrainRoads[][2] = {{1, 2}, {1, 3}, {1, 6}, {2, 4}, {2, 3}, {3, 4}, {3, 6}, {4, 5}, {6, 5}};
	
	// find max number, which is == to number of peaks
	int size = 0;
	for (int i = 0; i < sizeof(TrainRoads)/sizeof(TrainRoads[0]); i++){
		for(int j = 0; j < 2; j++){
			if (size < TrainRoads[i][j])
				size = TrainRoads[i][j];
		}	
		printf("%d, %d\n", TrainRoads[i][0], TrainRoads[i][1]);
	}
	printf("Number of peaks %d\n", size);
	// initialization of path matrix
	int path_matrix[size][size];
	for (int i = 0; i<size; i++){
		for (int j = 0; j<size; j++){
			path_matrix[i][j] = 0;
		}
	}

	for (int i = 0; i < sizeof(TrainRoads)/sizeof(TrainRoads[0]); i++){

		path_matrix[TrainRoads[i][0]-1][TrainRoads[i][1]-1] = OilCosts[i];
		path_matrix[TrainRoads[i][1]-1][TrainRoads[i][0]-1] = OilCosts[i];
	}
	// showing our matrix
	for (int i = 0; i<size; i++){
		for (int j = 0; j<size; j++)
			printf("%d \t", path_matrix[i][j]);
		printf("\n");
	}
	
	int destination[size]; // minimal destination to i-peak
	int visited[size]; // array of visited peaks(0 - not visited)
	int pathes[size];

	int p[size];
	pred = p;
	
	// arras initialization
	for (int i = 0; i<size; i++){
		destination[i] = INFINITY;
		visited[i] = 0;
		pred[i] = -1;
	}
	destination[0] = 0;
	int current_peak, shortest_path;
	
	//main loop
	while(1){
		current_peak = INFINITY;
		shortest_path = INFINITY;
		// finding not visited peak with shortest path 
		for (int i = 0; i<size; i++){ 
		  if ((visited[i] == 0) && (destination[i] < shortest_path)){
			shortest_path = destination[i];
			current_peak = i;
		  }
		}
		// if current_peak value doesn't change
		// it means we walk over all peaks
		if (current_peak != INFINITY){
		    for (int i = 0; i < size; i++){
			    //check is exist path from current_peak to i-peak
				if (path_matrix[current_peak][i] > 0){
					//check is our shortest_path is shorter then current
					int temp = shortest_path + path_matrix[current_peak][i];
					if (temp < destination[i]){
						destination[i] = temp;
						pathes[current_peak] = i;
						pred[i] = current_peak;
					}
				}
			}
			visited[current_peak] = 1;
		} else {
			break;
		}
		
	}
	
	
	for(int i = 0; i <= size-1; i++){
		printf("peak[%d] destination = %d\n", i + 1, destination[i]);
	}
	
	printWay(5);
}












