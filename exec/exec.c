#include "../minishell.h"
//#include <cerrno>
#include <unistd.h>

void clear_path_arr(t_data *data)
{
	int i;

	i = 0;
	while (data->path_arr[i] != NULL)
	{
		free(data->path_arr[i]);
		i++;
	}
	free(data->path_arr);
}

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

int run_execve(t_cmd *cmd, char **envp, char *full_path) {
//    printf("full_path: %s\n", full_path);

	// Check if the command is a directory
	struct stat sb;
	if (stat(full_path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
//        ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		return 126;
	}
	// Check if the command exists
	if (!full_path || access(full_path, F_OK) == -1) {
//        ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return 127;
	}


	// Check if the command is executable
	if (access(full_path, X_OK) == -1) {
//        ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": Permission denied!\n", STDERR_FILENO);
		return 126;
	}
//execve(full_path, cmd->args, envp);
//    Execute the command
	if (execve(full_path, cmd->args, envp) == -1) {
		perror("execve");
		return 0;
	}

	return 0;
}

int run_pipe(t_data *data, t_cmd *cmd, char **envp)
{
	int fds[2];
	int prev_fd = STDIN_FILENO;
	int status;
	pid_t pid;

	while (cmd != NULL)
	{
		data->redir_err = 0;
    // printf("begin  %s  %s\n", cmd->args[0], cmd->redir->val);

		if (!check_parent_buildin(cmd))
		{
			data->err_no = exec_buildin(data, cmd);
			if (cmd->next == NULL)
				return (0);
		}
		// if(cmd->next != NULL)
		// {
		// 	printf("cmd->next->cmd %s\n", cmd->next->cmd);
		// 	return (data->err_no);
		// }
//         if (cmd->built_in == CD)
//         {
//             data->err_no = changedir(data, cmd);
// //            return data->err_no;
//             if(cmd->next != NULL)
//                 return (0);
//        }
//printf("err_no %d  %s\n", data->err_no, cmd->args[0]);
		// Создание пайпа
		if (cmd->next != NULL && pipe(fds) == -1)
			panic("pipe err");

		pid = fork();
		if (!cmd->next)
			data->last_pid = pid;
		if (pid == -1)
			panic("fork err");
		else if (pid == 0) // Дочерний процесс
		{
			// Перенаправляем ввод из предыдущей команды
			if (prev_fd != STDIN_FILENO)
			{
				if (dup2(prev_fd, STDIN_FILENO) == -1)
					panic("dup2 prev_fd");
				close(prev_fd);
			}

			// Обрабатываем редиректы (ввод и вывод)
			if (handle_redirects(cmd) == -1)
			{
				data->err_no = 1;
				data->redir_err = 1;
//            	panic("minishell: ");
				// return (0);
			}

			int check_redir = 0;
			if (cmd->redir && (cmd->redir->type == OUT || cmd->redir->type == APPEND))
				check_redir = 1;
			if (cmd->next != NULL && !check_redir)
			{
				close(fds[0]); // Закрываем конец для чтения
				if (dup2(fds[1], STDOUT_FILENO) == -1)
					panic("dup2 fds[1]");
				close(fds[1]);
			}
			if (!check_child_buildin(cmd) && data->redir_err == 0)
			{
			    data->err_no = exec_buildin(data, cmd);
			}
//			if (check_child_buildin(cmd))
//			
			else if (data->redir_err == 0)
			{
				data->path_arr = get_path_arr(envp);
				char *full_path = find_path(cmd->args[0], data->path_arr);
				data->err_no = run_execve(cmd, envp, full_path);
				free(full_path);
			}
			exit(data->err_no);
		}

		// Родительский процесс: закрываем дескрипторы
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		if (cmd->next != NULL)
		{
			close(fds[1]);    // Закрываем конец записи
			prev_fd = fds[0]; // Устанавливаем новый ввод для следующей команды
		}
		cmd = cmd->next;
	}

	// Ожидание завершения дочерних процессов
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			data->err_no = WEXITSTATUS(status);
	}
//    clear_path_arr(data);
	return (0);
}

