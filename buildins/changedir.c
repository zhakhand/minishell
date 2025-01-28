#include "../minishell.h"
#include <time.h>

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
			//			return (EXIT_SUCCESS);
			//			break
		}
		temp = temp->next;
	}
	//	data->env_var = temp;
	free(data->pwd);
	data->pwd = ft_strdup(pwd);
	free(pwd);
	return (0);
}

int change_old_pwd_in_env(t_data *data, char *pwd)
{
	t_var *temp;

	temp = data->env_var;
	while (temp)
	{
		if (ft_strncmp(temp->key, "OLDPWD", 7) == 0)
		{
			free(temp->val);
			temp->val = ft_strdup(pwd);
			temp->is_valid = 1;
			if (!temp->val)
				return (EXIT_FAILURE);
			//			return (EXIT_SUCCESS);
		}
		temp = temp->next;
	}
	//	data->env_var = temp;
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
		{
			return (temp->val);
		}
		temp = temp->next;
	}
	return (NULL);
}

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

int cd_home(t_data *data)
{
	char *home;

	home = get_home(data);
	if (!home)
		panic("home error!");
	if (chdir(home) == -1)
		perror("home: No such file or directory");
	change_old_pwd_in_env(data, data->pwd);
	change_pwd_in_env(data, getcwd(NULL, 0));
	//	printf(" > %s\n", "~");
	//	free(home);
	return (0);
}

int cd_prev(t_data *data)
{
	char *pwd;
	char *old_pwd;

	pwd = ft_strdup(data->pwd);
	old_pwd = ft_strdup(data->old_pwd);
	if (!pwd || !old_pwd)
		panic("pwd error!");
	if (chdir(old_pwd) == -1)
		perror("cd");
	ft_putstr_fd(old_pwd, 1);
	ft_putstr_fd("\n", 1);
	change_old_pwd_in_env(data, pwd);
	change_pwd_in_env(data, getcwd(NULL, 0));
	//	printf(" > %s\n", data->old_pwd);
	free(pwd);
	free(old_pwd);
	return (0);
}

// char *dir_join(t_data *data, char *path, int pwd_line)
// {
// 	char *tmp;
// 	tmp = ft_strjoin(data->)

// }

int cd_up(t_data *data, t_cmd *node)
{
	char *pwd;
//	char *old_pwd;
	char *tmp;
	char *tmp2;
	int i;
	// printf(" p> %s\n", data->pwd);

	if (ft_strcmp(data->pwd, "/") == 0 || ft_strcmp(data->pwd, "/home") == 0)
		return (0);
	tmp2 = NULL;
	pwd = ft_strdup(data->pwd);
	i = ft_strlen(pwd);
	// if(data->old_pwd)
	// 	old_pwd = ft_strdup(data->old_pwd);
	if (!pwd)
		panic("pwd error!");
	while (pwd[i] != '/')
		i--;
	tmp = ft_substr(pwd, 0, i);
	if (!tmp)
		panic("strdup1");
//	 printf(" > %s\n", node->args[1]);
	if (node->args[1][2] && node->args[1][2] == '/' && ft_strlen(node->args[1]) > 2)	
	{
		tmp2 = ft_substr(node->args[1], 3, ft_strlen(node->args[1]));
		if (!tmp2)
			panic("strdup2");
	}
	if (chdir(tmp) == -1)
	{
		perror("cd err");
		return (EXIT_FAILURE);
	}
	// data->old_pwd = ft_strdup(data->pwd);
	// data->pwd = getcwd(NULL, 0);
	// if (!data->old_pwd || !data->pwd)
	// 	panic("strdup");
	change_old_pwd_in_env(data, pwd);
	change_pwd_in_env(data, getcwd(NULL, 0));

	free(tmp);
	if (tmp2)
	{
		free(node->args[1]);
		node->args[1] = ft_strdup(tmp2);
		// printf("tmp %s\n", tmp2);
		changedir(data, node);
	}
	//	free(tmp2);

	return (0);
}

int cd_dir(t_data *data, t_cmd *node)
{
	char *pwd;
	//char *old_pwd;

	//	printf(" aaaa> %s\n", node->args[1]);
	pwd = ft_strjoin(data->pwd, node->args[1]);
	// if(data->old_pwd)
	// 	old_pwd = ft_strdup(data->old_pwd);
	if (!pwd)
		panic("pwd error!");
	check_abs_path(node);
	// if(node->abs_path == 1)
	// {
	if (chdir(node->args[1]) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(node->args[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	else
	{
		change_old_pwd_in_env(data, data->pwd);
		change_pwd_in_env(data, getcwd(NULL, 0));
		//			printf(" > %s\n", data->pwd);
	}
	// }
	free(pwd);
	return (0);
}

int changedir(t_data *data, t_cmd *node)
{
	int res;
	res = -1;
	if (node->prev)
	{
		return (0);
	}
	check_abs_path(node);
	if (node->args && node->args[1] && node->args[2])
	{
		ft_putmsg_fd(MSH, "cd", T_M_A, STDERR_FILENO);
		// ft_putstr_fd("minishell: ", STDERR_FILENO);
		// ft_putstr_fd("cd: ", STDERR_FILENO);
		// ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	// if (check_cd(node))
	// {
	if (!node->next)
	{
	if (node->args[1] == NULL || ft_strncmp(node->args[1], "~", 2) == 0)
		res = cd_home(data);

	else if (ft_strncmp(node->args[1], "..", 2) == 0
		|| (ft_strncmp(node->args[1], "../", 3) == 0))
		res = cd_up(data, node);
	else if (ft_strncmp(node->args[1], ".", 1) == 0)
		res = 0;
	else if (ft_strncmp(node->args[1], "-", 1) == 0)
		res = cd_prev(data);
	else
		res = cd_dir(data, node);
	//			}
	}
	return (res);
}