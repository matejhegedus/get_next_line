/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhegedus <mhegedus@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:37:56 by mhegedus          #+#    #+#             */
/*   Updated: 2024/10/14 23:25:54 by mhegedus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buf	buf;
	size_t			ln_len;
	int				i;
	char			*result;
	bool			is_eol;

	ln_len = 0;
	i = 0;
	is_eol = false;
	while (!is_eol)
	{
		if (read_buf(&buf, fd, ln_len) == 0)
			return (NULL);
		if (buf.bytes_read == 0 && ln_len != 0)
			return (result);
		i = 0;
		while (i < buf.remainder_count && !is_eol)
			if (buf.buf[buf.bytes_read - buf.remainder_count + i++] == '\n')
				is_eol = true;
		ln_len += i;
		result = add_buf_to_result(result, &(buf.buf[buf.bytes_read - buf.remainder_count]), ln_len - i, ln_len);
		if (result == NULL)
			return (NULL);
		buf.remainder_count = buf.remainder_count - i;
	}
	return (result);
}

// #include <fcntl.h>
// int main(void)
// {
// 	int	fd;
// 	fd = open("./test/test2.txt", O_RDONLY);
// 	// fd = -2147483648;
// 	int j = 0;
// 	char *str;
// 	while (++j)
// 	{
// 		str = get_next_line(fd);
// 		if (str == NULL)
// 				break;
// 		if (j == 11)
// 			write(1, str, 10);
// 		else
// 		{
// 			int i = 0;
// 			while(str[i] != '\n')
// 			{
// 				write(1, &str[i], 1);
// 				i++;
// 			}
// 			if (str[i] == '\n')
// 				write(1, &str[i], 1);
// 		}
// 		free(str);
// 	}		
// 	close(fd);
// }