/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makamins <makamins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:51:47 by makamins          #+#    #+#             */
/*   Updated: 2025/03/19 18:01:05 by makamins         ###   ########.fr       */
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

char	*find_cmd_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = construct_path(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;

	if (!cmd || !cmd[0])
		return (NULL);
	paths = ft_split(cmd, ' ');
	if (access(paths[0], X_OK) == 0)
	{
		cmd_path = ft_strdup(paths[0]);
		free_array(paths);
		return (cmd_path);
	}
	free_array(paths);
	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	return (find_cmd_in_paths(paths, cmd));
}
