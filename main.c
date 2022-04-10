#include "stdio.h"

/*
2) реализация эффективных структур данных (список, двунаправленная очередь, дерево) на С/С++
*/


struct some_structure
{
    int first_number;
    float second_number;
};


int main(){
    int a = 8;
    int* pa = &a;
    printf("%p\n", pa);
    return 0;
}