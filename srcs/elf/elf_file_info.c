/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_file_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:15:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/12/12 14:19:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elf_file_info.h"

void		elf_file_info(t_env *e)
{
	void	(*file_info[2])(t_env *) = { elf_file_info_32, elf_file_info_64 };
	Elf64_Ehdr	*file_header;

	file_header = (Elf64_Ehdr *)e->filemap;
	if (ft_memcmp(file_header->e_ident, ELFMAG, SELFMAG))
		ft_fatal("Invalid ELF file type", e);
	if (file_header->e_ident[EI_CLASS] == ELFCLASSNONE)
		ft_fatal("Unsupported ELF file class", e);
	if (file_header->e_ident[EI_DATA] == ELFDATANONE)
		ft_fatal("Unsupported ELF file byte order", e);
	if (file_header->e_ident[EI_VERSION] != EV_CURRENT)
		ft_fatal("Unsupported ELF file version", e);
	if (file_header->e_type != ET_EXEC && file_header->e_type != ET_DYN)
		ft_fatal("Unsupported ELF file type", e);
	if (file_header->e_version != EV_CURRENT)
		ft_fatal("Unsupported ELF file version", e);

	file_info[file_header->e_ident[EI_CLASS] - 1](e);
}