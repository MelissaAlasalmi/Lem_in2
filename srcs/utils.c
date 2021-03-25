#include "lem_in.h"

/*
**	Scans the array if the number i exists, MOVE TO UTILS
*/

int scan_forbidden(int *array, int i, t_lem *lem)
{
	int j;

	j = 0;
	while (j < lem->nbr_tunnels)
	{
		if (array[j] == i)
			return (1);
		j++;
	}
	return (0);
}

/*
** Adds an element onto the int array, UTILS FUNCTION
*/

int add_elem_int_array(int *forbidden_array, t_lem *lem, char *block_name, int parent)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if (scan_forbidden(forbidden_array, i, lem) == 1) // moves forward in the index if it's forbidden
			i++;
		else if (ft_strstr(lem->tunnels[i], block_name))
		{
			while (forbidden_array[j] > -1)
				j++;
			forbidden_array[j] = i;
			i++;
			if (parent == 1)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int find_parent_links(char *parent, t_lem *lem, int *forbidden_array) //returns the amount of hits of a room name found in tunnels
{
	int i;
	int t;

	t = 0;
	i = 0;
	while (i < lem->nbr_tunnels)
	{
		if (scan_forbidden(forbidden_array, i, lem) == 1) // moves forward in the index if it's forbidden
			i++;
		else if (ft_strstr(lem->tunnels[i], parent))
		{
			t++;
			i++;
		}
		else
			i++;
	}
	if (t > 1)
		return (1);

	return (0);
}

/*
**	This functions will find the needle in the haystack, then return
**	the other part of the haystack minus the middle character
**	dividing them.
*/

char *needle_crop(char *haystack, char *needle)
{
	char **new;
	char *ret;

	new = ft_strsplit(haystack, '-');
	if (ft_strcmp(new[0], needle))
		ret = ft_strdup(new[0]);
	else
		ret = ft_strdup(new[1]);
	free(new[0]);
	free(new[1]);
	free(new);
	return (ret);
}
