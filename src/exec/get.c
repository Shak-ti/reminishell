#include "minishell.h"

char	*get_cmd_name(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (NULL);
	return (cmd->args[0]);
}

int	get_exit_status(t_command *cmd)
{
	if (!cmd)
		return (ERROR);
	return (cmd->exit_status);
}

char	*get_cmd_path(t_command *cmd)
{
	if (!cmd)
		return (NULL);
	return (cmd->path);
}

int	get_builtin(const char *cmd_name, char **args, t_minishell *ms)
{
	if (!ft_strcmp(cmd_name, "echo"))
		return (ft_echo(args));
	else if (!ft_strcmp(cmd_name, "cd"))
		return (ft_cd(ms, args));
	else if (!ft_strcmp(cmd_name, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd_name, "export"))
		return (ft_export(ms, args));
	else if (!ft_strcmp(cmd_name, "unset"))
		return (ft_unset(ms, args));
	else if (!ft_strcmp(cmd_name, "env"))
		return (ft_env(ms));
	else if (!ft_strcmp(cmd_name, "exit"))
		return (ft_exit(ms, args));
	return (ERROR);
}
