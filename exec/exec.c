
#include "../minishell.h"

void run(t_cmd_node *list, char **envp)
{
	char *full_path;

	full_path = find_path(list->cmd_args[0], envp);
//	printf("aaaaa   %s", full_path);
	if (execve(full_path, list->cmd_args, envp) == -1)
	{
		perror("fail");
	}
	
}

void run_fork(t_cmd_node *list, char **envp)
{
	char *full_path;
	int pid;

	full_path = find_path(list->cmd_args[0], envp);
	pid = fork();
	if (pid == 0)
	{
		if (execve(full_path, list->cmd_args, envp) == -1)
			{
				perror("fail");
			}
	}
	waitpid(pid, NULL, 0);
//	printf("aaaaa parent   %s", full_path);

}

int run_pipe(t_data *data, t_cmd *cmd, char **envp)
{
	char *full_path;
	int pid;
	int fds[2];


	pid = 0;
	if (data == NULL)
		return (-1);
//	printf("ex %s \n", cmd->built_in);
	
	full_path = find_path(cmd->args[0], data->path_arr);

	if (cmd->next != NULL && !cmd->redir)
	{
		if (pipe(fds) == -1)
			panic("pipe err");
		pid = fork();
	}
	if (pid == -1)
		panic("fork err");
	else if (pid == 0)
	{
		if (cmd->redir)
			handle_redirects(cmd);
		if (cmd->next != NULL && !cmd->redir)
		{
			close(fds[0]);
			if (dup2(fds[1], STDOUT_FILENO) == -1)
				panic("dup2");
			close(fds[1]);
		}
		if (!check_if_buildin(cmd))
		{
			exec_buildin(data, cmd);
	//		printf("buildin\n");
		}
		else
		{
//		printf("exec  %s\n", cmd->args[0]);
		if (execve(full_path, cmd->args, envp) == -1)
			panic("execveaaaaa fail2");
		else
			free(full_path);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (cmd->next != NULL && !cmd->redir)
		{
			close(fds[1]);
			if (dup2(fds[0], STDIN_FILENO) == -1)
				panic("dup2");
			close(fds[0]);
		}
	//		printf("ln %s\n", list->left->cmd_args[0]);
		if (cmd->next != NULL)
			run_pipe(data, cmd->next, envp);
	}
//	free_data(data);
	free(full_path);
	return (0);
}
