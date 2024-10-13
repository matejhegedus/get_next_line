/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhegedus <mhegedus@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:37:56 by mhegedus          #+#    #+#             */
/*   Updated: 2024/10/13 16:12:39 by mhegedus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>
#include "get_next_line.h"

char *get_next_line(int fd)
{
	char	*buf;
	size_t	ln_len;
	size_t	i;
	bool	is_eol;
	char	*result;


	buf = malloc(BUFFER_SIZE);
	if (buf == NULL)
		return (NULL);
	is_eol = false;
	read(fd, buf, BUFFER_SIZE);
	i = 0;
	while (i < BUFFER_SIZE)
	{
		ln_len++;
		if(buf[i] == '\n')
		{
			is_eol = true;
			break;
		}
	}
	
	result = malloc(ln_len);
	if (result == NULL)
		return (NULL);
	
	return (buf);
}

#include <fcntl.h>
int main(void)
{
	int fd = open("./test/test.txt", O_RDONLY);
	write(1, get_next_line(fd), BUFFER_SIZE);
	close(fd);
}