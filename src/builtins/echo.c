#include "minishell.h"

/* check if arg is -n flag
- `-nnnn` = true
- `-nnx` = false
- `-x` = false
- `-n` = true
*/
static bool	is_n_flag(char *arg)
{
	int	j;

	j = 1;
	if (!arg || arg[0] != '-' || arg[1] == '\0')
		return (false);
	while (arg[j] && arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

/* skip n flags and set newline to false if -n */
static int	skip_n_flags(char **args, bool *newline)
{
	int	i;

	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		*newline = false;
		i++;
	}
	return (i);
}

/* print args for echo */
static void	print_arguments(char **args, int start)
{
	int	i;

	i = start;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

/* ft_echo with -n */
int	ft_echo(char **args)
{
	bool	newline;
	int		i;

	newline = true;
	i = skip_n_flags(args, &newline);
	print_arguments(args, i);
	if (newline)
		printf("\n");
	return (SUCCESS);
}
