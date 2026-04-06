/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bokim <bokim@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:54:47 by bokim             #+#    #+#             */
/*   Updated: 2026/04/06 15:46:52 by bokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/codexion.h"

int ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

static int	digit_test(char **args)
{
	int i;
	int j;

	i = 1;
	while (i < 8)
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]))
				return 0;
			j++;
		}
		i++;
	}
	return 1;
}

int parse_args(int argc, char **args, t_config *config)
{
	if(argc == 9 && digit_test(args) &&
		(!strcmp(args[8], "fifo") || !strcmp(args[8], "edf")))
	{
		config->num_coder = atoi(args[1]);
		config->time_burnout = atoi(args[2]);
		config->time_compile = atoi(args[3]);
		config->time_debug = atoi(args[4]);
		config->time_refactor = atoi(args[5]);
		config->num_compiles = atoi(args[6]);
		config->dongle_cooldown = atoi(args[7]);
		if (!strcmp(args[8], "fifo"))
			config->scheduler = true;
		else
			config->scheduler = false;
		return 1;
	}
	else
	{
		printf("Error: Invalid Input\n");
		return 0;
	}
}
