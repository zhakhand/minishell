
#include "../minishell.h"

// void sort_env(t_data *data)
// {
// 	int i;
// 	int j;
// 	char *tmp;

// 	i = 0;
// 	while (data->env[i] != NULL)
// 	{
// 		j = i + 1;
// 		while (data->env[j] != NULL)
// 		{
// 			if (ft_strncmp(data->env[i], data->env[j], ft_strlen(data->env[i])) > 0)
// 			{
// 				tmp = data->env[i];
// 				data->env[i] = data->env[j];
// 				data->env[j] = tmp;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

int add_to_env(char *str, t_data *data)
{
	t_var *new_var;
	t_var *temp;
	int i;


	i = 0;
	new_var = malloc(sizeof(t_var));
	if (!new_var)
		panic("malloc");
	while (str[i] != '=')
		i++;
	new_var->key = ft_substr(str, 0, i);
	new_var->val = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	if (!new_var->key || !new_var->val)
		panic("strdup");
	new_var->next = NULL;
	if (!data->env_var)
	{
		data->env_var = new_var;
		return (0);
	}
	temp = data->env_var;
	while (temp->next)
		temp = temp->next;
	temp->next = new_var;
	return (0);
	// int i;
	// int len;
	// char **new_env;

	// i = 0;
	// len = get_arr_lines(data->env);
	// new_env = malloc((len + 2) * sizeof(char *));
	// if (!new_env)
	// 	panic("malloc");
	// while (data->env[i] != NULL)
	// {
	// 	new_env[i] = ft_strdup(data->env[i]);
	// 	if (!new_env[i])
	// 		panic("strdup");
	// 	i++;
	// }
	// new_env[i] = ft_strdup(str);
	// if (!new_env[i])
	// 	panic("strdup");
	// new_env[i + 1] = NULL;
	// free(data->env);
	// data->env = new_env;
}

int check_symbols(char *str)
{
	int i;

	i = 0;
	if (str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z')
		return (1);
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_' && str[i] != '='
			&& str[i] != '"' && str[i] != '$')
			return (1);
		i++;
	}
	return (0);
}

char *add_quotes(char *str)
{
	char *new_str;
	int i;
	int len;

	i = 0;
//	printf("jjsdsdsjjsdsdasdsa   %s\n", str);

	len = ft_strlen(str);
	new_str = malloc((len + 3) * sizeof(char));
	if (!new_str)
		panic("malloc");
	while (str[i] != '=')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '=';
	i++;
	new_str[i] = '"';
	i++;
	while (str[i - 1] != '\0')
	{
		new_str[i] = str[i - 1];
		i++;
	}
	new_str[i] = '"';
	new_str[i + 1] = '\0';
//	printf("jjsdsdsjj   %s\n", new_str);

	return (new_str);
}

int check_open_quotes(char *str)
{
	int i;
	int open;

	i = 0;
	open = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			open++;
		i++;
	}
	if (open % 2 != 0)
		return (1);
	return (0);
}

char *remove_quotes_in_the_middle(char *str)
{
	char *new_str;
	int i;
	int j;

	i = 0;
	j = 0;
	new_str = malloc((ft_strlen(str) - 1) * sizeof(char));
	if (!new_str)
		panic("malloc");
	while (str[i] != '\0')
	{
		if (str[i] != '"')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
//	printf("jjjjjj   %s\n", new_str);
	return (new_str);
}

char *if_one_quote(char *str)
{
	char *new_str;
//	int i;
	int open_quotes;
	char *buffer;

	open_quotes = check_open_quotes(str);	
//	i = 0;
	while (open_quotes != 0)
	{
		buffer = readline("> ");
		if (!buffer)
			return (NULL);
		new_str = ft_strjoin(str, buffer);
		if (!new_str)
			panic("strjoin");
		free(str);
		str = new_str;
		open_quotes = check_open_quotes(str);
		free(buffer);
	}
	return (str);
}

void export_no_args(t_data *data)
{
	t_var *temp;
//	int i;
//	int out_fd;
	char *tmp;
//	i = 0;
//	sort_env(data);
	temp = data->env_var;
	while (temp)
	{
		if (temp->key)
		{
			tmp = add_quotes(temp->key);
			printf("declare -x %s", tmp);
			printf("=\"%s\"\n", temp->val);
			free(tmp);
		}
		temp = temp->next;
	}
	// {
	// 	tmp = add_quotes(data->env[i]);
	// 	printf("declare -x %s\n", tmp);
	// 	free(tmp);
	// 	i++;
	// }
}

int ft_export(t_data *data, t_cmd *node)
{
	int i;

	// if (node->left == NULL)
	// {
		if(node->args[1] == NULL)
		{
			export_no_args(data);
			return (0);
		}
		i = 1;
		while (node->args[i] != NULL)
		{
			if (check_symbols(node->args[i]) == 1)
			{
				ft_putstr_fd("minishell: export: ", STDERR_FILENO); 
				ft_putstr_fd(node->args[i], STDERR_FILENO);
				ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
				return (1);
			}
			if (ft_strchr(node->args[i], '=') != NULL)
			{
				if (check_open_quotes(node->args[i]) == 1)
				{
					node->args[i] = if_one_quote(node->args[i]);
					if (!node->args[i])
						return (0);
				}
			remove_quotes_in_the_middle(node->args[i]);
	//		node->cmd_args[i] = add_quotes(node->cmd_args[i]);
			}
			add_to_env(node->args[i], data);
			i++;
		}
	return (0);
//	}
}
