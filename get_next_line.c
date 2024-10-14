/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhegedus <mhegedus@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:37:56 by mhegedus          #+#    #+#             */
/*   Updated: 2024/10/14 19:40:32 by mhegedus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	size_t		ln_len;
	int			i;
	bool		is_eol;
	char		*result;
	static int	bytes_read;
	static int	remainder_count;

	is_eol = false;
	ln_len = 0;
	while (!is_eol)
	{
		if (remainder_count == 0)
		{
			bytes_read = read(fd, buf, BUFFER_SIZE);
			remainder_count = bytes_read;
		}
		if (bytes_read == -1 || (bytes_read == 0 && ln_len == 0))
			return (NULL);
		else if (bytes_read == 0 && ln_len != 0)
			return (result);
		i = 0;
		while (i < bytes_read && !is_eol)
		{
			ln_len++;			
			if (buf[bytes_read - remainder_count + i] == '\n')
				is_eol = true;
			i++;
		}
		result = add_buf_to_result(result, &(buf[BUFFER_SIZE - remainder_count]), ln_len - i, ln_len);
		if (result == NULL)
			return (NULL);
		remainder_count = bytes_read - i;
	}
	return (result);
}

#include <fcntl.h>
int main(void)
{
	int fd = open("./test/test.txt", O_RDONLY);
	while (true)
	{
		char *str = get_next_line(fd);
		if (str == NULL)
			break;
		int i = 0;
		while(str[i] != '\n')
		{
			write(1, &str[i], 1);
			i++;
		}
		if (str[i] == '\n')
			write(1, &str[i], 1);
		free(str);
	}		
	close(fd);
}