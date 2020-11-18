/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 22:44:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/11/18 19:59:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "elf_file_info.h"

static int		ft_fatal(char *str, t_env *e)
{
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

	Elf64_Ehdr	*file_header;
	file_header = (Elf64_Ehdr *)e.filemap;

	if (ft_memcmp(file_header->e_ident, ELFMAG, SELFMAG))
		ft_fatal("Invalid ELF file type", &e);
	if (file_header->e_ident[EI_CLASS] == ELFCLASSNONE)
		ft_fatal("Unsupported ELF file class", &e);
	if (file_header->e_ident[EI_DATA] == ELFDATANONE)
		ft_fatal("Unsupported ELF file byte order", &e);
	if (file_header->e_ident[EI_VERSION] != EV_CURRENT)
		ft_fatal("Unsupported ELF file version", &e);
	if (file_header->e_type != ET_EXEC && file_header->e_type != ET_DYN)
		ft_fatal("Unsupported ELF file type", &e);
	if (file_header->e_version != EV_CURRENT)
		ft_fatal("Unsupported ELF file version", &e);

	void	(*file_info[2])(t_env *) = { elf_file_info_32, elf_file_info_64 };

	file_info[file_header->e_ident[EI_CLASS] - 1](&e);
	munmap(e.filemap, e.file_size);
	if (e.x_section)
		free(e.x_section);
	return 0;
}
