#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include <stdlib.h>
# include <fcntl.h> //for reading files from FD

typedef struct s_lem
{
	int				ants;
	int				nbr_tunnels;
	int				nbr_rooms;
	int				current_roomnum;
	int				**tunnel_directory;
	char			**room_directory;
	int				found_start_end;
	int				path_index;
	int				test_index; // remove after
	int				tunnel_index;
	int				test_stopper;
	int				path;
	int				max_paths;
	int				malloc_len;
	int				*w_child;
	int				*w_parent;
	int				index_options;
	int				i_pos;
	int				negative_one;
	int				total_paths;
	struct s_room	*all_rooms;
	int				**all_paths;
	int				**final;
	char			**tunnels;
	char			*start_room_name;
	char			*e_room_name;
	int				start_room_index;
	int				e_room_index;
	int				sib_name;
	int				comp;
	struct s_tree	*tree;
	int				*result;
	int				sets;
	int				stopper;
	int				moves_per_set;
	int				printed;
}					t_lem;

typedef struct s_tree
{
	int				name;
	struct s_tree	*parent;
	struct s_tree	*child;
	struct s_tree	*sib;
}					t_tree;

typedef struct s_room
{
	char				*name;
	int					roomtype;
	int					roomnum;
	struct s_room		*next;	
}						t_room;

/*
**	PROTOTYPES
*/

/*
**	INITIALIZE
*/

t_lem		*initialize_lem(void);
t_room		*initialize_room(t_lem *lem);

/*
**	STORE_DATA.C
*/

int			store_data(t_lem *lem, t_room *room, int fd);
void		test_structs(t_lem *lem);
int			file_is_valid(t_lem *lem, int fd);
int			search_for_all_paths(t_lem *lem);
int			needle_crop(int *haystack, int needle);
int			find_parent_links(int parent, t_lem *lem);
int			tree_creation(t_lem *lem);
t_tree		*tree_init(t_tree *parent);
int			add_elem_int_array(int *forbidden, t_lem *lem, int block, int parent);
int			make_child(t_tree *parent, t_lem *lem);
int			make_sibling(t_tree *child, t_tree *parent, t_lem *lem);
t_tree		*head_tree_init(int name);
int			create_path_arr(t_lem *lem);
void		free_tree(t_tree *start, t_lem *lem);
void		free_room(t_room *room);
void		free_lem(t_lem *lem);
void		free_array(char **array);
void		print_int_arr(int *arr, int len, char *str); //remove later!
int			check_tunnel_validity(char *line, t_lem *lem);
t_room		*get_room(char *line, t_room *room, t_lem *lem);
int			check_rooms_validity(char *line, t_lem *lem, int i, int space);
int			*ft_newintarr(int *forbidden, int i);
void		get_room_num(t_tree *tree, t_lem *lem, int r, int i);
int			flow_management(t_lem *lem);
int			**append_array(int **arr, int max);
void		sort_paths(t_lem *lem);
void		count_valid_paths(t_lem *lem);
int			ft_strword(int *haystack, int needle);
void		arr_row_size(t_tree *start, t_lem *lem);
void		print_double_arr(int **arr, int max); //remove later!
void		print_tunnel_dir(int **arr, int max); // remove later!
int			output(t_lem *lem);
void		get_tunnel_int_arr(t_lem *lem);
void		remove_elem_int_array(int *forb, t_lem *lem, int block, int parent);
void		get_tunnel_int_arr(t_lem *lem);
void		free_int_array(int **array, int max_paths);
int			set_steps(int *option, t_lem *lem);
int			scan_similar(t_lem *lem, int *index_of_valid_paths, int *to_comp);
int			room_duplicates(t_lem *lem, char *r_name, int i);

#endif