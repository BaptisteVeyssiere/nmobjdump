/*
** flag.c for nm in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Fri Feb 24 00:39:41 2017 Baptiste Veyssiere
** Last update Sun Feb 26 00:33:47 2017 Baptiste Veyssiere
*/

#include "nm.h"

char	get_index_flags(uint16_t index)
{
  char		flags[] = {'U', 'A', 'C'};
  uint16_t	indexs[] = {SHN_UNDEF, SHN_ABS, SHN_COMMON};

  for (int i = 0; i < 3; i++)
    if (index == indexs[i])
      return (flags[i]);
  return ('?');
}

char	get_type_flags(uint32_t type, uint32_t flag)
{
  char		flags[] = {'B', 'R', 'D', 'T'};
  uint32_t	types[] = {SHT_NOBITS, SHT_PROGBITS, SHT_PROGBITS, SHT_PROGBITS};
  uint32_t	flags_tab[] = {(SHF_ALLOC | SHF_WRITE), SHF_ALLOC,
			       (SHF_ALLOC | SHF_WRITE), (SHF_ALLOC | SHF_EXECINSTR)};

  for (int i = 0; i < 4; i++)
    if (type == types[i] && flag == flags_tab[i])
      return (flags[i]);
  return ('?');
}

char	get_global_flags(uint16_t index, uint32_t type, uint32_t flags)
{
  char		symbol;

  symbol = '?';
  if ((symbol = get_index_flags(index)) != '?')
    return (symbol);
  else if ((symbol = get_type_flags(type, flags)) != '?')
    return (symbol);
  else if (type == SHT_DYNAMIC)
    symbol = 'D';
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
    {
      symbol = index == SHN_UNDEF ? 'w' : 'W';
      if (ELF32_ST_TYPE(info) == STT_OBJECT)
	symbol = index == SHN_UNDEF ? 'v' : 'V';
    }
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
    {
      symbol = index == SHN_UNDEF ? 'w' : 'W';
      if (ELF64_ST_TYPE(info) == STT_OBJECT)
	symbol = index == SHN_UNDEF ? 'v' : 'V';
    }
  else
    symbol = get_global_flags(index, type, flags);
  if (ELF64_ST_BIND(info) == STB_LOCAL && symbol != '?')
    symbol += 32;
  if ((type == SHT_FINI_ARRAY || type == SHT_INIT_ARRAY) && flags == 3)
    symbol = 't';
  return (symbol);
}
