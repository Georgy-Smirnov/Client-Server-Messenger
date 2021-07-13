#include "minitalk.h"

int my_char = 0, count = 128;

void	func(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	pid_t pid_client = info->si_pid;
	if (sig == SIGUSR1)
	{
		my_char += count;
 		count /= 2;	
	}
	if (sig == SIGUSR2)
	{
		count/=2;	
	}
	kill(pid_client, SIGUSR1);
}

void	print_pid(void)
{
	pid_t server_pid;

	server_pid = getpid();
	pid_server = server_pid;
	ft_putnbr_fd((int)server_pid, 1);
	write(1, "\n", 1);
}

int main(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_sigaction = func;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	print_pid();
	do
	{
		if (count == 0)
		{
			if (my_char == 0)
			{
				write(1, "\n", 1);
			}
			else
				write(1, &my_char, 1);
			count = 128;
			my_char = 0;
		}
	} while (1);
}