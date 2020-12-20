#include "multithreading.h"

/**
 * thread_entry_blur - Thread entry point. Prints out a string
 *
 * @arg: image portion
 *
 * Return: NULL
 */
void *thread_entry_blur(void *arg)
{
	blur_portion((blur_portion_t const *) arg);
	pthread_exit(NULL);
}

/**
* create_list_portion - create a list of poriton equal to numbers of threads
* Return: a list of portions
*/
blur_portion_t *create_list_portion(void)
{
	blur_portion_t *new_list = NULL;

	new_list = calloc(NUM_THREADS, sizeof(blur_portion_t));
	if (!new_list)
		return (NULL);

	return (new_list);
}

/**
* create_list_thr - create a list of thr ids equal to numbers of threads
* Return: a list of threads ids
*/
pthread_t *create_list_thr(void)
{
	pthread_t *new_list = NULL;

	new_list = calloc(NUM_THREADS, sizeof(pthread_t));
	if (!new_list)
		return (NULL);

	return (new_list);
}

/**
* free_list_portion_thr - free the memory use for creating l_portion and l_trh
* @l_portion: list of portions
* @l_thr: list of threads ids
* Return: Nothing
*/
void free_list_portion_thr(blur_portion_t *l_portion, pthread_t *l_thr)
{
	free(l_portion);
	free(l_thr);
}


/**
* blur_image - blur a image using gaussian convolution method
* @img_blur: matrix representation of the blur image
* @img: matrix representation of the image
* @kernel: matrix convolution window
* Return: Nothing
*/
void blur_image(img_t *img_blur, img_t const *img, kernel_t const *kernel)
{
	blur_portion_t *portion = NULL;
	ssize_t i = 0, rest_pixels = 0;
	pthread_t *thr = NULL;

	portion = create_list_portion();
	thr = create_list_thr();

	if (img->w % NUM_THREADS)
		rest_pixels = img->w % NUM_THREADS;

	i = 0;
	while (i < NUM_THREADS)
	{
		portion[i].img = img;
		portion[i].img_blur = img_blur;
		portion[i].kernel = kernel;
		portion[i].w = img->w / NUM_THREADS;
		portion[i].h = img->h;
		portion[i].x = i * portion[i].w;
		portion[i].y = 0;
		if (i + 1 == NUM_THREADS && rest_pixels)
			portion[i].w += rest_pixels;
		pthread_create(&thr[i], NULL, &thread_entry_blur, &portion[i]);
		i++;
	}

	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(thr[i], NULL);
		i++;
	}

	free_list_portion_thr(portion, thr);
}
