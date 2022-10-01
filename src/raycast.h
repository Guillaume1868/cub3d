/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:35:45 by gaubert           #+#    #+#             */
/*   Updated: 2022/10/01 13:36:50 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "minimap.h"

void	vertical_rays(t_rvars *v, t_game *g);
void	horizontal_rays(t_rvars *v, t_game *g);
void	ray_cast(t_game *g);

#endif