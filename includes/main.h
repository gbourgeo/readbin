/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:10:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/12/12 15:03:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/mman.h>

# include "ft_printf.h"
# include "libft.h"

# ifdef __linux__
#  include <elf.h>
#  define MY_LITTLE_ENDIAN	ELFDATA2LSB
#  define MY_BIG_ENDIAN		ELFDATA2MSB
# elif __darwin__
#  define MY_LITTLE_ENDIAN	1
#  define MY_BIG_ENDIAN		2
# endif

# define DEF				"\e[1;0m"
# define CO1				"\e[1;31m"
# define CO2				"\e[1;32m"
# define CO3				"\e[1;33m"
# define CO4				"\e[1;34m"
# define CO5				"\e[1;35m"
# define CO6				"\e[1;36m"

typedef struct	s_section
{
	char		*name;
	int			bit;
}				t_sec;

typedef struct	s_env
{
	char	*prog;
	char	*file;
	void	*filemap;
	ssize_t	file_size;
	int		fd;
	size_t	option;
	t_sec	*x_section;
	size_t	x_len;
	char	*error;
}				t_env;

typedef struct	s_option
{
	char	*opt;
	char	*description;
	size_t	bit;
	int		(*func)();
}				t_opt;

/*
** 0 0 0 0 0 0 0 0  0 0 0 0 0 0 0 0
**                        d y c g h
*/

enum
{
	OPT_HEADER        = (1UL << 0),
	OPT_SEGMENT       = (1UL << 1),
	OPT_SECTION       = (1UL << 2),
	OPT_SYMBOL        = (1UL << 3),
	OPT_DYNAMIC       = (1UL << 4),
	OPT_X_SECTION     = (1UL << 5),
	OPT_XG_SECTION    = (1UL << 6),
	OPT_XD_SECTION    = (1UL << 7),
	OPT_XW_SECTION    = (1UL << 8),
	OPT_XX_SECTION    = (1UL << 9),
	OPT_V_SECTION     = (1UL << 10),
	OPT_LITTLE_ENDIAN = (1UL << 11),
	OPT_BIG_ENDIAN    = (1UL << 12),
	OPT_HELP          = (1UL << 13),
};

int			ft_fatal(char *str, t_env *e);
void		parse_opt(char **av, t_env *e);
void		elf_file_info(t_env *e);
void		macho_file_info(t_env *e);
void		print_hex(unsigned char *file, size_t size, size_t offset, size_t endian, int xprint);

#endif
