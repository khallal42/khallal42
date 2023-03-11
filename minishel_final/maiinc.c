#include "minishell.h"
int	main(void)
{
	int i;
	char *str = malloc(1);
	str[0] = 'p';
	i = 0;
	if (fork() == 0)
	{
		str[0] = 'Y';

		i = 9;
		printf("here in child   %c in address %p\n", str[0], &i);
	}
	printf("here in child   %c in address %p\n", str[0], &i);
	wait(NULL);
}