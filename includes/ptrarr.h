#ifndef PTRARR_H
# define PTRARR_H

# include "libft_def.h"

# define PTRARR_INITIAL_CAP 1

typedef struct s_ptrarr
{
	int		len;
	int		cap;
	void	**data;
}	t_ptrarr;

t_ptrarr	*ptrarr_create(void);
t_ptrarr	*ptrarr_destroy(t_ptrarr *ptrarr, t_bool free_all);
int			ptrarr_expand(t_ptrarr *ptrarr);
int			ptrarr_append(t_ptrarr *ptrarr, void *data);
void		ptrarr_free_all_ptr(t_ptrarr *ptrarr);

#endif
