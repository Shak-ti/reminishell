#include "minishell.h"

static int	export_equal(t_minishell *ms, char *arg);

static int	export_equal(t_minishell *ms, char *arg)
{
	char	**tab;

	tab = NULL;
	tab = ft_split(arg, '=');
	if (!tab)
		return (printf("malloc error\n"), FAILURE);
	if (!is_valid_key(tab[0]))
	{
		printf("export: `%s': not a valid identifier\n", tab[0]);
		return (free_tab(tab), FAILURE);
	}
	if (tab[1] == NULL)
		envlst_update(ms, tab[0], "", true);
	else
		envlst_update(ms, tab[0], tab[1], true);
	return (free_tab(tab), SUCCESS);
}

/* ft_export
- no arg = print env
- export TEST : should not print with env but only with export
- export TEST= : should print in both env and export without args
*/
int	ft_export(t_minishell *ms, char **args)
{
	if (!args[1])
		return (print_env_ordered(ms, ms->envlst));
	if (ft_strchr(args[1], '=') != NULL)
		return (export_equal(ms, args[1]));
	else
		envlst_update_without_equal(ms, args[1], true);
	return (SUCCESS);
}
