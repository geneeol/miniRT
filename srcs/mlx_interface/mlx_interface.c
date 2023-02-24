#include "libft.h"
#include "mlx_interface.h"
#include "mlx.h"
#include <stdlib.h>

t_display	*display_destroy(t_display *disp)
{
	if (disp->img)
		mlx_destroy_image(disp->mlx, disp->img);
	if (disp->win)
		mlx_destroy_window(disp->mlx, disp->win);
	if (disp->v)
		free(disp->v);
	free(disp);
	return (NULL);
}

static int	get_display_info(t_display *disp)
{
	int	i[3];

	disp->img_addr = mlx_get_data_addr(disp->img, i, i + 1, i + 2);
	disp->bpp = i[0];
	disp->nbytes = i[1];
	disp->endian = i[2];
	if (!disp->img_addr)
		return (CODE_ERROR_IO);
	mlx_destroy_image(disp->mlx, disp->img);
	disp->img = NULL;
	disp->img_addr = NULL;
	return (CODE_OK);
}

t_display	*display_create(int width, int height, char *title)
{
	t_display	*disp;

	disp = malloc(sizeof(t_display));
	if (!disp)
		return (NULL);
	ft_bzero(disp, sizeof(t_display));
	disp->mlx = mlx_init();
	if (!disp->mlx)
		return (display_destroy(disp));
	disp->win = mlx_new_window(disp->mlx, width, height, title);
	if (!disp->win)
		return (display_destroy(disp));
	disp->w = width;
	disp->h = height;
	disp->ratio = (double)disp->w / (double)disp->h;
	disp->img = mlx_new_image(disp->mlx, width, height);
	if (!disp->img)
		return (display_destroy(disp));
	if (get_display_info(disp))
		return (display_destroy(disp));
	return (disp);
}