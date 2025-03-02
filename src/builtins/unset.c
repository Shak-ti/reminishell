#include "minishell.h"

/* ft_unset: unset env var

in bash:
- no arg : return 0
- var doesn't exist : return 0
- too many args : free args[1], return 0
- invalid key : error message + return 1
*/
int	ft_unset(t_minishell *ms, char **args)
{
	if (!args[1])
		return (SUCCESS);
	if (!is_valid_key(args[1]))
	{
		printf("unset: `%s': not a valid identifier\n", args[1]);
		return (FAILURE);
	}
	envlst_remove(ms, args[1]);
	return (SUCCESS);
}
