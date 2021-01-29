#include "../includes/lem_in.h"

int file_is_valid(t_lem *lem, int fd)
{
    // if (file is determined to be valid)
    //     return (0);
    // else
    //     return (1);
    char	*line;
    get_next_line(fd, &line); //gets rid of ants for now, fix for error handling
    if (!ft_isalldigit(line))
        return (1);
    ft_strdel(&line);
	while (get_next_line(fd, &line) > 0)
	{
		if (!(ft_strstr(line, "-")))
        {
            if (ft_strstr(line, "#")) //does not include ##start or ##end in room count
                ft_strdel(&line);
            else
            {
                lem->nbr_rooms++;
                ft_strdel(&line);
            }
        }
        else
        {
			lem->nbr_tunnels++;
		    ft_strdel(&line);
        }
	}
    return(0);
}