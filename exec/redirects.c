
#include "../minishell.h"

extern sig_atomic_t g_signal;

int handle_heredoc(t_data *data, char *delimiter)
{
    char *line;
    int temp_fd;

//	ft_putmsg_fd(, "heredoc", " ", STDERR_FILENO);
    // Create a unique temporary file
    temp_fd = get_random_fd(data);
	//unlink("temp");
//	temp_fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0666);
    // Read lines until the delimiter is entered
	//set_signals(HEREDOC);
    while (1)
    {
		// // if (isatty(fileno(stdin)))
		// // 	line = readline("> ");
		// // else
		// // {
		// char *pr;
		// pr = get_next_line(fileno(stdin));
		// line = ft_strtrim(pr, "\n");
		// free(pr);
		// // }

        line = readline("> ");
        if (!line)
        {
            ft_putstr_fd("minishell: warning: heredoc delimited by EOF\n", STDERR_FILENO);
            break;
        }
		if (g_signal == SIGINT)
		{
			free(line);
			break ;
		}
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }

        write(temp_fd, line, ft_strlen(line));
        write(temp_fd, "\n", 1);
        free(line);
//        line = readline("> ");
    }
	// close(temp_fd);
    // temp_fd = open("/tmp/<pid>", O_RDONLY); // Reopen the correct temp file for reading

    // Reset file pointer and unlink the temporary file
    if (lseek(temp_fd, 0, SEEK_SET) == -1)
    {
        perror("Error seeking in temp file");
		set_signals(PARENT);
        close(temp_fd);
        return -1;
    }
	set_signals(PARENT);

//system("ls -l temp");
//    system("cat temp");

	// close(temp_fd);
	// temp_fd = open("temp", O_RDONLY);
    return temp_fd;
}


// int handle_input_redirects(t_redir *redir)
// {
// 	t_redir *redirects = redir;
// 	int in_fd;
// 	int temp_fd;

// 	while (redirects)
// 	{
// 		if (redirects->type == IN)
// 		{
// 			in_fd = open(redirects->val, O_RDONLY);
// 			if (in_fd == -1)
// 			{
// //				ft_putmsg_fd(MSH, redirects->val, N_F_D, STDERR_FILENO);
// 				// ft_putstr_fd("minishell: ", STDERR_FILENO);
// 				// ft_putstr_fd(redirects->val, STDERR_FILENO);
// 				// ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
// 				return (-1);
// 			}
// 			if (dup2(in_fd, STDIN_FILENO) == -1)
// 				return (-1);
// 			close(in_fd);
// 		}
// 		else if (redirects->type == HEREDOC)
// 		{
// 			set_signals(HEREDOC);
// 			temp_fd = handle_heredoc(redirects->val);
// //			printf("temp_fd %d\n", temp_fd);
// 			if (temp_fd == -1)
// 			{
// 				ft_putstr_fd("minishell: error handling heredoc\n", STDERR_FILENO);
// 				return (-1);
// 			}
// 			if (dup2(temp_fd, STDIN_FILENO) == -1)
// 				return (-1);
// 			close(temp_fd);
// 		}
// 		redirects = redirects->next; // Move to the next redirect
// 	}
// 	return (0);
// }

int handle_input_redirects(t_redir *redir)
{
    t_redir *redirects = redir;
    int in_fd;
//    int temp_fd;
//    int last_fd = -1;
	
//	temp_fd = data->err_no;
    while (redirects)
    {
//		printf("from handle input  |%s|  %d\n", redirects->val, redirects->type);
        if (redirects->type == IN)
        {
			if (redirects->ambig == 1)
            {
                ft_putmsg_fd(MSH, redirects->val, AMB, STDERR_FILENO);
                return (-1);
            }
            in_fd = open(redirects->val, O_RDONLY);
            if (in_fd == -1)
            {
                ft_putmsg_fd(MSH, redirects->val, N_F_D, STDERR_FILENO);
                return (-1);
            }
            if (dup2(in_fd, STDIN_FILENO) == -1)
                return (-1);
            close(in_fd);
        }
        else if (redirects->type == HEREDOC)
        {
            set_signals(HEREDOC);
            in_fd = open(redirects->heredoc, O_RDONLY);
            if (in_fd == -1)
            {
                ft_putmsg_fd(MSH, redirects->heredoc, N_F_D, STDERR_FILENO);
                return (-1);
            }
            if (dup2(in_fd, STDIN_FILENO) == -1)
                return (-1);
            close(in_fd);
			//unlink(redirects->heredoc);
//            last_fd = in_fd;
        }
        redirects = redirects->next; // Move to the next redirect
    }

    // if (last_fd != -1)
    // {
    //     if (dup2(last_fd, STDIN_FILENO) == -1)
    //         return (-1);
    //     close(last_fd);
//		printf("temp_name %s\n", data->temp_name);
//		unlink(data->temp_name);
//    }
    return (0);
}

int open_and_close(t_redir *redir)
{
	int out_fd;
	out_fd = -1;

	// if (access(redir->val, O_WRONLY) == -1)
	// {
	// 	panic("No such file or directory");
	// 	return (-1);
	// }
	if (ft_strcmp(redir->val, "/dev/null") == 0)
	{
//	printf("acc %d %s\n", access(redir->val, O_WRONLY), redir->val);
		return (0);
	}
	out_fd = open(redir->val, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (out_fd == -1)
	{
		ft_putmsg_fd(MSH, redir->val, N_F_D, STDERR_FILENO);

//		panic("minishell");
		return (-1);
	}
	close(out_fd);

	return (0);
}

int check_directory(char *file)
{
	struct stat sb;

	char *temp;
	int i;

	i = ft_strlen(file);
	while (i > 0)
	{
		if (file[i] == '/')
			break;
		i--;
	}
	if (i == 0)
		temp = ft_strdup(file);
	else
		temp = ft_substr(file, 0, i);
	// printf("temp %s\n", temp);
	if (stat(file, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
	// 	&& i != 0) 
	// {
	// 	if ( i == 0)
	// 	{
			ft_putmsg_fd(MSH, file, I_A_D, STDERR_FILENO);
			free(temp);
			return (-1);
		// }
	}
	// if (i != 0 && (stat(temp, &sb) != 0 || !S_ISDIR(sb.st_mode)))
	// {
	// 	ft_putmsg_fd(MSH, temp, N_F_D, STDERR_FILENO);
	// 	free(temp);
	// 	return (-1);
	// }
//	printf("temp %s\n", temp);
//	int res = chdir(temp);
//	if ( i != 0 && res == -1)
	if (stat(temp, &sb) != 0 && !S_ISDIR(sb.st_mode)
		&& i != 0)

	{
		ft_putmsg_fd(MSH, file, N_F_D, STDERR_FILENO);
		// ft_putstr_fd("minishell: ", 2);
		// ft_putstr_fd(file, 2);
		// ft_putstr_fd(": No such file or directory\n", 2);
		free(temp);
		return (-1);
	}
	// else if (res == 0)
	// 	{
	// 	chdir("..");
	// 	}
	free(temp);
	return (0);
}

int handle_output_redirects(t_redir *redirects)
{
	int out_fd;
	out_fd = -1;
	t_redir *redir;
	int res;

	res = 0;
	redir = redirects;
	// out_fd = open(redir->val, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (check_directory(redirects->val) == -1)
		return (-1);
	while (redir)
	{
//		printf("from handle output  |%s|  %d\n", redir->val, redir->type);
		if (redirects->ambig == 1)
		{
			ft_putmsg_fd(MSH, redirects->val, AMB, STDERR_FILENO);
			return (-1);
		}
		if (redir->next)
		{
			res = open_and_close(redir);
			if (res == -1)
			{
				ft_putmsg_fd(MSH, redir->val, N_F_D, STDERR_FILENO);
				return (-1);
			}
		}
		else
		{
			// if (redir->type == OUT || redir->type == APPEND)
			// {
				if (redir->type == OUT)
				{
					out_fd = open(redir->val, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				}
				else if (redir->type == APPEND)
				{
					out_fd = open(redir->val, O_WRONLY | O_CREAT | O_APPEND, 0666);
				}
				if (out_fd == -1)
				{
					ft_putmsg_fd(MSH, redir->val, N_F_D, STDERR_FILENO);
					return (-1);
				}
				if (dup2(out_fd, STDOUT_FILENO) == -1)
					return (-1);
//				ft_putstr_fd("from handle output  ", 2);
//	printf("from handle output  %d %s\n", out_fd, redirects->val);
				close(out_fd);
		}
		redir = redir->next;
		}
	// }
	return (0);
}

int check_access(char *file)
{
	if (access(file, F_OK) == -1)
	{
		ft_putmsg_fd(MSH, file, N_F_D, STDERR_FILENO);
		return (-1);
	}
	return (0);
}

int handle_redirects(t_data *data, t_cmd *node)
{
    t_redir *input_redirects = NULL;
    t_redir *output_redirects = NULL;
    t_redir *temp = node->redir;
    t_redir *last_input = NULL;
    t_redir *last_output = NULL;
    int err = 0;

//    printf("from start  |%s|  %d\n", temp->val, temp->type);
    while (temp)
    {

        if (temp->type == IN && check_access(temp->val) == -1)
            return (-1);
        else if ((temp->type == OUT || temp->type == APPEND) && check_directory(temp->val) == -1)
            return (-1);

        if (temp->type == IN || temp->type == HEREDOC)
        {
            if (!input_redirects)
            {
                input_redirects = temp;
                last_input = temp;
            }
            else
            {
                last_input->next = temp;  // Add to end of list
                last_input = temp;        // Move tail pointer
            }
        }
        else if (temp->type == OUT || temp->type == APPEND)
        {
//            printf("from handle redir out |%s|  %d\n", temp->val, temp->type);
            if (!output_redirects)
            {
                output_redirects = temp;
                last_output = temp;
            }
            else
            {
                last_output->next = temp;  // Add to end of list
                last_output = temp;        // Move tail pointer
            }
        }
        temp = temp->next;
    }

    // Ensure lists terminate properly
	if (last_input)
		last_input->next = NULL;
	if (last_output)
		last_output->next = NULL;
	if (input_redirects)
	{
		if (handle_input_redirects(input_redirects) == -1)
			err = -1;
	}
	if (output_redirects)
		if (handle_output_redirects(output_redirects) == -1)
			err = -1;

	data->err_no = err;
	return err;
}


// int handle_redirects(t_data *data, t_cmd *node)
// {
// 	t_redir *input_redirects;
// 	t_redir *output_redirects;
// 	t_redir *temp;
// //	t_redir *temp2;
// //	t_redir *last_output;
// //	t_redir *last_input;
// 	int err;

// 	err = 0;
// 	temp = node->redir;
// 	input_redirects = NULL;
// 	output_redirects = NULL;
// 	while (temp)
// 	{
// 		printf("from start  |%s|  %d\n", temp->val, temp->type);
// 		if(temp->type == IN
// 			&& check_access(temp->val) == -1)
// 			return (-1);
// 		else if (temp->type ==OUT || temp->type == APPEND)
// 		{
// 			if (check_directory(temp->val) == -1)
// 				return (-1);
// 		}
// 		if (temp->type == IN || temp->type == HEREDOC)
// 		{
// //				printf("from handle redir in |%s|  %d\n", temp->val, temp->type);
// 			// if (input_redirects == NULL)
// 			// {
// 			// 	input_redirects = temp;
// 			// 	last_input = temp;
// 			// }
// 			// else
// 			// {
// 			// 	last_input->next = temp;
// 			// 	last_input = temp;
// 			// }
// 			// last_input->next = NULL;
// 			// {
// 			// 	ft_putmsg_fd("11", input_redirects->val, N_F_D, STDERR_FILENO);
// 			// 	return (-1);
// 			// }
// 			if (input_redirects == NULL)
// 			{
// 				input_redirects = temp;
// //				last_output = temp; // Инициализация последнего элемента
// 			}
// 			else
// 			{
// 				while (input_redirects->next)
// 					input_redirects = input_redirects->next;
// 				input_redirects->next = temp; // Добавление в конец списка
// //				last_output = temp;      // Обновляем указатель на последний элемент
// 			}
// //
// 		}
// 		else if (temp->type == OUT || temp->type == APPEND)
// 		{
// 				printf("from handle redir out |%s|  %d\n", temp->val, temp->type);
// 			if (output_redirects == NULL)
// 			{
// 				output_redirects = temp;
// //				last_output = temp; // Инициализация последнего элемента
// 			}
// 			else
// 			{
// 				while (output_redirects->next)
// 					output_redirects = output_redirects->next;
// 				output_redirects->next = temp; // Добавление в конец списка
// //				last_output = temp;      // Обновляем указатель на последний элемент
// 			}
// 		}
// 		input_redirects->next = NULL;
// 		output_redirects->next = NULL;
// 		temp = temp->next;
// 	}
// 	if(input_redirects)
// 	{
// 		if (handle_input_redirects(input_redirects) == -1)
// 		{
// 			err = -1;
// 		}
// 	}
// 	if (output_redirects)
// 	{
// 		if (handle_output_redirects(output_redirects) == -1)
// 		{
// 			err = -1;
// 		}
// 	}
// 	data->err_no = err;
// 	return (err);
// }
