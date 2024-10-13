/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhegedus <mhegedus@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:11:41 by mhegedus          #+#    #+#             */
/*   Updated: 2024/10/13 20:19:49 by mhegedus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	char_count;

// 	char_count = 0;
// 	while (s[char_count] != '\0')
// 		char_count++;
// 	return (char_count);
// }

// allocate longer result, copy the old value to result and free the old pointer
char	*add_buf_to_result(char *old_result, char *buf, size_t new_len)
{
	char	*new_result;
	size_t	old_len;
	size_t	i;
	size_t	j;

	if (new_len % BUFFER_SIZE == 0)
		old_len = new_len - BUFFER_SIZE;
	else
		old_len = new_len - (new_len % BUFFER_SIZE);
	new_result = malloc(new_len * sizeof(char));
	if (new_result == NULL)
		return (NULL);
	i = 0;
	while (i < old_len)
	{
		new_result[i] = old_result[i];
		i++;
	}
	j = 0;
	while (i < new_len)
	{
		new_result[i] = buf[j];
		i++;
		j++;
	}
	if (old_len != 0)
		free(old_result);
	return (new_result);
}