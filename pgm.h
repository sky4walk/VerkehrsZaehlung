/*
 *
 */

#define EXTENSION ".pgm"
#define PGM_MAX 255

int isWhiteSpace(int num);
int char2Int(FILE *f);
void int2Char(int num, FILE *f);

int **ReadImage(char *name, int *rows, int *columns);
void WriteImageInt(int **image, int rows, int columns, char *name);

