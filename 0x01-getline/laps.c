#include "laps.h"

/**
  * order_cars - order and int list numericly. buble sort
  * @cars_and_laps: list containnig the car id and number of laps
  * @num_cars: numbers of car that the list of cars have
  * Return: 0 on sucess
  */
int order_cars(int cars_and_laps[3000][2], int num_cars)
{
	int cur_index = 0, nex_index = 0;
	int tmp_car = 0, tmp_lap = 0;

	for (cur_index = 0; cur_index < num_cars - 1; cur_index++)
	{
		for (nex_index = 0; nex_index < num_cars - cur_index - 1; nex_index++)
		{
			if (cars_and_laps[nex_index][0] > cars_and_laps[nex_index + 1][0])
			{
				tmp_car = cars_and_laps[nex_index][0];
				cars_and_laps[nex_index][0] = cars_and_laps[nex_index + 1][0];
				cars_and_laps[nex_index + 1][0] = tmp_car;

				tmp_lap = cars_and_laps[nex_index][1];
				cars_and_laps[nex_index][1] = cars_and_laps[nex_index + 1][1];
				cars_and_laps[nex_index + 1][1] = tmp_lap;
			}
		}
	}
	return (0);
}

/**
  * order_id - order and int list numericly. buble sort
  * @id: list containnig the car id
  * @size: numbers of car the list of cars id have
  * Return: 0 on sucess
  */
int order_id(int *id, size_t size)
{
	size_t cur_index = 0, nex_index = 0;
	int tmp_car = 0;

	for (cur_index = 0; cur_index < size - 1; cur_index++)
	{
		for (nex_index = 0; nex_index < size - cur_index - 1; nex_index++)
		{
			if (id[nex_index] > id[nex_index + 1])
			{
				tmp_car = id[nex_index];
				id[nex_index] = id[nex_index + 1];
				id[nex_index + 1] = tmp_car;
			}
		}
	}
	return (0);
}

/**
  * race_state - order and int list numericly
  * @id: list containnig the car ids
  * @size: numbers of car that the list of cars have
  * Return: nothing
  */
void race_state(int *id, size_t size)
{
	static int cars_and_laps_cars[3000][2];
	static size_t num_cars;
	size_t index = 0, index_car = 0, flag = 0;

	if (!size)
	{
		for (index = 0; index < num_cars; index++)
		{
			cars_and_laps_cars[index][0] = 0;
			cars_and_laps_cars[index][1] = 0;
		}
		num_cars = 0;
		return;
	}
	/*order_id(id, size);*/
	for (index = 0; index < size; index++)
	{
		flag = 1;
		for (index_car = 0; index_car < num_cars; index_car++)
			if (cars_and_laps_cars[index_car][0] == id[index])
				if (cars_and_laps_cars[index_car][1] != 0)
				{
					cars_and_laps_cars[index_car][1]++;
					flag = 0;
					break;
				}
		if (flag)
		{
			cars_and_laps_cars[index_car][0] = id[index];
			cars_and_laps_cars[index_car][1]++;
			num_cars++;
			printf("Car %d joined the race\n", id[index]);
		}
	}
	order_cars(cars_and_laps_cars, num_cars);
	printf("Race state:\n");
	for (index = 0; index < num_cars; index++)
		printf("Car %d [%d laps]\n", cars_and_laps_cars[index][0],
			   cars_and_laps_cars[index][1] - 1);
}
