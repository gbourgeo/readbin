/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_file_info.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:24:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/12/12 14:59:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHO_FILE_INFO_H
# define MACHO_FILE_INFO_H

# include <mach-o/loader.h>

# include "main.h"

void			macho_file_info_32(void *file, int file_size);
void			macho_file_info_64(void *file, int file_size);

#endif
