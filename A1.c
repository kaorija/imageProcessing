
/* This program reads a 2D image from an input file, applies
to it some image processing transformation upon request and
prints the output both to the screen and to a file.
The 2D image is stored and handled as a 2D array of characters. */

/****** PSEUDO CODE: ******
	*Initialization:
		Open the input file
			if problems, print message and exit
		Open the output file
				if problems, print message and exit
		Print a header message to screen and to file

		*Obtain the input data:
		Read row size and column size of image
		Read elements of image as integers, convert to characters, and store as 2D char array
		Print image as characters with headings to screen and to file

		*Processing the image:
		Repeat until the end of file is reached:
			Read an integer k from the input file specifying a task for the image
				Case k of:
					If 1 then call Vertical Mirror Image routine
					If 2 then call Horizontal Mirror Image routine
					If 3 then call Diagonal Right Image routine
					If 4 then call Diagonal Left Image routine
					If 5 then call Rotate Right Image routine (BONUS)
				Print the new image generated with headings to screen and to file

		*Closure:
		When End of File is reached
			Print a final message to screen and to file
			Close input and output files
		Exit the program*/

/* Code for File I/O to be taken from FileIntegersArray2.c */

#include <stdio.h>	/* include needed libraries */
#include <stdlib.h>
#include <string.h>

#define MAXROW 50	/*set maximum sizes for image 2D array */
#define MAXCOL 50
#define	AP	'&'		/*char symbols used in array */
#define	PL	'+'

/* global variables*/
FILE *fpin1,*fpout1;	/*pointers to files*/

/*************************************************************/
/****** void PrImage(Image, Nrows,Ncols) ******/
/* This procedure prints a 2D char array row by row
	both to the screen and to an output file (global) */
void PrImage( char Image[MAXROW][MAXCOL], int Nrows, int Ncols)
{
	int		i, j;

	for(i = 0; i < Nrows; i++) {
		for(j = 0; j < Ncols; j++) {
			if(j == Ncols-1) {
				fprintf(stdout, "%c", Image[i][j]);
				fprintf(fpout1, "%c", Image[i][j]);
			}
			else {
				fprintf(stdout, "%c ", Image[i][j]);
				fprintf(fpout1, "%c ", Image[i][j]);
			}
		}
		fprintf(stdout, "\n");
		fprintf(fpout1, "\n");
	}
}/*End of PrImage*/
/*************************************************************/
/****** void CopyCol(Mat1,Mat2,Nrows,Coli,Colj) ******/
/* Copy Coli of Mat1 to Colj of Mat2 of the same dimensions */
void CopyCol( char Mat1[MAXROW][MAXCOL], char Mat2[MAXROW][MAXCOL],
	int Nrows, int Coli, int Colj)
{
	int		i;
	for(i = 0; i < Nrows; i++) {
		Mat2[i][Colj] = Mat1[i][Coli];
	}
}/*End of CopyCol*/
/*************************************************************/
/****** void CopyRow(Mat1,Mat2,Ncols,Rowi,Rowj) ******/
/* Copy row i of Mat1 to row j of Mat2 of the same dimensions */
void CopyRow( char Mat1[MAXROW][MAXCOL], char Mat2[MAXROW][MAXCOL],
	int Ncols, int Rowi, int Rowj)
{
	int		j;
	for(j = 0; j < Ncols; j++) {
		Mat2[Rowj][j] = Mat1[Rowi][j];
	}
}/*End of CopyRow*/
/*************************************************************/
/****** void CopyColRow(Mat1,Mat2,Nrows,Coli,Rowj) ******/
/* Copy col i of Mat1 to row j of Mat2 */
void CopyColRow( char Mat1[MAXROW][MAXCOL], char Mat2[MAXROW][MAXCOL],
	int Nrows, int Ncols, int Coli, int Rowj)
{
	int		i, j;
	for(i = 0; i < Nrows; i++) {
		Mat2[Rowj][i] = Mat1[i][Coli];
	}
}/*End of CopyColRow*/
/*************************************************************/
/****** void CopyColrevRow(Mat1,Mat2,Nrows,Ncols,Coli,Rowj) ******/
/* Copy col i from (Nrows to 0) of Mat1 to row j of Mat2 from 0 to Ncols */
/* that is, copy the column, from bottom to top element,to the row */
/* 	copy column (Ncols-1) from (Nrows-1 element) to row (0) from (0) element
	copy column (Ncols-2) from (Nrows-1 element) to row (1) from (0) element
	copy column (0) from (Nrows-1 element) to row (Ncols-1) from (0) element*/
void CopyColrevRow( char Mat1[MAXROW][MAXCOL], char Mat2[MAXROW][MAXCOL],
	int Nrows, int Ncols, int Coli, int Rowj)
{
	// char temp[MAXROW][MAXCOL];
	// int		j;

	// for(j = 0; j < Ncols; j++) {
	// 	CopyColRow(Mat1, temp, Nrows, Ncols, j, Ncols-j-1);
	// }
	// for(j = 0; j < Ncols; j++) {
	// 	CopyRow(temp, Mat2, Nrows, j, Ncols-j-1);
	// }
}/*End of CopyrevColRow*/
/*************************************************************/
/****** void VMirror(Image1, Image2, Nrows, Ncols) ******/
/* Given the 2D char array of Image1 and its dimensions,
	construct the vertical mirror image in Image 2 as in:
	copy columns (0,1,...,Ncols-1) of Image1 to
	columns (Ncols-1, Ncols-2, ..., 1, 0) respectively of Image2 */
void VMirror( char Image1[MAXROW][MAXCOL], char Image2[MAXROW][MAXCOL],
	int Nrows, int Ncols)
{
	int		j;
	for(j = 0; j < Ncols; j++) {
		CopyCol(Image1, Image2, Nrows, j, Ncols-j-1);
	}
}/*End of VMirror*/
/*************************************************************/
/****** void HMirror(Image1, Image2, Nrows, Ncols) ******/
/* Given the 2D char array of Image1 and its dimensions,
	construct the horizontal mirror image in Image 2 as in:
		copy rows (0,1,...,Nrows-1) of Image1
		to rows (Nrows-1,Nrows-2,...,1,0) respectively of Image2 */
void HMirror( char Image1[MAXROW][MAXCOL], char Image2[MAXROW][MAXCOL],
	int Nrows, int Ncols)
{
	int			i;
	for(i = 0; i < Nrows; i++) {
		CopyRow(Image1, Image2, Ncols, i, Nrows-i-1);
	}
}/*End of HMirror*/
/*************************************************************/
/****** void DiagR(Image1, Image2, Nrows, Ncols) ******/
/*Given the 2D char array of Image1 and its dimensions,
	construct the flipped image in Image2 along the top
	left to bottom right diagonal as in:
		 copy col 0 of Image1 -> row 0 of Image2
		 copy col 1 of Image1 -> row 1 of Image2
		......................................
		 copy col (Ncols-1) of Image1 to row (Ncols-1) of Image2
		 NOTE: sizes of Image2 are inverted from Image1 */
void DiagR( char Image1[MAXROW][MAXCOL], char Image2[MAXROW][MAXCOL],
	int Nrows, int Ncols)
{
	int			j;
	for(j = 0; j < Ncols; j++) {
		CopyColRow(Image1, Image2, Nrows, Ncols, j, j);
	}
}/*End of DiagR*/
/*************************************************************/
/****** void DiagL(Image1, Image2, Nrows, Ncols) ******/
/*Given the 2D char array of Image1 and its dimensions,
	construct the flipped image in Image2 along the top
	right to bottom left diagonal as in:
		copy col (Ncols-1) of Image1 -> row 0 of Image2
		copy col (Ncols-2) of Image1 -> row 1 of Image2
		......................................
		copy col 0 of Image1 -> row (Ncols-1) of Image2
		NOTE: sizes of Image2 are inverted from Image1 */
void DiagL( char Image1[MAXROW][MAXCOL], char Image2[MAXROW][MAXCOL],
	int Nrows, int Ncols)
{
	char temp[MAXROW][MAXCOL];
	int		j;

	for(j = 0; j < Ncols; j++) {
		CopyColRow(Image1, temp, Nrows, Ncols, j, Ncols-j-1);
	}
	VMirror(temp, Image2, Ncols, Nrows);
}/*End of DiagL*/
/*************************************************************/
/****** void RotR(Image1, Image2, Nrows, Ncols) ******/
/*Given the 2D char array of Image1 and its dimensions,
	construct the rotated by 90 degree image in Image2 */
void RotR( char Image1[MAXROW][MAXCOL], char Image2[MAXROW][MAXCOL],
	int Nrows, int Ncols)
{
	// fprintf(stdout, "\n Optional task 5 - not implemented \n");
	// fprintf(fpout1, "\n Optional task 5 - not implemented \n");

	int		i, j;
	for(i = 0; i < Nrows; i++) {
		for(j = 0; j < Ncols; j++) {
			Image2[j][Nrows-i-1] = Image1[i][j];
		}
	}


}/*End of RotR*/
/*************************************************************/
/****** void RdSize(*Nrows,*Ncols) ******/
/*Read from an input file two integers for the number of rows and
	number of columns of the image to be processed*/
void RdSize(int *Nrows, int *Ncols)
{
	fscanf(fpin1, "%d %d\n", Nrows, Ncols);
}/*End of RdSize*/
/*************************************************************/
/****** void RdImage(Image,Nrows,Ncols) ******/
/*Read from an input file the integers describing the image to
	be processed and store the corresponding character in the 2D array*/
void RdImage(char Image1[MAXROW][MAXCOL],int Nrows, int Ncols)
{
	char 	*line = NULL;
	size_t 	len = 0;
    ssize_t read;
	int		i, j;

	char	*token;
    char	*rest;

	for(i = 0; i < Nrows; i++) {
		read = getline(&line, &len, fpin1);
		rest = line;
		for(j = 0; j < Ncols; j++)
		{
			token = strtok_r(rest, " ", &rest);
			if(!token)
				break;
			if(atoi(token) == 0)
				Image1[i][j] = PL;
			else
				Image1[i][j] = AP;
		}
	}
	if (line)
        free(line);
}/*End of RdImage*/
/*************************************************************/
/****** void RdDoTask(Image1,Image2,Nrows,Ncols)***/
/*Read integers from an opened input file until EOF, and call
the appropriate stub routine for each task represented*/
int RdDoTask(char Image1[MAXROW][MAXCOL],
			char Image2[MAXROW][MAXCOL],int Nrows, int Ncols)
{
	int 	nTask;
	while(fscanf(fpin1, "%d", &nTask) == 1) {
		switch(nTask) {
			case 1:
				fprintf(stdout,"\nTask %d = Vertical Mirroring\n", nTask);
				fprintf(fpout1,"\nTask %d = Vertical Mirroring\n", nTask);
				VMirror(Image1, Image2, Nrows, Ncols);
				fprintf(stdout, "IMchr2 contains: \n");
				fprintf(fpout1, "IMchr2 contains: \n");
				PrImage(Image2, Nrows, Ncols);
				break;
			case 2:
				fprintf(stdout,"\nTask %d = Horizontal Mirroring\n", nTask);
				fprintf(fpout1,"\nTask %d = Horizontal Mirroring\n", nTask);
				HMirror(Image1, Image2, Nrows, Ncols);
				fprintf(stdout, "IMchr2 contains: \n");
				fprintf(fpout1, "IMchr2 contains: \n");
				PrImage(Image2, Nrows, Ncols);
				break;
			case 3:
				fprintf(stdout,"\nTask %d = Diagonal Right\n", nTask);
				fprintf(fpout1,"\nTask %d = Diagonal Right\n", nTask);
				DiagR(Image1, Image2, Nrows, Ncols);
				fprintf(stdout, "IMchr2 contains: \n");
				fprintf(fpout1, "IMchr2 contains: \n");
				PrImage(Image2, Ncols, Nrows);
				break;
			case 4:
				fprintf(stdout,"\nTask %d = Diagonal Left\n", nTask);
				fprintf(fpout1,"\nTask %d = Diagonal Left\n", nTask);
				DiagL(Image1, Image2, Nrows, Ncols);
				fprintf(stdout, "IMchr2 contains: \n");
				fprintf(fpout1, "IMchr2 contains: \n");
				PrImage(Image2, Ncols, Nrows);
				break;
			case 5:
				fprintf(stdout,"\nTask %d = Rotation Right\n", nTask);
				fprintf(fpout1,"\nTask %d = DiaRotation Right\n", nTask);
				RotR(Image1, Image2, Nrows, Ncols);
				fprintf(stdout, "IMchr2 contains: \n");
				fprintf(fpout1, "IMchr2 contains: \n");
				PrImage(Image2, Ncols, Nrows);
				break;
		}
	}
	
} /*End RdDoTask*/


/*************************************************************/
/*************************************************************/
int main() {

    int	eof;

    /* Initialize a 4x3 char image for testing*/
	// int Rsize1 = 4;
	// int Csize1 = 3;
	// char IM1[MAXROW][MAXCOL] = {{'+', '+', '&'},{'+', '&', '&'},
	// 	{'+', '&', '&'},{'+', '&', '+'}};

	/* these are probably the real declarations you will need */
    int Rsize1, Csize1;	/*image sizes*/
	char IMchr1[MAXROW][MAXCOL]; /*original image*/
	char IMchr2[MAXROW][MAXCOL]; /*resulting image after processing*/

	fprintf(stdout, "Hello:\n");		/*start of program*/

	/*open all input and output files*/
	// fpin1 = fopen("A1In.txt", "r");  /* open the file for reading */
	fpin1 = fopen("A1inF.txt", "r");  /* open the file for reading */
	if (fpin1 == NULL) {
		fprintf(stdout, "Cannot open input file - Bye\n");
		return(0); /*if problem, exit program*/
	}

	fpout1 = fopen("A1Out.txt", "w");  /* open the file for writing */
	if (fpout1 == NULL) {
		fprintf(stdout, "Cannot open output file - Bye\n");
		return(0); /*if problem, exit program*/
	}

	/*hello message to screen and output file*/
	fprintf(stdout, "\n Kayode Abraham Orija - Student Number 181114 \n");
	fprintf(stdout, "\n File = A1.c	- Winter 2022 \n");
	fprintf(stdout, "\n Welcome to CSC 367, Assignment 1, Part 2\n\n");
	fprintf(fpout1, "\n Kayode Abraham Orija - Student Number 181114\n");
	fprintf(fpout1, "\n File = A1.c	- Winter 2022 \n");
	fprintf(fpout1, "\n Welcome to CSC 367, Assignment 1, Part 2\n\n");

	fprintf(stdout,"Starting: \n");
	fprintf(fpout1,"Starting: \n");

	/*Read in the sizes for the image*/
	RdSize(&Rsize1, &Csize1);
	/*Read in the image*/
	RdImage(IMchr1, Rsize1, Csize1);

	/*Print the initial image*/
	fprintf(stdout, " Initial IMchr1 contains: \n");
	fprintf(fpout1, " Initial IMchr1 contains: \n");
	PrImage(IMchr1, Rsize1, Csize1);

	/* read all integers from file until EOF - for each call the
	required stub routine for the image processing task*/
	RdDoTask(IMchr1, IMchr2, Rsize1, Csize1);

	/* Closure */
	fprintf(stdout, "\n The program is all done - Bye! \n");
	fprintf(fpout1, "\n The program is all done - Bye! \n");

	fclose(fpin1);  /* close the files */
	fclose(fpout1);

	return (0);
}/*End of Main*/
