#include "../minishell.h"

// int get_old_pwd_line(t_data *data)
// {
// 	int i;

// 	i = 0;
// 	while (data->env[i] != NULL)
// 	{
// 		if (ft_strncmp(data->env[i], "OLDPWD=", 7) == 0)
// 			return (i);
// 		i++;
// //	printf("old  %s \n", data->env[i]);
// 	}
// 	return (-1);
// }

// int get_pwd_line(t_data *data)
// {
// 	int i;

// 	i = 0;
// 	while (data->env[i] != NULL)
// 	{
// 		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// char *get_pwd(t_data *data)
// {
// 	int i;
// 	char *pwd;

// 	pwd = NULL;
// 	i = 0;
// 	while (data->env[i] != NULL)
// 	{
// 		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
// 		{
// 			pwd = ft_strdup(data->env[i] + 4);
// 			if(!pwd)
// 			{
// 				panic("strdup");
// 				return (NULL);
// 			}
// 		}
// 		i++;
// 	}
// 	return pwd;
// }

int change_pwd_in_env(t_data *data, char *pwd)
{
	t_var *temp;

	temp = data->env_var;
	while (temp)
	{
		if (ft_strncmp(temp->key, "PWD", 4) == 0)
		{
			free(temp->val);
			temp->val = ft_strdup(pwd);
			if (!temp->val)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		temp = temp->next;
	}
	data->env_var = temp;
	free(data->pwd);
	data->pwd = ft_strdup(pwd);
	return (0);
}

int change_old_pwd_in_env(t_data *data, char *pwd)
{
	t_var *temp;

	temp = data->env_var;
	while (temp)
	{
		if (ft_strncmp(temp->key, "OLD_PWD", 8) == 0)
		{
			free(temp->val);
			temp->val = ft_strdup(pwd);
			if (!temp->val)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		temp = temp->next;
	}
	data->env_var = temp;
	free(data->old_pwd);
	data->old_pwd = ft_strdup(pwd);
	return (0);
}

char *get_home(t_data *data)
{
	t_var *temp;

	temp = data->env_var;
	while (temp)
	{
		if (ft_strncmp(temp->key, "HOME", 4) == 0)
			return (temp->val);
		temp = temp->next;
	}
	return (NULL);
	// int i;
	// char *pwd;

	// pwd = NULL;
	// i = 0;
	// while (data->env[i] != NULL)
	// {
	// 	if (ft_strncmp(data->env[i], "HOME=", 5) == 0)
	// 	{
	// 		pwd = ft_strdup(data->env[i] + 5);
	// 		if(!pwd)
	// 		{
	// 			panic("strdup");
	// 			return (NULL);
	// 		}
	// 	}
	// 	i++;
	// }
	//return pwd;
}


// void change_old_pwd(t_data *data)
// {
// 	char *pwd;
// 	int old_pwd_line;

// 	pwd = get_pwd(data);
// 	old_pwd_line = get_old_pwd_line(data);
// 	if (!pwd || old_pwd_line == -1)
// 		panic("pwd error!");

// 	free(data->env[old_pwd_line]);
// 	data->env[old_pwd_line] = ft_strjoin("OLDPWD=", pwd);
// 	if (!data->env[old_pwd_line])
// 		panic("strdup");
// 	printf("old  %s \n", data->env[old_pwd_line]);
// 	free(pwd);
// }

// void change_pwd(t_data *data, t_cmd_node *node, char *pwd)
// {
// 	int pwd_line;
// 	char *temp;
// 	char *temp2;

// 	pwd_line = get_pwd_line(data);
// 	temp = ft_strdup(data->env[pwd_line]);
// 	temp2 = ft_strjoin(temp, "/");
// 	free(data->env[pwd_line]);
// 	printf("new abs %d \n", node->abs_path);
	
// 	if (node->abs_path == 1)
// 		data->env[pwd_line] = ft_strjoin("PWD=", node->cmd_args[1]);
// 	else
// 		data->env[pwd_line] = ft_strjoin(temp2, pwd);
// 	if (!data->env[pwd_line])
// 		panic("strjoin");
// 	printf("new  %s \n", data->env[pwd_line]);

// 	free(temp);
// 	free(temp2);
// }

void check_abs_path(t_cmd *node)
{
	if (node->args[1])
	{
		if (node->args[1][0] == '/')
			node->abs_path = 1;
		else
			node->abs_path = 0;
	}
}

// int check_cd(t_cmd *node)
// {
// 	if (ft_strncmp(node->cmd[0], "cd", 2) == 0 && ft_strlen(node->cmd_args[0]) == 2)
// 	{
// 		node->cd = 1;
// 		return (1);
// 	}
// 	else
// 	{
// 		node->cd = 0;
// 		return (0);
// 	}
// }

int cd_home(t_data *data)
{
	char *home;

	home = get_home(data);
	if (chdir(home) == -1)
		perror(" No such file or directory");
	change_old_pwd_in_env(data, data->pwd);
	change_pwd_in_env(data, home);
	printf(" > %s\n", "~");
	free(home);
	return (EXIT_SUCCESS);
}

int cd_prev(t_data *data)
{
	char *pwd;
	char *old_pwd;

	pwd = data->pwd;
	old_pwd = data->old_pwd;
//	printf(" wwwww> %s   %s\n", pwd, old_pwd);
	if (!pwd || !old_pwd)
		panic("pwd error!");

	if (chdir(old_pwd) == -1)
		perror("cd");
	change_old_pwd_in_env(data, pwd);
	change_pwd_in_env(data, old_pwd);
	printf(" > %s\n", data->old_pwd);
	free(pwd);
	free(old_pwd);
	return (EXIT_SUCCESS);
}

// char *dir_join(t_data *data, char *path, int pwd_line)
// {
// 	char *tmp;
// 	tmp = ft_strjoin(data->)

// }
int cd_dir(t_data *data, t_cmd *node)
{
	char *pwd;
	char *old_pwd;
	
	pwd = ft_strdup(data->pwd);
	old_pwd = ft_strdup(data->old_pwd);
	if (!pwd || !old_pwd)
		panic("pwd error!");
	check_abs_path(node);
	// if(node->abs_path == 1)
	// {
		if (chdir(node->args[1]) == -1)
			perror(" No such file or directory");
		else
		{
			change_old_pwd_in_env(data, data->pwd);
			change_pwd_in_env(data, node->args[1]);
			printf(" > %s\n", data->pwd);
		}
	// }
	free(old_pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

int changedir(t_data *data, t_cmd *node)
{
	int res;

	res = -1;
	check_abs_path(node);

	if (node->args[2])
	{
		printf("cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	// if (check_cd(node))
	// {
			if (!node->next)
			{
				if (node->args[1] == NULL || ft_strncmp(node->args[1], "~", 2) == 0)
					res = cd_home(data);
				else if (ft_strncmp(node->args[1], "-", 1) == 0)
					res = cd_prev(data);
				else
					res = cd_dir(data, node);
			}
		// }	
		return (res);
}
