#include "../minishell.h"

int	show_pwd(t_data *data)
{
	if (data->pwd != NULL)
	{
		ft_putstr_fd(data->pwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	else
		ft_putstr_fd("PWD not set\n", STDERR_FILENO);
	return (1);
}
