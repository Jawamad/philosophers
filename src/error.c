/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:17:20 by flmuller          #+#    #+#             */
/*   Updated: 2024/07/24 09:29:24 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_error(int code)
{
	if (code == 0)
		printf("there is an error in arg\n");
	if (code == 1)
		printf("there is an error in init\n");
	if (code == 2)
		printf("there is an error in atoi\n");
	if (code == 3)
		printf("there is an error in atoi last arg\n");
	if (code == 4)
		printf("there is an error in init mutex\n");
}
