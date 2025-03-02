#include "libft.h"

/*
The	strchr(void) function locates the first occurrence
of c (converted to a char) in the string pointed to by s.
The terminating null character is considered to be part
of the string; therefore if c is ‘\0’,
the functions locate the terminating ‘\0’.

The	strrchr(void) function is identical to strchr(),
except it locates the last occurrence of c.

The functions strchr() and strrchr() return a pointer to the located character,
or NULL if the character does not appear in the string.
*/
char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	char	*str;
	char	*last;

	str = (char *)s;
	ch = (char)c;
	last = NULL;
	while (*str)
	{
		if (*str == ch)
		{
			last = str;
		}
		str++;
	}
	if (ch == '\0')
	{
		return (str);
	}
	return (last);
}
