/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fagr <rel-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:12:07 by rel-fagr          #+#    #+#             */
/*   Updated: 2022/09/29 18:37:29 by rel-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* ------------------------------- LIBRARIES -------------------------------- */
# include "../../cub3d.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_data_p
{
	char	*ptr1;
	char	*ptr2;
	char	*ptr3;
	char	*ptr4;
	int		i;

}	t_data_p;

/* ------------------------------- GET_N_L -------------------------------- */

# define BUFFER_SIZE 940

char	*get_next_line(int fd);
size_t	ft_strlen1(char *str);
char	*ft_strjoin1(char *s1, char *s2);
char	*if_star(void);
char	*ft_substr1(char *s, unsigned int start, unsigned int len);
void	ft_bzero1(void *s, size_t n);

/* ------------------------------- PARSER -------------------------------- */

int		process_data(char *str, t_map_ *map, int *count);
int		check_map(char *str, t_map_ *data, int i);
void	creat_map_array(t_map_ *data, char **argv);
void	free_garbage(t_map_ *data, char *str);
int		check_empty_line(t_map_ *data, int i);
int		check_up_down(t_map_ *data, int i, int j);
int		check_left_right(char *str, int i);
void	virtual_wall(t_map_ *data);
void	remp_color(int *count, char *ptr, t_map_ *data, char *c);

#endif
