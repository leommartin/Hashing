#include<stdio.h>
#include<math.h>

#define M 11

struct element{
    int key;
    int removed;
    int empty;
};
typedef struct element elem_t;

int hashFunctionT1(int key)
{
    return ( key % M );
}

double hashFunctionT2(int key)
{
    return floor( M * ( key * 0.9 - floor(key * 0.9) ) );
}

int insertionT1(elem_t t1[], int key)
{
    int pos;

    pos = hashFunctionT1(key);

    if(t1[pos].empty == 1)
        t1[pos].key = key;
}

int main()
{
    elem_t t1[M], t2[M];

    // passar os valores para inserir nas tabelas.

}