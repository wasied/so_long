#include "so_long.h"

/* Count the amount of lines in a file
@param path -> The relative path to the file
@return int: the amount of lines
*/
int	count_lines(const char *path)
{
	char	*line;
	int		fd;
	int		count;

	fd = open(path, O_RDONLY);
	count = 0;
	while (fd > -1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
	}
	close(fd);
	return (count);
}

/* Free the map 2D array
@param map -> t_map structure pointer
@param message -> the message to print when exited
*/
void	free_map(t_map *map, char *message)
{
	size_t	i;

	i = 0;
	while (map->map[i])
		free(map->map[i++]);
	free(map->map);
	printf("%s\n", message);
	exit(0);
}

/* Count the amount of repetitions of a letter in the map
@param c -> the character we want to count
@return int: the amount of items
*/
int	count_items(t_map *map, char c)
{
	size_t	x;
	size_t	y;
	size_t	burgers;

	burgers = 0;
	y = 0;
	while (y < map->h)
	{
		x = 0;
		while (x < map->w)
		{
			if (map->map[y][x] == c)
				burgers++;
			x++;
		}
		y++;
	}
	return (burgers);
}

/* Check if there are walls everywhere around the map
@param map -> t_map structure pointer
@return int:
	0 = walls invalid
	1 = walls valid
*/
int	check_walls(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->w)
		if (map->map[0][i++] != '1')
			return (0);
	i = 0;
	while (i < map->w)
		if (map->map[map->h - 1][i++] != '1')
			return (0);
	i = 0;
	while (i < map->h)
		if (map->map[i++][0] != '1')
			return (0);
	i = 0;
	while (i < map->h)
		if (map->map[i++][map->w - 1] != '1')
			return (0);
	return (1);
}

/* Parse the map and allocate it correctly
@param map -> t_map structure pointer
@param path -> the file path where the map is stored (.ber only)
*/
void	parse_map(t_map *map, const char *path)
{
	char	*line;
	int		fd;
	size_t	width;
	size_t	tall;
	int		y;

	tall = count_lines(path);
	if (tall < 3)
		return ;
	width = 0;

	map->map = malloc((tall + 1) * sizeof(char *));
	if (!map->map)
		return ;

	y = 0;
	while (y <= tall)
		map->map[y++] = NULL;

	y = 0;
	fd = open(path, O_RDONLY);
	while (fd > -1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;

		if (line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';

		if (!width)
			width = ft_strlen(line);
		if (width != ft_strlen(line) || width < 3)
		{
			free_map(map, "The map in the .ber file must be a rectangle! Aborting.");
			break ;
		}

		map->map[y] = ft_strdup(line);
		if (!map->map[y])
		{
			free_map(map, "An unknown erorr has occured with memory allocation! Aborting.");
			break ;
		}
		y++;
	}
	map->map[y] = NULL;
	map->w = width;
	map->h = tall;

	if (check_walls(map) == 0)
	{
		free_map(map, "Map must be surrounded only by walls (1) in the .ber file! Aborting.");
		return ;
	}

	map->burgers = count_items(map, 'C');
	if (map->burgers <= 0)
		free_map(map, "You need to put at least 1 burger (C) in the .ber file! Aborting.");
	if (count_items(map, 'E') <= 0)
		free_map(map, "You need to put at least 1 exit (E) in the .ber file! Aborting.");
	if (count_items(map, 'P') <= 0)
		free_map(map, "You need to put at least 1 start position (P) in the .ber file! Aborting.");
	close(fd);
}