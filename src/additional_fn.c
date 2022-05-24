/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_fn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pngamcha <pngamcha@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 00:02:35 by pngamcha          #+#    #+#             */
/*   Updated: 2022/05/24 12:04:38 by pngamcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

void	shell_ls(void)
{
	DIR				*d;
	struct dirent	*filename;

	d = opendir(getcwd(NULL, 1024));
	if (!d)
		perror("");
	else
	{
		filename = readdir(d);
		while (filename)
		{
			printf("%s  ", filename->d_name);
			filename = readdir(d);
		}
		printf("\n");
		closedir(d);
	}
}

void	shell_clear(void)
{
	printf(CLEAR_SCRN);
}
