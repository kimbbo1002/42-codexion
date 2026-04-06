/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokim <bokim@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:54:43 by bokim             #+#    #+#             */
/*   Updated: 2026/04/06 16:57:23 by bokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
#define CODEXION_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_config
{
    int		num_coder;
    int		time_burnout;
    int		time_compile;
    int		time_debug;
    int		time_refactor;
    int		num_compiles;
	int		dongle_cooldown;
	bool	scheduler;
}	t_config;

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	lock;
	unsigned long	last_used;
}	t_dongle;

typedef	struct s_coder
{
	int				id;
	pthread_t		thread_id;
	int				compile_count;
	unsigned long	last_compile;
	
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;

	t_config		*config;
} t_coder;

typedef struct s_hub
{
	t_config	*config;
	t_coder		*coders;
	t_dongle	*dongles;
	
	unsigned long	start_time;
	bool			running;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	print_lock;
}	t_hub;


int	parse_args(int argc, char **args, t_config *config);

#endif