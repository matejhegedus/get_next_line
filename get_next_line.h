/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhegedus <mhegedus@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:37:39 by mhegedus          #+#    #+#             */
/*   Updated: 2024/10/14 23:17:36 by mhegedus         ###   ########.fr       */
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
	int		bytes_read;
	int		remainder_count;
}	t_buf;

char	*get_next_line(int fd);
char	*add_buf_to_result(char *old_result, char *buf, size_t old_len,
			size_t new_len);
int read_buf(t_buf *buf, int fd, int ln_len);

#endif