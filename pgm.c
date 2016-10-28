/*
 *
 * Functions for reading and writing a PGM format file.
 *
 *				(C) 1997 by Garavelos Thodoris.
 *
 */

#include <stdio.h>
#include <string.h>
#include "pgm.h"

/*
 *
 * Checks for white spaces.
 *
 */
int isWhiteSpace(int num)
{
   if ((num == ' ') || (num == '\t') || (num == '\n') || (num == '\r'))
      return 1;
   else
      return 0;
}

/*
 *
 * Converts a string to an int ignoring white spaces and comment lines.
 *
 */
int char2Int(FILE *f)
{
   int num;
   char ch, tmp;

   num = 0;
   do
   {
      do
      {
	 fread(&ch, sizeof(char), 1, f);
      } while (isWhiteSpace(ch) == 1);
      if (ch == '#')
	 while (ch != '\n')
	    fread(&ch, sizeof(char), 1, f);
   } while (isWhiteSpace(ch) == 1);
   while (('0' <= ch) && (ch <= '9'))
   {
      num = 10*num + ch - '0';
      fread(&ch, sizeof(char), 1, f);
   }
   return num;
}

/*
 *
 * Reads a PGM file format. The file name is in name. As output you get
 * the image dimensions in rows and columns while an array is returned
 * containing the image values.
 *
 * The raw PGM format follows:
 *
 * 	P5
 * 	# lines with '#' are comments, we ignore everything up to a new line
 *	# and are optional.
 *	width height
 *	max_value #usally set to 255
 *	and follows the image as rows starting from the top of the image
 *	while columns go from left to right.
 *
 */
int **ReadImage(char *name, int *rows, int *columns)
{
   FILE *fp;
   char P, type;
   unsigned char ch;
   int i, j, max;
   int **pic;

   fp = fopen(name, "r");
   if (fp == NULL)
   {
      printf("File open error\n");
      exit(0);
   }
   
   fread(&P, sizeof(char), 1, fp);
   fread(&type, sizeof(char), 1, fp);
   if ((P != 'P') || (type != '5'))
   {
      printf("Not a raw PGM file\n");
      exit(0);
   }
   
   *columns = char2Int(fp);
   *rows = char2Int(fp);
   max = char2Int(fp);

   pic = (int **) calloc(*rows, sizeof(int *));
   if (pic == NULL)
   {
      printf("Not enough memory.\n");
      exit(0);
   }
   for (i = 0; i < *rows; i++)
   {
      pic[i] = (int *) calloc(*columns, sizeof(int));
      if (pic[i] == NULL)
      {
         printf("Not enough memory.\n");
         exit(0);
      }
   }
   for (i = 0; i < *rows; i++)
      for (j = 0; j < *columns; j++)
      {
	 fread(&ch, sizeof(unsigned char), 1, fp);
	 pic[i][j] = ch;
      }
   fclose(fp);

   return pic;
}


/*
 *
 * Converts an int to a string and writes it to a file.
 *
 */
void int2Char(int num, FILE *f)
{
   int count;
   char m[40];

   count = 0;
   do
   {
      m[count] = num%10 + '0';
      num -= num % 10;
      num /= 10;
      count++;
   } while (num > 0);

   for (count = count - 1; count >= 0; count--)
      fwrite(&m[count], sizeof(char), 1, f);
}

/*
 *
 * Writes the image having dimensions (rows x columns) to a file in PGM
 * format. PGM format is described in prgRead function comments.
 *
 */
void WriteImageInt(int **image, int rows, int columns, char *name)
{
   int i, j, length;
   unsigned char ch;
   char *fileName;
   FILE *f;

   /* Add .pgm extension. */
   if (strstr(name, EXTENSION) == NULL)
   {
      length = strlen(name) + strlen(EXTENSION) + 1;
      fileName = (char *) malloc(length * sizeof(char));
      if (fileName == NULL)
      {
         printf("Memory allocation error\n");
	 exit(0);
      }
      strcpy(fileName, name);
      strcat(fileName, EXTENSION);
   }
   else
      fileName = name;
   f = fopen(fileName, "w");
   if (f == NULL)
   {
      printf("File writing error\n");
      exit(0);
   }
   
   fwrite("P5\n", sizeof(char), 3, f);
   fwrite("# CREATOR: Garavelos Thodoris  (C) 1997\n", sizeof(char), 40, f);
   fwrite("#        :           CSD Univ. of Crete\n", sizeof(char), 40, f);
   int2Char(columns, f);
   fwrite(" ", sizeof(char), 1, f);
   int2Char(rows, f);
   fwrite("\n", sizeof(char), 1, f);
   int2Char(PGM_MAX, f);
   fwrite("\n", sizeof(char), 1, f);
   for (i = 0; i < rows; i++)
      for (j = 0; j < columns; j++)
      {
	 ch = image[i][j];
         fwrite(&ch, sizeof(unsigned char), 1, f);
      }

   fclose(f);
}

