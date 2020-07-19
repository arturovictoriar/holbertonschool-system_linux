#include "headerls.h"

/**
  * all_hls_opt - get all options of hls
  * Return: relation options with functions
  */
tag_option *all_hls_opt(void)
{
	static tag_option choose[] = {
		{"", ls_basic},
		{"1", ls_1_flg},
		{"a", ls_a_flg},
		{"A", ls_A_flg},
		{"l", ls_l_flg},
		{NULL, NULL},
	};
	return (choose);
}
