#include "../includes/lem_in.h"

static int		get_room(char *line, t_room *r_data)
{
	if (ft_strstr((char*)line, "##start") || ft_strstr(line, "##end"))
	{
		if (ft_strstr((char*)line, "##start"))
			r_data->roomtype = 3;
		else
			r_data->roomtype = 1;
		ft_strdel(&line);
	}
	else
		r_data->roomtype = 2;
	
	int		i;
	char	**coord;

	i = 0;
	if (*line == 'L')
		return (1);
	while (*line != ' ')
	{
		r_data->name[i] = *line;
		i++;
		line++;
	} 
	i++;
	if (!(coord = ft_strsplit(&line[i], ' ')))
		return (1);
	r_data->y = ft_atoi(coord[0]);
	r_data->x = ft_atoi(coord[1]);
	free_array(coord);
}

<<<<<<< HEAD:srcs/room_helpers.c
static int		check_room(char *line, t_room *r_data)
{
	if (ft_strstr((char*)line, "-"))
		get_tunnel(void);
	else if (ft_strstr((char*)line, "##start") || ft_strstr(line, "##end"))
	{
		room_values(line);
		if (ft_strstr((char*)line, "##start"))
			r_data->roomtype = 1;
		else
			r_data->roomtype = 3;
	}
	else
		r_data->roomtype = 2;
	return (0);
}

int				get_rooms(char *line, t_room *r_data)
=======
int				get_data(char *line, t_room *r_data)
>>>>>>> d8931f3cc94b81b0af248fa2a5f479611e90361d:srcs/sudocode.c
{
	t_room new_room;
	t_room temp;

	temp = r_data;
	// this should add the links between the rooms
	while (get_next_line(2, &line) > 0)
	{
		if (conditions suggest room)
			if (r_data->name != NULL)
			{
				initialize_room(&new_room);
				r_data->next = new_room;
				r_data = new_room;
				r_data->prev = temp;
			}
			get_room(line, r_data) == 1)
			return (1);
		else (conditions suggest tunnel)
			//construct tunnel array of linked list
		ft_strdel(&line);
	}
	return (0);
}





char **tunnels;

lem->tunnels[i] = line;
i++;