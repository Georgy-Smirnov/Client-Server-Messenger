#include "minitalk.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0 && n > -10)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n / 10 != 0)
		ft_putnbr_fd(n / 10, fd);
	if (n < 0)
		ft_putchar_fd('0' + n % 10 * -1, fd);
	else
		ft_putchar_fd('0' + n % 10, fd);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	rezult;
	int	checker;

	i = 0;
	rezult = 0;
	checker = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		checker = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		rezult *= 10;
		rezult += str[i] - 48;
		i++;
	}
	if (checker == 1)
		return (-rezult);
	return (rezult);
}

void	*ft_memset(void *b, int c, size_t len)
{
	int				i;
	unsigned char	*a;

	i = 0;
	a = (unsigned char *)b;
	while (len)
	{
		a[i] = c;
		i++;
		len--;
	}
	return (a);
}

int	error(void)
{
	write (1, "\e[1;31mThe message was not delivered!\n\e[0m", 43);
	return (1);
}
