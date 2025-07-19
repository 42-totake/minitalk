/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:54:19 by totake            #+#    #+#             */
/*   Updated: 2025/07/19 18:46:59 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>
#define MIN_PID 1
#define MAX_PID 4194304

volatile sig_atomic_t	g_ack_received = 0;

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

void	handle_ack(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	g_ack_received = 1;
}

void	send_char(pid_t server_pid, unsigned char c)
{
	int	i;
	int	bit;

	i = 7;
	while (i >= 0)
	{
		usleep(50);
		bit = (c >> i) & 1;
		if (bit)
		{
			if (kill(server_pid, SIGUSR1) == -1)
				handle_errors("kill: failed to send signal (SIGUSR2)");
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
				handle_errors("kill: failed to send signal (SIGUSR2)");
		}
		while (!g_ack_received)
			pause();
		g_ack_received = 0;
		i--;
	}
}

pid_t	parse_args(int argc, char **argv)
{
	pid_t	server_pid;
	char	*str;

	if (argc != 3 || !argv[1] || !argv[2] || !argv[1][0] || !argv[2][0])
		handle_errors("Usage: ./client_bonus <server_pid> <message>");
	str = argv[1];
	while (*str)
	{
		if (!ft_isdigit(*str))
			handle_errors("PID: PID must be a numeric value");
		str++;
	}
	server_pid = (pid_t)ft_atoi(argv[1]);
	if (server_pid < MIN_PID || server_pid > MAX_PID)
		handle_errors("PID: PID out of valid range");
	if (kill(server_pid, 0) == -1)
		handle_errors("kill: No such process or insufficient permission");
	return (server_pid);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				server_pid;
	char				*msg;

	server_pid = parse_args(argc, argv);
	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_sigaction = handle_ack;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		handle_errors("sigaction: failed to set handler for SIGUSR1");
	msg = argv[2];
	while (*msg)
		send_char(server_pid, (unsigned char)*msg++);
	ft_printf("%s\n", "SUCCESS");
	return (0);
}
