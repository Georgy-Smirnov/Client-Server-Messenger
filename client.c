#include "minitalk.h"

void	func_wait(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
}

void	send_char(char c, int pid_server)
{
	int i = 128;

	while (i >= 1)
	{
		if (i & c)
		{
			write(1, "1", 1);
			kill(pid_server, SIGUSR1);
		}
		else
		{
			write(1, "0", 1);
			kill(pid_server, SIGUSR2);
		}
		pause();
		i/=2;
	}
	write(1, "\n", 1);
}

void	send_message(char *p_serv, char *message)
{
	int	i;
	int pid_server;

	i = 0;
	pid_server = ft_atoi(p_serv);
	while (message[i])
	{
		send_char(message[i], pid_server);
		i++;
	}
	send_char(message[i], pid_server);
}

int main(int argc, char **argv)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sa.sa_sigaction = func_wait;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);

	if (argc == 3)
		send_message(argv[1], argv[2]);
	else	
		write(1, "Use: ./client [pid_server] [message]\n", 37);
	return (0);
}