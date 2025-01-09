#include "../minishell.h"

int get_old_pwd_line(t_data *data)
{
	int i;

	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], "OLDPWD=", 7) == 0)
			return (i);
		i++;
//	printf("old  %s \n", data->env[i]);
	}
	return (-1);
}

int get_pwd_line(t_data *data)
{
	int i;

	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char *get_pwd(t_data *data)
{
	int i;
	char *pwd;

	pwd = NULL;
	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
		{
			pwd = ft_strdup(data->env[i] + 4);
			if(!pwd)
			{
				panic("strdup");
				return (NULL);
			}
		}
		i++;
	}
	return pwd;
}

char *get_home(t_data *data)
{
	int i;
	char *pwd;

	pwd = NULL;
	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], "HOME=", 5) == 0)
		{
			pwd = ft_strdup(data->env[i] + 5);
			if(!pwd)
			{
				panic("strdup");
				return (NULL);
			}
		}
		i++;
	}
	return pwd;
}


void change_old_pwd(t_data *data)
{
	char *pwd;
	int old_pwd_line;

	pwd = get_pwd(data);
	old_pwd_line = get_old_pwd_line(data);
	if (!pwd || old_pwd_line == -1)
		panic("pwd error!");

	free(data->env[old_pwd_line]);
	data->env[old_pwd_line] = ft_strjoin("OLDPWD=", pwd);
	if (!data->env[old_pwd_line])
		panic("strdup");
	printf("old  %s \n", data->env[old_pwd_line]);
	free(pwd);
}

void change_pwd(t_data *data, t_cmd_node *node, char *pwd)
{
	int pwd_line;
	char *temp;
	char *temp2;

	pwd_line = get_pwd_line(data);
	temp = ft_strdup(data->env[pwd_line]);
	temp2 = ft_strjoin(temp, "/");
	free(data->env[pwd_line]);
	printf("new abs %d \n", node->abs_path);
	
	if (node->abs_path == 1)
		data->env[pwd_line] = ft_strjoin("PWD=", node->cmd_args[1]);
	else
		data->env[pwd_line] = ft_strjoin(temp2, pwd);
	if (!data->env[pwd_line])
		panic("strjoin");
	printf("new  %s \n", data->env[pwd_line]);

	free(temp);
	free(temp2);
}

void check_abs_path(t_cmd_node *node)
{
	if (node->cmd_args[1])
	{
		if (node->cmd_args[1][0] == '/')
			node->abs_path = 1;
		else
			node->abs_path = 0;
	}
}

int check_cd(t_cmd_node *node)
{
	if (ft_strncmp(node->cmd_args[0], "cd", 2) == 0 && ft_strlen(node->cmd_args[0]) == 2)
	{
		node->cd = 1;
		return (1);
	}
	else
	{
		node->cd = 0;
		return (0);
	}
}

void cd_home(t_data *data, t_cmd_node *node, char *pwd)
{
	char *home;

	home = get_home(data);
	if (chdir(home) == -1)
		perror("cd");
	change_old_pwd(data);
	change_pwd(data, node, home);
	printf(" > %s\n", "~");
	free(home);
}

void cd_prev(t_data *data, t_cmd_node *node)
{
	char *pwd;
	char *old_pwd;
	int pwd_line;
	int old_pwd_line;

	pwd_line = get_pwd_line(data);
	pwd = get_pwd(data);
	old_pwd_line = get_old_pwd_line(data);

	old_pwd = ft_strdup(data->env[old_pwd_line] + 7);
	printf(" wwwww> %s   %s\n", pwd, old_pwd);
	if (!pwd || !old_pwd || pwd_line == -1 || old_pwd_line == -1)
		panic("pwd error!");

	if (chdir(old_pwd) == -1)
		perror("cd");
	change_old_pwd(data);
	change_pwd(data, node, old_pwd);
	printf(" > %s\n", data->env[pwd_line] + 4);
	free(pwd);
}

// char *dir_join(t_data *data, char *path, int pwd_line)
// {
// 	char *tmp;
// 	tmp = ft_strjoin(data->)

// }
void cd_dir(t_data *data, t_cmd_node *node)
{
	char *pwd;
	char *old_pwd;
	int pwd_line;
	int old_pwd_line;
	
	pwd_line = get_pwd_line(data);
	pwd = get_pwd(data);
	old_pwd_line = get_old_pwd_line(data);
	old_pwd = ft_strdup(data->env[old_pwd_line] + 7);
	if (!pwd || !old_pwd || pwd_line == -1 || old_pwd_line == -1)
		panic("pwd error!");
	check_abs_path(node);
	// if(node->abs_path == 1)
	// {
		if (chdir(node->cmd_args[1]) == -1)
			perror("cd");
		else
		{
			change_old_pwd(data);
			change_pwd(data, node, node->cmd_args[1]);
			printf(" > %s\n", data->env[pwd_line] + 4);
		}
	// }
	free(old_pwd);
	free(pwd);
}

void changedir(t_data *data, t_cmd_node *node)
{
	char *pwd;
	int old_pwd_line;
	int pwd_line;
	char *old_pwd;

	check_abs_path(node);
	pwd = get_pwd(data);
	old_pwd_line = get_old_pwd_line(data);
	pwd_line = get_pwd_line(data);
	old_pwd = ft_strdup(data->env[old_pwd_line] + 7);
	if (!pwd || !old_pwd || pwd_line == -1 || old_pwd_line == -1)
		panic("pwd error!");

	if (get_arr_lines(node->cmd_args) > 2)
	{
		printf("cd: too many arguments\n");
		return ;
	}	
	if (check_cd(node))
	{
			if (!node->left)
			{
				if (node->cmd_args[1] == NULL || ft_strncmp(node->cmd_args[1], "~", 2) == 0)
					cd_home(data, node, pwd);
				else if (ft_strncmp(node->cmd_args[1], "-", 1) == 0)
					cd_prev(data, node);
				else
					cd_dir(data, node);
			}
		}	
		free(old_pwd);
		if (pwd)
			free(pwd);
}
