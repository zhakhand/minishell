#include "../minishell.h"

int	first_arg(t_cmd *node)
{
	int	i;

	i = 1;
	while (node->args[i] != NULL && ft_strncmp(node->args[i], "-n", 3) == 0)
		i++;
	return (i);
}

int	if_no_newline(t_cmd *node)
{
	int	i;
	int	j;
	int	no_newline;
	int	flag;

	no_newline = 0;
	i = first_arg(node);
	flag = i - 1;
	while (node->args[i] != NULL && ft_strncmp(node->args[i], "-n", 2) == 0)
	{
		j = 2;
		while (node->args[i][j] != '\0')
		{
			no_newline = 0;
			if (node->args[i][j] != 'n')
				break ;
			j++;
			no_newline = 1;
		}
		if (no_newline == 0)
			break ;
		flag++;
		i++;
	}
	return (flag);
}

int	ft_echo(t_data *data, t_cmd *node)
{
	int	i;
	int	s;

	s = data->argc;
	if (node->args[1] == NULL)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	i = if_no_newline(node) + 1;
	while (node->args[i] != NULL)
	{
		ft_putstr_fd(node->args[i], STDOUT_FILENO);
		if (node->args[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	i = s;
	if (if_no_newline(node) == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
