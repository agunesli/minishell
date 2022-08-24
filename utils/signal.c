#include "../minishell.h"

void	signal_crtc(int sig)
{
	(void)sig;
	g_error = 1;
//	signal(sig, signal_crtc);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_crtbs(int sig)
{
	(void)sig;
//	signal(sig, signal_crtbs);
	printf("\b\b  \b\b");
}

void	signal_def(void)
{
	signal(SIGINT, signal_crtc);
	signal(SIGQUIT, signal_crtbs);
}

// SIG_IGN => demande a ignnorer le signal
// SIG_DFL => action par defaut
void	signal_exec(int pid)
{
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
