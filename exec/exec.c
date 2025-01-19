#include "../minishell.h"
//#include <cerrno>
#include <unistd.h>

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


//ORIGINAL RUN_EXECVE
// int run_execve(t_cmd *cmd, char **envp, char *full_path)
// {
// 	printf("full_path: %s\n", cmd->cmd);
// 	// if (cmd->cmd[0] == '.' && cmd->cmd[1] == '/')
// 	// 	if (chdir(cmd->args[0]) == 0)
// 	// 	{
// 	// 		chdir(data->pwd);
// 	// 		ft_putstr_fd("minishell: ", STDERR_FILENO);
// 	// 		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
// 	// 		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
// 	// 		return(126);
// 	// 	}
// 	// int acc = access(full_path, F_OK);
// 	// 	printf("acc %s %s %d\n", full_path, data->cmds->cmd, acc);
// 	if (!full_path || access(full_path, F_OK) == -1)
// 	{
		
// 		ft_putstr_fd("minishell: ", STDERR_FILENO);
// 		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
// 		ft_putstr_fd(": command not found\n", STDERR_FILENO);
// 		return 127;
// 	}
// 	if (access(full_path, X_OK) == -1)
// 	{
// 		ft_putstr_fd("minishell: ", STDERR_FILENO);
// 		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
// 		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
// 		return 126;
// 	}
// 	if (execve(full_path, cmd->args, envp) == -1)
// 	{
// 		// if (errno == EISDIR)
// 		// {
// 			ft_putstr_fd("minishell: ", STDERR_FILENO);
// 			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
// 			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
// 			return 126;
// 		// }
// 		// perror("execve fail");
// 		return 1;
// 	}

// 	return 0;
// }
// FROM COPILOT
// int run_pipe(t_data *data, t_cmd *cmd, char **envp) {
//     int fds[2];
//     int prev_fd = STDIN_FILENO;
//     int status;
//     pid_t pid;

//     while (cmd != NULL) {
//         if (cmd->built_in == CD) {
//             data->err_no = changedir(data, cmd);
//             return data->err_no;
//         }

//         if (cmd->next != NULL && pipe(fds) == -1)
//             panic("pipe err");

//         if (cmd->redir)
//             data->err_no = (handle_redirects(cmd) == -1);

//         printf("fd %d\n", prev_fd);
//                if (!check_if_buildin(cmd)) {
//                 printf("Before exec_buildin: prev_fd=%d, fds[0]=%d, fds[1]=%d\n", prev_fd, fds[0], fds[1]);
//                 data->err_no = exec_buildin(data, cmd);
//                 printf("After exec_buildin: prev_fd=%d, fds[0]=%d, fds[1]=%d\n", prev_fd, fds[0], fds[1]);
// 			   }
//         pid = fork();
//         if (pid == -1)
//             panic("fork err");
//         else if (pid == 0) {
//             // Child process
//             printf("prev_fd: %d, fds[0]: %d, fds[1]: %d %s\n", prev_fd, fds[0], fds[1], cmd->args[0]);

//             if (prev_fd != STDIN_FILENO) {
//                 if (dup2(prev_fd, STDIN_FILENO) == -1)
//                     panic("dup2 prev_fd");
//                 close(prev_fd);
//             }

//             if (cmd->next != NULL) {
//                 close(fds[0]);
//                 if (dup2(fds[1], STDOUT_FILENO) == -1)
//                     panic("dup2 fds[1]");
//                 close(fds[1]);
//             }

// //             else {
//                 char *full_path = find_path(cmd->args[0], data->path_arr);
//                 data->err_no = run_execve(cmd, envp, full_path);
//                 free(full_path);
//                 exit(data->err_no);
// //            }
//         } else {
//             // Parent process
//             printf("parent: prev_fd=%d, fds[0]=%d, fds[1]=%d\n", prev_fd, fds[0], fds[1]);

//             if (prev_fd != STDIN_FILENO)
//                 close(prev_fd);

//             if (cmd->next != NULL) {
//                 close(fds[1]);
//                 prev_fd = fds[0];
//             }

//             waitpid(pid, &status, 0);
//             printf("parent after wait: prev_fd=%d, fds[0]=%d, fds[1]=%d\n", prev_fd, fds[0], fds[1]);
//         }

//         cmd = cmd->next;
//     }

//     // Wait for all child processes to finish
//     while (waitpid(-1, &status, 0) > 0) {
//         if (WIFEXITED(status))
//             data->err_no = WEXITSTATUS(status);
//     }

//     return data->err_no;
// }

int run_execve(t_cmd *cmd, char **envp, char *full_path) {
//    printf("full_path: %s\n", full_path);

    // Check if the command is a directory
    struct stat sb;
    if (stat(full_path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(cmd->args[0], STDERR_FILENO);
        ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
        return 126;
    }

    // Check if the command exists
    if (!full_path || access(full_path, F_OK) == -1) {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(cmd->args[0], STDERR_FILENO);
        ft_putstr_fd(": command not found\n", STDERR_FILENO);
        return 127;
    }

    // Check if the command is executable
    if (access(full_path, X_OK) == -1) {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
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

// int run_pipe(t_data *data, t_cmd *cmd, char **envp)
// {
// 	int fds[2];
// 	int prev_fd = STDIN_FILENO;
// 	int status;
// 	pid_t pid;

// 	while (cmd != NULL)
// 	{
// 		if(cmd->built_in == CD)
// 		{
// 			data->err_no = changedir(data, cmd);
// 			return data->err_no;
// 		}
// 		if (cmd->next != NULL && pipe(fds) == -1)
// 			panic("pipe err");
// 		pid = fork();
// 		if (pid == -1)
// 			panic("fork err");
// 		else if (pid == 0)
// 		{
// 			if (prev_fd != STDIN_FILENO)
// 			{
// 				if (dup2(prev_fd, STDIN_FILENO) == -1)
// 					panic("dup2 prev_fd");
// 				close(prev_fd);
// 			}
// 			if (cmd->redir)
// 				data->err_no = (handle_redirects(cmd) == -1);
// 			// if (handle_redirects(cmd) == -1)
// 			// 	panic("minishell: ");
// 			if (cmd->next != NULL)
// 			{
// 				close(fds[0]); // Закрываем чтение из нового пайпа
// 				if (dup2(fds[1], STDOUT_FILENO) == -1)
// 					panic("dup2 fds[1]");
// 				close(fds[1]);
// 			}
// 			if (!check_if_buildin(cmd))
// 				data->err_no = exec_buildin(data, cmd);
// 			if (check_if_buildin(cmd))
// 			{
// 				char *full_path = find_path(cmd->args[0], data->path_arr);
// 				data->err_no = run_execve(cmd, envp, full_path);
// 				free(full_path);
// 			}
// 				exit(data->err_no);
// 		}
// 		if (prev_fd != STDIN_FILENO)
// 			close(prev_fd);

// 		if (cmd->next != NULL)
// 		{
// 			close(fds[1]); // Закрываем запись в новый пайп
// 			prev_fd = fds[0]; // Устанавливаем новый ввод для следующей команды
// 		}
// 		cmd = cmd->next;
// 	}
// 	while (waitpid(-1, &status, 0) > 0)
// 	{
// 		if (WIFEXITED(status))
// 			data->err_no = WEXITSTATUS(status);
// 	}
// 	return data->err_no;
// }
int run_pipe(t_data *data, t_cmd *cmd, char **envp)
{
    int fds[2];
    int prev_fd = STDIN_FILENO;
    int status;
    pid_t pid;

    while (cmd != NULL)
    {
        if (cmd->built_in == CD)
        {
            data->err_no = changedir(data, cmd);
            return data->err_no;
        }

        // Создание пайпа
        if (cmd->next != NULL && pipe(fds) == -1)
            panic("pipe err");

        pid = fork();
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
//            	panic("minishell: ");
				// return (0);
			}
			// Перенаправляем вывод в следующий пайп, если он есть
//				 printf("minishell: pipe\n");
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
//            printf("err_no %d\n", data->err_no);
            // Выполнение команды (builtin или execve)
            if (!check_if_buildin(cmd) && data->err_no == 0)
                data->err_no = exec_buildin(data, cmd);
            else if (check_if_buildin(cmd) && data->err_no == 0)
            {
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

    return (0);
}


//  ORIGINAL
// int run_pipe(t_data *data, t_cmd *cmd, char **envp)
// {
// 	int fds[2];
// 	int prev_fd = STDIN_FILENO;
// 	int status;
// 	pid_t pid;

// 	while (cmd != NULL)
// 	{

// 		if(cmd->built_in == CD)
// 		{
// 			data->err_no = changedir(data, cmd);
// 			return data->err_no;
// 		}
// 		// if (cmd->next != NULL)
// 		// {
// 		// 	close(fds[1]); // Закрываем запись в новый пайп
// 		// 	prev_fd = fds[0]; // Устанавливаем новый ввод для следующей команды
// 		// }
// 		if (cmd->redir)
// 			data->err_no = (handle_redirects(cmd) == -1);

// 		// Настраиваем пайп, если есть следующая команда
// 		if (cmd->next != NULL && pipe(fds) == -1)
// 			panic("pipe err");
// 		// if (cmd->next != NULL)
// 		// 	{
// 		// 		close(fds[0]); // Закрываем чтение из нового пайпа
// 		// 		if (dup2(fds[1], STDOUT_FILENO) == -1)
// 		// 			panic("dup2 fds[1]");
// 		// 		close(fds[1]);
// 		// }

// 		// Проверяем, является ли команда билдином
// //				return (-1);
// //				panic("Failed to handle redirects");

// 			// Обработка редиректов в билдинах
// 			// Выполнение билдина в родительском процессе
// 		// else
// 		// {
// 		pid = fork();
// 		if (pid == -1)
// 			panic("fork err");
// 		else if (pid == 0)
// 		{
// 			// Дочерний процесс

// 			// Перенаправляем ввод, если нужно
// 			if (prev_fd != STDIN_FILENO)
// 			{
// 				if (dup2(prev_fd, STDIN_FILENO) == -1)
// 					panic("dup2 prev_fd");
// 				close(prev_fd);
// 			}

// 			// Обработка редиректов
// //			data->err_no = handle_redirects(cmd);
// 			if (handle_redirects(cmd) == -1)
// 				panic("minishell: ");
// 			// Перенаправляем вывод, если нужно
// 			if (cmd->next != NULL)
// 			{
// 				close(fds[0]); // Закрываем чтение из нового пайпа
// 				if (dup2(fds[1], STDOUT_FILENO) == -1)
// 					panic("dup2 fds[1]");
// 				close(fds[1]);
// 		}

// 		if (!check_if_buildin(cmd))
// 		{
// 			data->err_no = exec_buildin(data, cmd);
// 		}

// 		// else
// 		// {
// 				// Выполнение команды
// 				if (check_if_buildin(cmd))
// 				{
// //					printf("%d\n", check_if_buildin(cmd));
// 				char *full_path = find_path(cmd->args[0], data->path_arr);
// 				data->err_no = run_execve(cmd, envp, full_path);
// 				free(full_path);
// 				}
// 				exit(data->err_no);
// 		// }
// 			}
// 		// }

// 		// Родительский процесс

// 		// Закрываем старые пайпы
// 		if (prev_fd != STDIN_FILENO)
// 			close(prev_fd);

// 		if (cmd->next != NULL)
// 		{
// 			close(fds[1]); // Закрываем запись в новый пайп
// 			prev_fd = fds[0]; // Устанавливаем новый ввод для следующей команды
// 		}

// 		cmd = cmd->next;
// 	}

// 	// Ожидаем завершения всех дочерних процессов
// 	while (waitpid(-1, &status, 0) > 0)
// 	{
// 		if (WIFEXITED(status))
// 			data->err_no = WEXITSTATUS(status);
// 	}

// 	return data->err_no;
// }


// int run_pipe(t_data *data, t_cmd *cmd, char **envp)
// {
//     int fds[2];
//     int prev_fd = STDIN_FILENO;
//     int status;
//     pid_t pid;

//     while (cmd != NULL)
//     {
//         printf("fd %d \n", prev_fd);
//         if(cmd->built_in == CD)
//         {
//             data->err_no = changedir(data, cmd);
//             return data->err_no;
//         }
//         // Настраиваем пайп, если есть следующая команда
//         if (cmd->next != NULL && pipe(fds) == -1)
//             panic("pipe err");

//         // Проверяем, является ли команда билдином
//         if (cmd->redir != NULL)
// {
//             data->err_no = (handle_redirects(cmd) == -1);
// //            return (-1);
// }
// //				panic("Failed to handle redirects");

//             // Обработка редиректов в билдинах
//             // Выполнение билдина в родительском процессе
//         // else
//         // {
//         pid = fork();
//         if (pid == -1)
//             panic("fork err");
//         else if (pid == 0)
//         {
//             // Дочерний процесс
//             printf("prev_fd: %d, fds[0]: %d, fds[1]: %d %s\n", prev_fd, fds[0], fds[1], cmd->args[0]);
//             // Перенаправляем ввод, если нужно
//             if (prev_fd != STDIN_FILENO)
//             {
//                 printf("fd in if %d\n", prev_fd);

//                 if (dup2(prev_fd, STDIN_FILENO) == -1)
//                     panic("dup2 prev_fd");
//                 close(prev_fd);
//             }

//             // Обработка редиректов
// //			data->err_no = handle_redirects(cmd);
//             if (handle_redirects(cmd) == -1)
//                 panic("minishell: ");
//             // Перенаправляем вывод, если нужно
//             if (cmd->next != NULL)
//             {
//                 close(fds[0]); // Закрываем чтение из нового пайпа
//                 if (dup2(fds[1], STDOUT_FILENO) == -1)
//                     panic("dup2 fds[1]");
//                 close(fds[1]);
//             }

//             if (!check_if_buildin(cmd))
//             {
//                 printf("Before exec_buildin: prev_fd=%d, fds[0]=%d, fds[1]=%d\n", prev_fd, fds[0], fds[1]);
//                 data->err_no = exec_buildin(data, cmd);
//                 printf("After exec_buildin: prev_fd=%d, fds[0]=%d, fds[1]=%d\n", prev_fd, fds[0], fds[1]);
//             }
//             else
//             {
//                 // Выполнение команды
//                 // if (check_if_buildin(cmd))
//                 // {
//                 char *full_path = find_path(cmd->args[0], data->path_arr);
//                 data->err_no = run_execve(cmd, envp, full_path);
//                 free(full_path);
//                 // }
//                 exit(data->err_no);
//             }
//         }
//         else
//         {
//             // Родительский процесс
//             printf("parent: prev_fd=%d, fds[0]=%d, fds[1]=%d\n", prev_fd, fds[0], fds[1]);

//             if (prev_fd != STDIN_FILENO)
//                 close(prev_fd);

//             if (cmd->next != NULL)
//             {
//                 close(fds[1]);
//                 prev_fd = fds[0];
//             }

//             waitpid(pid, &status, 0);
//             printf("parent after wait: prev_fd=%d, fds[0]=%d, fds[1]=%d\n", prev_fd, fds[0], fds[1]);
//         }

//         cmd = cmd->next;
//     }

//     return 0;
// }
