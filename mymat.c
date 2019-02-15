/* This program is a matrix calculator
   This class is main class getting a comman from the user
   Author:  Roman Serkinskiy
   Id:		312643489
   */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "mat.h"
#define COMMANDLIMIT 30

struct {
	char *name;
	void(*func)(void);
}cmd[] = {
	{ "read_mat",read_mat },
	{ "print_mat", print_mat },
	{ "add_mat", add_mat },
	{ "sub_mat", sub_mat },
	{ "mul_mat", mul_mat },
	{ "trans_mat", trans_mat },
	{ "mul_scalar", mul_scalar },
	{ "stop", stop },
	{ "not_valid",NULL },
};


int main(void) {
	char command[COMMANDLIMIT];
	int i;
	int j = 0;
	char menu[] = "\nPlease enter a command: ";
	char ch;

	FOREVER{
		printf("%s", menu);
	while ((ch = getchar()) != ' ' && ch != '\t' && ch != '\n') {
		if (ch == EOF) {
			printf("\nInvalid terminating of the program, terminating of the program must use stop command\n");
			return 0;
		}
		command[j] = ch;
		j++;
	}
	command[j] = '\0';
	j = 0;

	for (i = 0; cmd[i].func != NULL; i++) {
		if (strcmp(command, cmd[i].name) == 0)
			break;
	}
	if (cmd[i].func == NULL) {

		printf("\nUnknown command name:\t%s\n", command);
		gets(command);

	}
	else

		(*(cmd[i].func))();

	}

	return 0;
}


