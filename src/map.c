/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:23:16 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/08 17:15:07 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

#include "file.h"
#include "math/math.h"
#include "util.h"

static size_t hextoc(int *c, const char *fbuf)
{
	size_t	r;
	int		t;

	r = 0;
	while (isdigit(fbuf[r]) || fbuf[r] == '-')
		++r;
	while (is_space(fbuf[r]))
		++r;
	if (fbuf[r] == ',')
	{
		++r;
		while (is_space(fbuf[r]))
			++r;
		*c = ft_atoi_hex(&fbuf[r]);
		if (!*c)
			*c = 0x00010101;
		while (isalnum(fbuf[r]))
			++r;
		t = *c & 0xff;
		*c = *c << 8;
		*c |= 0xff - t;
	}
	return (r);
}

static size_t strcountnums(const char* str, char stop)
{
	size_t c;

	c = 0;
	while(*str != stop)
	{
		if(isdigit(*str))
		{
			++c;
			while(isalnum(str[1]))
				++str;
			if(str[1] == ',')
			{
				++str;
				while(isalnum(str[1]))
					++str;
			}
		}
		++str;
	}
	return (c);
}

static size_t strcountln(const char* str)
{
	size_t c;

	c = 1;
	while(*str)
	{
		if(*str == '\n' && str[1])
			++c;
		++str;
	}
	return (c);
}

static void parsemap(t_map* map, const char* fbuf)
{
	size_t x;
	static size_t y = -1;
	float sx[2];

	map->s = 1.0f / (float)(map->w - (map->w != 1));
	sx[0] = -0.5f * (float)(map->w - (map->w != 1)) * map->s;
	sx[1] = -0.5f * (float)(map->h - (map->h != 1)) * map->s;
	while(++y < map->h)
	{
		x = -1;
		while(++x < map->w)
		{
			map->v[y * map->w + x].x = sx[0] + (float)x * map->s;
			map->v[y * map->w + x].z = sx[1] + (float)y * map->s;
			while(!isdigit(*fbuf) && *fbuf != '-')
				++fbuf;
			map->v[y * map->w + x].y = (float)atoi(fbuf);
			fbuf += hextoc(&map->c[y * map->w + x], fbuf);
			map->v[y * map->w + x].w = 1.0f;
		}
	}
}

static void normalizemap(t_map* map)
{
	float maxh;
	float minh;
	size_t i;

	maxh = 0.001f;
	minh = -0.001f;
	i = -1;
	while(++i < map->h * map->w)
	{
		if(map->v[i].y > maxh)
			maxh = map->v[i].y;
		else if(map->v[i].y < minh)
			minh = map->v[i].y;
	}
	if(!(maxh - minh))
		return;
	i = -1;
	while(++i < map->h * map->w)
	{
		if(!map->c[i])
			map->c[i] = interpc(0xffffffff, 0xff0000ff,
				(map->v[i].y - minh) / (maxh - minh));
		map->v[i].y = ((map->v[i].y - minh) / (maxh - minh))
			* map->s - map->s * 0.5f;
	}
}

int loadmap(t_map* map, const char* file)
{
	char* l;

	l = readfile(file);
	if(!l)
		return (0);
	map->w = strcountnums(l, '\n');
	map->h = strcountln(l);
	map->v = malloc(sizeof(*map->v) * (map->w * map->h));
	map->vc = malloc(sizeof(*map->v) * (map->w * map->h));
	map->c = calloc(sizeof(map->c), (map->w * map->h));
	if(!map->v || !map->vc || !map->c)
	{
		free(map->v);
		free(map->vc);
		free(map->c);
		free(l);
		return (0);
	}
	parsemap(map, l);
	free(l);
	normalizemap(map);
	return (1);
}
