/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:53:43 by totake            #+#    #+#             */
/*   Updated: 2025/07/21 16:43:29 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_signal_state	g_state = {0, 0, 0};

void	handle_errors(const char *msg)
{
	ssize_t	i;

	i = 0;
	write(2, "Error: ", 7);
	while (msg && msg[i])
		write(2, &msg[i++], 1);
	write(2, "\n", 1);
	exit(1);
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)context;
	g_state.signal_received = 1;
	g_state.received_sig = sig;
	g_state.sender_pid = info->si_pid;
}

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) == -1)
		handle_errors("sigemptyset: failed to sigemptyset");
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		handle_errors("sigaction: failed to set handler for SIGUSR1");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		handle_errors("sigaction: failed to set handler for SIGUSR2");
}

void	process_signal(unsigned char *char_buf, int *bit_count)
{
	if (g_state.received_sig == SIGUSR1)
		*char_buf |= (1 << (7 - *bit_count));
	if (++(*bit_count) == 8)
	{
		write(1, char_buf, 1);
		*char_buf = 0;
		*bit_count = 0;
	}
	usleep(50);
	if (kill(g_state.sender_pid, SIGUSR1) == -1)
		handle_errors("kill: failed to send ACK");
}

int	main(void)
{
	static unsigned char	char_buf = 0;
	static int				bit_count = 0;
	int						usleep_count;

	usleep_count = 0;
	setup_signal_handlers();
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
		while (!g_state.signal_received)
		{
			usleep(100);
			if (++usleep_count >= 10000)
			{
				write(2, "Error: Timeout\n", 15);
				char_buf = 0;
				bit_count = 0;
				usleep_count = 0;
			}
		}
		g_state.signal_received = 0;
		usleep_count = 0;
		process_signal(&char_buf, &bit_count);
	}
}
