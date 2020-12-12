# readbin
Read binary tool, just like readelf for Linux

## Usage
```sh
readbin [-h] [-g] [-c] [-y] [-d] [-xg] [-xd] [-xw] [-xx] [-x] [-v] [-LE] [-BE] [-H] file
	-h	Print file Header
	-g	Print file Segments
	-c	Print file Sections
	-y	Print file Symbol Table
	-d	Print file Dynamic Section
	-xg	Print hexa/text/long_int specified Section
	-xd	Print hexa/text/int      specified Section
	-xw	Print hexa/text/short    specified Section
	-xx	Print hexa/text/char     specified Section
	-x	Print hexa/text          specified Section
	-v	Print Symbol Versionning
	-LE	Force output to be print in little endian
	-BE	Force output to be print in big endian
	-H	Print Help
```

## Examples
```sh
$ ./readbin -h readbin 
file info:
size	 class	 encoding	 version OS/ABI		 ABIv	 padding
0x0e749	 64-bit	 little-endian	 1	 System V	 0	 0

file header:
Entry Point	 phoff	 shoff	 ehsize	 phentsize	 phnum	 shentsize	 shnum	 shstrndx
0x0000000020f0	 0x40	 0xdfc8 0x40	 0x38		 11	 0x40		 30	 0x1d
```

```sh
$ ./readbin -g readbin 
file info:
size	 class	 encoding	 version OS/ABI		 ABIv	 padding
0x0e749	 64-bit	 little-endian	 1	 System V	 0	 0

program header: (11 entries)
type		 flags	 offset	 vaddr		 paddr		 filesz	 memsz	 align
PHDR           	 R    	 0x00040 0x000040	 0x000040	 0x00268 0x00268 0x000008
INTERP         	 R    	 0x002a8 0x0002a8	 0x0002a8	 0x0001c 0x0001c 0x000001
LOAD           	 R    	 0x00000 0x000000	 0x000000	 0x01428 0x01428 0x001000
LOAD           	 R X  	 0x02000 0x002000	 0x002000	 0x06a6d 0x06a6d 0x001000
LOAD           	 R    	 0x09000 0x009000	 0x009000	 0x01ec0 0x01ec0 0x001000
LOAD           	 RW   	 0x0bde8 0x00cde8	 0x00cde8	 0x00770 0x00778 0x001000
DYNAMIC        	 RW   	 0x0bdf8 0x00cdf8	 0x00cdf8	 0x001e0 0x001e0 0x000008
NOTE           	 R    	 0x002c4 0x0002c4	 0x0002c4	 0x00044 0x00044 0x000004
GNU_EH_FRAME   	 R    	 0x0a1b0 0x00a1b0	 0x00a1b0	 0x00294 0x00294 0x000004
GNU_STACK      	 RW   	 0x00000 0x000000	 0x000000	 0x00000 0x00000 0x000010
GNU_RELRO      	 R    	 0x0bde8 0x00cde8	 0x00cde8	 0x00218 0x00218 0x000001
```

```sh
$ ./readbin -xg .dynsym readbin 
file info:
size	 class	 encoding	 version OS/ABI		 ABIv	 padding
0x0e749	 64-bit	 little-endian	 1	 System V	 0	 0

'.dynsym' section:
0x00000330 00000000 00000000 00000000 00000000 ................ 0000000000000000 0000000000000000 
0x00000340 00000000 00000000 0000006a 00000012 ...........j.... 0000000000000000 000000120000006a 
0x00000350 00000000 00000000 00000000 00000000 ................ 0000000000000000 0000000000000000 
0x00000360 00000010 00000012 00000000 00000000 ................ 0000001200000010 0000000000000000 
0x00000370 00000000 00000000 0000007b 00000020 ...........{...  0000000000000000 000000200000007b 
0x00000380 00000000 00000000 00000000 00000000 ................ 0000000000000000 0000000000000000 
0x00000390 00000064 00000012 00000000 00000000 ...d............ 0000001200000064 0000000000000000 
0x000003a0 00000000 00000000 0000001f 00000012 ................ 0000000000000000 000000120000001f 
0x000003b0 00000000 00000000 00000000 00000000 ................ 0000000000000000 0000000000000000 
0x000003c0 00000018 00000012 00000000 00000000 ................ 0000001200000018 0000000000000000 
0x000003d0 00000000 00000000 00000024 00000012 ...........$.... 0000000000000000 0000001200000024 
0x000003e0 00000000 00000000 00000000 00000000 ................ 0000000000000000 0000000000000000 
0x000003f0 00000038 00000012 00000000 00000000 ...8............ 0000001200000038 0000000000000000 
0x00000400 00000000 00000000 00000052 00000012 ...........R.... 0000000000000000 0000001200000052 
0x00000410 00000000 00000000 00000000 00000000 ................ 0000000000000000 0000000000000000 
0x00000420 00000097 00000020 00000000 00000000 ....... ........ 0000002000000097 0000000000000000 
0x00000430 00000000 00000000 0000002a 00000012 ...........*.... 0000000000000000 000000120000002a 
0x00000440 00000000 00000000 00000000 00000000 ................ 0000000000000000 0000000000000000 
0x00000450 00000031 00000012 00000000 00000000 ...1............ 0000001200000031 0000000000000000 
0x00000460 00000000 00000000 0000003e 00000012 ...........>.... 0000000000000000 000000120000003e 
0x00000470 00000000 00000000 00000000 00000000 ................ 0000000000000000 0000000000000000 
0x00000480 0000000b 00000012 00000000 00000000 ................ 000000120000000b 0000000000000000 
0x00000490 00000000 00000000 000000a6 00000020 ...............  0000000000000000 00000020000000a6 
0x000004a0 00000000 00000000 00000000 00000000 ................ 0000000000000000 0000000000000000 
0x000004b0 00000043 00000022 00000000 00000000 ...C..."........ 0000002200000043 0000000000000000 
0x000004c0 00000000 00000000                   ........         0000000000000000 
```

## Author(s)
Gilles Bourgeois