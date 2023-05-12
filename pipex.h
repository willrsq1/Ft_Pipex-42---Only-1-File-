/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 00:02:10 by wruet-su          #+#    #+#             */
/*   Updated: 2023/05/13 01:30:08 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h> //write
# include <stdlib.h>   //malloc
# include <unistd.h> //pipe
# include <sys/types.h> //open fork
# include <sys/stat.h> //open
# include <fcntl.h> //open
# include <sys/wait.h> //waitpid
# include <stdio.h>

# define FIRST_CHILD 0
# define SECOND_CHILD 1

#endif
