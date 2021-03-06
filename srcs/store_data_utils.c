#include "lem_in.h"
void	room_duplicates(t_lem *lem, char *r_name, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (ft_strcmp(lem->room_directory[j], r_name) == 0)
			error_message(lem, 5);
		j++;
	}
}

void	get_room_data(char *line, t_room *room, t_lem *lem)
{
	int	len;

	len = 0;
	while (line[len] != ' ')
		len++;
	room->name = (char *)malloc(sizeof(char) * len + 1);
	if (room->name == NULL)
		error_message(lem, 1);
	room->name[len] = '\0';
	while (len > 0)
	{
		len--;
		room->name[len] = line[len];
	}
	if (room->roomtype == 1 || room->roomtype == 3)
	{
		if (room->roomtype == 1)
			lem->s_room_name = ft_strdup(room->name);
		else
			lem->e_room_name = ft_strdup(room->name);
	}
}

t_room	*get_room(char *line, t_room *room, t_lem *lem)
{
	room->next = initialize_room(lem);
	get_room_data(line, room, lem);
	return (room->next);
}

int	check_rooms_validity(char *line, t_lem *lem, int i, int space)
{
	if (line[0] == 'L')
		error_message(lem, 4);
	if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
	{
		lem->found_start_end++;
		return (0);
	}
	else if (ft_strstr(line, " ") || ft_strstr(line, "#"))
	{
		if (ft_strstr(line, "#"))
			return (0);
		else
		{
			while (line[i] != '\0')
			{
				if (line[i] == ' ')
					space++;
				i++;
			}
			lem->nbr_rooms++;
		}
	}
	if (space == 2)
		return (0);
	error_message(lem, 4);
	return (1);
}

int	check_tunnel_validity(char *line, t_lem *lem)
{
	if (ft_strstr(line, "-") || ft_strstr(line, "#"))
	{
		if (ft_strstr(line, "#"))
			return (0);
		lem->nbr_tunnels++;
	}
	else
		error_message(lem, 8);
	return (0);
}
