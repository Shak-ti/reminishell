#include "libft.h"

/*
Allocates (with malloc(3)) and returns a substring
from the string ’s’.
The substring begins at index ’start’ and is of
maximum size ’len’.

s:  The string from which to create the substring.
start:  The start index of the substring in the
string ’s’.
len:  The maximum length of the substring


The substring.
NULL if the allocation fails.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if ((len + start) > ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		len = 0;
	dst = (char *)malloc(sizeof(char) * ((len) + 1));
	if (!dst)
		return (NULL);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < len)
		dst[j++] = s[i++];
	dst[j] = '\0';
	return (dst);
}
