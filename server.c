/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehay <ehay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:25:37 by ehay              #+#    #+#             */
/*   Updated: 2024/03/08 13:46:39 by ehay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	convert_char(char **str, int *len, int *count, int pid)
{
	write(1, *str, *len);
	write(1, "\n", 1);
	free(*str);
	*len = 0;
	*str = NULL;
	*count = 0;
	if (kill(pid, SIGUSR2) == -1)
		ft_printf("Failed to send SIGUSR2\n");
	if (kill(pid, SIGUSR1) == -1)
		ft_printf("Failed to send SIGUSR1\n");
}

static void	convert_int(int sig, int *len, void *context)
{
	static int	len_total = 0;
	static int	bit = 0;

	(void)context;
	if (sig == SIGUSR1)
		len_total += 1 << (31 - bit);
	bit++;
	if (bit == 32)
	{
		*len = len_total;
		len_total = 0;
		bit = 0;
	}
}

static void	convert_message(int sig, siginfo_t *info, void *context)
{
	static int	bit = 0;
	static int	c = 0;
	static int	len = 0;
	static char	*str = NULL;
	static int	count = 0;

	if (len == 0)
		convert_int(sig, &len, &context);
	else
	{
		if (str == NULL && len >= 1)
			str = malloc(sizeof(char) * (len + 1));
		if (sig == SIGUSR1)
			c += 1 << (7 - bit);
		bit++;
		if (bit == 8)
		{
			bit = 0;
			str[count] = c;
			count++;
			c = 0;
		}
		if (count == len)
			convert_char(&str, &len, &count, info->si_pid);
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	sig;

	if (argc != 1 || argv[1] != 0)
	{
		ft_printf("\033[91mError : wrong format.\n\033[33mTry : ./server\n");
		return (0);
	}
	else
	{
		sig.sa_flags = SA_SIGINFO;
		sigemptyset(&sig.sa_mask);
		sig.sa_sigaction = convert_message;
		pid = getpid();
		if (sigaction(SIGUSR1, &sig, NULL) == -1
			|| sigaction(SIGUSR2, &sig, NULL) == -1)
		{
			ft_printf("SIGUSR asn't been set.\n");
			return (1);
		}
		ft_printf("\033[94mPID\033[0m \033[96m:\033[0m %d\n", pid);
		while (1)
			pause();
	}
	return (0);
}
