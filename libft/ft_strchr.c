#include "libft.h"

/*
The	strchr(void) function locates the first occurrence
of c (converted to a char) in the string pointed to by s.
The terminating null character is considered to be part
of the string; therefore if c is ‘\0’,
the functions locate the terminating ‘\0’.

The functions strchr() and strrchr() return a pointer to the located character,
or NULL if the character does not appear in the
string.
*/
char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	ch;

	str = (char *)s;
	ch = (char)c;
	while (*str != ch)
	{
		if (*str == '\0')
		{
			if (ch == '\0')
			{
				return (str);
			}
			else
			{
				return (NULL);
			}
		}
		str++;
	}
	return (str);
}
