#include "lem_in.h"

int	*get_result(int **options, t_lem *lem)
{
	int i;
	int lowest;
	int tab;

	i = 0;
	tab = 0;
	lowest = options[0][1];
	while(i < lem->i_placeholder)
	{
		if (options[i][1] < lowest)
		{
			lowest = options[i][1];
			tab = i;
		}
		i++;
	}
	return(options[tab]);
}

int compare(int *final_paths, int *other_path)
{
	int i;
	int j;

	i = 2;
	while (i < (final_paths[0] * -1) - 1)
	{
		j = 2;
		while (j < (other_path[0] * -1) - 1)
		{
			if (final_paths[i] == other_path[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		set_steps(int *options, t_lem *lem) // we have a segfault here when  we test map 3ways.map (someone's lemin)
{
	int	*ants_and_len;
	int i;
	int ants_cpy;
	int tab;

	tab = (options[0] * -1) - 2;
	ants_cpy = lem->ants;
	i = 0;
	if (!(ants_and_len = (int *)malloc(sizeof(int) * tab)))
		ft_printf("ERRRROR");
	while (i < tab) //somewhere between here
	{
		ants_and_len[i] = (lem->final_paths[options[i + 2]][0] * - 1) - 3;
		i++;
	}
	i = 0;
	while (ants_cpy > 0)
	{
		while (i + 1 < tab && ants_and_len[i] > ants_and_len[i + 1])
			i++;
		ants_and_len[i]++;
		ants_cpy--;
		i = 0;
	}
	tab = ants_and_len[0]; // and here
	free(ants_and_len);
	return (tab);
}

int **add_minor_option(int **options, t_lem *lem, int len, int num)
{
	int i;
	int j;

	i = 1;
	j = 2;
	if (!(options[num] = (int *)malloc(sizeof(int) * len)))
		ft_printf("ERRRRRRRRORRRRROORRR");
	options[num][0] = len * -1;
	while (len > 3)
	{
		options[num][j] = options[num - 1][j];
		j++;
		len--;
	}
	options[num][j] = lem->i_placeholder + 1;
	options[num][j + 1] = '\0';
	options[num][1] = set_steps(options[num], lem);
	return (options);
}

int scan_similar(t_lem *lem, int *index_of_valid_paths, int *to_compare)
{
	int i;

	i = 2;
	while (i < (index_of_valid_paths[0] * -1))
	{
		if (compare(lem->final_paths[index_of_valid_paths[i]], to_compare) == 1)
			return (1);
		i++;
	}
	return (0);
}

int **recursion_adding(t_lem *lem, int **options, int compare)
{
	int i;

	i = 0;
	if (lem->i_placeholder < lem->max_paths - 1)
	{
		while (compare < lem->max_paths) 
		{
			/*
			**	Assumes we are comparing a "x | y | path" int array, adding onto paths as long as possible.
			**	Have to exit once it's not possible, and add next path as a single option.
			*/
			if (scan_similar(lem, options[lem->i_placeholder - 1], lem->final_paths[compare]) == 0) // finds if the two indexes has any rooms that are similar
			{
				lem->malloc_len++;
				options = append_array(options, lem->i_placeholder); // adding a malloced space for a valid path
				options = add_minor_option(options, lem, lem->malloc_len, lem->i_placeholder); // NEEDS TO BE FIXED
				lem->i_placeholder++;
				options = recursion_adding(lem, options, compare + 1);
			}
			compare++;
		}
	
	}
	lem->malloc_len = 3;
	return(options);
}

int **add_major_option(int **options, t_lem *lem, int index, int num)
{
	if (!(options[index] = (int *)malloc(sizeof(int) * 4)))
		ft_printf("ERRRRRRRRORRRRROORRR");
	options[index][0] = -3; //sets the len (index0) to a negative number
	options[index][1] = lem->ants + (lem->final_paths[num][0] * -1) - 4; //set_steps(options[0], lem->ants); //should set the steps (index1) to # of steps 
	options[index][2] = num;
	options[index][3] = '\0';
	return (options);
}

int flow_management(t_lem *lem)
{
	int **options;
	int i;
	int j;
	int compare;
	int	major_index;

	i = 0;
	j = 0;
	compare = 0;
	major_index = 0;
	lem->i_placeholder = 0;
	if (!(options = (int **)malloc(sizeof(int *) * 1)))
		return (1);
	options = add_major_option(options, lem, lem->i_placeholder, 0);
	while (major_index <= lem->max_paths - 1)
	{
		if (lem->i_placeholder != 0)
		{
			options = append_array(options, lem->i_placeholder);
			add_major_option(options, lem, lem->i_placeholder, major_index);
		}
		lem->i_placeholder++;
		major_index++;
		compare++;
		options = recursion_adding(lem, options, compare);
	}
	print_double_arr(options, lem->i_placeholder);
	lem->result = get_result(options, lem);
	return (0);
}