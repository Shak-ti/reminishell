#include "minishell.h"

void	print_command(t_command *cmd)
{
	int		i;
	t_redir	*redir;

	printf("\nCOMMAND:\n");
	while (cmd)
	{
		i = 0;
		printf("%d\n", cmd->index);
		printf("  args:\n");
		if (cmd->args)
		{
			while (cmd->args[i])
			{
				printf("      %s\n", cmd->args[i]);
				i++;
			}
		}
		printf("  redir:\n");
		redir = cmd->redir;
		while (redir)
		{
			printf("  type: %s\n", get_token_type_string(redir->type));
			printf("  file: %s\n", redir->file);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

void	free_redir(t_redir *redirections)
{
	t_redir	*tmp;

	while (redirections)
	{
		tmp = redirections;
		redirections = redirections->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}

void	free_cmd(t_command *cmd, bool ms_aussi)
{
	t_command	*tmp;

	if (ms_aussi)
	{
		if (cmd->ms->envlst)
			free_env(cmd->ms->envlst);
	}
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->args)
			free_tab(tmp->args);
		if (tmp->redir)
			free_redir(tmp->redir);
		if (tmp->fd)
			free(tmp->fd);
		if (tmp->path)
			free(tmp->path);
		free(tmp);
	}
	cmd = NULL;
}

int	check_heredoc_count(t_command *cmd)
{
	t_redir	*redir;
	int		count;

	count = 0;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
				count++;
			if (count > 16)
				return (FAILURE);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}
