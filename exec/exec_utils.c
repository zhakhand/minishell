/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:33:22 by oshcheho          #+#    #+#             */
/*   Updated: 2025/01/11 13:33:23 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void panic(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void ft_putmsg_fd(char *msg1, char *msg2, char *msg3, int fd)
{
	char *msg;
//	int len;
//	len = ft_strlen(msg1) + ft_strlen(msg2)
//		+ ft_strlen(msg3) + 1;

	msg = ft_strdup(msg1);
	if (!msg)
		panic("strdup");
	msg = ft_strjoin(msg, msg2);
	if (!msg)
		panic("strjoin");
	msg = ft_strjoin(msg, msg3);
	if (!msg)
		panic("strjoin"); 
	ft_putstr_fd(msg, fd);
	free(msg);
	msg = NULL;
}

int ft_edge_cases(t_data *data, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "") == 0 ||
		ft_strcmp(cmd->args[0], ".") == 0 ||
		ft_strcmp(cmd->args[0], "..") == 0 ||
		// ft_strcmp(cmd->args[0], "/") == 0 ||
		ft_strcmp(cmd->args[0], "//") == 0 ||
		ft_strcmp(cmd->args[0], "~") == 0)
	{
		data->err_no = 127;
		ft_putmsg_fd(MSH, cmd->args[0], C_N_F, STDERR_FILENO);
		return (1);
	}
	return (0);
}

int get_random_fd(t_data *data)
{
//	int fd;
	int fd[2];
	int pid;
	int temp_fd;
	char *temp;

	if (pipe(fd) == -1)
		panic("pipe");
	pid = fork();
	if (pid == -1)
		panic("fork");
	if (pid == 0)
	{
		close(fd[0]);
		close(fd[1]);
//		system("ls -l /proc/self/fd"); // List open file descriptors
		exit (0);	
	}
	else
	{
		close(fd[1]);
		temp = ft_strjoin("/tmp/", ft_itoa(pid));
		temp_fd = open(temp, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (temp_fd == -1)
			panic("open");
		
		free(temp);
	}
	data->temp_name = ft_strjoin("/tmp/", ft_itoa(pid));
	return (temp_fd);
}

char *get_temp_name(int pid)
{
	char *temp;

	temp = ft_strjoin("/tmp/", ft_itoa(pid));
	return (temp);
}