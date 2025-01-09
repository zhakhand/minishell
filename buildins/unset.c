
#include "../minishell.h"

int find_var_str(char *str, t_data *data)
{
	int i;

	i = 0;
	while(data->env[i] != NULL)
	{
	if (ft_strncmp(data->env[i], str, ft_strlen(str)) == 0 && data->env[i][ft_strlen(str)] == '=')
		return (i);
	i++;
	}
	return (-1);
}

void free_env_array(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}
void unset_var(t_data *data, t_cmd_node *node, int num)
{
	int i;
	int j;
	int str_num;
	char **temp;

	temp = NULL;
	i = 0;
	j = 0;
	str_num = find_var_str(node->cmd_args[num], data);
	if (str_num >= 0)
	{
		temp = ft_calloc(get_arr_lines(data->env) + 1, sizeof(char *));
		while (data->env[i] != NULL)
		{
			if (i != str_num)
			{
				temp[j] = ft_strdup(data->env[i]);
				j++;
			}
			i++;
		}
		temp[j] = NULL;
	}
	free_env_array(data->env);
	data->env = temp;
}

void ft_unset(t_data *data, t_cmd_node *node)
{
	int i;

	// printf("\nBEFORE unset:\n");
	// for (int i = 0; data->env[i] != NULL; i++)
	// 	printf("%s\n", data->env[i]);


	i = 1;
	while (node->cmd_args[i] != NULL)
	{
		unset_var(data, node, i);
		i++;
	}

	// printf("\nAfter unset:\n");
	// for (int i = 0; data->env[i] != NULL; i++)
    // 	printf("%s\n", data->env[i]);
}
