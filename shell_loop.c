#include "shell.h"


/**
 * hsh - the main shell loop.
 * @info: Par. and return info struct.
 * @av: Argument vector from main()
 *
 * Return: On Success 0, On error 1, or error code.
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (1)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r == -1)
			break;
		set_info(info, av);
		builtin_ret = find_builtin(info);
		if (builtin_ret == -1)
			find_cmd(info);
		free_info(info, 0);
	}

	write_history(info);
	free_info(info, 1);

	if (!interactive(info) && info->status)
		exit(info->status);

	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}

	return (builtin_ret);
}



/**
 * find_builtin - Looks for a builtin command.
 * @info: Par. and return info struct.
 *
 * Return: -1 if builtin not found, 0 if builtin executed successfully,
 *          1 if builtin found but not successful, 2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
	{
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			return (builtintbl[i].func(info));
		}
	}

	return (-1);
}



/**
 * find_cmd - looks for a command in PATH.
 * @info: Parameter and return info struct.
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	int i, k;

	for (i = 0, k = 0; info->arg[i]; i++)
	{
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	}

	if (k == 0)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if (is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}


/**
 * fork_cmd - creates an executable thread to run cmd.
 * @info: Par. and return info struct.
 *
 * Return: Void.
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}

	wait(&(info->status));
	if (WIFEXITED(info->status))
	{
		info->status = WEXITSTATUS(info->status);
		if (info->status == 126)
			print_error(info, "Permission denied\n");
	}
}
