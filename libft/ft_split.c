#include "libft.h"

static char		**malloc_error(char **tab);
static size_t	count_words(char const *s, char c);
static size_t	next_word_len(char const *s, size_t start, char sep);

/*
Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer

s: The string to be split.
c: The delimiter character.

Return value

The array of new strings resulting from the split.
NULL if the allocation fails.
*/
char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	start;
	size_t	word_len;
	size_t	words;
	size_t	i;

	start = 0;
	i = 0;
	res = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!s || !res)
		return (NULL);
	words = count_words(s, c);
	while (i < words)
	{
		while (s[start] && s[start] == c)
			start++;
		word_len = next_word_len(s, start, c);
		res[i] = ft_substr(s, start, word_len);
		if (!res[i])
			return (malloc_error(res));
		start += word_len;
		i++;
	}
	res[i] = NULL;
	return (res);
}

static char	**malloc_error(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	words;
	int		trigger;

	trigger = 0;
	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && !trigger)
		{
			trigger = 1;
			words++;
		}
		else if (s[i] == c)
			trigger = 0;
		i++;
	}
	return (words);
}

static size_t	next_word_len(const char *s, size_t start, char c)
{
	size_t	i;

	i = start;
	while (s[i] && s[i] != c)
		i++;
	return (i - start);
}
