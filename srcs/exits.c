/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vangirov <vangirov@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:00:36 by vangirov          #+#    #+#             */
/*   Updated: 2022/05/25 17:02:52 by vangirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(t_fdf *data, char *message)
{
	ft_free_data(data);
	perror(message);
	exit(1);
}

void	ft_escape(t_fdf *data)
{
	ft_free_data(data);
	exit(0);
}

void	ft_free_data(t_fdf *data)
{
	int i;

	i = 0;
	while (i < data->height)
		free(data->matrix[i++]);
	free(data->matrix);
	free(data);
}