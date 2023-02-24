#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "ptrarr.h"
#include "objects.h"
#include "msgdef.h"
#include "parser_internal.h"

static t_bool	read_file_to_strarr_init(
		const char *path, t_ptrarr **arr, int *fd)
{
	*arr = ptrarr_create();
	if (!(*arr))
	{
		ft_dprintf(2, "%s: "MSG_MALLOC"\n", EXEC_NAME);
		return (FALSE);
	}
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
	{
		ptrarr_destroy(*arr, TRUE);
		perror(EXEC_NAME);
		return (FALSE);
	}
	return (TRUE);
}

t_ptrarr	*read_file_to_strarr(const char *path)
{
	t_ptrarr	*arr;
	int			fd;
	char		*newline;

	if (!read_file_to_strarr_init(path, &arr, &fd))
		return (NULL);
	while (TRUE)
	{
		newline = get_next_line(fd);
		if (!newline)
			return (arr);
		if (ft_strlen(newline) == 1 && newline[0] == '\n')
		{
			free(newline);
			continue ;
		}
		newline[ft_strlen(newline) - 1] = '\0';
		if (ptrarr_append(arr, newline))
		{
			ptrarr_destroy(arr, TRUE);
			return (NULL);
		}
	}
}

/*
	returns TRUE if line matches pattern, FALSE if doesn't,
	negative if error occurs.
*/
int	parse_line(const char *line, t_scene *scene,
	t_patternmatcher tester, t_builder builder)
{
	t_ptrarr	*tokens;
	int			stat;

	tokens = tokenize(line);
	if (!tokens)
		return (CODE_ERROR_MALLOC);
	stat = FALSE;
	if (tester(tokens))
	{
		stat = builder(tokens, scene);
		if (!stat)
			stat = TRUE;
	}
	ptrarr_destroy(tokens, TRUE);
	return (stat);
}

int	parse_scene(const char *path, t_scene *scene)
{
	int			stat;
	t_ptrarr	*lines;

	lines = read_file_to_strarr(path);
	if (!lines)
		return (CODE_ERROR_IO);
	stat = parse_entities(lines, scene);
	ptrarr_destroy(lines, TRUE);
	return (stat);
}
