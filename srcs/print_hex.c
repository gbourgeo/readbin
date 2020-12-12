/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:49:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/12/12 14:49:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			print_hex(u_char *file, size_t size, size_t offset, size_t endian, int xprint)
{
	size_t i = 0;
	size_t j = 0;
	size_t j2 = 0;

	file += offset;
	while (i < size) {
		if (i % 16 == 0)
			ft_printf("0x%.08x", i + offset);
		if (endian == MY_LITTLE_ENDIAN) {
			for (size_t k = 0; k < 4; k++) {
				for (size_t l = (i + 4 > size) ? size : i + 4; l > i; l--) {
					if (l == size || (l - i) % 4 == 0)
						ft_printf(" ");
					ft_printf("%02x", file[l - 1]);
				}
				i = (i + 4 > size) ? size : i + 4;
				if (i == size)
					break;
			}
		} else {
			for (size_t k = i + 16; i < size && i < k; i++) {
				if (i % 4 == 0)
					ft_printf(" ");
				ft_printf("%02x", file[i]);
			}
		}
		if (i == size || i % 16 == 0) {
			/*** Print TEXT ***/
			int space = 1;
			if (i % 16 != 0) {
				space += (35 - ((i % 16) * 2) - ((i % 16) / 4) + (i % 4 == 0));
			}
			write(1,"                                              ", space);

			j2 = j;
			if (endian == MY_LITTLE_ENDIAN) {
				for (size_t k = 0; k < 4; k++) {
					for (size_t l = (j + 4 >= i) ? i : j + 4; l > j; l--) {
						if (ft_isprint(file[l - 1]))
							ft_printf("%c", file[l - 1]);
						else
							ft_printf(".");
					}
					j += 4;
					if (j > i)
						break ;
				}
			} else {
				while (j < i) {
					if (ft_isprint(file[j]))
						ft_printf("%c", file[j]);
					else
						ft_printf(".");
					j++;
				}
			}

			/*** Print INT ***/
			if (xprint & OPT_XG_SECTION || xprint & OPT_XD_SECTION
			|| xprint & OPT_XW_SECTION || xprint & OPT_XX_SECTION) {

				int		opt_size;
				unsigned long int k;

				j = j2;
				space = 1;
				if (i % 16 != 0) {
					space += (16 - (i % 16));
				}
				write(1,"                                              ", space);

				if (endian == MY_LITTLE_ENDIAN) {
					while (j < i) {
						opt_size = (xprint & OPT_XG_SECTION) ? 8 : (xprint & OPT_XD_SECTION) ? 4 : (xprint & OPT_XW_SECTION) ? 2 : 1;
						while (j + opt_size > i)
							opt_size /= 2;
						if (opt_size == sizeof(unsigned long int)) {
							k = *(unsigned long int *)(file + j);
						} else if (opt_size == sizeof(unsigned int)) {
							k = *(unsigned int *)(file + j);
						} else if (opt_size == sizeof(unsigned short)) {
							k = *(unsigned short *)(file + j);
						} else {
							k = *(unsigned char *)(file + j);
						}
						printf("%.*lx ", opt_size * 2, k);
						j += opt_size;
					}
				} else {
					for (size_t k = 0; k < 4; k++) {
						for (size_t l = (j + 4 >= i) ? i : j + 4; l > j; l--) {
							if (ft_isprint(file[l - 1]))
								ft_printf("%c", file[l - 1]);
							else
								ft_printf(".");
						}
						j += 4;
						if (j > i)
							break ;
					}
				}
			}
			printf("\n");
		}
	}
}
