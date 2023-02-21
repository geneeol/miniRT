#ifndef TEXTURE_H
# define TEXTURE_H

# include "geometry.h"

typedef struct s_texture	t_texture;

typedef struct s_texture
{
	void	(*get_color_at)(t_texture *, t_color *, t_uv, t_vec3 *);
}	t_texture;

typedef struct s_texture_solid
{
	void	(*get_color_at)(t_texture *, t_color *, t_uv, t_vec3 *);
	t_color	color;
}	t_texture_solid;

t_texture	*texture_solid_create(t_color color);

void		texture_solid_get_color_at(
				t_texture *self, t_color *out, t_uv uv, t_vec3 *p);

#endif