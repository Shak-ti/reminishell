#include "minishell.h"

int	write_heredoc_line(int fd, char **line)
{
	if (write(fd, *line, ft_strlen(*line)) == -1)
	{
		free(*line);
		return (handle_system_error("write"));
	}
	free(*line);
	return (SUCCESS);
}

static int	eof_warning(const char *delimiter)
{
	if (g_sig_status == SIGINT || g_sig_status == SIGQUIT)
	{
		return (130);
	}
	ft_putstr_fd("minishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted `", 2);
	ft_putstr_fd((char *)delimiter, 2);
	ft_putstr_fd("')\n", 2);
	return (ERROR);
}

int	heredoc_content(int fd, const char *delimiter)
{
	char	*line;
	int		status;

	status = SUCCESS;
	line = NULL;
	while (status == SUCCESS)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			return (eof_warning(delimiter));
		if (ft_strnstr(line, delimiter, ft_strlen(delimiter)))
			return (free(line), SUCCESS);
		else
			status = write_heredoc_line(fd, &line);
	}
	return (status);
}
