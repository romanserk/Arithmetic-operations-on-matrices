/*
This class makes the calculation on the matrixes
line 54:   read_mat    - stores values in a given matrix.
line 110:  print_mat   - printing the given as parameter matrix.
line 141:  add_mat     - adds the sum of two matrix into third matrix.
line 165:  sub_mat     - substracts two matrix and stores the sum in third matrix.
line 191:  mul_mat     - multiply two matrix and stores the multiplication in third matrix.
line 260:  mul_scalar  - multiply matrix by scalar (second parameter real number) and stores the multiplication on second matrix.
line 307:  trans_mat   - make a transpose of matrix and store in second matrix.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "mat.h"

#define LIMIT	100
#define FALSE	0
#define TRUE	1

mat MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F;

struct {
	char *name;
	mat *matrix;
} mats[] = {
	{ "MAT_A",&MAT_A },
	{ "MAT_B",&MAT_B },
	{ "MAT_C",&MAT_C },
	{ "MAT_D",&MAT_D },
	{ "MAT_E",&MAT_E },
	{ "MAT_F",&MAT_F },
};

typedef struct tnode {
	mat *first_parm;
	mat *second_parm;
	mat *result;
}parms;

parms temp_parm;
char command[LIMIT];



mat *ismatrix(char *);
char *skipspace(char *);
int isnumber(char *);
int checkMatrixes(char *, int num);
int validcommand(char *, int num);

/* stores values in a given matrix*/
void read_mat() {
	char *token;
	double *p;
	double *q;
	double temp;
	mat *matx;
	mat tempmat;

	gets(command);

	if (validcommand(command, 1)) {

		token = skipspace(strtok(command, ","));	/* gets the first token from the command */
		printf("\nReading matrix: %s\n", token);
		if ((matx = ismatrix(token)) != NULL) {			/* checks if the token is matrix */
			temp_parm.first_parm = matx;
			token = skipspace(strtok(NULL, ","));	/* gets the next token from the command */

			p = (double *)temp_parm.first_parm;
			q = (double *)tempmat;

			while (p < (((double *)temp_parm.first_parm) + 16)) {
				if ((token != NULL)) {
					if (isnumber(skipspace(token))) {	/* checks if the current token is a number, and stores it in the matrix if true*/
						temp = atof(token);
						*q = temp;
					}
					else {
						return;
					}
				}
				else {									/* stores 0 in the remaining of the matrix if empty*/
					*q = 0;
				}
				token = strtok(NULL, ",");
				p++;
				q++;
			}
			p = (double *)temp_parm.first_parm;
			q = (double *)tempmat;
			while (p < (((double *)temp_parm.first_parm) + 16)) {

				*p = *q;
				p++;
				q++;

			}
			printf("\nReading succeeded\n");

		}

	}

}

/*printing the given as parameter matrix. */
void print_mat() {
	char *token;
	double *p;
	mat *mtx;
	int row = 0;

	gets(command);
	if (validcommand(command, 1)) {
		token = skipspace(command);
		if ((mtx = ismatrix(token)) != NULL) {
			temp_parm.first_parm = mtx;
		}
		else {
			return;
		}
		printf("\nPrinting matrix %s  ...\n", token);
		printf("\n\n");
		for (p = (double *)temp_parm.first_parm; p < ((double *)temp_parm.first_parm) + 16; p++) {
			printf("%0.2f\t\t", *p);
			row++;

			if (row == 4) {
				printf("\n");
				row = 0;
			}
		}
		printf("\nPrinting succeeded\n");
	}
}

/* adds the sum of two matrix into third matrix*/
void add_mat() {
	char *token;
	double *p;
	double *q;
	double *result;

	gets(command);
	printf("\nSumming matrices...\n");
	if (validcommand(command, 3)) {
		token = skipspace(command);

		if (checkMatrixes(token, 3)) {
			for (p = (double *)temp_parm.first_parm, q = (double *)temp_parm.second_parm, result = (double *)temp_parm.result; p < ((double *)temp_parm.first_parm) + 16; p++, q++, result++) /* itarate over the 3 mats*/
				*result = *p + *q;
			printf("\nCommand succeeded\n");

		}
		else
			return;
	}

}

/* substracts two matrix and stores the sum in third matrix*/
void sub_mat() {
	char *token;
	double *p;
	double *q;
	double *result;

	gets(command);
	printf("\nSubtracting matrices...\n");
	if (validcommand(command, 3)) {
		token = skipspace(command);
		if (checkMatrixes(token, 3)) {

			q = (double *)temp_parm.second_parm;
			result = (double *)temp_parm.result;

			for (p = (double *)temp_parm.first_parm; p < ((double *)temp_parm.first_parm) + 16; p++, q++, result++)
				*result = *p - *q;
			printf("\nCommand succeeded\n");

		}
		else
			return;
	}
}

/* multiply two matrix and stores the multiplication in third matrix. */
void mul_mat() {
	char *token;
	double *p;
	double *q;
	double *temp;
	double *result;
	double sum = 0;
	int count = 0;
	int col = 0;
	int nextrow = 0;
	mat tempmat;

	gets(command);
	if (validcommand(command, 3)) {
		printf("\nMultiplying matrices...\n");
		token = skipspace(command);

		if (checkMatrixes(token, 3)) {

			p = (double *)temp_parm.first_parm;
			q = (double *)temp_parm.second_parm;
			temp = (double *)tempmat;

			while (temp < (((double *)tempmat) + 16)) {
				/*multyply row of mat a over column of mat b*/
				while (col < SIZE) {
					sum += (*p) * (*q);
					p++;
					q += SIZE;
					col++;
				}
				*temp = sum;
				sum = 0;
				count++;
				col = 0;

				if (count == SIZE) {		/* if we are at the last column, initiate the column pointer position and move to the next row*/
					nextrow += SIZE;
					p = (double *)temp_parm.first_parm;
					p += nextrow;
					q = (double *)temp_parm.second_parm;
					count = 0;
				}
				else {		/* if we are not in the last column, move to the next one and initiate the row poition*/
					q = (double *)temp_parm.second_parm;
					q += count;
					p = (double *)temp_parm.first_parm;
					p += nextrow;

				}
				temp++;
			}
			temp = ((double *)tempmat);
			result = (double *)temp_parm.result;
			while (result < ((double *)temp_parm.result) + 16) {

				*result = *temp;
				result++;
				temp++;
			}
			printf("\nMultiplication succeeded\n");

		}
		else
			return;
	}
}

/*  multiply matrix by scalar (second parameter real number) and stores the multiplication on second matrix */
void mul_scalar() {

	char *token;
	double *p;
	double *result;
	mat *mtx;
	double scalar;

	gets(command);
	printf("\nMultiplying matrix by scalar...\n");
	if (validcommand(command, 3)) {
		token = skipspace(strtok(command, ","));	/* gets the first token from the command */
		printf("%s", token);
		if ((mtx = ismatrix(token)) != NULL) {
			temp_parm.first_parm = mtx;
		}
		else {
			return;
		}

		token = skipspace(strtok(NULL, ","));		/* gets the next token from the command */
		if (isnumber(token)) {					/* checks if the token is a real number*/
			scalar = atof(token);
			printf(" by scalar %0.2f and puts the result to ", scalar);
			token = skipspace(strtok(NULL, ","));		/* gets the third token from the command */
			if ((mtx = ismatrix(token)) != NULL) {
				temp_parm.second_parm = mtx;
				printf("%s", token);
			}
			else {						/* return if the token isn't matrix */
				return;
			}
			result = (double *)temp_parm.second_parm;

			for (p = (double *)temp_parm.first_parm; p < ((double *)temp_parm.first_parm) + 16; p++) {
				*result = *p * scalar;
				result++;
			}
			printf("\nMultiplication by scalar succeeded\n");
		}
		else
			return;
	}

}

/* make a transpose of matrix and store in second matrix */
void trans_mat() {

	char *token;
	double *p;
	double *q;
	double *result;
	int count = 1, resultindx = 1;
	mat tempmat;


	gets(command);
	printf("\nTransposing matrix...\n");
	if (validcommand(command, 2)) {
		token = skipspace(command);

		if (checkMatrixes(token, 2)) {
			q = (double *)tempmat;

			for (p = (double *)temp_parm.first_parm; p < ((double *)temp_parm.first_parm + 16); p++) {

				*q = *p;
				if (count == SIZE) { 					/* end of p row starts new result column */
					q = (double *)tempmat;
					q += resultindx;
					resultindx++;
					count = 1;
				}
				else {
					q += SIZE;
					count++;
				}

			}
			q = (double *)tempmat;
			result = (double *)temp_parm.second_parm;
			while (result < ((double *)temp_parm.second_parm + 16)) {
				*result = *q;
				result++;
				q++;
			}
			printf("\nTransposing succeeded\n");
		}
		else
			return;
	}

}

void stop() {
	exit(0);
}


/* gets a pointer to a string, and returns the pointer to the matrix with the same name if exists*/
mat *ismatrix(char *token) {
	int i;
	token = skipspace(token);

	for (i = 0; mats[i].matrix != NULL; i++) {		/* looks for the given matrix in the matrix struct*/
		if (strcmp(token, mats[i].name) == 0) {
			break;
		}
	}
	if ((mats[i].matrix == NULL)) {
		printf("\nUndefined matrix name:\t%s\n\nCommand canceled\n", token);		/* return error if not found*/
		return NULL;
	}
	else
		return mats[i].matrix;						/* return pointer to the relevant matrix if found*/
}

/* gets a pointer to a string, and returns 1 if is a number or 0*/
int isnumber(char *token) {
	char *p;
	int flaga = 1;
	int flagb = 1;
	int flagc = 1;

	p = token;
	while (*p) {
		if (isdigit(*p) && flagc) {
			p++;
		}
		else if ((*p == '.') && (flaga)) {
			flaga = 0;
			p++;
		}
		else if ((*p == '-') && (flagb)) {
			flagb = 0;
			p++;
		}
		else if ((*p == ' ' || *p == '\t') && (flagc)) {
			flagc = 0;
			while (*p == ' ' || *p == '\t')
				p++;
		}
		else {
			printf("Parameter not a real number:\t%s\n\nCommand canceled\n", token);
			return 0;
		}
	}
	return 1;

}

int checkMatrixes(char *token, int num) {
	mat *mtx;

	token = skipspace(strtok(command, ","));	/* gets the first token from the command */
	if ((mtx = ismatrix(token)) != NULL) {
		temp_parm.first_parm = mtx;
		printf("%s", token);
	}
	else {						/* return if the token isn't matrix */
		return 0;
	}

	token = skipspace(strtok(NULL, ","));		/* gets the second token from the command */
	if ((mtx = ismatrix(token)) != NULL) {
		temp_parm.second_parm = mtx;
		if (num == 3) {
			printf(" %s", token);
		}
		if (num == 2) {
			printf(" to %s", token);
		}
	}
	else {						/* return if the token isn't matrix */
		return 0;
	}
	if (num == 3) {
		token = skipspace(strtok(NULL, ","));		/* gets the third token from the command */
		if ((mtx = ismatrix(token)) != NULL) {
			temp_parm.result = mtx;
			printf(" and puts the result to %s", token);
		}
		else {						/* return if the token isn't matrix */
			return 0;
		}
	}

	return 1;

}

/* gets a pointer to a string, and returns the pointer to the same string without whitespaces*/
char *skipspace(char *pointer) {
	while (((*pointer) == ' ' || (*pointer) == '\t'))
		pointer++;

	return pointer;
}
/* check the validation of the command */
int validcommand(char *com, int num) {
	int flaga = 1;
	int count = 0;
	int let = 0;

	while (*com) {
		if (let == 0 && *com == ',') {
			printf("Invalid comma after command name\n");
			return 0;
		}
		while (*com == ' ' || *com == '\t') {
			com++;
		}
		if (*com == ',') {
			flaga = 0;
			count++;
		}
		else {
			flaga = 1;
		}
		let++;
		com++;
		if (*com == ',' && !flaga) {
			printf("Multiple consecutive commas\nCommand canceled\n");
			return 0;
		}
	}

	if (num == 1) {
		if (let < 1) {
			printf("Missing parameter\nCommand canceled\n");
			return 0;
		}
		if (let > 0 && let < 5) {
			printf("Undefined matrix name\nCommand canceled\n");
			return 0;
		}
	}
	if (num == 2) {
		if (count < 1) {
			printf("Missing comma\nCommand canceled\n");
			return 0;
		}if (let > 11) {
			printf("Extraneous text at the end of command\nCommand canceled\n");
			return 0;
		}
	}
	if (num == 3) {
		if (count < 2) {
			printf("Missing comma\nCommand canceled\n");
			return 0;
		}if (let > 17) {
			printf("Extraneous text at the end of command\nCommand canceled\n");
			return 0;
		}
	}
	if (!flaga) {
		printf("Extraneous text at the end of command\nCommand canceled\n");
		return 0;
	}



	return 1;
}

