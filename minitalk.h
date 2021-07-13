#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int my_char;
int	count = 128;
pid_t	pid_server;

int	ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);