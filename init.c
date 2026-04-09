/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokim <bokim@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 16:41:35 by bokim             #+#    #+#             */
/*   Updated: 2026/04/09 15:45:55 by bokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_dongles(t_hub *hub)
{
	int	i;

	hub->dongles = malloc(sizeof(t_dongle) * hub->config->num_coder);
	if (!hub->dongles)
		return (0);
	i = 0;
	while (i < hub->config->num_coder)
	{
		hub->dongles[i].id = i + 1;
		pthread_mutex_init(&hub->dongles[i].lock, NULL);
		hub->dongles[i].last_used = 0;
		i++;
	}
}

int	init_coders(t_hub *hub)
{
	int	i;

	hub->coders = malloc(sizeof(t_coder) * hub->config->num_coder);
	if (!hub->coders)
		return (0);
	i = 0;
	while (i < hub->config->num_coder)
	{
		hub->coders[i].id = i + 1;
		hub->coders[i].compile_count = 0;
		hub->coders[i].hub = hub;
		hub->coders[i].left_dongle = &hub->dongles[i];
		hub->coders[i].right_dongle = &hub->dongles[(i + 1)
			% hub->config->num_coder];
		hub->coders[i].last_compile = get_time();
		i++;
	}
}

int	init_hub(t_hub *hub, t_config *config)
{
	hub->config = config;
	hub->running = true;
	hub->start_time = get_time();
	if (!init_dongles(hub) || !init_coders(hub))
	{
		printf("Error: Failed to initiate hub");
		return (0);
	}
	return (1);
}
