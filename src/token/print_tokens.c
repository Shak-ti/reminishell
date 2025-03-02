#include "minishell.h"

// TODO remove/comment before eval

const char	*token_type_string[] = {
	[TOKEN_APPEND] = "Append",
	[TOKEN_HEREDOC] = "Heredoc",
	[TOKEN_INPUT] = "Infile",
	[TOKEN_OUTPUT] = "Outfile",
	[TOKEN_WORD] = "Command",
	[TOKEN_PIPE] = "Pipe",
};

const char	*get_token_type_string(t_token_type type)
{
	return (token_type_string[type]);
}

void	print_tokens(t_token *tokens)
{
	printf("TOKENS:\n");
	if (!tokens)
	{
		printf("No tokens\n");
		return ;
	}
	while (tokens)
	{
		printf("%s : %s\n", get_token_type_string(tokens->type), tokens->value);
		tokens = tokens->next;
	}
}
