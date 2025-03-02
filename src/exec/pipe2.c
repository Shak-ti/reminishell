#include "minishell.h"

void	clean_pipe(t_command *cmd, t_pipe *pipe_array, int nb_of_pipes)
{
	cleanup_fds(cmd);
	free_cmd(cmd, true);
	cleanup_remaining_pipes(pipe_array, nb_of_pipes);
	free(pipe_array);
}

void	execute_pipeline_command(t_command *cmd, t_pipe *pipe_array,
		int position, int nb_of_pipes)
{
	int	status;

	configure_pipe_fds(pipe_array, position, nb_of_pipes);
	close_unused_pipes(pipe_array, position, nb_of_pipes);
	if (cmd->redir)
	{
		status = setup_redir(cmd);
		if (status != SUCCESS)
		{
			clean_pipe(cmd, pipe_array, nb_of_pipes);
			exit(status);
		}
	}
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, true));
	status = prepare_exec(cmd);
	if (status != SUCCESS)
	{
		handle_command_error(cmd, status);
		clean_pipe(cmd, pipe_array, nb_of_pipes);
		exit(COMMAND_NOT_FOUND);
	}
	execve(cmd->path, cmd->args, NULL);
	clean_pipe(cmd, pipe_array, nb_of_pipes);
	exit(handle_system_error("execve"));
}

static int	handle_parent_pipes(t_pipe *pipe_array, int position)
{
	if (position > 0)
	{
		if (close(pipe_array[position - 1][0]) == SYSCALL_ERROR)
			return (ERROR);
		if (close(pipe_array[position - 1][1]) == SYSCALL_ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int	init_pipeline(int nb_of_pipes, pid_t **pid_array_ptr)
{
	*pid_array_ptr = malloc(sizeof(pid_t) * (nb_of_pipes + 1));
	if (!*pid_array_ptr)
		return (handle_system_error("malloc"));
	return (SUCCESS);
}

pid_t	fork_pipeline_process(t_command *cmd, t_pipe *pipe_array, int position,
		int nb_of_pipes)
{
	pid_t	pid;

	pid = fork();
	if (pid == SYSCALL_ERROR)
		return (SYSCALL_ERROR);
	if (pid == 0)
		execute_pipeline_command(cmd, pipe_array, position, nb_of_pipes);
	else
	{
		if (handle_parent_pipes(pipe_array, position) == ERROR)
		{
			cleanup_remaining_pipes(pipe_array, nb_of_pipes);
			return (SYSCALL_ERROR);
		}
	}
	return (pid);
}
