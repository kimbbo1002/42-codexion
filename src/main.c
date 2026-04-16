/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokim <bokim@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 14:48:41 by bokim             #+#    #+#             */
/*   Updated: 2026/04/14 20:21:56 by bokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_hub		hub;
	t_config	config;

	hub.config = &config;
	if (!parse_args(argc, argv, &hub))
		return (0);
	if (!init_hub(&hub))
		return (0);
	if (start_hub(&hub))
		return (0);
	stop_hub(&hub);
	clean_hub(&hub);
}
