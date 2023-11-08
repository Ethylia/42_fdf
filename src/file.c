/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:17:35 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 16:59:55 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

size_t filelen(const char* file)
{
	int fd;
	size_t r;
	ssize_t tr;
	char b[256];

	fd = open(file, 0);
	if(!fd)
		return (0);
	r = 0;
	while(1)
	{
		tr = read(fd, b, 256);
		if(!tr || tr == -1)
			break;
		r += (size_t)tr;
	}
	close(fd);
	return (r);
}

char* readfile(const char* file)
{
	size_t l;
	char* r;
	int fd;

	l = filelen(file);
	fd = open(file, 0);
	if(!l || fd == -1)
		return (0);
	r = malloc(l + 1);
	if(!r)
	{
		close(fd);
		return (0);
	}
	if(read(fd, r, l) <= 0)
	{
		close(fd);
		free(r);
		return (0);
	}
	r[l] = '\0';
	close(fd);
	return (r);
}
