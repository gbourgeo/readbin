/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho_file_info_64.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:47:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/12/12 14:53:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macho_file_info.h"

static int		is_64(uint32_t magic)
{
	return (magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}

static int		is_swap(uint32_t magic)
{
	return (magic == MH_MAGIC || magic == MH_MAGIC_64);
}

void			macho_file_info_64(void *file, int file_size)
{
	struct mach_header_64		*header = (struct mach_header_64 *)file;
	uint32_t					offset = sizeof(*header);
	struct load_command			*cmd;
	struct segment_command_64	*segment;
	struct segment_command_64	*segtext;
	struct section_64			*sectext;
	char						maxprot[]  = "(   )";
	char						initprot[] = "(   )";
	struct section_64			*sectlast;

	ft_printf(CO2);
	ft_printf("addr\t\t magic\t\t bit\t endian\t\t cputype\t cpusubtype\t filetype\t ncmds\t sizecmds\t flags\n");
	ft_printf(DEF);
	ft_printf("%p\t %p\t %s\t %s\t %d\t\t %d\t\t %d\t\t %d\t %d\t\t %#.08x\n",
			  header, header->magic,
			  (!is_64(header->magic)) ? "32" : "64",
			  (!is_swap(header->magic)) ? "little-endian" : "big-endian",
			  header->cputype & ~CPU_ARCH_MASK, header->cpusubtype & ~CPU_SUBTYPE_MASK,
			  header->filetype, header->ncmds,
			  header->sizeofcmds, header->flags);
	ft_printf("\n");

	ft_printf(CO3);
	ft_printf("cmd\t\t cmdsize\t segname\t vmaddr\t\t vmsize\t fileoff\t filesize\t maxprot\t initprot\t nsects\t flags\n");
	ft_printf(DEF);
	for (size_t i = 0, j = 0; i < header->ncmds; i++)
	{
		ft_printf("%d ", i);
		cmd = (struct load_command *)(file + offset);
		if (cmd->cmd == LC_SEGMENT_64)
		{
			segment = (struct segment_command_64 *)cmd;
			if (ft_strcmp(segment->segname, SEG_TEXT) == 0)
				segtext = segment;
			maxprot[1] = (segment->maxprot & 0x1) ? 'R' : ' ';
			maxprot[2] = (segment->maxprot & 0x2) ? 'W' : ' ';
			maxprot[3] = (segment->maxprot & 0x4) ? 'X' : ' ';
			initprot[1] = (segment->initprot & 0x1) ? 'R' : ' ';
			initprot[2] = (segment->initprot & 0x2) ? 'W' : ' ';
			initprot[3] = (segment->initprot & 0x4) ? 'X' : ' ';
			ft_printf("%-11s\t %#.5x\t %-11s\t %-11p\t %#x\t %#-5x\t\t %#-5x\t\t %d %s\t %d %s\t %-5d\t %#x\n",
					  "LC_SEGMENT_64", segment->cmdsize, segment->segname, segment->vmaddr,
					  segment->vmsize, segment->fileoff, segment->filesize, segment->maxprot, maxprot,
					  segment->initprot, initprot, segment->nsects, segment->flags);
			if (segment->nsects)
			{
				struct section_64 *section = (struct section_64 *)(segment + 1);
				if (ft_strcmp(section->sectname, SECT_TEXT) == 0)
					sectext = section;
				ft_printf(CO4);
				ft_printf("\t section\t segment\t addr\t\t size\t offset\t align\t reloff\t nreloc\t flags\t\t 1\t 2\t3\n");
				ft_printf(DEF);
				for (j = 0; j < segment->nsects; j++) {
					ft_printf("\t %-15s %-11s\t %-11p\t %#.5x %#.5x %#x\t %#x\t %#x\t %#.8x\t %#x\t %#x\t %#x\n",
							  section[j].sectname, section[j].segname, section[j].addr,
							  section[j].size, section[j].offset, section[j].align, section[j].reloff,
							  section[j].nreloc, section[j].flags, section[j].reserved1,
							  section[j].reserved2, section[j].reserved3);
				}
			}
		}
		else if (cmd->cmd == LC_MAIN)
		{
			struct entry_point_command *entry = (struct entry_point_command *)cmd;
			ft_printf("%-11s\t %#.5x\t %#-11p\t %#x\n",
					  "LC_MAIN", entry->cmdsize, entry->entryoff, entry->stacksize);
			ft_printf(CO3);
			ft_printf("cmd\t\t cmdsize\t entryoff\t stacksize\n");
			ft_printf(DEF);
		}
		else if (cmd->cmd == LC_SYMTAB)
		{
			struct symtab_command *sym = (struct symtab_command *)cmd;
			ft_printf("%-11s\t %#.5x\t %#.5x\t %#.5x\t %#.5x\t %#.5x\n",
					  "LC_SYMTAB", sym->cmdsize, sym->symoff, sym->nsyms, sym->stroff, sym->strsize);
			ft_printf(CO3);
			ft_printf("cmd\t\t cmdsize\t symoff\t\t nsyms\t\t stroff\t\t strsize\n");
			ft_printf(DEF);
		}
		else if (cmd->cmd == LC_DYSYMTAB)
		{
			struct dysymtab_command *dsym = (struct dysymtab_command *)cmd;
			ft_printf("%-11s\t %#.5x %#.7p %#.7p %#.8p %#.8p "
					  "%#.7x %#.7x %#.4x %#.4x %#.7x %#.7x "
					  "%#.10x %#.11x\n",
					  "LC_DYSYMTAB", dsym->cmdsize, dsym->ilocalsym, dsym->nlocalsym, dsym->iextdefsym, dsym->nextdefsym,
					  dsym->iundefsym, dsym->nundefsym, dsym->tocoff, dsym->ntoc, dsym->modtaboff, dsym->nmodtab,
					  dsym->extrefsymoff, dsym->nextrefsyms);
			ft_printf(CO3);
			ft_printf("cmd\t\t cmdsize ilocalsym nlocalsym iextdefsym nextdefsym iundefsym nundefsym tocoff ntoc modtaboff nmodtab "
					  "extrefsymoff nextrefsyms\n");
			ft_printf(DEF);
			ft_printf("\t\t %#.12x %#.11x %#.9x %#.7x %#.9x %#.7x\n",
					  dsym->indirectsymoff, dsym->nindirectsyms, dsym->extreloff, dsym->nextrel, dsym->locreloff, dsym->nlocrel);
			ft_printf(CO3);
			ft_printf("\t\t indirectsymoff nindirectsyms extreloff nextrel locreloff nlocrel\n");
			ft_printf(DEF);
		}
		else
		{
			char *name[] = { "", "LC_SEGMENT", "LC_SYMTAB", "LC_SYMSEG", "LC_THREAD", "LC_UNIXTHREAD", "LC_LOADFVMLIB",
							 "LC_ICFVMLIB", "LC_IDENT", "LC_FVMFILE", "LC_PREPAGE", "LC_DYSYMTAB", "LC_LOAD_DYLIB",
							 "LC_ID_DYLIB", "LC_LOAD_DYLINKER", "LC_ID_DYLINKER", "LC_PREBOUND_DYLIB", "LC_ROUTINES",
							 "LC_SUB_FRAMEWORK", "LC_SUB_UMBRELLA", "LC_CLIENT", "LC_LIBRARY", "LC_TWOLEVEL_HINTS", 
							 "LC_PREBIND_CKSUM", "???"/*LC_LOAD_WEAK_DYLIB*/, "LC_SEGMENT_64", "LC_ROUTINES_64", "LC_UUID",
							 "???"/*LC_RPATH*/, "LC_CODE_SIGNATURE", "LC_SEGMENT_SPLIT_INFO", "???"/*LC_REEXPORT_DYLIB*/, "LC_LAZY_LOAD_DYLIB",
							 "LC_ENCRYPTION_INFO", "LC_DYLD_INFO", "???"/*LC_DYLD_INFO_ONLY, LC_LOAD_UPWARD_DYLIB*/, 
							 "LC_VERSION_MIN_MACOSX", "LC_VERSION_MIN_IPHONEOS", "LC_FUNCTION_STARTS", "LC_DYLD_ENVIRONMENT",
							 "LC_MAIN", "LC_DATA_IN_CODE", "LC_SOURCE_VERSION", "LC_DYLIB_CODE_SIGN_DRS", "LC_ENCRYPTION_INFO_64",
							 "LC_LINKER_OPTION", "LC_LINKER_OPTIMIZATION_HINT", "LC_VERSION_MIN_TVOS", "LC_VERSION_MIN_WATCHOS" };

			if (cmd->cmd <= 0x30)
				ft_printf("%-11s\t %#.5x\n", name[cmd->cmd], cmd->cmdsize);
			else if (cmd->cmd == LC_LOAD_WEAK_DYLIB)
				ft_printf("%-11s\t %#.5x\n", name[0x18], cmd->cmdsize);
			else if (cmd->cmd == LC_RPATH)
				ft_printf("%-11s\t %#.5x\n", name[0x1c], cmd->cmdsize);
			else if (cmd->cmd == LC_DYLD_INFO_ONLY)
				ft_printf("%-11s\t %#.5x\n", name[0x22], cmd->cmdsize);
			else if (cmd->cmd == LC_LOAD_UPWARD_DYLIB)
				ft_printf("%-11s\t %#.5x\n", name[0x23], cmd->cmdsize);
			else if (cmd->cmd == LC_LOAD_UPWARD_DYLIB)
				ft_printf("%-11s\t %#.5x\n", name[0x23], cmd->cmdsize);
			else
				ft_printf("%-11d\t %#.5x\n", cmd->cmd, cmd->cmdsize);

		}
		offset += cmd->cmdsize;
	}

	print_hex((u_char *)file, file_size);

/* 	struct section_64 *section = (struct section_64 *)(segtext + 1); */
/* 	ft_printf("%s %#x\n", section->sectname, section->size); */
/* 	print_hex((u_char *)section, sizeof(*section)); */
/* 	print_hex((u_char *)(file + section->offset), section->size); */
}
