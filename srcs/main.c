/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 22:44:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/12/12 15:11:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				ft_fatal(char *str, t_env *e)
{
	if (str)
		ft_printf("%s: %s '%s'\n", e->prog, str, e->file);
	if (e->fd >= 0)
		close(e->fd);
	if (e->filemap != MAP_FAILED)
		munmap(e->filemap, e->file_size);
	if (e->x_section)
		free(e->x_section);
	exit(1);
}

int				main(int ac, char **av)
{
	t_env	e;

	(void)ac;
	ft_memset(&e, 0, sizeof(e));
	e.prog = ft_strrchr(av[0], '/');
	e.prog = (e.prog) ? e.prog + 1 : av[0];
	e.fd = -1;
	e.filemap = MAP_FAILED;
	parse_opt(av, &e);
	if ((e.fd = open(e.file, O_RDONLY)) == -1)
		ft_fatal("error opening", &e);
	if ((e.file_size = lseek(e.fd, 1, SEEK_END)) == -1)
		ft_fatal("cant seek end of file", &e);
	e.filemap = mmap(NULL, e.file_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, e.fd, 0);
	if (e.filemap == MAP_FAILED) {
		ft_fatal("cant map file", &e);
	}
	close(e.fd);
	e.fd = -1;

#ifdef __linux__
	elf_file_info(&e);
#elif __darwin__
	macho_file_info(&e);
#endif

	munmap(e.filemap, e.file_size);
	if (e.x_section)
		free(e.x_section);
	return 0;
}
