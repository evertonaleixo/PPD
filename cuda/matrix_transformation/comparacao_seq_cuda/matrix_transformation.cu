#include <stdio.h>
#include <cuda.h>
#include<sys/time.h>
#include <time.h>
#include<math.h>


// Kernel that executes on the CUDA device
__global__ void square_array(float *a, int N)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx<N) a[idx] = sqrtf(powf(2,a[idx]) + powf(a[idx],3));
}


// main routine that executes on the host
int main(void)
{
struct timeval iniciototal, finaltotal;
    gettimeofday(&iniciototal, NULL);
    int N, exec;  // Number of elements in arrays
    struct timeval inicio, final;
    int tmili,tmilifim;
    float media, soma ;
    int tam;
    for (N = 10; N <= 18; N++)
    {
    soma=0;
    tam = pow(2,N);
        for(exec =1; exec <= 10; exec++)
        {
            clock_t start, end;
            double cpu_time_used;


            start = clock();

            gettimeofday(&inicio, NULL);


            float *a_h, *a_d;  // Pointer to host & device arrays
            size_t size = tam * sizeof(float);
            a_h = (float *)malloc(size);        // Allocate array on host


            cudaMalloc((void **) &a_d, size);   // Allocate array on device
            // Initialize host array and copy it to CUDA device
            for (int i=0; i<tam; i++) a_h[i] = (float)i;
            cudaMemcpy(a_d, a_h, size, cudaMemcpyHostToDevice);
            // Do calculation on device:
            int block_size = 32;
            int n_blocks = tam/block_size + (tam%block_size == 0 ? 0:1);


            square_array <<< n_blocks, block_size >>> (a_d, tam);

            // Retrieve result from device and store it in host array
            cudaMemcpy(a_h, a_d, sizeof(float)*tam, cudaMemcpyDeviceToHost);






            //printf("%d\n", n_blocks);
            // Print results
            //for (int i=0; i<N; i++) printf("%d %f\n", i, a_h[i]);
            // Cleanup
            free(a_h);
            cudaFree(a_d);

            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nTempo Clock: %f secs", cpu_time_used);
            gettimeofday(&final, NULL);
            tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);

            soma+=tmili;

        }

        media = soma/10;
        printf("tamanho: %d \t tempo decorrido: %f\n", tam, media);
    }

    gettimeofday(&finaltotal, NULL);
            tmilifim = (int) (1000 * (finaltotal.tv_sec - iniciototal.tv_sec) + (finaltotal.tv_usec - iniciototal.tv_usec) / 1000);
            printf("tempo total decorrido: %d\n", tmilifim);
}
