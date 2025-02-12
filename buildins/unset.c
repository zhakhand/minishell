#include "../minishell.h"

void	free_temp(t_var *temp)
{
	free(temp->key);
	free(temp->val);
	free(temp);
}

void	unset_one(t_data *data, t_cmd *n, int i)
{
	t_var	*temp;
	t_var	*temp2;
	t_var	*temp3;

	temp3 = data->env_var;
	temp = data->env_var;
	while (temp)
	{
		temp2 = temp->next;
		if (temp2 == NULL)
			break ;
		if (ft_strncmp(temp2->key, n->args[i], ft_strlen(n->args[i])) == 0)
		{
			temp->next = temp2->next;
			free_temp(temp2);
		}
		temp = temp->next;
	}
	data->env_var = temp3;
}

void	ft_unset(t_data *data, t_cmd *n)
{
	int		i;

	i = 1;
	while (n->args[i] != NULL)
	{
		if (ft_strncmp(n->args[i], "OLDPWD", 6) == 0)
		{
			free(data->old_pwd);
			data->old_pwd = NULL;
		}
		unset_one(data, n, i);
		i++;
	}
}
