/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_file_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 22:57:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/12/12 14:52:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macho_file_info.h"

static int		is_macho(uint32_t magic)
{
	return (magic == MH_MAGIC || magic == MH_CIGAM ||
			magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}	

int			macho_file_info(t_env *e)
{
	struct mach_header	*header;
	uint32_t			magic;

	header = (struct mach_header *)file;
	magic = header->magic;
	if (!is_macho(magic))
		ft_fatal("Invalid MACHO file type");
	if (header->filetype != MH_EXECUTE)
		ft_fatal("Unsupported MACHO file type");

	macho_file_info_64(file, file_size);
}
