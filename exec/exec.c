#include "../minishell.h"
#include "../parser.h"
//#include <cerrno>
#include <unistd.h>

extern sig_atomic_t g_signal;

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

int run_execve(t_data *data, t_cmd *cmd, char **envp) {
    struct stat sb;
    char *full_path = NULL;
    int is_explicit_path = ft_strchr(cmd->args[0], '/') != NULL;

    // If the command contains a '/', treat it as a direct path
    if (is_explicit_path) 
        full_path = cmd->args[0];
    else {
        // Get PATH environment variable and split into an array
        data->path_arr = get_path_arr(envp);
        if (!data->path_arr || !data->path_arr[0])  // Handle empty or NULL PATH
            full_path = NULL;
        else
            full_path = find_path(cmd->args[0], data->path_arr);
    }

    // If no valid path was found, check if the command exists in the current directory
    if (!full_path) {
        if (stat(cmd->args[0], &sb) == 0) { // Check if file exists in current dir
            if (access(cmd->args[0], X_OK) == -1) {
                ft_putstr_fd(cmd->args[0], STDERR_FILENO);
                ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
                return 126;
            }
            full_path = cmd->args[0];
        } else {
            ft_putstr_fd(cmd->args[0], STDERR_FILENO);
            ft_putstr_fd(": command not found\n", STDERR_FILENO);
            return 127;
        }
    }

    // Check if the file exists
    if (stat(full_path, &sb) == -1) {
        ft_putstr_fd(cmd->args[0], STDERR_FILENO);
        ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
        return 127;
    }

    // Check if it's a directory
    if (S_ISDIR(sb.st_mode)) {
        ft_putstr_fd(cmd->args[0], STDERR_FILENO);
        ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
        return 126;
    }

    // Check execute permissions
    if (access(full_path, X_OK) == -1) {
        ft_putstr_fd(cmd->args[0], STDERR_FILENO);
        ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
        return 126;
    }

    // Execute the command
    execve(full_path, cmd->args, envp);
    perror("execve");
    return 1;
}
int is_path_exist(t_data *data)
{
	t_var *temp;
	temp = data->env_var;
	while (temp)
	{
		if (ft_strcmp(temp->key, "PATH") == 0 
			&& (temp->val != NULL || temp->val[0] != '\0'))
			return (1);
		temp = temp->next;
	}
	return (0);
}

// int run_execve(t_data *data, t_cmd *cmd, char **envp) {
//     struct stat sb;
//     char *full_path = NULL;

// 	if (is_path_exist(data) == 1)
// 	{
//         full_path = cmd->args[0];
// //		printf("full_path %s\n", full_path);
// 		if ((ft_strncmp(cmd->args[0], "./", 2 ) != 0 
// 		|| ft_strncmp(cmd->args[0], "/", 1 ) != 0)
// 		&& stat(full_path, &sb) == -1)
// 		{
// 			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
// 			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
// 			return 127;
// 	    }
// 		// else {
// 		// 	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
// 		// 	ft_putstr_fd(": command not found\n", STDERR_FILENO);
// 		// 	return 127;
		
// 		// }
// 	}
//     // If the command contains a '/', treat it as a direct path
//     if (ft_strchr(cmd->args[0], '/') && is_path_exist(data)) 
//         full_path = cmd->args[0];

//     else if (is_path_exist(data) == 1)
// 	{
//         full_path = cmd->args[0];
// //		printf("full_path %s\n", full_path);
// 		if (stat(full_path, &sb) == -1)
// 		{
// 			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
// 			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
// 			return 127;
// 	    }
// 	}
//     else {
//         // Get PATH environment variable and split into an array
//         data->path_arr = get_path_arr(envp);
//         if (!data->path_arr || !data->path_arr[0])  // Handle empty or NULL PATH
//             full_path = NULL;
//         else
//             full_path = find_path(cmd->args[0], data->path_arr);
//     }

//     // If no valid path was found, return "command not found"
//     if (!full_path) {
// 		if(ft_strncmp(cmd->args[0], "/", 1 ) != 0
// 			|| ft_strncmp(cmd->args[0], "./", 2 ) != 0)
// 		{
//         ft_putstr_fd(cmd->args[0], STDERR_FILENO);
//         ft_putstr_fd(": command not found\n", STDERR_FILENO);
//         return 127;
// 		}
// 		else {
// 			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
// 			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
// 			return 127;
// 		}
//     }

//     // Check if the file exists
//     if (stat(full_path, &sb) == -1) {
//         ft_putstr_fd(cmd->args[0], STDERR_FILENO);
//         ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
//         return 127;
//     }

//     // Check if it's a directory
//     if (S_ISDIR(sb.st_mode)) {
//         ft_putstr_fd(cmd->args[0], STDERR_FILENO);
//         ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
//         return 126;
//     }

//     // Check execute permissions
//     if (access(full_path, X_OK) == -1) {
//         ft_putstr_fd(cmd->args[0], STDERR_FILENO);
//         ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
//         return 126;
//     }

//     // Execute the command
//     if (execve(full_path, cmd->args, envp) == -1) {
//         perror("execve");
//         return 1;
//     }

//     return 0;
// }

// int run_execve(t_data *data, t_cmd *cmd, char **envp) {
//     struct stat sb;
//     char *full_path = NULL;
//  //   int status = 0;
//     // If the command contains a '/', treat it as a path
// 	if (ft_strchr(cmd->args[0], '/') && is_path_exist(data)) 
// 		full_path = cmd->args[0];

// 	else if (!is_path_exist(data))
// 		full_path = cmd->args[0];
// 	else
// 	{      // Otherwise, look up the command in PATH
// 		data->path_arr = get_path_arr(envp);
// 		if (data->path_arr)
// 			full_path = find_path(cmd->args[0], data->path_arr);
// 		else
// 		{
// 			full_path = NULL;
// 		}
// 	}
//     // If no valid path was found and it's not an absolute/relative path
//     if (!*full_path && ft_strncmp(cmd->args[0], "/", 1) != 0) {
//         ft_putstr_fd(cmd->args[0], STDERR_FILENO);
//         ft_putstr_fd(": command not found\n", STDERR_FILENO);
//         return 127;
//     }
//     else if (!*full_path && ft_strncmp(cmd->args[0], "/", 1) == 0) {
//         ft_putstr_fd(cmd->args[0], STDERR_FILENO);
//         ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
//         return 127;
//     }


//     // Check if the file exists
//     if (stat(full_path, &sb) == -1) {
//         ft_putstr_fd(cmd->args[0], STDERR_FILENO);
//         ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
//         return 127;
//     }

//     // Check if it's a directory
//     if (S_ISDIR(sb.st_mode)) {
//         ft_putstr_fd(cmd->args[0], STDERR_FILENO);
//         ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
//         return 126;
//     }

//     // Check execute permissions
//     if (access(full_path, X_OK) == -1) {
//         ft_putstr_fd(cmd->args[0], STDERR_FILENO);
//         ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
//         return 126;
//     }

//     // Execute the command
//     if (execve(full_path, cmd->args, envp) == -1) {
//         perror("execve");
//         return 1;
//     }

//     return 0;
// }

int run_pipe(t_data *data, t_cmd *cmd, char **envp)
{
	int fds[2];
	int prev_fd = STDIN_FILENO;
	int status;
	pid_t pid;

	data->child_start = 0;

	while (cmd != NULL)
	{
		data->redir_err = 0;
		if (!check_parent_buildin(cmd))
		{
			data->err_no = exec_buildin(data, cmd);
			if (cmd->next == NULL)
				return (0);
		}
		if (cmd->next != NULL && pipe(fds) == -1)
			panic("pipe err");
		data->child_start = 1;
		pid = fork();
		if (!cmd->next)
			data->last_pid = pid;
		if (pid == -1)
			panic("fork err");
		else if (pid == 0) // Дочерний процесс
		{
			set_signals(CHILD);
			if (prev_fd != STDIN_FILENO)
			{
				if (dup2(prev_fd, STDIN_FILENO) == -1)
					panic("dup2 prev_fd");
				close(prev_fd);
			}
			if (handle_redirects(data, cmd) == -1)
			{
				data->err_no = 1;
				data->redir_err = 1;
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
			else if (data->redir_err == 0 
			&& !ft_edge_cases(data, cmd) && check_child_buildin(cmd) == 1)
			{
				data->err_no = run_execve(data, cmd, envp);
//				free(full_path);
			}
//			system("ls -l /proc/self/fd"); // List open file descriptors
			int err = data->err_no;
			clean_data(data);
			if (envp)
				free_args(&envp);
			exit(err);
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
	set_signals(WAIT);
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			data->err_no = WEXITSTATUS(status);
	}
//    clear_path_arr(data);
	return (0);
}

