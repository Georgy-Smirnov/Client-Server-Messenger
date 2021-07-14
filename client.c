#include "minitalk.h"

void	func_wait(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR1)
		write (1, "\e[1;32mThe message was delivered!\n\e[0m", 38);
}

int	send_char(char c, int pid_server)
{
	int	i;

	i = 128;
	while (i)
	{
		if (i & c)
		{
			if (kill(pid_server, SIGUSR1))
				return (error());
		}
		else
		{
			if (kill(pid_server, SIGUSR2))
				return (error());
		}
		usleep(600);
		i /= 2;
	}
	return (0);
}

int	send_message(char *p_serv, char *message)
{
	int	i;
	int	pid_server;

	i = 0;
	pid_server = ft_atoi(p_serv);
	while (message[i])
	{
		if (send_char(message[i], pid_server))
			return (1);
		i++;
	}
	if (send_char(message[i], pid_server))
		return (1);
	return (0);
}

void	init(struct sigaction *sa)
{
	sigemptyset(&(sa->sa_mask));
	sigaddset(&(sa->sa_mask), SIGUSR1);
	sa->sa_sigaction = func_wait;
	sa->sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, sa, NULL);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	init(&sa);
	if (argc == 3)
	{
		if (send_message(argv[1], argv[2]))
			return (1);
	}
	else
		write(1, "Use: ./client [pid_server] [message]\n", 37);
	return (0);
}
