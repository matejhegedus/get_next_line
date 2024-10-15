/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhegedus <mhegedus@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:11:41 by mhegedus          #+#    #+#             */
/*   Updated: 2024/10/15 13:29:57 by mhegedus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

// allocate longer result, copy the old value to result and free the old pointer

void	add_buf_to_result(t_result *result, char *buf, size_t add_len)
{
	char	*new_result;
	size_t	i;

	new_result = malloc((result->len + add_len) * sizeof(char));
	if (new_result == NULL)
		return ;
	i = 0;
	while (i < result->len)
	{
		new_result[i] = result->content[i];
		i++;
	}
	i = 0;
	while (i < add_len)
	{
		new_result[i + result->len] = buf[i];
		i++;
	}
	if (result->len != 0)
		free(result->content);
	result->content = new_result;
	result->len += add_len;
}

// Function checks if theres anything left over from the last read
// by checking the variable remainder_count. If it's 0, it reads into 
// the buffer.
// Return value 0 when gnl should return null - there was an error with read
// or it read 0 bytes and the current resulting line is empty
// Return value 1, when gnl should process the remainder of the current buffer  
int	read_buf(t_buf *buf, int fd, int ln_len)
{
	if ((*buf).size_rem == 0)
	{
		(*buf).size_read = read(fd, (*buf).buf, BUFFER_SIZE);
		(*buf).size_rem = (*buf).size_read;
	}
	if ((*buf).size_read == -1 || ((*buf).size_read == 0 && ln_len == 0))
		return (0);
	else
		return (1);
}
