#include "so_long.h"

/* Dynamically allocate a string and put a '\0' at the end of it
@param str -> The string that will be allocated
@param char* -> The allocated string
*/
char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	str_len;
	char	*ptr;

	str_len = ft_strlen((char *)str);
	ptr = malloc((str_len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}