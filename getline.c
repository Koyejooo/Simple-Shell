include "simshell.h"

/**
 * input_buf - function that buffers chained commands
 * @info: incoming argument for stuct list
 * @buf: incoming argument for address of buffer
 * @len: incoming argument for length of var
 *
 * Return: no. of bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - function that gets a line, but leaves out the newline
 * @info: incoming argument for struct list
 *
 * Return: no. of bytes read
 */
ssize_t get_input(info_t *info)
{
	static shar *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (strlen(p));
	}
	*buf_p = buf;
	return (r);
}

/**
 * read_buf - a function that reads the contents of a buffer
 * @info: incoming argument for stuct list
 * @buf: incoming argument for buffer to be read
 * @i: incoming argument for size of buffer to be read
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - a function that gets the next line of input from STDIN
 * @info: incoming argument for sturct list
 * @ptr: incoming argument for address of pointer to buffer, prealloc'd or NULL
 * @length: incoming argument for size of prealloc'd ptr buffer, if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p),  -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncopy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (lenght)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - a function that blocks the ctrl+C input
 * @sig_num: incoming arguments for the signal number
 *
 * Return: Nothing
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
