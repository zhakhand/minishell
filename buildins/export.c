
#include "../minishell.h"

void sort_env(t_data *data)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	while (data->env[i] != NULL)
	{
		j = i + 1;
		while (data->env[j] != NULL)
		{
			if (ft_strncmp(data->env[i], data->env[j], ft_strlen(data->env[i])) > 0)
			{
				tmp = data->env[i];
				data->env[i] = data->env[j];
				data->env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void add_to_env(char *str, t_data *data)
{
	int i;
	int len;
	char **new_env;

	i = 0;
	len = get_arr_lines(data->env);
	new_env = malloc((len + 2) * sizeof(char *));
	if (!new_env)
		panic("malloc");
	while (data->env[i] != NULL)
	{
		new_env[i] = ft_strdup(data->env[i]);
		if (!new_env[i])
			panic("strdup");
		i++;
	}
	new_env[i] = ft_strdup(str);
	if (!new_env[i])
		panic("strdup");
	new_env[i + 1] = NULL;
	free(data->env);
	data->env = new_env;
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

void export_no_args(t_data *data, t_cmd_node *node)
{
	int i;
//	int out_fd;
	char *tmp;
	i = 0;
	sort_env(data);
	// if (ft_strncmp(node->redirects->type, ">", 1) == 0)
	// {
	// 	out_fd = open(node->redirects->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	// 	if (out_fd == -1)
	// 		panic("outfile");
	// 	if (dup2(out_fd, STDOUT_FILENO) == -1)
	// 		panic("dup2");
	// 	close(out_fd);
	// }
	while (data->env[i] != NULL)
	{
		tmp = add_quotes(data->env[i]);
		printf("declare -x %s\n", tmp);
		free(tmp);
		i++;
	}
}

void ft_export(t_data *data, t_cmd_node *node)
{
	int i;

	// if (node->left == NULL)
	// {
		if(node->cmd_args[1] == NULL)
		{
			export_no_args(data, node);
			return ;
		}
		i = 1;
		while (node->cmd_args[i] != NULL)
		{
			if (check_symbols(node->cmd_args[i]) == 1)
			{
				printf("minishell: export: `%s': not a valid identifier\n", node->cmd_args[i]);
				return ;
			}
			if (ft_strchr(node->cmd_args[i], '=') != NULL)
			{
				if (check_open_quotes(node->cmd_args[i]) == 1)
				{
					node->cmd_args[i] = if_one_quote(node->cmd_args[i]);
					if (!node->cmd_args[i])
						return ;
				}
			remove_quotes_in_the_middle(node->cmd_args[i]);
	//		node->cmd_args[i] = add_quotes(node->cmd_args[i]);
			}
			add_to_env(node->cmd_args[i], data);
			i++;
		}
//	}
}

// void export_to_pipe(t_data *data, t_cmd_node *node)
// {
// //	int i;
// 	int out_fd;
// 	int fds[2];
// //	char *tmp;
// //	i = 0;
// 	sort_env(data);
// 	if (node->left != NULL)
// 	{
// 		if (pipe(fds) == -1)
// 			panic("pipe err");
// 	}
// 	if (fork() == 0)
// 	{
// 		if (node->out_file != NULL)
// 		{
// 			out_fd = open(node->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 			if (out_fd == -1)
// 				panic("outfile");
// 			if (dup2(out_fd, STDOUT_FILENO) == -1)
// 				panic("dup2");
// 			close(out_fd);
// 		}
// 		if (node->left != NULL)
// 		{
// 			if (dup2(fds[1], STDOUT_FILENO) == -1)
// 				panic("dup2");
// 			close(fds[1]);
// 			close(fds[0]);
// 			ft_export(data, node);
// 			run_pipe(data, node->left, data->env);
// 		}
// 		waitpid(0, NULL, 0);
// 	}
// 	else
// 	{
// 		if (node->left != NULL)
// 		{
// 			if (dup2(fds[1], STDOUT_FILENO) == -1)
// 				panic("dup2");
// 			close(fds[1]);
// 			close(fds[0]);
// 			run_pipe(data, node->left, data->env);
// 		}
// 		waitpid(0, NULL, 0);
// 	}
// }
