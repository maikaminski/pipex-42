/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makamins <makamins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:56:27 by makamins          #+#    #+#             */
/*   Updated: 2025/03/19 17:56:47 by makamins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	init_pipex(&pipex, argc, argv, envp);
	validate_commands(&pipex, argv);
	get_command_paths(&pipex);
	run_pipex(&pipex);
	cleanup_and_exit(&pipex, 0);
	return (0);
}
