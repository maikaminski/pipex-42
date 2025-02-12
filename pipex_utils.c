/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makamins <makamins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:52:57 by makamins          #+#    #+#             */
/*   Updated: 2025/02/12 15:59:17 by makamins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    cleanup_and_exit(t_pipex *pipex, int exit_code)
{
    if (pipex->cmd1_args)
        free_array(pipex->cmd1_args);
    if (pipex->cmd2_args)
        free_array(pipex->cmd2_args);
    if (pipex->cmd1_path)
        free(pipex->cmd1_path);
    if (pipex->cmd2_path)
        free(pipex->cmd2_path);
    close_fds(pipex);
    exit(exit_code);
}
//Função para achar o path
char    **get_paths(char **envp)
{
    int     i;
    
    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
        i++;
    if (!envp[i])
    return (NULL);
    return (ft_split(envp[i] + 5, ':'));
}

char *construct_path(char *dir, char *cmd)
{
    size_t path_len = ft_strlen(dir) + ft_strlen(cmd) + 2;
    char *full_path = malloc(path_len);
    if (!full_path)
        return (NULL);
    ft_strlcpy(full_path, dir, path_len);
    ft_strlcat(full_path, "/", path_len);
    ft_strlcat(full_path, cmd, path_len);
    return (full_path);
}
char *get_cmd_path(char *cmd, char **envp)
{
    char **paths = get_paths(envp);
    char *full_path;
    int i = 0;

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

//Função para dar free

void    free_array(char **array)
{
    int i = 0;

    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}
//Função pra printar os erros

void    is_error(int i, t_pipex *pipex)
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
        perror("Error: Command not found");
    else if (i == 5)
        perror("Error: Execution failed");
    else if (i == 6)
        perror("Error: right prototype: ./pipex file1 cmd1 cmd2 file2");
    else if (i == 7)
        perror("Error: creating pipe");
    else if (i == 8)
        perror("Error: creating process");
    cleanup_and_exit(pipex, EXIT_FAILURE);
}
// static int	count_words(const char *s, char c)
// {
// 	int	count;
// 	int	in_word;

// 	count = 0;
// 	in_word = 0;
// 	while (*s)
// 	{
// 		if (*s != c && in_word == 0)
// 		{
// 			count++;
// 			in_word = 1;
// 		}
// 		else if (*s == c)
// 			in_word = 0;
// 		s++;
// 	}
// 	return (count);
// }
