/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:53:43 by totake            #+#    #+#             */
/*   Updated: 2025/07/17 18:50:41 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h> //write
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

void	handle_errors(const char *msg)
{
	ssize_t i;

	i = 0;
	write(2, "Error: ", 7);
	while (msg && msg[i])
		write(2, &msg[i++], 1);
	write(2, "\n", 1);

	exit(1);
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	char_buf = 0;
	static int				bit_count = 0;

	(void)context;
	if (sig == SIGUSR1)
		char_buf |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &char_buf, 1);
		char_buf = 0;
		bit_count = 0;
	}
	if(kill(info->si_pid, SIGUSR1) == -1)
		handle_errors("kill: failed to send signal (SIGUSR1)");
}

int	main(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		handle_errors("sigaction: failed to set handler for SIGUSR1");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		handle_errors("sigaction: failed to set handler for SIGUSR2");

	ft_printf("Server PID: %d\n", getpid());

	while (1)
		pause();

	return (0);
}
