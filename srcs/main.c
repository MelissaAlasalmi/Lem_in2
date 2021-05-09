#include "lem_in.h"

void	error_message(t_lem *lem, t_room *room)
{
	free(lem);
	free(room);
	ft_printf("ERROR\n");
}

int	main(void)
{
	t_lem	*lem;

	lem = initialize_lem();
	lem->all_rooms = initialize_room(lem);
	if (store_data(lem, lem->all_rooms, 0) == 0)
	{
		get_tunnel_int_arr(lem);
		if (tree_creation(lem))
		{
			error_message(lem, lem->all_rooms);
			return (1);
		}
		create_path_arr(lem);
		count_valid_paths(lem);
		// ft_printf("ALL PATHS:\n");
		// print_double_arr(lem->all_paths, lem->max_paths);
		sort_paths(lem);
		flow_management(lem);
		output(lem);
		//while (1);
		ft_printf("\nprinted:%d, steps:%d\n", lem->printed, lem->result[1]);
		free_tree(lem->tree, lem);
		//free_room(lem->all_rooms);
		//free_lem(lem);
	}
	else
	{
		error_message(lem, lem->all_rooms);
		return (1);
	}
	return (0);
}
