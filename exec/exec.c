
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

void run_pipe(t_data *data, t_cmd_node *list, char **envp)
{
	char *full_path;
	int pid;
	int fds[2];

	printf(" arg0 %s red %s\n", list->cmd_args[0], list->redirects->file);

	if (list == NULL)
		return ;
//	printf(" %s \n", full_path, list->cmd_args[0]);
	
	if (list->redirects)
	
		handle_redirects(list);
	full_path = find_path(list->cmd_args[0], envp);
	printf("full_path  %s   arg0 %s \n", full_path, list->cmd_args[0]);
	if (list->left != NULL && !list->redirects)
	{
		if (pipe(fds) == -1)
			panic("pipe err");
	}
	pid = fork();
	if (pid == -1)
		panic("fork err");
	else if (pid == 0)
	{
		if (list->left != NULL && !list->redirects)
		{
			close(fds[0]);
			if (dup2(fds[1], STDOUT_FILENO) == -1)
				panic("dup2");
			close(fds[1]);
		}
		printf("exec  %s\n", list->cmd_args[0]);
		if (execve(full_path, list->cmd_args, envp) == -1)
			panic("execveaaaaa fail2");
		// if (check_if_buildin(data, list) == 1)
		// {
		// 	// printf("buildin\n");
		// 	free_data(data);

		// 	exit(0);
		// }
		else
		{
			// full_path = find_path(list->cmd_args[0], envp);
			free(full_path);
			free_data(data);
			free_node_2(list);
		}
//		}

	}
	
	else
	{
	waitpid(pid, NULL, 0);
	if (list->left != NULL && !list->redirects)
	{
		close(fds[1]);
		if (dup2(fds[0], STDIN_FILENO) == -1)
			panic("dup2");
		close(fds[0]);
//			}
	}
	if (check_if_buildin(data, list) == 1)
	{
		printf("buildin\n");
		// free_data(data);
		// free_node_2(list);
//			return ;
//			exit(0);
	}
//		printf("ln %s\n", list->left->cmd_args[0]);
	if (list->left != NULL)
		run_pipe(data, list->left, envp);
}
//	free_data(data);
}
