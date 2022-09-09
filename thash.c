#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define M 11

struct hashTable{
    int key;
    bool removed;
    bool empty;
    int table;
    int position;
};
typedef struct hashTable hashTable_T;

/* Inicializa Tabelas */
void initializeTables(hashTable_T t1[], hashTable_T t2[])
{
    int i;

    for(i = 0; i < M; i++)
    {
        t1[i].empty = true;
        t2[i].empty = true;

        t1[i].removed = false;
        t2[i].removed = false;

        t1[i].table = 1;
        t2[i].table = 2;

        t1[i].key = -1;
        t2[i].key = -1;

        t1[i].position = -1;
        t2[i].position = -1;
    }
}

/* Função Hash da Tabela I */
int hashFunctionT1(int key)
{
    return ( key % M );
}

/* Função Hash da Tabela II */
double hashFunctionT2(int key)
{
    return floor ( M * ( key * 0.9 - floor(key * 0.9) ) );
}

int keySearch(hashTable_T t1[], hashTable_T t2[], int key, int *table)
{
    int pos;

    /* Testa se está na Tabela I */
    pos = hashFunctionT1(key);

    /* Posição de T1 vazia ou com chave removida*/
    if(t1[pos].empty || t1[pos].removed)
        return -1;

    /* Posição de T1 já ocupada com a chave buscada */
    if(t1[pos].key == key)
    {
        *table = 1;
        return pos;
    }

    /* Testa se está na Tabela II */
    pos = hashFunctionT2(key);

    /* Posição de T2 já ocupada com a chave buscada */
    if(t2[pos].key == key)
    {
        *table = 2;
        return pos;
    }
    else
        return -2;
}

int keyInsertion(hashTable_T t1[], hashTable_T t2[], int key)
{
    int table, posT1, posT2;

    posT1 = hashFunctionT1(key);

    /* Inserção em posição vazia ou excluída em T1 */
    if( keySearch(t1, t2, key, &table) == -1 )
    {
        t1[posT1].key   = key;
        t1[posT1].empty = false;
        t1[posT1].position = posT1;

        return 1;
    }

    /* Temos uma colisão, calculamos h2(kT1) e inserimos em T2 */
    posT2 = hashFunctionT2(t1[posT1].key);
    
    /* Insere chave prévia de T1 em T2 */
    t2[posT2].key = t1[posT1].key;
    t2[posT2].empty = false;
    t2[posT2].position = posT2;
    
    /* Insere nova chave em T1 sobrescrevendo a chave anterior */
    t1[posT1].key = key;

    return 2;
}

int keyDelete(hashTable_T t1[], hashTable_T t2[], int key)
{
    int table;
    int posT1 = hashFunctionT1(key);
    int posT2 = hashFunctionT2(key);

    /* Testa se a chave está na Tabela II */
    if( (keySearch(t1, t2, key, &table) >= 0) && (table == 2) )
    {
        // t2[posT2].removed = true;
        t2[posT2].empty = true;
        t2[posT2].key = -1;
        return table;
    } 
    /* Senão, testa se a chave está na Tabela I */
    else if( (keySearch(t1, t2, key, &table) >= 0) && (table == 1) )
    {
        t1[posT1].removed = true;
        t1[posT1].empty = true;
        t1[posT1].key = -1;
        return table;
    }
    else /* Falha na remoção, chave não encontrada */
        return 0;
}

/* Retorna a comparação entre duas chaves para ordenação */
int keyCompare(const void *a, const void *b)
{
    if ((*(struct hashTable*)a).key == (*(struct hashTable*)b).key)
        return  0;
    else if ((*(struct hashTable*)a).key < (*(struct hashTable*)b).key)
        return -1;
    else
        return  1;       
}

int main()
{
    hashTable_T t1[M], t2[M], tr[M+M];

    char op;
    int i, key;

    initializeTables(t1, t2);

    /* Leitura das operações a partir da entrada padrão */
    while(scanf("%c %d\n", &op, &key) != EOF)
    {
        if(op == 'i')
            keyInsertion(t1, t2, key);
        else if(op == 'r')
            keyDelete(t1, t2, key);
        else
            printf("\nOperação inválida.\n");
    }

    /* Cópia das informações das Tabelas T1 e T2 para TR */
    int j = M;
    for(i = 0; i < M; i++)
    {
        tr[i]= t1[i];
        tr[j+i]= t2[i];
    }

    /* Ordena TR */
    qsort(tr, M*2, sizeof(hashTable_T), keyCompare);

    /* Imprime Ordenado */
    for(i = 0; i < M*2; i++)
    {
        if( (!tr[i].empty) && (tr[i].table == 1) )
            printf("%d,T1,%d\n",tr[i].key, tr[i].position);
        else 
            if( (!tr[i].empty) && (tr[i].table == 2) )
                printf("%d,T2,%d\n",tr[i].key, tr[i].position);
    }
    
    return 0;
}
