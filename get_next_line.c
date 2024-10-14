/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhegedus <mhegedus@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:37:56 by mhegedus          #+#    #+#             */
/*   Updated: 2024/10/14 17:17:41 by mhegedus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>
#include "get_next_line.h"

char *get_next_line(int fd)
{
	char	buf[BUFFER_SIZE];
	size_t	ln_len;
	static int		i;
	bool	is_eol;
	char	*result;
	int		bytes_read;
	static char buf_remainder[BUFFER_SIZE];
	static int remainder_count;

	is_eol = false;
	ln_len = 0;
	while (!is_eol) 
	{
		i = 0;
		if (remainder_count != 0)
		{
			// process the rest of the buffer at first before reading next chars
			while (i < remainder_count && !is_eol)
			{
				ln_len++;
				if(buf_remainder[i] == '\n')
					is_eol = true;
				i++;
			}
			result = add_buf_to_result(result, buf_remainder, ln_len - i, ln_len);
			if (i == remainder_count)
				remainder_count = 0;
			else if(i != remainder_count)
			{
				int j = 0;
				while(j + i < remainder_count)
				{
					buf_remainder[j] = buf_remainder[j + i];
					j++;
				}
				remainder_count = remainder_count - j;
			}
		}
		else
		{
			bytes_read = read(fd, buf, BUFFER_SIZE);
			if (bytes_read == -1 || (bytes_read == 0 && ln_len == 0))
				return (NULL);
			else if (bytes_read == 0)
				return (result);
			while (i < bytes_read && !is_eol)
			{
				ln_len++;			
				if(buf[i] == '\n')
					is_eol = true;
				i++;
			}
			result = add_buf_to_result(result, buf, ln_len - i, ln_len);
			if(i != bytes_read)
			{
				remainder_count = bytes_read - i;
				while(i < bytes_read)
				{
					buf_remainder[i - (bytes_read - remainder_count)] = buf[i];
					i++;
				}
			}	
		}
		if (result == NULL)
			return (NULL);
		// if buf or buf_remainder didnt get copied in whole, save the rest
		// in remainder	
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