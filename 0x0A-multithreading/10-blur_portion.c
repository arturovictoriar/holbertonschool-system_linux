#include "multithreading.h"

/**
 * conv_sum - create a convolutional pixel
 * @portion: portion struct with the portion of the image
 * @i: value x for the initial point
 * @j: value y for the initial point
 * @img: matrix of pixel representing the original image
 * Return: pixel struct with the news rbg values
 */
pixel_t *conv_sum(blur_portion_t const *portion, size_t i, size_t j,
		pixel_t ***img)
{
	pixel_t *new_pixel = NULL;
	float conv_s = 0.0, **kernel = NULL;
	float pixel_r = 0.0, pixel_b = 0.0, pixel_g = 0.0;
	ssize_t size_kernel = 0, mid_kernel = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	new_pixel = calloc(1, sizeof(pixel_t));
	size_kernel = portion->kernel->size;
	mid_kernel = size_kernel / 2;
	kernel = portion->kernel->matrix;

	y1 = i - mid_kernel;
	x1 = j - mid_kernel;
	y2 = i + mid_kernel;
	x2 = j + mid_kernel;
	while (y1 <= y2)
	{
		x1 = j - mid_kernel;
		while (x1 <= x2)
		{
			if (y1 > -1 && x1 > -1 && x1 < (ssize_t) portion->img->w &&
					y1 < (ssize_t) portion->img->h)
			{
				pixel_r += (img[y1][x1]->r *
						kernel[y1 - i + mid_kernel][x1 - j + mid_kernel]);
				pixel_b += (img[y1][x1]->b *
						kernel[y1 - i + mid_kernel][x1 - j + mid_kernel]);
				pixel_g += (img[y1][x1]->g *
						kernel[y1 - i + mid_kernel][x1 - j + mid_kernel]);
				conv_s += kernel[y1 - i + mid_kernel][x1 - j + mid_kernel];
			}
			x1++;
		}
		y1++;
	}

	new_pixel->r = pixel_r / conv_s;
	new_pixel->b = pixel_b / conv_s;
	new_pixel->g = pixel_g / conv_s;

	return (new_pixel);
}

/**
 * print_img_conv - print the conv portion
 * @portion: portion struct with the information portion
 * @img_c: matrix representation of the blur image
 * Return: Nothing
 */
void print_img_conv(blur_portion_t const *portion, pixel_t ***img_c)
{
	size_t i = portion->y, j = 0;

	printf("red\n");
	while (i < portion->y + portion->h)
	{
		j = portion->x;
		while (j < portion->x + portion->w)
		{
			printf("%3u ", (img_c[i][j])->r);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("blue\n");
	i = portion->y;
	while (i < portion->y + portion->h)
	{
		j = portion->x;
		while (j < portion->x + portion->w)
		{
			printf("%3u ", (img_c[i][j])->b);
			j++;
		}
		printf("\n");
		i++;
	}
	(printf("green\n"), i = portion->y);
	while (i < portion->y + portion->h)
	{
		j = portion->x;
		while (j < portion->x + portion->w)
		{
			printf("%3u ", (img_c[i][j])->g);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("x = %lu\ny = %lu\n", portion->x, portion->y);
}

/**
 * free_img_utils - free util matrix img and img_c
 * @portion: portion struct with the information of the portion
 * @img_c: matrix representation of the blur image
 * @img: matrix representation of the original image
 * Return: Nothing
 */
void free_img_utils(blur_portion_t const *portion, pixel_t ***img_c,
		pixel_t ***img)
{
	size_t i = 0;

	i = 0;
	while (i < portion->img->h)
	{
		free(img_c[i]);
		free(img[i]);
		i++;
	}
	free(img_c);
	free(img);
}

/**
 * blur_portion - blur a portion of an image
 * @portion: portion struct with the information of the portion
 * Return: Nothing
 */
void blur_portion(blur_portion_t const *portion)
{
	pixel_t ***img_c = NULL, ***img = NULL, *con_pixel = NULL;
	size_t i = 0, j = 0;

	img_c = calloc(portion->img->h, sizeof(img_t **));
	img = calloc(portion->img->h, sizeof(img_t **));
	while (i < portion->img->h)
	{
		img_c[i] = calloc(portion->img->w, sizeof(img_t *));
		img[i] = calloc(portion->img->w, sizeof(img_t *));
		i++;
	}
	i = 0;
	while (i < portion->img->h)
	{
		j = 0;
		while (j < portion->img->w)
		{
			img_c[i][j] = &(portion->img_blur->pixels[(portion->img->w * i) + j]);
			img[i][j] = &(portion->img->pixels[(portion->img->w * i) + j]);
			j++;
		}
		i++;
	}
	i = portion->y;
	while (i < portion->y + portion->h)
	{
		j = portion->x;
		while (j < portion->x + portion->w)
		{
			con_pixel = conv_sum(portion, i, j, img);
			(img_c[i][j])->r = con_pixel->r;
			(img_c[i][j])->b = con_pixel->b;
			(img_c[i][j])->g = con_pixel->g;
			free(con_pixel);
			j++;
		}
		i++;
	}
	/*	print_img_conv(portion, img_c);*/
	free_img_utils(portion, img_c, img);
}
