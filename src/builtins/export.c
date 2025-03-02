#include "minishell.h"

static void	sort_keys(char **key_ordered, int size);
static void	copy_keys(t_env *src, char **key_ordered);
static int	print_env_ordered(t_minishell *ms, t_env *src);

/* bubble sort keys */
static void	sort_keys(char **key_ordered, int size)
{
	int		j;
	int		k;
	char	*tmp;

	j = 0;
	while (j < size - 1)
	{
		k = 0;
		while (k < size - j - 1)
		{
			if (ft_strcmp(key_ordered[k], key_ordered[k + 1]) > 0)
			{
				tmp = key_ordered[k];
				key_ordered[k] = key_ordered[k + 1];
				key_ordered[k + 1] = tmp;
			}
			k++;
		}
		j++;
	}
}

/* copy keys */
static void	copy_keys(t_env *src, char **key_ordered)
{
	int		i;
	t_env	*current;

	i = 0;
	current = src;
	while (current)
	{
		key_ordered[i++] = current->key;
		current = current->next;
	}
	key_ordered[i] = NULL;
}

/* print env ordered */
static void	print_env_ordered_loop(t_minishell *ms, char **key_ordered)
{
	int		i;
	t_env	*current;

	i = 0;
	while (key_ordered[i])
	{
		current = envlst_get_env(ms, key_ordered[i]);
		if (current->has_equal)
			printf("export %s=\"%s\"\n", key_ordered[i], current->value);
		else
			printf("export %s\n", key_ordered[i]);
		i++;
	}
}

/* bash : export KEY=value */
static int	print_env_ordered(t_minishell *ms, t_env *src)
{
	char	**key_ordered;
	int		size;

	size = envlst_len(src);
	key_ordered = (char **)malloc(sizeof(char *) * (size + 1));
	if (!key_ordered)
		return (printf("malloc"), FAILURE);
	copy_keys(src, key_ordered);
	sort_keys(key_ordered, size);
	print_env_ordered_loop(ms, key_ordered);
	free(key_ordered);
	return (SUCCESS);
}

/* ft_export
- no arg = print env
- export TEST : should not print with env but only with export
- export TEST= : should print in both env and export without args
*/
int	ft_export(t_minishell *ms, char **args)
{
	char	**tab;
	bool	has_equal;

	tab = NULL;
	has_equal = false;
	if (!args[1])
		return (print_env_ordered(ms, ms->envlst));
	if (ft_strchr(args[1], '=') != NULL)
	{
		has_equal = true;
		
	}
	tab = ft_split(args[1], '=');
	if (!tab)
		return (printf("malloc"), FAILURE);
	if (!is_valid_key(tab[0]))
	{
		printf("export: `%s': not a valid identifier\n", tab[0]);
		return (free(tab), FAILURE);
	}
	if (!has_equal)
		envlst_update_without_equal(ms, args[1], true);
	else
		envlst_update(ms, tab[0], tab[1], true);
	return (free(tab), SUCCESS);
}
