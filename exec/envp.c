
#include "../minishell.h"

void add_slash(char ***path_arr)
{
	int i;
	char *new_path;
	
	i = 0;
	while ((*path_arr)[i])
	{
		if ((*path_arr)[i][ft_strlen((*path_arr)[i]) - 1] != '/')
		{
			new_path = ft_strjoin((*path_arr)[i], "/");
			free((*path_arr)[i]);
			(*path_arr)[i] = new_path;
//			free(new_path);
		}
		i++;
	}

}

char **get_path_arr(char **envp)
{
	int i;
	char **path_arr;
	char *trimmed_path0;

	i = 0;
	path_arr = NULL;
	trimmed_path0 = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			if (envp[i][5] == '\0')	// if PATH is empty
				return (NULL);
			path_arr = ft_split(envp[i], ':');
			if (!path_arr)
				return (NULL);
//			*path_arr[0] = *path_arr[0] + 5;
			break;
		}
	i++;

	}
	if (!path_arr)
		return (NULL);

	if (envp[i][5] != '\0')
		trimmed_path0 = ft_strdup(path_arr[0] + 5);
	if (trimmed_path0)
	{
		free(path_arr[0]);
		path_arr[0] = trimmed_path0;
	}
	add_slash(&path_arr);
	return (path_arr);
}

void print_path(char **path_arr)
{
	int i;
	
	i = 0;
	while (path_arr[i] != NULL)
	{
		printf("%s \n", path_arr[i]);
		i++;
	}
}

char *find_path(char *cmd, char **path)
{
	int i;
	char *res;
//	char *exec_o;

	res = NULL;
//	printf("CMD1  %s \n", cmd);
	
	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		res = ft_substr(cmd, 2, ft_strlen(cmd) - 2);
			if (access(res, F_OK) == 0)
			{
//				printf("CMD  %s %s \n", cmd, res);
				return(res);
			}

		// printf("sub %s\n", res);
		// return (res);
	}
	else if (ft_strncmp(cmd, "/", 1) == 0)
	{
		if (access(cmd, F_OK) == 0)
		{
			return(cmd);
		}
	}
	else
	{
	
		i = 0;
		while (path[i] != NULL)
		{
			res = ft_strjoin(path[i], cmd);
			if (access(res, F_OK) == 0)
			{
				return(res);
			}
			i++;
			free(res);
		}
	}
//	printf("CMD   %s", res);
	return (NULL);
}

