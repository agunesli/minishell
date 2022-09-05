#include "../minishell.h"

void	signal_ctrc(int sig)
{
	(void)sig;
	g_error = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_ctrbs(int sig)
{
	(void)sig;
//	g_error = 131;
	printf("\b\b  \b\b");
}

void	sg_heredoc(int sig)
{
	(void)sig;
	g_error = 130;
	printf("\n");
	close(STDIN_FILENO);
}

// SIGINT => Terminal interrupt signal
// SIGQUIT => Terminal quit signal
// SIG_IGN => demande a ignnorer le signal
// SIG_DFL => action par defaut
void	signal_def(void)
{
	signal(SIGINT, signal_ctrc);
	signal(SIGQUIT, SIG_IGN);
}