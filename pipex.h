/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makamins <makamins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:49:39 by makamins          #+#    #+#             */
/*   Updated: 2025/02/12 16:05:23 by makamins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H
    # include <unistd.h>
    # include <stdlib.h>
    # include <stdio.h>
    # include <fcntl.h>
    # include <sys/types.h>
    # include <sys/wait.h>
    # include "../libft/libft.h"

typedef struct s_pipex
{
    int infile;       // File descriptor do arquivo de entrada
    int outfile;      // File descriptor do arquivo de saída
    int pipe_fd[2];   // Pipe [0] = leitura, [1] = escrita
    pid_t pid1;       // PID do primeiro processo (cmd1)
    pid_t pid2;       // PID do segundo processo (cmd2)
    char *cmd1_path;  // Caminho completo do primeiro comando
    char *cmd2_path;  // Caminho completo do segundo comando
    char **cmd1_args; // Argumentos do primeiro comando
    char **cmd2_args; // Argumentos do segundo comando
    char **envp;      // Variáveis de ambiente
} t_pipex;

char    **get_paths(char **envp);
char    *get_cmd_path(char *cmd, char **envp);
void    free_array(char **array);
void    is_error(int i, t_pipex *pipex);
// static int	count_words(const char *s, char c);
void	close_fds(t_pipex *pipex);
void	child_process(t_pipex *pipex);
void	parent_process(t_pipex *pipex);
void	run_pipex(t_pipex *pipex);
int	main(int argc, char **argv, char **envp);
char *construct_path(char *dir, char *cmd);
void    cleanup_and_exit(t_pipex *pipex, int exit_code);


#endif
