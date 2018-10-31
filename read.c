#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define F_NAME_MAX_LEN 256
#define BUFF_SIZE 2056

double get_val(double *m, int row, int col, int ncols);
void set_val(double *m, int row, int col, int ncols, double val);
void fill_mat(double *m, char* csv_file, int nrows, int ncols);

int main(int argc, char *argv[])
{
    char *filename;
    int nrows;
    int ncols;
    double *m;

    
    /* Print number of arguments.*/
    printf("Number of arguments: %d\n", argc);

    if (argc != 4)
    {
        exit(0);
    }

    filename = (char*) malloc(F_NAME_MAX_LEN*sizeof(char));
    strcpy(filename, argv[1]);
    nrows = atoi(argv[2]);
    ncols = atoi(argv[3]);

    printf("%s, %d, %d\n", filename, nrows, ncols);
    m = (double *)malloc(sizeof(double)*nrows*ncols);
    fill_mat(m, filename, nrows, ncols);
    free(m);
    m = NULL;
}

double get_val(double *m, int row, int col, int ncols)
{
    return m[row*ncols + col];
}

void set_val(double *m, int row, int col, int ncols, double val)
{
    m[row*ncols + col] = val;
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
