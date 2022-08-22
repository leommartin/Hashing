#include<stdio.h>
#include<math.h>

int main()
{
    float valor;

    scanf("%f", &valor);
    printf("valor: %.2f\n", valor);
    printf("valor considerando piso: %.2f\n", floor(valor));
}