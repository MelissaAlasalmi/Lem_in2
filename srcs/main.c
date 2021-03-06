#include "lem_in.h"

void error_message(t_lem *lem, int i) //removed free(room) from here, so need to do that where it's needed before this is called
{
	free(lem);
	if (i == 1)
		ft_putstr("ERROR: MALLOC\n");
	else if (i == 2)
		ft_putstr("ERROR: NO ANTS\n");
	else if (i == 3)
		ft_putstr("ERROR: NO ROOMS\n");
	else if (i == 4)
		ft_putstr("ERROR: ROOM INVALID\n");
	else if (i == 5)
		ft_putstr("ERROR: DUPLICATE ROOM\n");
	else if (i == 6)
		ft_putstr("ERROR: NO START/END ROOM\n");
	else if (i == 7)
		ft_putstr("ERROR: DUPLICATE START/END\n");
	else if (i == 8)
		ft_putstr("ERROR: TUNNEL INVALID\n");
	else if (i == 9)
		ft_putstr("ERROR: NO SOLUTION\n");
	exit(1);
}

int main(void)
{
	t_lem *lem;

	lem = initialize_lem();
	lem->all_rooms = initialize_room(lem);
	store_data(lem, lem->all_rooms, 0);
	get_tunnel_int_arr(lem);
	tree_creation(lem);
	create_path_arr(lem);
	count_valid_paths(lem);
	sort_paths(lem);
	create_final_arr(lem);
	flow_management(lem);
	ft_printf("ending flow_management\n");
	output(lem);
	ft_printf("\nprinted:%d, steps:%d\n", lem->printed, lem->result[1]);
	ft_printf("how many ants do we have? We have %d ants.\n", lem->ants);
	//free_tree(lem->tree, lem);
	return (0);
}
