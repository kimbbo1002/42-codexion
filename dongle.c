/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokim <bokim@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 08:43:04 by bokim             #+#    #+#             */
/*   Updated: 2026/04/16 09:23:03 by bokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	get_dongle(t_dongle *dongle, t_coder *coder)
{
	t_request	req;
	t_request	**pos;

	pthread_mutex_lock(&coder->compile_lock);
	req.deadline = coder->last_compile + coder->hub->config->time_burnout;
	pthread_mutex_unlock(&coder->compile_lock);
	req.coder_id = coder->id;
	req.granted = 0;
	req.next = NULL;
	pthread_cond_init(&req.cond, NULL);
	pthread_mutex_lock(&dongle->queue_lock);
	if (coder->hub->config->scheduler)
	{
		pos = &dongle->queue;
		while (*pos)
			pos = &(*pos)->next;
		*pos = &req;
	}
	else
	{
		pos = &dongle->queue;
		while (*pos && (*pos)->deadline <= req.deadline)
			pos = &(*pos)->next;
		req.next = *pos
		*pos = &req;
	}
}
