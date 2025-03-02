#include "libft.h"

/*
The	memset(void) function writes len bytes of value c
(converted to an unsigned char) to the string b.
The	memset(void) function returns its first argument.
*/
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}
