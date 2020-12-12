/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_file_info.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 20:12:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/12/12 15:04:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELF_FILE_INFO_H
# define ELF_FILE_INFO_H

# include "main.h"

void		elf_file_info_32(t_env *e);
void		elf_file_info_64(t_env *e);

#endif
