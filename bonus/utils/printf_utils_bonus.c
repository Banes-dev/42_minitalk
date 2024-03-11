/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehay <ehay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:24:49 by ehay              #+#    #+#             */
/*   Updated: 2024/02/02 15:25:25 by ehay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk_bonus.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		return (write(1, "(null)", 6));
	}
	while (str[i] != '\0')
	{
		write (1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		count += ft_putnbr(n / 10);
	}
	count += ft_putchar(n % 10 + '0');
	return (count);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += ft_putnbr_unsigned(n / 10);
	}
	count += ft_putchar(n % 10 + 48);
	return (count);
}

int	ft_puthexalower(long double nbr)
{
	int		count;
	char	*hexa;

	count = 0;
	hexa = "0123456789abcdef";
	if (nbr < 0)
	{
		nbr = -nbr;
		write(1, "-", 1);
		count++;
	}
	if (nbr >= 16)
		count += ft_puthexalower(((unsigned long) nbr / 16));
	ft_putchar(hexa[(unsigned long)nbr % 16]);
	count++;
	return (count);
}

int	ft_puthexaupper(long double nbr)
{
	int		count;
	char	*hexa;

	count = 0;
	hexa = "0123456789ABCDEF";
	if (nbr < 0)
	{
		nbr = -nbr;
		write(1, "-", 1);
		count++;
	}
	if (nbr >= 16)
		count += ft_puthexaupper(((unsigned long) nbr / 16));
	ft_putchar(hexa[(unsigned long)nbr % 16]);
	count++;
	return (count);
}
