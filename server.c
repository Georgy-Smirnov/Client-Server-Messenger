#include "minitalk.h"

void	func_one(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	printf("one\n");
	my_char += count;
	count /= 2;
	kill(pid_server, SIGUSR1);
}

void	func_zero(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	printf("zero\n");
	count /= 2;
	kill(pid_server, SIGUSR1);
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
	struct sigaction one;
	struct sigaction zero;

	one.sa_sigaction = func_one;
	zero.sa_sigaction = func_zero;
	one.sa_flags = SA_SIGINFO;
	zero.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &one, NULL);
	sigaction(SIGUSR2, &zero, NULL);
	print_pid();
	do
	{
		pause();
		printf(">>>>%d\n", count);
		if (count == 0)
		{
			write(1, &my_char, 1);
			count = 128;
			my_char = 0;
		}
	} while (1);
	
}