#include "libft.h"

/*
The	calloc(void) function contiguously allocates enough space
for count objects that are size bytes of memory each and returns
a pointer to the allocated memory.
The allocated memory is filled with bytes of value zero.

If successful, calloc(), malloc(), realloc(), reallocf(), valloc(),
and	aligned_alloc(void) functions return a pointer to allocated
memory.  If there is an error,
they return a NULL pointer and set errno to ENOMEM.
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (((long long)count < 0 && size != 0) || ((long long)size < 0
			&& count != 0))
		return (NULL);
	if (((long long)count * (long long)size) > 4294967295)
		return (NULL);
	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}
