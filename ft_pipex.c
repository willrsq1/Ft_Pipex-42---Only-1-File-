/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 21:18:23 by wruet-su          #+#    #+#             */
/*   Updated: 2023/05/13 01:30:15 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stddef.h> //write
#include <stdlib.h>   //malloc
#include <unistd.h> //pipe
#include <sys/types.h> //open fork
#include <sys/stat.h> //open
#include <fcntl.h> //open
#include <sys/wait.h> //waitpid
#include <stdio.h>

#define FIRST_CHILD 0
#define SECOND_CHILD 1

static int	ft_child(char **argv, int mode, int *pipes, char **envp);
static char	*ft_get_command(char *token, char **envp, int i, int y);
static char	**ft_split(char *token, char c, int i, int y);
static char	*ft_strcat(char *s1, char *s2, int len1, int len2);

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipes[2];

	if (argc != 5)
		return (write(2, "Invalid Args\n", 14), 1);
	if (pipe(pipes) == -1)
		return (perror("Pipe"), 1);
	pid1 = fork();
	if (pid1 == -1)
		return (perror("First fork"), 1);
	if (!pid1)
		ft_child(argv, FIRST_CHILD, pipes, envp);
	pid2 = fork();
	if (pid2 == -1)
		return (perror("Second fork"), 1);
	if (!pid2)
		ft_child(argv, SECOND_CHILD, pipes, envp);
	close(pipes[0]);
	close(pipes[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

static int	ft_child(char **argv, int mode, int *pipes, char **envp)
{
	char	**tab;
	int		fd;
	char	*cmd;

	close(pipes[mode]);
	if (mode == FIRST_CHILD)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1 || dup2(fd, 0) == -1 || dup2(pipes[1], 1) == -1)
			return (perror(argv[1]), exit(1), 1);
	}
	if (mode == SECOND_CHILD)
	{
		fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 000644);
		if (fd == -1 || dup2(pipes[0], 0) == -1 || dup2(fd, 1) == -1)
			return (perror(argv[4]), exit(1), 1);
	}
	tab = ft_split(argv[2 + mode], ' ', -1, 0);
	cmd = ft_get_command(ft_strcat("/", tab[0], 0, 0), envp, 0, -1);
	if (cmd && execve(cmd, tab, envp) == -1)
		perror(cmd);
	fd = -1;
	while (tab && tab[++fd])
		free(tab[fd]);
	return (free(tab), exit(1), 1);
}

static char	*ft_get_command(char *token, char **envp, int i, int y)
{
	char	**paths;
	char	*path_tested;

	while (envp[i] && !(envp[i][0] == 'P' && envp[i][1] == 'A' && \
		envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '='))
		i++;
	if (envp[i])
		paths = ft_split(envp[i] + 5, ':', -1, 0);
	else
		paths = ft_split(" ", ' ', -1, 0);
	while (paths[++y])
	{
		path_tested = ft_strcat(paths[y], token, 0, 0);
		if (access(path_tested, X_OK) != -1)
			return (path_tested);
		free(path_tested);
	}
	if (access(token, X_OK) != -1)
		return (token);
	perror(&token[1]);
	i = -1;
	while (paths[++i])
		free(paths[i]);
	return (free(paths), free(token), NULL);
}

static char	**ft_split(char *token, char c, int i, int y)
{
	char	**tab;
	int		line;

	if (!token)
		return (NULL);
	while (token && token[++i])
		;
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (perror("Malloc failed"), NULL);
	line = -1;
	while (++line > -1 && *token)
	{
		y = -1;
		while (*token && *token == c)
			token++;
		tab[line] = malloc(sizeof(char) * (i + 1));
		if (!*token || (!tab[line] && write(2, "Malloc failed !\n", 17)))
			return (tab[line] = NULL, tab);
		while (*token && *token != c)
			tab[line][++y] = *token++;
		tab[line][++y] = '\0';
	}
	return (tab[line] = NULL, tab);
}

static char	*ft_strcat(char *s1, char *s2, int len1, int len2)
{
	char	*str;
	int		i;
	int		y;

	if (!s2 || !s1)
	{
		str = malloc(sizeof(char) * 2);
		str[0] = ' ';
		str[1] = '\0';
		return (str);
	}
	while (s1[len1])
		len1++;
	while (s2[len2])
		len2++;
	str = malloc(len1 + len2 + 1);
	if (!str)
		return (perror("Malloc strcat failed: "), s2);
	i = -1;
	while (s1 && s1[++i])
		str[i] = s1[i];
	y = -1;
	while (s2 && s2[++y])
		str[i + y] = s2[y];
	return (str[i + y] = '\0', str);
}
