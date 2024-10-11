/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhegedus <mhegedus@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:37:56 by mhegedus          #+#    #+#             */
/*   Updated: 2024/10/11 23:49:40 by mhegedus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include "get_next_line.h"

char *get_next_line(int fd)
{
	// static size_t	curr_pos;
	char			*buf;

	buf = malloc(BUFFER_SIZE);
	if (buf == NULL)
		return (NULL);
	read(fd, buf, BUFFER_SIZE);
	return (buf);
}

#include <fcntl.h>
int main(void)
{
	int fd = open("./test/test.txt", O_RDONLY);
	write(1, get_next_line(fd), BUFFER_SIZE);
	close(fd);
}