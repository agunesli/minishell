#include "minishell.h"

int	found_strong_piece(char *read)
{
	int	or;
	int	and;
	int	pipe;

	or = -1;
	pipe = found_char(read, '|');
	if (read[pipe + 1] == '|')
	{
		or = pipe;
		pipe = -1;
	}
	and = found_char(read, '&');
	if (read[and + 1] != '&') // aue passa si un seul & ?
		and = -1;
	if (and == -1 && or == -1 && pipe == -1)
		return (-1);
	if (and == -1 && or == -1)
		return (pipe);
	if (and == -1  && pipe == -1)
		return (or);
	if (or == -1 && pipe == -1)
		return (and);
	return (ft_min(and, or, pipe));	
}

int	found_medium_piece(char *read, int x)
{
	int	in;
	int	out;

	in = found_char(read, '<');
	out = found_char(read, '>');
	if (in == -1 && out == -1)
		return (-1);
	else if (in < out)
		return (in);
	else
		return (out);
}

// fonction a refaire !!!!
void	hub_medium_piece(char *read, int y)
{
	if (y == -1)
		low_piece(read); // fonction a faire
	else if (read[y] == '<' && read[y + 1] == '<')
		syn.id = heredoc;
	else if (read[y] == '<' && read[y + 1] != '<')
		syn.id = in;
	else if (read[y] == '>' && read[y + 1] == '>')
		syn.id = append;
	else if (read[y] == '>' && read[y + 1] != '>')
		syn.id = out;

}

t_syntax	*medium_piece(char *read, int x)
{

}

t_syntax	parser(char *read)
{
	t_syntax *syn;
	int	x;

	x = found_strong_piece(read);
	if (x == -1)
		syn = medium_piece(read, x); // fonction a faire
	syn.content = NULL;
	if (read[x] == '&')
		syn.id = AND;
	else if (read[x] == '|' && read[x + 1] == '|')
		syn.id = OR;
	else
		syn.id = pipe;
	syn.left = medium_piece(read, x);
	//reflechir pour bien positionner pour la recursion
}
