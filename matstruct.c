#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_SIZE 2056

typedef struct{
    double *m;
    int N;
    int M;
} d_matrix;


double dm_get_val(int r, int c, d_matrix dm);
d_matrix init_d_matrix(char *csv_file, int N, int M);
void fill_mat(double *m, char* csv_file, int nrows, int ncols);

int main(int argc, char **argv)
{
    int i;
    int j;

    char *csv_file_1 = "example_mat_A2.csv"; 
    int N1 = 3;
    int M1 = 5;

    char *csv_file_2 = "example_mat_B2.csv"; 
    int N2 = 5;
    int M2 = 3;
    
    d_matrix dm1 = init_d_matrix(csv_file_1, N1, M1);
    d_matrix dm2 = init_d_matrix(csv_file_2, N2, M2);

    for (i = 0; i < N1; i++)
    {
        for (j = 0; j < M1; j++)
	{
	    printf(" %f ", dm_get_val(i, j, dm1));
	}
	printf("\n");
    }
}

double dm_get_val(int r, int c, d_matrix dm)
{
    return dm.m[r*dm.M+c];
}

d_matrix init_d_matrix(char *csv_file, int N, int M)
{
    d_matrix dm;
    dm.N = N;
    dm.M = M;
    dm.m = (double *)malloc(sizeof(double)*N*M);
    fill_mat(dm.m, csv_file, N, M);
    return dm;
}

void fill_mat(double *m, char *csv_file, int nrows, int ncols)
{
    int i;
    int mi;
    int sub_str_len;
    
    char* sub_buffer = (char*) malloc(BUFF_SIZE * sizeof(char));
    char* f_buffer = (char*) malloc(BUFF_SIZE * sizeof(char));
    char* new_buff = (char*) malloc(BUFF_SIZE * sizeof(char));
    char delim[] = ",";


    FILE* f = fopen(csv_file, "r");
    mi = 0;
    while (fgets(f_buffer, BUFF_SIZE, f) != NULL)
    {
        for (i = 0; i < strlen(f_buffer); i++)
        {
            if (f_buffer[i] != '\n')
                new_buff[i] = f_buffer[i];
        }
        
        char* top_ptr = strtok(new_buff, delim);

        while (top_ptr != NULL)
        {
            if (top_ptr[0] == '-')
            {
                sub_str_len = strlen(top_ptr);
                memcpy(sub_buffer, &top_ptr[1], sub_str_len-1);
                sub_buffer[sub_str_len] = '\0';
                m[mi] = (-1.0) * atof(sub_buffer);
            }
            else
            {
                m[mi] = atof(top_ptr);
            }
            mi++;
            top_ptr = strtok(NULL, delim);
        }
    }

}
