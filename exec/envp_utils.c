#include "../minishell.h"

void get_envs(t_data *data, char **envp)
{
	int i;
	int arr_lines;

	i = 0;
	arr_lines = get_arr_lines(envp) + 1;
	data->env = malloc(arr_lines * sizeof(char *));;
	if(!data->env)
	{
		panic("malloc");
		return ;
	}
	while(envp[i] != NULL)
	{
		data->env[i] = ft_strdup(envp[i]);
		if(!data->env[i])
		{
			while (i > 0)
				free(data->env[--i]);
			free(data->env);
			return ;
		}
//		printf("%s\n", data->env[i]);  
		i++;
	}
	data->env[i] = NULL;
}

void change_env_to_value(t_cmd_node *node, t_data *data, char *found, int ii)
{
	int i;
	int len;
	char *no_dollar;
	char *value;int execute(t_data *data)


	printf("fou %s", found);
	no_dollar = ft_strdup(found + 1);
	i = 0;
	len = ft_strlen(no_dollar);
	while(data->env[i] != NULL)
	{
//	printf("val %s", data->env[i]);
		if (ft_strncmp(data->env[i], no_dollar, len) == 0)
		{

			value = ft_strdup(data->env[i] + len + 1);
			if (!value)
				panic("strdup");
			free(node->cmd_args[ii]);
			node->cmd_args[ii] = ft_strdup(value);
			if (!node->cmd_args[ii])
				panic("strdup");
			free(value);
		}
		i++;
	}
	free(no_dollar);
}

void find_env_in_cmd(t_cmd_node **node, t_data *data)
{
	t_cmd_node *current;
	int i;
	char *found_env;

	found_env = NULL;
	current = *node;
//	printf("bbbbbb  %s\n", current->cmd_args[0]);
	while (current)
	{
		i = 0;
		while (current->cmd_args[i] != NULL)
		{
			if(current->cmd_args[i][0] == '$')
			{
				found_env = ft_strdup(current->cmd_args[i]);
				printf("ENV: %s  %d\n", current->cmd_args[i], i);
				change_env_to_value(current, data, found_env, i);
			}
			i++;
		}
		current = current->left;    
	}
	if(found_env)
		free(found_env);
}
