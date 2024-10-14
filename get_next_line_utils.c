/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhegedus <mhegedus@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:11:41 by mhegedus          #+#    #+#             */
/*   Updated: 2024/10/14 23:20:24 by mhegedus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	char_count;

// 	char_count = 0;
// 	while (s[char_count] != '\0')
// 		char_count++;
// 	return (char_count);
// }
// allocate longer result, copy the old value to result and free the old pointer

char	*add_buf_to_result(char *old_result, char *buf, size_t old_len,
			size_t new_len)
{
	char	*new_result;
	size_t	i;
	size_t	j;

	new_result = malloc(new_len * sizeof(char));
	if (new_result == NULL)
		return (NULL);
	i = 0;
	while (i < old_len)
	{
		new_result[i] = old_result[i];
		i++;
	}
	j = 0;
	while (i < new_len)
	{
		new_result[i] = buf[j];
		i++;
		j++;
	}
	if (old_len != 0)
		free(old_result);
	return (new_result);
}

int read_buf(t_buf *buf, int fd, int ln_len)
{
	if ((*buf).remainder_count == 0)
		{
			(*buf).bytes_read = read(fd, (*buf).buf, BUFFER_SIZE);
			(*buf).remainder_count = (*buf).bytes_read;
		}
	if ((*buf).bytes_read == -1 || ((*buf).bytes_read == 0 && ln_len == 0))
		return (0);
	else
		return (1);
}
