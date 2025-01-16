
#include "../minishell.h"

int ft_env_no_args(t_data *data)
{
	t_var *temp;
//	sort_env(data);
	if (!data->env_var)
		return (EXIT_FAILURE);
	temp = data->env_var;
	while (temp)
	{
		if (temp->key)
		{
			ft_putstr_fd(temp->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
		}
		if (temp->val)
		{
			ft_putstr_fd(temp->val, STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);

	// while (data->env[i] != NULL)
	// {
	// 	printf("%s\n", data->env[i]);
	// 	i++;
	// }
}

