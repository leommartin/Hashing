#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define M 11

struct hashTable{
    int key;
    bool removed;
    bool empty;
    int table;
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

    /* Posição de T1 vazia ou com chave removida/nao-removida*/
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
        // printf("Chave %d não está em nenhuma das tabelas.\n\n", key);
        return -2;
}

int keyInsertion(hashTable_T t1[], hashTable_T t2[], int key, int *position)
{
    int table, posT1, posT2;

    posT1 = hashFunctionT1(key);

    /* Inserção em posição vazia ou excluída em T1 */
    if( keySearch(t1, t2, key, &table) == -1 )
    {
        t1[posT1].key   = key;
        t1[posT1].empty = false;

        *position = posT1;
        return 1;
    }

    /* Temos uma colisão, calculamos h2(kT1) e inserimos em T2 */
    posT2 = hashFunctionT2(t1[posT1].key);
    
    /* Insere chave prévia de T1 em T2 */
    t2[posT2].key = t1[posT1].key;
    t2[posT2].empty = false;
    
    /* Insere nova chave em T1 sobrescrevendo a chave anterior */
    t1[posT1].key = key;

    *position = posT2;
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

int main()
{
    hashTable_T t1[M], t2[M], tR[M+M];

    // int vetor[5]  = { 10, 22, 4, 15, 59 };
    // int vetor2[3] = { 15, 22, 59 };

    char op;
    int i, table, position, key;

    initializeTables(t1, t2);

    printf("\n\n");

    while(scanf("%c %d\n", &op, &key) != EOF)
    {
        if(op == 'i')
        {
            if(keyInsertion(t1, t2, key, &position) == 1)
                printf("Chave %d inserida na tabela T1 na posição [%d].\n", key, position);
            else
                printf("Chave %d inserido na tabela T2 na posicao [%d] após colisão com T1.\n", key, position);
        }
        else if(op == 'r')
        {
            if(table = keyDelete(t1, t2, key))
                printf("Chave %d deletada da tabela T%d. \n", key, table);
            else
                printf("Chave %d não existe em ambas tabelas. \n", key);
        }
        else
            printf("\nOperação inválida.\n");
    }

    printf("\n\n");
    for(i = 0; i < M; i++)
        // if( ! t1[i].empty || !t2[i].empty )
            printf("t1[%d]: %d \t t2[%d]: %d \n", i, t1[i].key, i, t2[i].key);

    /* Opções de ordenação pela chave */
    
        /* Adicionar var "table" na struct dos elementos da THash? */
        /* Copiar todas as chaves existentes para um vetor com 2M posições e ordenar */

        /* Ordenar as duas tabelas após as inserções e remoções, comparar valores das duas tabelas ordenadas e imprimir */
    
    return 0;
}


// else if( ! t1[i].empty )
//     printf("t1[%d]: %d \t", i, t1[i].key);
// else if( ! t2[i].empty )
//     printf("t2[%d]: %d \n", i, t2[i].key);


/* REMOCAO */

// int posT1, posT2;

// posT2 = hashFunctionT2(key);

// if(t2[posT2].empty == 0 && key == t2[posT2].key)
// {
//     t2[posT2].empty = 1;
// }
// else
// {
//     posT1 = hashFunctionT1(key);

//     t1[posT1].removed = 1;
// }

// // Analisar e terminar a remoção.