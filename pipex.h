/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makamins <makamins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:49:39 by makamins          #+#    #+#             */
/*   Updated: 2025/03/19 12:54:26 by makamins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "./libft-pipex/libft.h"
# include <errno.h> 

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd1_args;
	char	**cmd2_args;
	char	**envp;
}	t_pipex;

char	**get_paths(char **envp);
char	*get_cmd_path(char *cmd, char **envp);
void	free_array(char **array);
void	is_error(int i, t_pipex *pipex);
void	close_fds(t_pipex *pipex);
void	execute_process(t_pipex *pipex);
void	run_pipex(t_pipex *pipex);
int		main(int argc, char **argv, char **envp);
char	*construct_path(char *dir, char *cmd);
void	cleanup_and_exit(t_pipex *pipex, int exit_code);
char	*find_cmd_in_paths(char **paths, char *cmd);

#endif
