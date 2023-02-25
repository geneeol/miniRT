#include "libft.h"
#include "geometry.h"

void	vec3_mult_num(t_vec3 *out, const t_vec3 *a, double b)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		out->i[i] = a->i[i] * b;
		i++;
	}
}

void	vec3_mult_num_inplace(t_vec3 *target, double b)
{
	t_vec3	temp;

	vec3_mult_num(&temp, target, b);
	ft_memcpy(target, &temp, sizeof(t_vec3));
}

void	vec3_mult_component_vec3(t_vec3 *out, const t_vec3 *a, const t_vec3 *b)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		out->i[i] = a->i[i] * b->i[i];
		i++;
	}
}

void	vec3_mult_component_vec3_inplace(t_vec3 *target, const t_vec3 *a)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		target->i[i] *= a->i[i];
		i++;
	}
}
