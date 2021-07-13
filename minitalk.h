#include <stdio.h>
#include <unistd.h>
#include <signal.h>


#include <string.h>

pid_t	pid_server;

int	ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);