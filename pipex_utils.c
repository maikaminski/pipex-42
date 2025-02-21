/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makamins <makamins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:52:57 by makamins          #+#    #+#             */
/*   Updated: 2025/02/21 14:26:13 by makamins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

char	*construct_path(char *dir, char *cmd)
{
	size_t	path_len;
	char	*full_path;

	path_len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full_path = malloc(path_len);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, path_len);
	ft_strlcat(full_path, "/", path_len);
	ft_strlcat(full_path, cmd, path_len);
	return (full_path);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_path = construct_path(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
			return (free_array(paths), full_path);
		free(full_path);
		i++;
	}
	return (free_array(paths), NULL);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	is_error(int i, t_pipex *pipex)
{
	if (i == 0)
		perror("Error: opening input file");
	else if (i == 1)
		perror("Error: duplicating fd[1] or infile");
	else if (i == 2)
		perror("Error: opening output file");
	else if (i == 3)
		perror("Error: duplicating fd[0] or outfile");
	else if (i == 4)
	{
		if (errno == ENOENT)
			perror("Error: Command not found");
		else
			perror("Error: Execution failed");
	}
	else if (i == 5)
		perror("Error: right prototype: ./pipex file1 cmd1 cmd2 file2");
	else if (i == 6)
		perror("Error: creating pipe");
	else if (i == 7)
		perror("Error: creating process");
	cleanup_and_exit(pipex, EXIT_FAILURE);
}
