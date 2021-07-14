#include "minitalk.h"

void	func(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (sig == SIGUSR1)
		g_info.message[g_info.i]++;
	if (g_info.i == BUF - 5)
		g_info.buf_overflow = 1;
	if (g_info.count_bit == 7)
	{
		if (g_info.message[g_info.i] == 0)
		{
			g_info.end_message = 1;
			kill(info->si_pid, SIGUSR1);
		}
		else
		{
			g_info.count_bit = 0;
			g_info.i++;
		}
	}
	else
	{
		g_info.message[g_info.i] <<= 1;
		g_info.count_bit++;
	}
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
	g_info.i = 0;
	g_info.count_bit = 0;
	g_info.end_message = 0;
	g_info.buf_overflow = 0;
	ft_memset(g_info.message, 0, BUF);
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
		pause();
		if (g_info.buf_overflow || g_info.end_message)
		{
			write(1, &g_info.message, g_info.i);
			ft_memset(g_info.message, 0, BUF);
			g_info.i = 0;
			g_info.count_bit = 0;
			if (g_info.end_message)
				write(1, "\n", 1);
			g_info.buf_overflow = 0;
			g_info.end_message = 0;
		}
	}
}
