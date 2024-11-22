/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhegedus <mhegedus@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:37:56 by mhegedus          #+#    #+#             */
/*   Updated: 2024/11/22 13:14:48 by mhegedus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "get_next_line.h"

// Returns a pointer to a line of text read from the file descriptor fd.
// The returned pointer should be passed to free() when no longer needed.
// If fd points to a file, subsequent calls to get_next_line() allow reading 
// the whole file.
// Returns NULL if read fails or if there's nothing left to read.
char	*get_next_line(int fd)
{
	static t_buf	buf;
	t_result		result;
	bool			is_eol;
	int				i;	

	result.len = 0;
	is_eol = false;
	i = 0;
	while (!is_eol)
	{
		if (read_buf_if_empty(&buf, fd, &result) == 0)
			return (NULL);
		if (buf.size_read == 0 && result.len != 0)
			return (add_nul(&(result.content), result.len));
		i = 0;
		while (i < buf.size_rem && !is_eol)
			if (buf.buf[buf.size_read - buf.size_rem + i++] == '\n')
				is_eol = true;
		add_buf_to_result(&result, &(buf.buf[buf.size_read - buf.size_rem]), i);
		if (result.content == NULL)
			return (NULL);
		buf.size_rem = buf.size_rem - i;
	}
	return (add_nul(&(result.content), result.len));
}

// #include <fcntl.h>
// #include <stdio.h>
// int main(void)
// {
// 	int	fd;
// 	fd = open("./test/test.txt", O_RDONLY);
// 	char *str;

// 	while ((str = get_next_line(fd)))
// 	{
// 		printf("%s", str);
// 		free(str);
// 	}
// 	close(fd);
// }
