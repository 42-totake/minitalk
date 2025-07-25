/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:43:03 by totake            #+#    #+#             */
/*   Updated: 2025/07/21 17:43:15 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "libft.h"
# include <signal.h>

# define MIN_PID 1
# define MAX_PID 4194304

typedef struct s_signal_state
{
	volatile sig_atomic_t	signal_received;
	volatile sig_atomic_t	sender_pid;
	volatile sig_atomic_t	received_sig;
}	t_signal_state;

#endif
