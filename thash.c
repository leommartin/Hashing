#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define M 11

struct hashTable{
    int key;
    bool removed;
    bool empty;
};
typedef struct hashTable hashTable_T;

void initializeTables(hashTable_T t1[], hashTable_T t2[])
{
    int i;

    for(i = 0; i < M; i++)
    {
        t1[i].empty = true;
        t2[i].empty = true;

        t1[i].removed = false;
        t2[i].removed = false;

        t1[i].key = -1;
        t2[i].key = -1;
    }
}

int hashFunctionT1(int key)
{
    return ( key % M );
}

double hashFunctionT2(int key)
{
    return floor ( M * ( key * 0.9 - floor(key * 0.9) ) );
}int keySearch(hashTable_T t1[], hashTable_T t2[], int key, int *table)
{
    int pos;

    /* Testa se está na Tabela I */
    pos = hashFunctionT1(key);

    if(t1[pos].empty)
    {
        *table = 1;
        return 0;
    }

    if(t1[pos].key == key)
    {
        *table = 1;
        return pos;
    }
    /* Testa se está na Tabela II */
    
    pos = hashFunctionT2(key);

    if(t2[pos].key == key)
    {
        *table = 2;
        return pos;
    }
    else
    {
        printf("Chave %d não está em nenhuma das tabelas.\n\n", key);
        return -1;
    }
}

int keyInsertion(hashTable_T t1[], hashTable_T t2[], int key, int *position)
{
    int pos, posT2;

    pos = hashFunctionT1(key);
    
    if( (t1[pos].empty == 1) || (t1[pos].key == key) || (t1[pos].removed == 1) )
    {
        t1[pos].key   = key;
        t1[pos].empty = false;

        *position = pos;
        return 1;
    }
    else
    {
        posT2 = hashFunctionT2(t1[pos].key);
        
        /* Insere chave prévia de T1 em T2 */
        t2[posT2].key = t1[pos].key;
        
        /* Insere chave nova em T1 sobrescrevendo a chave anterior */
        t1[pos].key = key;

        *position = posT2;
        return 2;
    }
}

int keyDelete(hashTable_T t1[], hashTable_T t2[], int key)
{
    int posT1, posT2;

    posT2 = hashFunctionT2(key);

    if(t2[posT2].empty == 0 && key == t2[posT2].key)
        t2[posT2].empty = 1;
    else
    {
        posT1 = hashFunctionT1(key);

        t1[posT1].removed = 1;
    }
}


int main()
{
    hashTable_T t1[M], t2[M];
    int vetor[5] = { 10, 22, 4, 15, 59 };
    int vetor2[3] = { 15, 22, 59 };

    int i, position;

    initializeTables(t1, t2);

    printf("\n\n");
    for(i = 0; i < 5; i++)
    {
        if(keyInsertion(t1, t2, vetor[i], &position) == 1)
        {
            printf("Valor %d inserido na tabela T1 na posição [%d].\n", vetor[i], position);
        }
        else
            printf("Valor %d inserido na tabela T2 na posicao [%d] após colisão com T1.\n", vetor[i], position);
    }

    printf("\n\n");
    for(i = 0; i < M; i++)
        printf("t1[%d]: %d \t t2[%d]: %d \n", i, t1[i].key, i, t2[i].key);
    

    return 0;
}