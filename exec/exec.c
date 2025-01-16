
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

// int run_pipe(t_data *data, t_cmd *cmd, char **envp)
// {
// 	char *full_path;
// 	int status;
// 	int pid;
// 	int fds[2];

// 	pid = 0;
// 	if (data == NULL)
// 		return (-1);
// 	full_path = find_path(cmd->args[0], data->path_arr);
// 	if (cmd->built_in == CD)
// 		data->err_no = changedir(data, cmd);
// 	if (cmd->redir)
// 		data->err_no = handle_redirects(cmd);
// //	printf("exec cd  %d\n", data->err_no);
// 	// if (cmd->next != NULL && !cmd->redir)
// 	// {
// 	if (pipe(fds) == -1)
// 		panic("pipe err");
// 	// }
// 	pid = fork();
// 	if (pid == -1)
// 		panic("fork err");
	
// //	 && !cmd->redir
// 	else if (pid == 0)
// 	{
// 		if (cmd->next != NULL)
// 		{
// 			close(fds[0]);
// 			if (dup2(fds[1], STDOUT_FILENO) == -1)
// 				panic("dup2");
// 			close(fds[1]);
// 		}
// 		if (!check_if_buildin(cmd))
// 		{
// 			data->err_no = exec_buildin(data, cmd);
// 	//		printf("buildin\n");
// 		}
// 		else
// 		{
// //		printf("exec  %s\n", cmd->args[0]);
// 		if (execve(full_path, cmd->args, envp) == -1)
// 			panic("execveaaaaa fail2");
// 		else
// 			free(full_path);
// 		}
// 	}
// 	// else
// 	// {
// 	waitpid(pid, &status, 0);
// 	if (WIFEXITED(status)) {
//     	data->err_no = WEXITSTATUS(status); // Сохраняем код возврата
// }
// //		 && !cmd->redir
// 	if (cmd->next != NULL)
// 	{
// 		close(fds[1]);
// 		if (dup2(fds[0], STDIN_FILENO) == -1)
// 			panic("dup2");
// 		close(fds[0]);
// 	}
// 	//		printf("ln %s\n", list->left->cmd_args[0]);

// //	}
// 	if (cmd->next != NULL)
// 		run_pipe(data, cmd->next, envp);
// 	free(full_path);
// //	data->err_no = 0;
// //	printf("before ex  %d\n", data->err_no);
// 	return (data->err_no);
// //	free_data(data);
// }

int run_execve(t_cmd *cmd, char **envp, char *full_path)
{
	if (!full_path || access(full_path, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return 127;
	}

	if (access(full_path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		return 126;
	}

	if (execve(full_path, cmd->args, envp) == -1)
	{
		if (errno == EISDIR)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			return 126;
		}
		perror("execve fail");
		return 1;
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
		if(cmd->built_in == CD)
		{
			data->err_no = changedir(data, cmd);
			return data->err_no;
		}
		// Настраиваем пайп, если есть следующая команда
		if (cmd->next != NULL && pipe(fds) == -1)
			panic("pipe err");

		// Проверяем, является ли команда билдином
		if (cmd->redir){

			if (handle_redirects(cmd) == -1)
				panic("Failed to handle redirects");
		}

			// Обработка редиректов в билдинах
			// Выполнение билдина в родительском процессе
		else
		{
			pid = fork();
			if (pid == -1)
				panic("fork err");
			else if (pid == 0)
			{
				// Дочерний процесс

				// Перенаправляем ввод, если нужно
				if (prev_fd != STDIN_FILENO)
				{
					if (dup2(prev_fd, STDIN_FILENO) == -1)
						panic("dup2 prev_fd");
					close(prev_fd);
				}

				// Обработка редиректов
				if (handle_redirects(cmd) == -1)
					panic("Failed to handle redirects");
				// Перенаправляем вывод, если нужно
				if (cmd->next != NULL)
				{
					close(fds[0]); // Закрываем чтение из нового пайпа
					if (dup2(fds[1], STDOUT_FILENO) == -1)
						panic("dup2 fds[1]");
					close(fds[1]);
				}


		if (!check_if_buildin(cmd))
		{
			data->err_no = exec_buildin(data, cmd);
		}
		else
		{
				// Выполнение команды
				// if (check_if_buildin(cmd))
				// {
				char *full_path = find_path(cmd->args[0], data->path_arr);
				data->err_no = run_execve(cmd, envp, full_path);
				free(full_path);
				// }
				exit(data->err_no);
		}
			}
		}

		// Родительский процесс

		// Закрываем старые пайпы
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);

		if (cmd->next != NULL)
		{
			close(fds[1]); // Закрываем запись в новый пайп
			prev_fd = fds[0]; // Устанавливаем новый ввод для следующей команды
		}

		cmd = cmd->next;
	}

	// Ожидаем завершения всех дочерних процессов
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			data->err_no = WEXITSTATUS(status);
	}

	return data->err_no;
}



// int run_pipe(t_data *data, t_cmd *cmd, char **envp)
// {
// 	int fds[2];
// 	int prev_fd = STDIN_FILENO;
// 	int status;
// 	char *full_path;
// 	pid_t pid;

// 	while (cmd != NULL)
// 	{
// 		full_path = find_path(cmd->args[0], data->path_arr);
// 		// Создаем пайп, если есть следующая команда./
// 		if (cmd->next != NULL)
// 		{
// 			if (pipe(fds) == -1)
// 				panic("pipe err");
// 		}
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			panic("fork err");
// 		}
// 		else if (pid == 0)
// 		{
// 			// В дочернем процессе
// 			// Если есть предыдущий пайп, перенаправляем ввод
// 			if (prev_fd != STDIN_FILENO)
// 			{
// 				if (dup2(prev_fd, STDIN_FILENO) == -1)
// 					panic("dup2 prev_fd");
// 				close(prev_fd);
// 			}

// 			// Если есть следующий пайп, перенаправляем вывод
// 			if (cmd->next != NULL)
// 			{
// 				close(fds[0]); // Закрываем чтение из нового пайпа
// 				if (dup2(fds[1], STDOUT_FILENO) == -1)
// 					panic("dup2 fds[1]");
// 				close(fds[1]);
// 			}
// 			if (cmd->redir)
// 			{
// 				if (handle_redirects(cmd) == -1)
// 					panic("redirect fail");
// 			}
// 			// Выполняем команду
// 			if (!check_if_buildin(cmd))
// 			{
// 				data->err_no = exec_buildin(data, cmd);
// 			}
// 			else
// 			{
// 				if (execve(full_path, cmd->args, envp) == -1)
// 					panic("execve fail");
// 			}
// 		}
// 		// Родительский процесс
// 		// Закрываем старые пайпы
// 		if (prev_fd != STDIN_FILENO)
// 			close(prev_fd);
// 		if (cmd->next != NULL)
// 		{
// 			close(fds[1]); // Закрываем запись в новый пайп
// 			prev_fd = fds[0]; // Устанавливаем новый ввод для следующей команды
// 		}
// 		// НЕ ждем завершения дочернего процесса здесь
// 		cmd = cmd->next;
// 		free(full_path);
// 	}
// 	// Ждём все дочерние процессы после завершения всех команд
// 	while (waitpid(-1, &status, 0) > 0)
// 	{
// 		if (WIFEXITED(status))
// 			data->err_no = WEXITSTATUS(status);
// 	}

// 	return data->err_no;
// }

