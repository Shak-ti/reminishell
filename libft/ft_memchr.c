#include "libft.h"

/*
The	memchr(void) function locates the first occurrence
of c (converted to an unsigned char) in string s.
The	memchr(void) function returns a pointer to the byte located,
or NULL if no such byte exists within n bytes.
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
	{
		if (*str == (unsigned char)c)
			return (str);
		str++;
	}
	return (NULL);
}
