/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhegedus <mhegedus@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:37:39 by mhegedus          #+#    #+#             */
/*   Updated: 2024/10/15 13:30:35 by mhegedus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <stddef.h>

typedef struct s_buf
{
	char	buf[BUFFER_SIZE];
	int		size_read;
	int		size_rem;
}	t_buf;

typedef struct s_result
{
	char	*content;
	size_t	len;
}	t_result;

char	*get_next_line(int fd);
void	add_buf_to_result(t_result *result, char *buf, size_t add_len);
int		read_buf(t_buf *buf, int fd, int ln_len);

#endif