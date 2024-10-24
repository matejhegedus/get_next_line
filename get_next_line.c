/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhegedus <mhegedus@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:37:56 by mhegedus          #+#    #+#             */
/*   Updated: 2024/10/24 14:18:50 by mhegedus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buf	buf;
	t_result		result;
	bool			is_eol;
	int				i;	

	result.len = 0;
	i = 0;
	is_eol = false;
	while (!is_eol)
	{
		if (read_buf(&buf, fd, result.len) == 0)
			return (NULL);
		if (buf.size_read == 0 && result.len != 0)
			return (result.content);
		i = 0;
		while (i < buf.size_rem && !is_eol)
			if (buf.buf[buf.size_read - buf.size_rem + i++] == '\n')
				is_eol = true;
		add_buf_to_result(&result, &(buf.buf[buf.size_read - buf.size_rem]), i);
		if (result.content == NULL)
			return (NULL);
		buf.size_rem = buf.size_rem - i;
	}
	return (result.content);
}

// #include <fcntl.h>
// int main(void)
// {
// 	while (true)
// 	{
// 		int i = 0;
// 		while(str[i] != '\n')
// 		{
// 			write(1, &str[i], 1);
// 			i++;
// 		}
// 	}

// 	// int	fd;
// 	// fd = open("./test/test2.txt", O_RDONLY);
// 	// // fd = 0;
// 	// int j = 0;
// 	// char *str;
// 	// while (true)
// 	// {
// 	// 	str = get_next_line(fd);
// 	// 	if (str == NULL)
// 	// 			break;
// 	// 	if (j == 0)
// 	// 		write(1, str, 1);
// 	// 	else
// 	// 	{
// 	// 		int i = 0;
// 	// 		while(str[i] != '\n')
// 	// 		{
// 	// 			write(1, &str[i], 1);
// 	// 			i++;
// 	// 		}
// 	// 		if (str[i] == '\n')
// 	// 			write(1, &str[i], 1);
// 	// 	}
// 	// 	free(str);
// 	// 	j++;
// 	// }		
// 	// close(fd);
// }
