
#include "../minishell.h"

// int check_if_buildin(t_cmd *node)
// {
// //	printf("check_if_buildin, %d\n", node->built_in);
// 	if (node == NULL || node->cmd == NULL || node->cmd == NULL)
// 		return (-1);
// 	if (node->built_in == 901 || 
// 		node->built_in == 902 || 
// 		node->built_in == 903 || 
// 		node->built_in == 904 || 
// 		node->built_in == 905 || 
// 		node->built_in == 906 || 
// 		node->built_in == 907)
// 		return (0);
// 	return (1);
// }

int check_parent_buildin(t_cmd *node)
{
//	printf("check_if_buildin, %d\n", node->built_in);
	if (node == NULL || node->cmd == NULL)
		return (-1);
	if (
		node->built_in == CD || 
		(node->built_in == EXPORT && node->args[1])|| 
		node->built_in == UNSET || 
		node->built_in == EXIT)
	{	
		return (0);
	}
	return (1);
}

int check_child_buildin(t_cmd *node)
{
	if (node == NULL || node->cmd == NULL)
		return (-1);
	if (node->built_in == ECH || 
		node->built_in == PWD || 
		(node->built_in == EXPORT && !node->args[1])|| 
		node->built_in == ENV)
	{	
		return (0);
	}
	return (1);
}

int exec_buildin(t_data *data, t_cmd *node)
{
	int res;

	res = 0;
	if (node == NULL || node->cmd == NULL || node->cmd == NULL)
		return (-1);
	if (node->built_in == CD)
		res = changedir(data, node);
	if (node->built_in == PWD)
		res = show_pwd(data);
	if (node->built_in == ECH)
		res = ft_echo(data, node);
	if (node->built_in == ENV)
		res = ft_env_no_args(data);
	if (node->built_in == UNSET)
		res = ft_unset(data, node);
	if (node->built_in == EXPORT)
		res = ft_export(data, node);
	if (node->built_in == EXIT)
		res = ft_exit(data, node);
	return (res);
}


