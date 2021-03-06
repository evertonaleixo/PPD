#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

struct merge_data {
   int i;
   int j;
   int *data;
};

void mergesort(void *data) {
    struct merge_data *value = (struct merge_data*)data;
    struct merge_data right_side;
    struct merge_data left_side;
    int i, j, k, middle, vector_len;

    middle = (int) (value->i+value->j)/2;
    vector_len = (value->j-value->i);

    if (DEBUG) {
        printf("ENTREI NO MERGE %d %d %d -- Meu vetor: ", value->i, value->j, middle);

        for(i=0 ; i <= (value->j - value->i) ; i++) {
           printf("%d ", value->data[i]);
        }
        printf("\n");
    }

    if(vector_len >= 1) {
	left_side.data = (int *) malloc(sizeof(int) * (middle - value->i + 1));
	left_side.i = 0;
	left_side.j = (middle - value->i);
        for(i=value->i, j=0 ; i <=middle  ; i++, j++) {
            left_side.data[j] = value->data[i];
        }
        if (DEBUG) {
	    printf("VETOR left_side: ");
            for(i=0 ; i < (middle - value->i + 1) ; i++) {
	       printf("%d ", left_side.data[i]);
	    }
	    printf("\n");
        }

	right_side.data = (int *) malloc(sizeof(int) * (value->j - middle));
	right_side.i = 0;
	right_side.j = (value->j - middle - 1);
        for(i=middle+1, j=0 ; i <= value->j ; i++, j++) {
            right_side.data[j] = value->data[i];
        }

        if (DEBUG) {
	    printf("VETOR right_side: ");
	    for(i=0 ; i < (value->j - middle) ; i++) {
	        printf("%d ", right_side.data[i]);
	    }
	    printf("\n\n");
        }

        mergesort((void *)&left_side);
	mergesort((void *)&right_side);
    } else {
	    left_side.data = (int *) malloc(sizeof(int) * (1));
        left_side.data[0] = value->data[value->i];        left_side.i = value->i;
        left_side.j = value->j;
	    right_side.data = (int *) malloc(sizeof(int) * (1));
	    right_side.data[0] = value->data[value->i];
        right_side.i = value->i;
        right_side.j = value->j;
    }

    // Junta as duas partes
    i = j = 0;
    for(k=value->i ; k<=value->j && (i<=right_side.j) && (j<=left_side.j) ; k++) {
        // Decide se vai usar o left ou o right
	if(right_side.data[i] < left_side.data[j]) {
            value->data[k] = right_side.data[i++];
        } else {
            value->data[k] = left_side.data[j++];
        }
    }
    // Adiciona o que sobrou no data
    while((i<=right_side.j)) {
	value->data[k++] = right_side.data[i++];
    }

    while((j<=left_side.j)) {
        value->data[k++] = left_side.data[j++];
    }

    if (DEBUG) {
        printf("VETOR PARCIALMENTE ORDENADO\n");
        for(k=0 ; k<=value->j ; k++) {
	    printf ("%d ", value->data[k]);
        }
        printf("\n\n\n");
    }

    free(left_side.data);
    free(right_side.data);
}

int * generate_randon_vector(int n) {
    int i;
    int * vector = (int *) malloc(sizeof(int) * n);
    srand(time(NULL));
    for(i=0 ; i<n ; i++) {
        int x = rand();
        vector[i] =  x%(3*n);
    }
    return vector;
}

int main (int argc, char *argv[]) {
    int i;
    int rc;
    struct merge_data struct_data;

    int n = 40000;
    int * data = generate_randon_vector(n);

    struct_data.data = data;
    struct_data.i = 0;
    struct_data.j = n;

    mergesort((void *)&struct_data);

/*
    printf("\n\nVETOR ORDENADO\n");
    for(i=0 ; i< n ; i++) {
        printf("%d ", data[i]);
    }
    printf("\n\n");
*/
    /* Last thing that main() should do */
    pthread_exit(NULL);
 }
