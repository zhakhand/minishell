
#include "../minishell.h"
/*
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
*/

int ft_unset(t_data *data, t_cmd *node)
{
	int i;

	// printf("\nBEFORE unset:\n");
	// for (int i = 0; data->env[i] != NULL; i++)
	// 	printf("%s\n", data->env[i]);

	t_var *temp;
	t_var *temp2;
	t_var *temp3;

	
	temp3 = data->env_var;
	i = 1;
	while (node->args[i] != NULL)
	{
		temp = data->env_var;
//	  printf("a i found %s\n", node->args[i]);
		while (temp)
		{
			temp2 = temp->next;
			if (temp2 == NULL)
				break;
			if (ft_strncmp(temp2->key, node->args[i], ft_strlen(node->args[i])) == 0)
			{

				temp->next = temp2->next;
				free(temp2->key);
				free(temp2->val);
				free(temp2);
//				break;
			}
			temp = temp->next;
			}
		i++;
	}
	data->env_var = temp3;
//	ft_env_no_args(data);
	return (0);
	// i = 1;
	// while (node->cmd[i] != NULL)
	// {
	// 	unset_var(data, node, i);
	// 	i++;
	// }

	// printf("\nAfter unset:\n");
	// for (int i = 0; data->env[i] != NULL; i++)
    // 	printf("%s\n", data->env[i]);
}
