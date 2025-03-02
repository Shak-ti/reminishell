#include "libft.h"

/*
should segvault on NULL param
test code : ft_strlcpy(((void*)0), ((void*)0), 10);
*/
size_t	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	size_t	i;

	i = 0;
	if (size)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}
