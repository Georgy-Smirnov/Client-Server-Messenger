#ifndef MINITALK_H
# define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>

# define BUF 128

typedef struct s_minitalk
{
	char	message[BUF];
	int		i;
	int		count_bit;
	int		end_message;
	int		buf_overflow;
}				t_minitalk;

t_minitalk	g_info;

int		ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);
void	*ft_memset(void *b, int c, size_t len);
int		error(void);

#endif