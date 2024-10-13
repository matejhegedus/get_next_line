/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhegedus <mhegedus@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:37:56 by mhegedus          #+#    #+#             */
/*   Updated: 2024/10/13 21:30:47 by mhegedus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>
#include "get_next_line.h"

char *get_next_line(int fd)
{
	static char	*buf = malloc(BUFFER_SIZE);
	size_t	ln_len;
	int		i;
	bool	is_eol;
	char	*result;
	int		bytes_read;
	static size_t remainder_pos;

	if (buf == NULL)
		return (NULL);
	is_eol = false;
	ln_len = 0;
	while (!is_eol)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return NULL;
		i = 0;
		while (i < bytes_read && !is_eol)
		{
			ln_len++;			
			if(buf[i] == '\n')
				is_eol = true;
			i++;
		}
		result = add_buf_to_result(result, buf, ln_len);
		if (result == NULL)
			return (NULL);
	}
	free(buf);
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