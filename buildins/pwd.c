
#include "../minishell.h"

int show_pwd(t_data *data)
{
	// int i;
	// char *pwd;
	// i = 0;
	if (data->pwd != NULL)
	{
		printf("%s\n", data->pwd);
		return (0);
	}
	else
	{
		printf("err!\n");

	}
	return (1);
// 	while (data->env[i] != NULL)
// 	{
// 		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
// 		{
// 			pwd = ft_strdup(data->env[i] + 4);
// 			printf("%s\n", pwd);
// 			free(pwd);
// 			return ;

// //free_data(data);
// 		//	exit(0);
// 		}
// 		i++;
// 	}
}
