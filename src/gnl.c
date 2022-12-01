#include "libft.h"
#include "gnl.h"

int init_read(int fd, t_read *strct)
{
	strct->fd = fd;
	strct->pos = 0;
	strct->max = read(fd, strct->backup, BUFFER_SIZE);

	if (strct->max <= 0)
		return (0);
	else
		return (1);
}

char    check_read(t_read *strct)
{
	char    result;

	if (strct->pos >= strct->max)
	{
		strct->max = read(strct->fd, strct->backup, BUFFER_SIZE);
		strct->pos = 0;
		if (strct->max <= 0)
			return (0);
	}
	result = strct->backup[strct->pos];
	strct->pos++;
	return (result);
}

char    *add_char_to_str(char *s1, char ch)
{
	char    *str;
	int     i;
	int     len;

	i = 0;
	len = ft_strlen(s1);
	str = (char *)malloc((len + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = ch;
	str[i + 1] = '\0';
	if (s1)
		free(s1);
	return (str);
}

char    *get_next_line(int fd)
{
	static	t_read strct = {.fd = -1};
	char	ch;
	char	*str;

	str = NULL;
	if (strct.fd != fd)
	{
		if (!init_read(fd, &strct))
			return (NULL);
	}
	ch = check_read(&strct);
	while (ch)
	{
		str = add_char_to_str(str, ch);
		if (ch == '\n')
			return (str);
		ch = check_read(&strct);
	}
	return (str);
}
