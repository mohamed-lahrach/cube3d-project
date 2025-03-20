
#ifndef PARSING_H
# define PARSING_H

# include "../get_next_line/get_next_line.h"
# include "../lib/libft/libft.h"
# include <stdbool.h>
# include <string.h>
#include <stdio.h>

typedef enum e_types
{
	FLOOR,
	CEILING,
	WEST,
	EAST,
	NORTH,
	SOUTH,
	MAP,
	INVALID
}					t_type;

typedef struct s_trimindices
{
	int				start;
	int				end;
	int				i;
}					t_TrimIndices;

typedef struct s_atoiindices
{
	int				i;
	int				num;
	int				sign;
}					t_AtoiIndices;

typedef struct s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct s_colors
{
	int				red;
	int				green;
	int				blue;
}					t_colors;

typedef struct s_mapp
{
	char			*line;
	struct s_mapp	*next;
}					t_mapp;

typedef struct s_components_list
{
	t_colors		*floor_color;
	t_colors		*ceiling_color;
	char			*path_to_west_texture;
	char			*path_to_east_texture;
	char			*path_to_north_texture;
	char			*path_to_south_texture;
	t_mapp			*map;
}					t_components;


bool				valid_path(char *path);
int					open_file_and_return_fd(char *path);
bool				check_validity_of_file(int fd);
bool				valid_map_line(char *str);
void				ft_free(char **splitted);
t_type				return_nd_free(t_type this, char **arr);
int					get_color(t_colors *color);
void				free_t_colors(t_colors **colors);
void				free_mapp(t_mapp **head);
// void				free_mlx_texture(mlx_texture_t **texture);
void				free_comps(t_components *comps);
bool				parse_the_file(char *path, t_components *comps);
int					get_max_string_length(t_mapp *head);
bool				valid_map(t_mapp *map);
bool				check_validity_of_map(t_mapp *map);
bool				check_validity_of_textures(t_components *comps);
bool				is_a_position_char(char c);
bool				check_player_position(t_mapp *map);
char				**list_to_array(t_mapp *head, int max_length);
void				determine_player_pos(t_pos *pos, char **arr);
void				check_borders(char **map_arr, int x, int y, bool *out);
void				set_all_to_null(t_components *comps);
void				print_components(const t_components *components);
bool				adjacent_space(char *line);
bool				treat_middle_line(char *line);
bool				treat_first_and_last(char *line);
bool				all_good(t_components *comps);
char				*remove_newline(char *line);
void				add_to_list(t_mapp **head, char *new_line);
bool				retrieve_map(int fd, t_components *comps, char *line);
bool				fill_it(int fd, t_components *comps);
bool				free_2d_nd_return_bool(char **splitted, bool boolean);
bool				parse_colors_string(t_type info_type, char *temp,
						t_components *comps);
bool				parse_colors(t_type info_type, char *temp,
						t_components *comps);
bool				fill_container(t_type info_type, char *temp,
						t_components *comps);
bool				return_bool_nd_free(bool boolean, char **temp);
int					get_length(char *array[]);
bool				check_color_validity(char *str, int *color_value);
bool				process_colors(char **array, t_colors *color);
bool				deal_with_colors(t_type info_type, t_components *comps,
						char **splitted);
int					count_commas(char *str);
t_type				detect_type(char *str);
bool				parse_texture_string(t_type info_type, char *temp,
						t_components *comps);
bool				parse_textures(t_type info_type, char *temp,
						t_components *comps);
int					where_to_start(t_type info_type, char *temp);
int					where_to_finish(int starting_index, char *temp);
int					ft_strcmp(const char *s1, const char *s2);
void				free_and_set_to_null(char **ptr);
char				*trim_white_spaces(char *str);
int					ft_isspace(int c);
int					ft_super_atoi(const char *str);
char				*ft_strncpy(char *dest, const char *src, size_t n);
void				copy_list_to_array(t_mapp *head, char **array,
						int max_length);
bool				retrieve_map(int fd, t_components *comps, char *line);
bool				process_line(int fd, t_components *comps, char *line);
bool				handle_map_type(int fd, t_components *comps, char *line,
						char *temp);
bool				fill_it(int fd, t_components *comps);
void				initialize_indices(t_AtoiIndices *indices);
void				skip_whitespace(const char *str, t_AtoiIndices *indices);
bool				check_length(const char *str, t_AtoiIndices *indices);
void				handle_sign(const char *str, t_AtoiIndices *indices);
bool				is_valid_digit(const char *str, t_AtoiIndices *indices);
void				convert_to_number(const char *str, t_AtoiIndices *indices);
bool				check_end_of_string(const char *str,
						t_AtoiIndices *indices);
int					get_y(t_mapp *head);

#endif