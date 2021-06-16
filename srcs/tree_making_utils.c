#include "lem_in.h"

/*
**	Searching for parent links, taking any forbidden into account.
*/
int	find_parent_links(int parent, t_lem *lem, int child, int siborchild)
{
	// return -1 in case of no sibling, return 0-whatever when finding a sibling

	int	i;
	int save;

	i = 0;
	save = -1;
	lem->links_found = 0;
	while (i < lem->nbr_tunnels)
	{
		if (lem->tunnel_dir[i][2] != 0 || lem->tunnel_dir[i][3] != 0)
			i++;
		else if (ft_strword(lem->tunnel_dir[i], parent))
		{
			if (ft_strword(lem->tunnel_dir[i], child))
			{
				save = i;
				if (siborchild == 1)
					return (save);
			}
			lem->links_found++;
			i++;
		}
		else
			i++;
	}
	i = 0;
	return (save);
}

/*
**	Returns a 1 if it finds the exact word in haystack 
**  that was in needle before or 
** 	after a '-' character.
*/

// CHANGE THE NAME OF THIS FUNCTION YOU DINGUS
int	ft_strword(int *haystack, int needle)
{
	if (haystack[0] == needle)
		return (haystack[1]);
	else if (haystack[1] == needle)
		return (haystack[0]);
	return (0);
}
