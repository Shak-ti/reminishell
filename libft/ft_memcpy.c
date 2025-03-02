#include "libft.h"

/*
The	memcpy(void) function copies n bytes from memory area src to memory area dst.
If dst and src overlap, behavior is undefined.
Applications in which dst and src might overlap should use memmove(3) instead.

The	memcpy(void) function returns the original value of dst.
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;

	dest = (unsigned char *)dst;
	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		i++;
		src++;
		dest++;
	}
	return (dst);
}
