#include <stdio.h>

#define MAX_SIZE 20

typedef struct {
    int Shares[20];
    int curent_item; 
    int summ;
} share_t;

void add_item(share_t* Shares_struct, int item){
        Shares_struct->Shares[Shares_struct->curent_item] =  item;
        Shares_struct->summ += item;
        Shares_struct->curent_item++;
}

share_t* get_min(share_t *FirstShares, share_t *SecondShares){
    if (SecondShares->summ < FirstShares->summ)
        return SecondShares;
    return FirstShares;
}

void insertionSort(int *array, int size){
    int key, j;
    for(int i = 2; i < size; i++){
        key = array[i];
        j = i - 1;
        while((j > 0) && (array[j] > key)){
            array[j + 1] = array[j];
            j--;
        }
        array[j +1 ] = key;
    }
}

void balancing(int *Shares, int size){
    if (size > 20){
        printf("Too long array\n");
        return;
    }

    insertionSort(Shares, size);

    share_t FirstShares = {{0}, 0, 0};
    share_t SecondShares = {{0}, 0, 0};

    for(int i = size - 1; i >= 0; i--){
        add_item(get_min(&FirstShares, &SecondShares), Shares[i]);
    }   

    printf("\nFirstShares = ");
    for(int i = 0; i < FirstShares.curent_item; i++){
        printf("%d, ", FirstShares.Shares[i]);
    }
    printf("\nSecondShares = ");
    for(int i = 0; i < SecondShares.curent_item; i++){
        printf("%d, ", SecondShares.Shares[i]);
    }
}
#define balance(Shares) balancing(Shares, sizeof(Shares)/sizeof(Shares[0]));

int main(int argc, char const *argv[])
{
    int Shares[] = {1, 5, 3, 7};
    int Shares2[] = {5, 5, 5, 5, 20};

    balance(Shares);
    balance(Shares2);
    return 0;
}