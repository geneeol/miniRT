#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "print.h"
#include "builder_internal.h"

t_bool	is_box_with_color(const t_ptrarr *tokens);
t_bool	is_box_with_material(const t_ptrarr *tokens);
int		add_box(t_scene *scene, t_box_info *info);

static int	parse_box_with_color(
				t_box_info *info, t_color *color, const t_ptrarr *tokens)
{
	build_vector(&info->cen, &tokens->data[1]);
	build_vector(&info->x_axis, &tokens->data[6]);
	info->x_angle = ft_atof(tokens->data[11]);
	info->width = ft_atof(tokens->data[12]);
	info->height = ft_atof(tokens->data[13]);
	info->depth = ft_atof(tokens->data[14]);
	build_vector(color, &tokens->data[15]);
	if (is_invalid_normalized_vec3(&info->x_axis) || is_invalid_color(color)
		|| is_invalid_length(info->width) || is_invalid_length(info->height)
		|| is_invalid_length(info->depth))
		return (CODE_ERROR_DATA);
	map_color(color);
	return (CODE_OK);
}

int	build_box_with_color(const t_ptrarr *tokens, t_scene *scene)
{
	t_box_info	info;
	t_color		color;
	int			i;

	if (parse_box_with_color(&info, &color, tokens))
		return (CODE_ERROR_DATA);
	if (add_texture_solid(scene, "", color))
		return (CODE_ERROR_MALLOC);
	if (add_material_lambertian(scene, "", ptrarr_getlast(scene->res.textures)))
		return (CODE_ERROR_MALLOC);
	i = 0;
	while (i < 6)
	{
		info.mt[i] = ptrarr_getlast(scene->res.materials);
		i++;
	}
	if (add_box(scene, &info))
		return (CODE_ERROR_MALLOC);
	printf("%s: ", __func__);
	print_box_info(&info);
	printf("\n");
	return (CODE_OK);
}
