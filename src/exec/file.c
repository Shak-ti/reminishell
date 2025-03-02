#include "minishell.h"

/* open file and returns fd
- opening /dev/null ensures it continues exec even without infile (bash)
- if no outfile (cannot create it) : exit
*/
int	open_file(char *filepath, bool is_out)
{
	int	fd;

	if (is_out)
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		perror(filepath);
		if (is_out)
		{
			exit(1);
		}
		else
		{
			fd = open("/dev/null", O_RDONLY);
			if (fd < 0)
			{
				perror("/dev/null");
				exit(1);
			}
		}
	}
	return (fd);
}
