/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehay <ehay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:53:01 by ehay              #+#    #+#             */
/*   Updated: 2024/03/05 16:06:47 by ehay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_confirm(int signal)
{
	if (signal == SIGUSR2)
		ft_printf("\033[96m Message received\033[0m\n");
}

void	ft_send_len(int pid, int len)
{
	int		nbr_bits;

	nbr_bits = 31;
	while (nbr_bits >= 0)
	{
		if (len >> nbr_bits & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		nbr_bits--;
	}
}

void	ft_send_bits(int pid, char *msg)
{
	unsigned char	c;
	int				nbr_bits;

	ft_send_len(pid, ft_strlen(msg));
	while (*msg)
	{
		c = *msg;
		nbr_bits = 7;
		while (nbr_bits >= 0)
		{
			if (c >> nbr_bits & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(500);
			nbr_bits--;
		}
		msg++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa_newsig;

	if (argc == 3)
	{
		sa_newsig.sa_handler = &ft_confirm;
		sigemptyset(&sa_newsig.sa_mask);
		sa_newsig.sa_flags = SA_SIGINFO;
		if (sigaction(SIGUSR1, &sa_newsig, NULL) == -1)
			ft_printf("Failed to change SIGUSR1's behavior");
		if (sigaction(SIGUSR2, &sa_newsig, NULL) == -1)
			ft_printf("Failed to change SIGUSR2's behavior");
		ft_send_bits(ft_atoi(argv[1]), argv[2]);
	}
	else
	{
		ft_printf("\033[96mError : \033[91mwrong format.\033[0m\n");
		ft_printf("\033[96mTry : \033[33m./client_bonus `pid` `message`\n");
		return (1);
	}
	return (0);
}
