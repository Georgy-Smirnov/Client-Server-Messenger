#include "minitalk.h"

void	func(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid != 0)
		g_info.pid = info->si_pid;
	if (sig == SIGUSR1)
		g_info.my_char++;
	if (g_info.count_bit == 7)
	{
		if (g_info.my_char == 0)
		{
			write(1, "\n", 1);
			kill(g_info.pid, SIGUSR1);
		}
		else
			write(1, &g_info.my_char, 1);
		g_info.count_bit = 0;
		g_info.my_char = 0;
	}
	else
	{
		g_info.my_char <<= 1;
		g_info.count_bit++;
	}
	usleep(50);
	kill(g_info.pid, SIGUSR2);
}

void	print_pid(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	write (1, "\e[1;34mPID: ", 12);
	ft_putnbr_fd((int)server_pid, 1);
	write(1, "\e[0m\n", 5);
}

void	init(struct sigaction *sa)
{
	g_info.count_bit = 0;
	g_info.my_char = 0;
	sigemptyset(&(sa->sa_mask));
	sigaddset(&(sa->sa_mask), SIGUSR1);
	sigaddset(&(sa->sa_mask), SIGUSR2);
	sa->sa_sigaction = func;
	sa->sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, sa, NULL);
	sigaction(SIGUSR2, sa, NULL);
}

int	main(void)
{
	struct sigaction	sa;

	init(&sa);
	print_pid();
	while (1)
	{
	}
}
