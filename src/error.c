/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:17:20 by flmuller          #+#    #+#             */
/*   Updated: 2024/07/28 00:25:00 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_error(int code)
{
	if (code == 0)
		printf("please verify argument format\n");
	if (code == 1)
		printf("please verify argument format\n");
	if (code == 2)
		printf("please verify argument format\n");
	if (code == 3)
		printf("please verify argument format\n");
	if (code == 4)
		printf("please verify argument format\n");
}
