/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:50:49 by flmuller          #+#    #+#             */
/*   Updated: 2024/07/24 09:29:42 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char **argv)
{
	t_table	spaghetti;

	if (argc < 5 || argc > 6)
	{
		ft_error(0);
		return (0);
	}
	else
	{
		if (!init_spaghetti(argc, argv, &spaghetti))
		{
			ft_error(1);
			return (0);
		}
		start_thread(&spaghetti);
	}
	return (0);
}
