/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:07:08 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/13 12:58:36 by tbertozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Prints input error message and exits the program with input code number
*/
void	print_error(int code, char *str)
{
	printf("Error - %s\n", str);
	exit(code);
}
