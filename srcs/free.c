#include "lem_in.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_int_array(int **array, int max_paths)
{
	int	i;

	i = 0;
	while (i < max_paths)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_lem(t_lem *lem)
{
	free_array(lem->tunnels);
	free_int_array(lem->all_paths, lem->max_paths);
	free_int_array(lem->final, lem->negative_one);
}

void	free_room(t_room *room)
{
	t_room	*tmp;
	t_room	*current;

	current = room;
	while (current->next != NULL)
	{
		tmp = current->next;
		free(current->name);
		free(current);
		current = tmp;
	}
	free(current->name);
	free(current);
}

void	free_tree(t_tree *start, t_lem *lem)
{
	t_tree	*tmp;
	int		n;

	n = 0;
	if (start->name != 0)
	{
		while (start->name != lem->e_room_index)
		{
			tmp = start->child;
			if (start->sib != NULL)
				free_tree(start->sib, lem);
			free(start);
			start = tmp;
			if (start->name == 0)
				break ;
		}
	}
	free(start);
}
