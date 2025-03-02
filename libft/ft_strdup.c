#include "libft.h"

/*
The	strdup(void) function allocates sufficient memory for a copy
of the string s1,
does the copy, and returns a pointer to it.
The pointer may subsequently be used as an argument to the function free(3).

If insufficient memory is available,
NULL is returned and errno is set to ENOMEM.
*/
char	*ft_strdup(char *s1)
{
	size_t	i;
	size_t	len;
	char	*dest;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
