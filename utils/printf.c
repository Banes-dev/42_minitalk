/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehay <ehay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:30:12 by ehay              #+#    #+#             */
/*   Updated: 2024/02/02 15:27:42 by ehay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}

int	printadress(const unsigned long n)
{
	if (n / 16)
		return (printadress(n / 16) + printadress(n % 16));
	else if (!(n / 10))
		ft_putchar(n + '0');
	else
		ft_putchar((char) n - 10 + 'a');
	return (1);
}

int	ft_putpointer(void *adress)
{
	if (!adress)
		return (ft_putstr("(nil)"));
	ft_putstr("0x");
	return (2 + printadress((unsigned long) adress));
}

int	conv(char form, va_list args)
{
	int	result;

	result = 0;
	if (form == 'c')
		result = ft_putchar((char) va_arg(args, int));
	else if (form == 's')
		result = ft_putstr(va_arg(args, char *));
	else if (form == 'p')
		result = ft_putpointer(va_arg(args, void *));
	else if (form == 'd')
		result = ft_putnbr(va_arg(args, int));
	else if (form == 'i')
		result = ft_putnbr(va_arg(args, int));
	else if (form == 'u')
		result = ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (form == 'x')
		result = ft_puthexalower(va_arg(args, unsigned int));
	else if (form == 'X')
		result = ft_puthexaupper(va_arg(args, unsigned ));
	else if (form == '%')
		result = ft_putchar('%');
	return (result);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		nb;

	va_start(args, format);
	i = 0;
	nb = 0;
	if (!format)
	{
		return (0);
	}
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			nb = nb + conv(format[i + 1], args);
			i++;
		}
		else
			nb = nb + ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (nb);
}
