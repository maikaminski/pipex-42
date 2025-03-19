/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makamins <makamins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:52:57 by makamins          #+#    #+#             */
/*   Updated: 2025/03/19 12:53:38 by makamins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	cleanup_and_exit(t_pipex *pipex, int exit_code)
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

void	close_fds(t_pipex *pipex)
{
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}

void	is_error(int i, t_pipex *pipex)
{
	if (i == 1)
		perror("Error: opening output file");
	else if (i == 2)
	{
		perror("Error: Not permission or command not found");
		if (pipex->outfile >= 0)
			close(pipex->outfile);
		exit(EXIT_FAILURE);
	}
	else if (i == 3)
		perror("Error: creating pipe");
	else if (i == 4)
		perror("Error: creating process");
	cleanup_and_exit(pipex, EXIT_FAILURE);
}
