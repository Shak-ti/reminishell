#include "minishell.h"

volatile int	g_sig_status = 0;

void	update_exit_code(t_minishell *ms)
{
	if (g_sig_status)
		ms->exit_code = 130;
	else
		ms->exit_code = ms->status;
}

int	init_ms(t_minishell *ms, char **envp)
{
	ms->line = NULL;
	ms->ast = NULL;
	ms->tokens = NULL;
	ms->exit_code = 0;
	ms->envlst = NULL;
	ms->status = 0;
	ms->envlst = init_env(ms, envp);
	if (!ms->envlst)
		return (FAILURE);
	return (SUCCESS);
}

void	process_line(t_minishell *ms)
{
	ms->tokens = ft_tokenize(ms);
	if (DEBUG)
		print_tokens(ms->tokens);
	if (ms->tokens)
	{
		if (syntax_tokens(ms->tokens, ms) == SUCCESS)
		{
			ft_expand(ms);
			if (ms->tokens)
			{
				ms->command = parse(ms->tokens, ms);
				free_tokens(ms->tokens);
				if (ms->command)
				{
					if (DEBUG)
						print_command(ms->command);
					ms->status = execute_command(ms->command, ms);
					free_cmd(ms->command, false);
				}
			}
		}
		ms->tokens = NULL;
	}
}

int	loop(t_minishell *ms)
{
	while (1)
	{
		setup_signals();
		g_sig_status = 0;
		ms->line = readline(PROMPT);
		if (!ms->line)
			return (ft_putendl_fd("exit", STDERR_FILENO), ms->exit_code);
		if (*ms->line)
		{
			catch_child_signals();
			add_history(ms->line);
			process_line(ms);
		}
		free(ms->line);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	int			status;

	(void)argc;
	(void)argv;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (init_ms(&ms, envp) != SUCCESS)
		return (EXIT_FAILURE);
	status = loop(&ms);
	free_env(ms.envlst);
	if (status != SUCCESS)
		exit_status(&ms);
	return (0);
}
