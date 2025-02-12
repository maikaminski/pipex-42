/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makamins <makamins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:49:27 by makamins          #+#    #+#             */
/*   Updated: 2025/02/12 15:58:58 by makamins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(t_pipex *pipex)
{
        if (pipex->infile >= 0)
        close(pipex->infile);
    if (pipex->outfile >= 0)
        close(pipex->outfile);
    close(pipex->pipe_fd[0]);
    close(pipex->pipe_fd[1]);
}

void	child_process(t_pipex *pipex)
{
	if (dup2(pipex->infile, 0) == -1 || dup2(pipex->pipe_fd[1], 1) == -1)
        cleanup_and_exit(pipex, 1);
    close_fds(pipex);
    execve(pipex->cmd1_path, pipex->cmd1_args, pipex->envp);
    cleanup_and_exit(pipex, 1);
}
void	parent_process(t_pipex *pipex)
{
	if (dup2(pipex->pipe_fd[0], 0) == -1 || dup2(pipex->outfile, 1) == -1)
        cleanup_and_exit(pipex, 1);
    close_fds(pipex);
    execve(pipex->cmd2_path, pipex->cmd2_args, pipex->envp);
    cleanup_and_exit(pipex, 1);
}
 void	run_pipex(t_pipex *pipex)
 {
	 if (pipe(pipex->pipe_fd) == -1)
        is_error(7, pipex);
    pipex->pid1 = fork();
    if (pipex->pid1 == -1)
        is_error(8, pipex);
    if (pipex->pid1 == 0)
        child_process(pipex);
    pipex->pid2 = fork();
    if (pipex->pid2 == -1)
        is_error(8, pipex);
    if (pipex->pid2 == 0)
        parent_process(pipex);
    waitpid(pipex->pid1, NULL, 0);
    waitpid(pipex->pid2, NULL, 0);
 }

 int	main(int argc, char **argv, char **envp)
 {
	 t_pipex	pipex;

    if (argc != 5)
        is_error(6, &pipex);
    pipex.envp = envp;
    pipex.infile = open(argv[1], O_RDONLY);
    pipex.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex.infile < 0 || pipex.outfile < 0)
        is_error(3, &pipex);
    pipex.cmd1_args = ft_split(argv[2], ' ');
    pipex.cmd2_args = ft_split(argv[3], ' ');
    pipex.cmd1_path = get_cmd_path(pipex.cmd1_args[0], pipex.envp);
    pipex.cmd2_path = get_cmd_path(pipex.cmd2_args[0], pipex.envp);
    if (!pipex.cmd1_path || !pipex.cmd2_path)
        is_error(5, &pipex);
    run_pipex(&pipex);
    cleanup_and_exit(&pipex, 0);
 }

