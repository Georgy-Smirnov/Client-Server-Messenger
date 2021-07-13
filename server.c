#include "minitalk.h"

void	func(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	g_info.pid_client = info->si_pid;
	if (sig == SIGUSR1)
	{
		g_info.my_char += g_info.count;
		g_info.count /= 2;
	}
	if (sig == SIGUSR2)
	{
		g_info.count /= 2;
	}
	kill(g_info.pid_client, SIGUSR1);
}

void	print_pid(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	ft_putnbr_fd((int)server_pid, 1);
	write(1, "\n", 1);
}

void	init(struct sigaction *sa)
{
	g_info.my_char = 0;
	g_info.count = 128;
	sigemptyset(&(sa->sa_mask));
	sigaddset(&(sa->sa_mask), SIGUSR1);
	sigaddset(&(sa->sa_mask), SIGUSR2);
	sa->sa_sigaction = func;
	sa->sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, sa, NULL);
	sigaction(SIGUSR2, sa, NULL);
}

void	print_rez(void)
{
	if (g_info.count == 0)
	{
		if (g_info.my_char == 0)
		{
			kill(g_info.pid_client, SIGUSR2);
			write(1, "\n", 1);
		}
		else
			write(1, &g_info.my_char, 1);
		g_info.count = 128;
		g_info.my_char = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	init(&sa);
	print_pid();
	while (1)
	{
		if (g_info.count == 0)
		{
			if (g_info.my_char == 0)
			{
				kill(g_info.pid_client, SIGUSR2);
				write(1, "\n", 1);
			}
			else
				write(1, &g_info.my_char, 1);
			g_info.count = 128;
			g_info.my_char = 0;
		}
	}
}
