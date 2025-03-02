#include "minishell.h"

/* check if key in envlst exists */
bool	envlst_key_exists(t_minishell *ms, char *key)
{
	t_env	*envlst;

	envlst = ms->envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (true);
		envlst = envlst->next;
	}
	return (false);
}

/* return value of env, NULL if it doesnt exist */
char	*envlst_get_value(t_minishell *ms, char *key)
{
	t_env	*envlst;

	envlst = ms->envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

/* return env ptr, NULL if it doesnt exist */
t_env	*envlst_get_env(t_minishell *ms, char *key)
{
	t_env	*envlst;

	envlst = ms->envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst);
		envlst = envlst->next;
	}
	return (NULL);
}
