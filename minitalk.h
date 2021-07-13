#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>

typedef struct s_minitalk
{
	int		my_char;
	int		count;
	pid_t	pid_client;
}				t_minitalk;

t_minitalk	g_info;

int		ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);

#endif