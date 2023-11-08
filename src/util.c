#include <stddef.h>
#include <ctype.h>

int is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static size_t _ft_reatoihex(const char* str, size_t n)
{
	if(!isalnum(*str))
		return (n);
	n *= 16;
	if(*str >= 'a' && *str <= 'f')
		n += (*str - 'a' + 10);
	else if(*str >= 'A' && *str <= 'F')
		n += (*str - 'A' + 10);
	else
		n += (*str - '0');
	return (_ft_reatoihex(++str, n));
}

size_t ft_atoi_hex(const char* str)
{
	size_t i;

	if(!str)
		return (0);
	i = 0;
	while(is_space(str[i]))
		++i;
	if(str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	return (_ft_reatoihex(&str[i], 0));
}
