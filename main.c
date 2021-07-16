#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_LEN 1024

int main (void)
{
	char line[BUFFER_LEN];
	char *path = "/bin/";
	char progpath[20];
	char *argv[100];
	int argc;

	while (1){
		printf ("My shell>> ");

		if  (! fgets (line, BUFFER_LEN, stdin)) {
			break;
		}
		size_t length = strlen (line);
		if (line[length - 1] == '\n') {
			line[length - 1] = '\0';
		}

		if (strcmp (line, "exit") == 0) {
			break;
		}

		char *token;
		token = strtok (line, " ");
		int i = 0;
		while (NULL != token) {
			argv[i] = token;
			token = strtok (NULL, " ");
			i++;
		}

		argv[i] = NULL;
		argc = i;

		for (i = 0; i < argc; i++) {
			printf ("%s\n", argv[i]);
		}

		strcpy (progpath, path);
		strcat (progpath, argv[0]);

		for (i = 0; i < strlen (progpath); i++) {
			if (progpath[i] == '\n') {
				progpath[i] = '\0';
			}
		}

		int pid = fork ();

		if (pid == 0) {
			execvp (progpath, argv);
			fprintf (stderr, "Child process could not to execvp\n");
		}
		else {
			wait (NULL);
			//printf ("Child exited\n");
		}
	} /* End of while */
	return 0;
}
