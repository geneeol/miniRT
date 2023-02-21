#include <stdlib.h>
#include "texture.h"

t_texture	*texture_solid_create(t_color color)
{
	t_texture_solid	*out;

	out = malloc(sizeof(t_texture_solid));
	if (!out)
		return (NULL);
	out->get_color_at = texture_solid_get_color_at;
	out->color = color;
	return ((t_texture *)out);
}

void	texture_solid_get_color_at(
			t_texture *self, t_color *out, t_uv uv, t_vec3 *p)
{
	(void)uv;
	(void)p;
	*out = ((t_texture_solid *)self)->color;
}