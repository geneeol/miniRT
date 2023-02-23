#include "libft.h"
#include "ptrarr.h"
#include "msgdef.h"
#include "../parser_internal.h"

/*
	returns TRUE if line matches one of unique entities,
	FALSE if line matches none,
	negative if error occurs.
*/
static int	parse_unique_entity_loop(t_bool *already_found, char *line)
{
	int		i;
	int		stat;
	t_bool	found_once;

	found_once = FALSE;
	i = 0;
	while (i < N_IDENTIFIER_UNIQUE)
	{
		stat = parse_line(line,
				unique_patternmatcher_manager(i), unique_builder_manager(i));
		if (stat == TRUE)
		{
			found_once = TRUE;
			if (already_found[i])
			{
				ft_dprintf(2, "%s: duplicate unique elements detected.\n", EXEC_NAME);
				return (CODE_ERROR_DATA);
			}
			already_found[i] = TRUE;
		}
		else if (stat < 0)
			return (stat);
		i++;
	}
	return (found_once);
}

/*
	returns TRUE if line matches one of common entities,
	FALSE if line matches none,
	negative if error occurs.
*/
static int	parse_common_entity_loop(char *line)
{
	int		i;
	int		stat;

	i = 0;
	while (i < N_IDENTIFIER_COMMON)
	{
		stat = parse_line(line,
				common_patternmatcher_manager(i), common_builder_manager(i));
		if (stat)
			return (stat);
		i++;
	}
	return (FALSE);
}

static int	parse_common_entity(char *line)
{
	int	stat;

	stat = parse_common_entity_loop(line);
	if (stat < 0)
		return (stat);
	if (stat == FALSE)
	{
		ft_dprintf(2, "%s: failed to parse line \"%s\"\n", EXEC_NAME, line);
		return (CODE_ERROR_DATA);
	}
	return (CODE_OK);
}

int	parse_entities(t_ptrarr *lines)
{
	int			i;
	int			stat;
	t_bool		already_found[N_IDENTIFIER_UNIQUE];

	ft_memset(already_found, FALSE, sizeof(already_found));
	i = 0;
	while (i < lines->len)
	{
		stat = parse_unique_entity_loop(already_found, lines->data[i]);
		if (stat < 0)
			return (stat);
		if (stat == FALSE)
		{
			stat = parse_common_entity(lines->data[i]);
			if (stat < 0)
				return (stat);
		}
		i++;
	}
	return (CODE_OK);
}