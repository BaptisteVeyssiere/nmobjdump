/*
** objdump.h for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Mon Feb 20 15:34:06 2017 Baptiste Veyssiere
** Last update Fri Feb 24 00:06:24 2017 Baptiste Veyssiere
*/

#ifndef OBJDUMP_H_
# define OBJDUMP_H_

#include <elf.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int	check_file(Elf32_Ehdr*, char*, char*);
int	objdump(char*, char*);
  
void	objdump64(void*, char*);
void	objdump32(void*, char*);

void	print_flags(uint32_t);

int	has_paged64(Elf64_Ehdr*);
int	has_symtab64(Elf64_Ehdr*);
int	has_paged32(Elf32_Ehdr*);
int	has_symtab32(Elf32_Ehdr*);

int	is_arfile(void*, char*, char*);

int	check_name64(Elf64_Ehdr*, char*);
int	check_name32(Elf32_Ehdr*, char*);

# ifndef __BFD_H_SEEN__
#  define __BFD_H_SEEN__

#  define BFD_NO_FLAGS	0x00
#  define HAS_RELOC	0x01
#  define EXEC_P	0x02
#  define HAS_LINENO	0x04
#  define HAS_DEBUG	0x08
#  define HAS_SYMS	0x10
#  define HAS_LOCALS	0x20
#  define DYNAMIC	0x40
#  define WP_TEXT	0x80
#  define D_PAGED	0x100

# endif /* !__BFD_H_SEEN__ */

#endif /* !OBJDUMP_H_ */
