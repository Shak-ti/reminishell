#include "libft.h"

/*
The	memmove(void) function copies len bytes from string src to string dst.
The two strings may overlap; the copy is always done in a
non-destructive manner.
The	memmove(void) function returns the original value of dst.
*/
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	if ((src == NULL && dst == NULL) || n == 0)
	{
		return (dst);
	}
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	i = 0;
	if (d > s)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
