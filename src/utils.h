/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:02:09 by gaubert           #+#    #+#             */
/*   Updated: 2022/09/16 16:00:44 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minimap.h"

float	dist(float ax, float ay, float bx, float by);
void	while_dof(t_game *g, t_rvars *v, char is_vertical);
void	store_ray(t_game *g, t_rvars *v);
void	anti_bad(t_ray *rays);
#endif