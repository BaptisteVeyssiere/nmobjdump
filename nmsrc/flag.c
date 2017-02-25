/*
** flag.c for nm in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Fri Feb 24 00:39:41 2017 Baptiste Veyssiere
** Last update Sun Feb 26 00:06:19 2017 Baptiste Veyssiere
*/

#include "nm.h"

char	get_global_flags(uint16_t index, uint32_t type, uint32_t flags)
{
  char		symbol;

  if (index == SHN_UNDEF)
    symbol = 'U';
  else if (index == SHN_ABS)
    symbol = 'A';
  else if (index == SHN_COMMON)
    symbol = 'C';
  else if (type == SHT_NOBITS && flags == (SHF_ALLOC | SHF_WRITE))
    symbol = 'B';
  else if (type == SHT_PROGBITS && flags == SHF_ALLOC)
    symbol = 'R';
  else if (type == SHT_PROGBITS && flags == (SHF_ALLOC | SHF_WRITE))
    symbol = 'D';
  else if (type == SHT_PROGBITS && flags == (SHF_ALLOC | SHF_EXECINSTR))
    symbol = 'T';
  else if (type == SHT_DYNAMIC)
    symbol = 'D';
  else
    symbol = '?';
  return (symbol);
}

char	get_flag32(Elf32_Sym *symtab, Elf32_Shdr *start)
{
  char		symbol;
  uint16_t	index;
  uint32_t	type;
  uint32_t	flags;
  unsigned char	info;

  index = symtab->st_shndx;
  type = start[symtab->st_shndx].sh_type;
  flags = start[symtab->st_shndx].sh_flags;
  info = symtab->st_info;
  if (ELF32_ST_BIND(info) == STB_GNU_UNIQUE)
     symbol = 'u';
  if (ELF32_ST_BIND(info) == STB_WEAK)
    symbol = index == SHN_UNDEF ? 'w' : 'W';
  else if (ELF32_ST_BIND(info) == STB_WEAK && ELF32_ST_TYPE(info))
    symbol = index == SHN_UNDEF ? 'v' : 'V';
  else
    symbol = get_global_flags(index, type, flags);
  if (ELF32_ST_BIND(info) == STB_LOCAL && symbol != '?')
    symbol += 32;
  if ((type == SHT_FINI_ARRAY || type == SHT_INIT_ARRAY) && flags == 3)
    symbol = 't';
  return (symbol);
}

char	get_flag64(Elf64_Sym *symtab, Elf64_Shdr *start)
{
  char		symbol;
  uint16_t	index;
  uint32_t	type;
  uint32_t	flags;
  unsigned char	info;

  index = symtab->st_shndx;
  type = start[symtab->st_shndx].sh_type;
  flags = start[symtab->st_shndx].sh_flags;
  info = symtab->st_info;
  if (ELF64_ST_BIND(info) == STB_GNU_UNIQUE)
     symbol = 'u';
  if (ELF64_ST_BIND(info) == STB_WEAK)
    symbol = index == SHN_UNDEF ? 'w' : 'W';
  else if (ELF64_ST_BIND(info) == STB_WEAK &&
	   ELF64_ST_TYPE(info))
    symbol = index == SHN_UNDEF ? 'v' : 'V';
  else
    symbol = get_global_flags(index, type, flags);
  if (ELF64_ST_BIND(info) == STB_LOCAL && symbol != '?')
    symbol += 32;
  if ((type == SHT_FINI_ARRAY || type == SHT_INIT_ARRAY) && flags == 3)
    symbol = 't';
  return (symbol);
}
