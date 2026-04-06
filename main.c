/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokim <bokim@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 14:48:41 by bokim             #+#    #+#             */
/*   Updated: 2026/04/06 16:41:17 by bokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/codexion.h"

int main(int argc, char **argv)
{
	t_hub		hub;
	t_config 	config;
	
	if (!parse_args(argc, argv, &config))
		return 0;
	hub.config = config;
	init_hub(&hub);
}