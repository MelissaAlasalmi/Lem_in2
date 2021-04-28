#include "lem_in.h"

void distance_special(t_lem *lem, int sibling)
{
	int i;

	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if ((lem->tunnel_directory[i][0] == sibling || lem->tunnel_directory[i][1] == sibling) && lem->tunnel_directory[i][2] == 0)
		{
			lem->tunnel_directory[i][2] = -1;
			lem->tunnel_directory[i][3] = 1;
		}
		i++;
	}
}

void distance_handling(t_lem *lem, int neg_pos, int object, int add_reduce) //neg_pos == -1/1 //add_reduce == -1/1
{
	int i;

	i = 0;
	if (add_reduce == 1)
	{
		while (i < lem->nbr_tunnels)
		{
			if (neg_pos < 0 && lem->tunnel_directory[i][2] < 0)
				lem->tunnel_directory[i][2]--;
			else if (lem->tunnel_directory[i][0] != lem->e_room_index && lem->tunnel_directory[i][1] != lem->e_room_index && neg_pos > 0 && lem->tunnel_directory[i][2] > 0)
				lem->tunnel_directory[i][2]++;
			else if ((lem->tunnel_directory[i][0] == object || lem->tunnel_directory[i][1] == object) && lem->tunnel_directory[i][2] == 0)
				lem->tunnel_directory[i][2] += neg_pos;
			i++;
		}
	}
	else if (add_reduce == -1)
	{
		while (i < lem->nbr_tunnels)
		{
			if (neg_pos < 0 && lem->tunnel_directory[i][2] < 0)
				lem->tunnel_directory[i][2]++;
			else if (neg_pos > 0 && lem->tunnel_directory[i][2] > 0)
				lem->tunnel_directory[i][2]--;
			i++;
		}
	}
}

void find_family(t_lem *lem, t_tree *parent, t_tree *child, int delete2, int sib_save)
{
	int sibling_trigger_save;

	//ft_printf("Start of find family:\n");
	if (find_parent_links(parent->name, lem) > 1)
	{
		lem->test_index++;
		while (delete2 <= 5)
		{
			ft_printf("-");
			delete2++;
		}
		// ft_printf("Before distance handling sibling add:\n");
		// print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
		distance_handling(lem, 1, child->name, 1);
		// ft_printf("After distance handling sibling add:\n");
		// print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
		lem->sibling_trigger++;
		lem->sib_name = make_sibling(child, parent, lem, sib_save);
		lem->sibling_trigger--;
		// ft_printf("Before distance handling sibling reduce:\n");
		// print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
		distance_handling(lem, 1, 0, -1);
		// ft_printf("After distance handling sibling reduce:\n");
		// print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
		// ft_printf("Before distance handling sibling Special:\n");
		// print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
		distance_special(lem, lem->sib_name);
		// ft_printf("After distance handling sibling Special:\n");
		// print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
		lem->sib_name = 0;
	}
	sibling_trigger_save = lem->sibling_trigger;
	ft_printf("\n");
	if (child->name != lem->e_room_index)
	{
		lem->sibling_compare++;
		// ft_printf("Before distance handling child add:\n");
		// print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
		distance_handling(lem, -1, parent->name, 1);
		// ft_printf("After distance handling child add:\n");
		// print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
		make_child(child, lem, sib_save);
		lem->sibling_compare--;
		// ft_printf("Before distance handling child reduce:\n");
		// print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
		distance_handling(lem, -1, 0, -1);
		// ft_printf("After distance handling child reduce:\n");
		// print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
	}
	else if (lem->total_paths == 7)
		child->child = tree_init(child);
}

int make_sibling(t_tree *child, t_tree *parent, t_lem *lem, int sib_save)
{
	t_tree *sibling;
	int i;
	int j;
	int delete;
	int delete2;

	delete2 = 0;
	j = 0;
	i = 0;
	sibling = tree_init(parent);
	child->sib = sibling;
	while (j < lem->nbr_tunnels)
	{
		if (lem->tunnel_directory[j][2] != 0)
			j++;
		else if (ft_strword(lem->tunnel_directory[j], lem->e_room_index))
			j++;
		else if (ft_strword(lem->tunnel_directory[j], parent->name))
		{
			sibling->name = needle_crop(lem->tunnel_directory[j], parent->name);
			delete = sibling->name;
			while (delete != 0)
			{
				delete = delete / 10;
				delete2++;
			}
			ft_printf("%d", sibling->name);
			sibling->parent = parent;
			break;
		}
		else
			j++;
	// 	if (ft_strword(lem->tunnel_directory[j], parent->name))
	// 	{
	// 		if (lem->tunnel_directory[j][2] == 0)
	// 		{
	// 			sibling->name = needle_crop(lem->tunnel_directory[j], parent->name);
	// 			delete = sibling->name;
	// 			while (delete != 0)
	// 			{
	// 				delete = delete / 10;
	// 				delete2++;
	// 			}
	// //			ft_printf("%d", sibling->name);
	// 			sibling->parent = parent;
	// 			break;
	// 		}
		// }
		// j++;
	}
	if (sibling->name != 0 /*&& lem->total_paths < lem->stopper*/)
		find_family(lem, parent, sibling, delete2, sib_save);
	if (sibling->name == 0)
	{
		ft_printf("sibling is 0 with parent: %d\n", parent->name);
		exit (1);
	}
	lem->test_index--;
	//	ft_printf("made sibling:%d\n", sibling->name);
	return (sibling->name);
}

void make_child(t_tree *parent, t_lem *lem, int compare)
{
	t_tree *child;
	int i;
	int j;
	int test_delete;
	int delete;
	int sib_save;
	int delete2 = 0;

	lem->ended = 0;
	sib_save = lem->sibling_trigger;
	test_delete = lem->test_index;
	j = 0;
	i = 0;
	delete = 0;
	compare = 0;
	while (test_delete > 1)
	{
		ft_printf("|     ");
		test_delete--;
	}
	ft_printf("|\n");
	while (test_delete < lem->test_index)
	{
		ft_printf("|     ");
		test_delete++;
	}
	child = tree_init(parent);
	parent->child = child;
	while (j < lem->nbr_tunnels)
	{
		if (lem->tunnel_directory[j][2] == 0)
		{
			if (ft_strword(lem->tunnel_directory[j], parent->name))
			{
				//ft_printf("went here with: %d, trigger:%d\n", lem->tunnel_directory[j][2], lem->sibling_trigger - lem->sibling_compare);
				child->name = needle_crop(lem->tunnel_directory[j], parent->name);
				delete = child->name;
				while (delete > 0)
				{
					delete = delete / 10;
					delete2++;
				}
				ft_printf("%d", child->name);
				child->parent = parent;
				break;
			}
		}
		j++;
	}
	if (child->name != 0 && child->name != lem->e_room_index)
		find_family(lem, parent, child, delete2, sib_save);
	if (child->name != 0 && child->name == lem->e_room_index)
	{
		lem->total_paths++;
	//	ft_printf("FUCK YEAH\n");
	//	exit (1);
	}
	if (child->name == 0 || child->name == lem->e_room_index)
	{
		lem->ended = 1;
		lem->making_sibling--;
		ft_printf("E", child->name);
	//	exit (1);
	}

	//	ft_printf("made child:%d\n", child->name);
}

int tree_creation(t_lem *lem)
{
	lem->making_sibling = 0;
	lem->sibling_trigger = 0;
	lem->sibling_compare = 0;
	lem->test_index = 1;
	ft_printf("\n\n<--****STARTING TREE MAKING****-->\n\n");
	ft_printf("Total of tunnels:%d\n", lem->nbr_tunnels);
	ft_printf("Total of rooms:%d\n\n", lem->nbr_rooms);
	lem->tree = head_tree_init(lem->start_room_index);
	ft_printf("%d\n", lem->start_room_index);
	make_child(lem->tree, lem, 0);
	distance_handling(lem, -1, 0, -1);
	// ft_printf("FINAL TUNNEL DIR:\n");
	// print_tunnel_dir(lem->tunnel_directory, lem->nbr_tunnels);
//	exit (1);
	ft_printf("\n\n");
	return (0);
}
