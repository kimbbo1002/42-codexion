/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokim <bokim@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:19:52 by bokim             #+#    #+#             */
/*   Updated: 2026/04/14 16:21:13 by bokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/codexion.h"

unsigned long	get_time(void)
{
}

int	get_running_status(t_hub *hub)
{
	int	status;

	pthread_mutex_lock(&hub->stop_lock);
	status = hub->running;
	pthread_mutex_unlock(&hub->stop_lock);
	return (status);
}

void	print_action(t_coder *coder, char *msg)
{
	unsigned long	time;

	pthread_mutex_lock(&coder->hub->print_lock);
	time = get_time() - coder->hub->start_time;
	if (get_running_status(coder->hub))
		print("%lu %d %s\n", time, coder->id, msg);
	pthread_mutex_unlock(&coder->hub->print_lock);
}

void	controlled_sleep(unsigned long sleep, t_hub *hub)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < sleep)
	{
		if (!get_running_status(hub))
			break ;
		usleep(500);
	}
}
