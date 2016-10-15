#include <stdio.h>
#include<sys/time.h>
#include<math.h>

float funcao (float x){
    float resul = sqrt(pow(2,x) + pow(x,3));
    return resul;
}

void main(void){
  int N;

struct timeval inicio, final;

    int tmili;

for (N = 10; N <= 27; N++){
    gettimeofday(&inicio, NULL);
    int tam = pow(2,N);
    float *vet = (float *)malloc(tam * sizeof(float));
    int i;

    for (i=0; i<tam; i++) vet[i] = (float)i + 1;

    for ( i=0; i<tam; i++) vet[i] = funcao(vet[i]);

    gettimeofday(&final, NULL);
    tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);

    printf("tamanho: %d \t tempo decorrido: %d\n",tam, tmili);
    free(vet);
}


}
