#include "minishell.h"

static int	exit_with_arg(char *arg);
static int	ft_tablen(char **tab);
static bool	is_num(char *str);
static int	handle_exit(t_minishell *ms, int code);

static int	ft_tablen(char **tab)
{
	int	len;

	if (!tab)
		return (0);
	len = 0;
	while (tab[len] != NULL)
	{
		len++;
	}
	return (len);
}

static bool	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

/* return exit code and print msg if exit is provided an arg
% 256 because exit code is 8 bit.
*/
static int	exit_with_arg(char *arg)
{
	int	code;

	if (!is_num(arg))
	{
		printf("exit: numeric argument required\n");
		return (255);
	}
	code = ft_atoi(arg);
	if (code > 255)
		return (code % 256);
	return (code);
}

// TODO check free_all??
static int	handle_exit(t_minishell *ms, int code)
{
	free_all(ms, false);
	exit(code);
	return (FAILURE);
}

/* exit
- no arg : exit with last exit code
- 1 arg : exit with code
- code > 255 : input % 256 (bc exit code is 8bit)
- too many args : error message, return 1, no exit
*/
int	ft_exit(t_minishell *ms, char **args)
{
	int	code;

	code = ms->exit_code;
	printf("exit\n");
	if (ft_tablen(args) > 2)
	{
		code = 1;
		printf("exit: too many arguments\n");
		return (code);
	}
	else if (args[1])
	{
		code = exit_with_arg(args[1]);
	}
	return (handle_exit(ms, code));
}
