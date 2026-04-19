/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_compile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:25:58 by bokim             #+#    #+#             */
/*   Updated: 2026/04/19 20:57:16 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*sim_one_coder(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->lock);
	print_action(coder, "has taken a dongle");
	controlled_sleep(coder->hub->config->time_burnout, coder->hub);
	pthread_mutex_unlock(&coder->left_dongle->lock);
	return (NULL);
}

static void lock_dongles(t_coder *coder)
{
    t_dongle    *first;
    t_dongle    *second;

    if (coder->left_dongle < coder->right_dongle)
    {
        first = coder->left_dongle;
        second = coder->right_dongle;
    }
    else
    {
        first = coder->right_dongle;
        second = coder->left_dongle;
    }
    pthread_mutex_lock(&first->lock);
    print_action(coder, "has taken a dongle");
    pthread_mutex_lock(&second->lock);
    print_action(coder, "has taken a dongle");
}

int	compile(t_coder *coder)
{
	if (!get_running_status(coder->hub))
		return (1);
	lock_dongles(coder);
	pthread_mutex_lock(&coder->compile_lock);
	coder->last_compile = get_time();
	pthread_mutex_unlock(&coder->compile_lock);
	print_action(coder, "is compiling");
	controlled_sleep(coder->hub->config->time_compile, coder->hub);
	pthread_mutex_unlock(&coder->left_dongle->lock);
	pthread_mutex_unlock(&coder->right_dongle->lock);
	pthread_mutex_lock(&coder->compile_lock);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->compile_lock);
    dongle_cooldown(coder);
	return (0);
}