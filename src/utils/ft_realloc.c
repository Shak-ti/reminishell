#include "minishell.h"

static void	case_size_zero(void *pointer, size_t old_size, size_t new_size)
{
	if (new_size == 0)
		free(pointer);
	else if (old_size == 0)
		pointer = malloc(new_size);
}

void	*ft_realloc(void *pointer, size_t old_size, size_t new_size)
{
	void	*res;

	res = NULL;
	case_size_zero(pointer, old_size, new_size);
	if (pointer == NULL)
		return (NULL);
	else if (new_size != 0 && old_size != 0 && old_size > new_size)
	{
		res = malloc(new_size);
		if (!res)
			return (NULL);
		ft_memcpy(res, pointer, new_size);
		free(pointer);
	}
	else if (new_size != 0 && old_size != 0)
	{
		res = malloc(new_size);
		if (!res)
			return (NULL);
		ft_memcpy(res, pointer, old_size);
		free(pointer);
	}
	return (res);
}
