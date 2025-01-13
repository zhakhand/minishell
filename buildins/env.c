
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
			printf("%s=", temp->key);
		if (temp->val)
			printf("%s", temp->val);
		printf("\n");
		temp = temp->next;
	}
	return (EXIT_SUCCESS);

	// while (data->env[i] != NULL)
	// {
	// 	printf("%s\n", data->env[i]);
	// 	i++;
	// }
}

