
#include "../minishell.h"

int add_to_env_end(t_data *data, char *str)
{
	t_var *new_var;
	int		i;

	i = 0;
	new_var = NULL;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == 0)
	{
		new_var = get_env_var(data, str);
		if (!new_var)
		{
			new_var = set_env_var(data, ft_strdup(str), "");
			new_var->is_valid = 0;
		}
		return (0);
	}
	else if (str[i] == '=' && !str[i + 1])
	{
		new_var = set_env_var(data, ft_substr(str, 0, i), "");
		new_var->is_valid = 1;
		return (0);
	}
	new_var = set_env_var(data, ft_substr(str, 0, i), str + i + 1);
	new_var->is_valid = 1;
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

char *add_quotes_to_val(char *str)
{
	char *new_str;
	int i;
	int len;

	len = ft_strlen(str);
	new_str = malloc((len + 4) * sizeof(char));
	if (!new_str)
		panic("malloc");
	new_str[0] = '=';
	new_str[1] = '"';
	i = 2;
	while (str[i - 2] != '\0')
	{
		new_str[i] = str[i - 2];
		i++;
	}
	new_str[i] = '"';
	new_str[i + 1] = '\0';
	return (new_str);
}

char **make_env_arr(t_data *data)
{
	char **res;
	t_var *temp;
	int i;
	char *tmp_val;

	temp = data->env_var;

	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	res = malloc((i + 1) * sizeof(char *));
	if (!res)
		panic("malloc");
	i = 0;
	temp = data->env_var;
	while (temp)
	{
		if (temp->is_valid == 1)
		{
			tmp_val = add_quotes_to_val(temp->val);
			res[i] = ft_strjoin(temp->key, tmp_val);
		}
		else
			res[i] = ft_strdup(temp->key);
		if (!res[i])
			panic("strjoin");
		if (tmp_val)
			free(tmp_val);
		tmp_val = NULL;
		i++;
		// res[i] = ft_strjoin(res[i], temp->val);
		// if (!res[i])
		// 	panic("strjoin");
		// if (res[i][ft_strlen(res[i]) - 1] == '=')
		// 	res[i] = add_quotes(res[i]);
		//
		//i++;// fix Katya
		temp = temp->next;
	}
	res[i] = NULL;
	return (res);
}

char **sort_env(char **arr)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	while (arr[i] != NULL)
	{
		j = i + 1;
		while (arr[j] != NULL)
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}

int add_to_env(char *str, t_data *data)
{
	t_var *new_var;
	// t_var *temp;
	int i;


	i = 0;
	// new_var = malloc(sizeof(t_var));
	// if (!new_var)
	// 	panic("malloc");
	while (str[i] != '=' && str[i] != '\0')
		i++;
	// new_var->key = ft_substr(str, 0, i);
	// new_var->val = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	// if (!new_var->key || !new_var->val)
	// 	panic("strdup");
	// new_var->next = NULL;
	// if (!data->env_var)
	// {
	// 	data->env_var = new_var;
	// 	return (0);
	// }
	// temp = data->env_var;
	// while (temp->next)
	// 	temp = temp->next;
	// temp->next = new_var;
	if (str[i] == 0)
	{
		new_var = get_env_var(data, str);
		if (!new_var)
		{
			new_var = set_env_var(data, str, "");
			new_var->is_valid = 0;
		}
		return (0);
	}
	else if (str[i] == '=' && !str[i + 1])
	{
		new_var = set_env_var(data, ft_substr(str, 0, i), "");
		new_var->is_valid = 1;
		return (0);
	}
	new_var = set_env_var(data, ft_substr(str, 0, i), str + i + 1);
	new_var->is_valid = 1;
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
	int flag;

//	printf("str   %s\n", str);
	i = 0;
	flag = 0;
	if (str[i] == '|')
		return (1);
	if (str[i] == '=')
		return (1);
	if (str[i] >= '0' && str[i] <='9' )
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			flag = 1;
			i++;
		}
		if (flag == 0 && str[i] == '-')
			return (1);
		if (flag == 1)
		{
//			printf("str[i]   %c\n", str[i]);
			// if (ft_isalnum(str[i]) == 0 && str[i] != '_' && str[i] != ' '
			// && str[i] != '"' && str[i] != '$' && str[i] != '-' && str[i] != '+')
			// return (1);
		}
		i++;
	}
	return (0);
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
		str = NULL;
		str = new_str;
		open_quotes = check_open_quotes(str);
		free(buffer);
		buffer = NULL;
	}
	return (str);
}

void export_no_args(t_data *data)
{
//	t_var *temp;
	int i;
	char **tmp;

	tmp = make_env_arr(data);
	tmp = sort_env(tmp);
	i = 0;
	while (tmp[i] != NULL)
	{
		printf("declare -x %s\n", tmp[i]);
		//free(tmp[i]);
		//tmp[i] = NULL;
		i++;
	}
	free_args(tmp);
	tmp = NULL;

//	sort_env(data);
	// temp = data->env_var;
	// while (temp)
	// {
	// 	if (temp->key)
	// 	{
	// 		tmp = add_quotes(temp->key);
	// 		printf("declare -x %s", tmp);
	// 		printf("=\"%s\"\n", temp->val);
	// 		free(tmp);
	// 	}
	// 	temp = temp->next;
	// }
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

	//  if (node->next == NULL)
	//  {
		if(node->args[1] == NULL)
		{
			export_no_args(data);
			return (0);
		}
		i = 1;
		if (check_symbols(node->args[1]) == 1)
		{
			ft_putstr_fd("export: `", STDERR_FILENO); 
			ft_putstr_fd(node->args[1], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (1);
		}
		while (node->args[i] != NULL)
		{
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
	//   if (node->next == NULL)
	//   {
			add_to_env_end(data, node->args[i]);
	//   }	
			i++;
		}
//	}
	return (0);
}
