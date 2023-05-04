// execvpe.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	printf("Current PID:%d\n", getpid());

	char *argv[] = {"./new", NULL};

	char *envp[] = {"AA", "BB", "CC", "DD", NULL};

	int ret = execvpe("./new", argv, envp);

	printf("This line will not been print after exec\n");

	return 0;
}
