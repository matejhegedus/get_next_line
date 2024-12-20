/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhegedus <mhegedus@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:11:41 by mhegedus          #+#    #+#             */
/*   Updated: 2024/11/21 21:17:11 by mhegedus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

// allocate memory for new result with the length = (result.len + add_len)
// copy old result to new result
// copy buffer content into the rest of new result
// free old result if it was not empty
void	add_buf_to_result(t_result *result, char *buf, size_t add_len)
{
	char	*new_result;
	size_t	i;

	if (add_len == 0)
		return ;
	new_result = malloc((result->len + add_len) * sizeof(char));
	if (new_result != NULL)
	{
		i = 0;
		while (i < result->len)
		{
			new_result[i] = result->content[i];
			i++;
		}
		i = 0;
		while (i < add_len)
		{
			new_result[result->len + i] = buf[i];
			i++;
		}
	}
	if (result->len != 0)
		free(result->content);
	result->content = new_result;
	result->len += add_len;
}

// Function checks if theres anything left over from the last read
// by checking the variable buf.size_rem. If it's 0, it reads a new set
// of characters from fd into the buffer.
// Return values:
//   0 when gnl should return null - there was an error with read
// or it read 0 bytes and the current resulting line is empty
//   1, when gnl should process the remainder of the current buffer
int	read_buf_if_empty(t_buf *buf, int fd, t_result *result)
{
	if (buf->size_rem == 0)
	{
		buf->size_read = read(fd, buf->buf, BUFFER_SIZE);
		buf->size_rem = buf->size_read;
		if (buf->size_read == -1
			|| (buf->size_read == 0 && result->len == 0))
		{
			buf->size_rem = 0;
			if (result->len > 0)
				free(result->content);
			return (0);
		}
	}
	return (1);
}

// adds a nul terminator to the text pointed to by str
// modifies the original str and also returns a pointer to it
char	*add_nul(char **str, int len)
{
	char	*new_str;
	int		i;

	new_str = malloc(len + 1);
	if (new_str == NULL)
	{
		if (len > 0)
			free((*str));
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		new_str[i] = (*str)[i];
		i++;
	}
	new_str[i] = '\0';
	if (len > 0)
		free((*str));
	*str = new_str;
	return (*str);
}
