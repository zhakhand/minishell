#include "../minishell.h"

int	check_full_path(char *full_path, t_cmd *cmd, char **envp)
{
	struct stat	sb;

	if (stat(full_path, &sb) == -1)
		return (ft_putmsg_fd("", cmd->args[0], N_F_D, STDERR_FILENO), 127);
	if (S_ISDIR(sb.st_mode))
		return (ft_putmsg_fd("", cmd->args[0], I_A_D, STDERR_FILENO), 126);
	if (access(full_path, X_OK) == -1)
		return (ft_putmsg_fd("", cmd->args[0], P_D, STDERR_FILENO), 126);
	if (execve(full_path, cmd->args, envp))
		return (perror ("execve"), 1);
	return (0);
}

char	*full_path_init(t_data *data, t_cmd *cmd, char **envp)
{
	char	*full_path;
	int		is_explicit_path;

	full_path = NULL;
	is_explicit_path = ft_strchr(cmd->args[0], '/') != NULL;
	if (is_explicit_path)
		full_path = cmd->args[0];
	data->path_arr = get_path_arr(envp);
	return (full_path);
}

int	run_execve(t_data *data, t_cmd *cmd, char **envp)
{
	struct stat		sb;
	char			*full_path;

	full_path = full_path_init(data, cmd, envp);
	if (!full_path)
	{
		if (!data->path_arr || !data->path_arr[0])
		{
			if (stat(cmd->args[0], &sb) == 0)
			{
				if (access(cmd->args[0], X_OK) == -1)
					return (ft_putmsg_fd("", cmd->args[0], P_D, 2), 126);
				full_path = cmd->args[0];
			}
			else
				return (ft_putmsg_fd("", cmd->args[0], N_F_D, 2), 127);
		}
		else
		{
			full_path = find_path(cmd->args[0], data->path_arr);
			if (!full_path)
				return (ft_putmsg_fd("", cmd->args[0], C_N_F, 2), 127);
		}
	}
	return (check_full_path(full_path, cmd, envp));
}
