/*
** flag.c for nm in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Fri Feb 24 00:39:41 2017 Baptiste Veyssiere
** Last update Sat Feb 25 18:18:55 2017 Baptiste Veyssiere
*/

#include "nm.h"

char	get_global_flags64(Elf64_Sym *symtab, Elf64_Shdr *start)
{
  char	symbol;

  if (symtab->st_shndx == SHN_UNDEF)
    symbol = 'U';
  else if (symtab->st_shndx == SHN_ABS)
    symbol = 'A';
  else if (symtab->st_shndx == SHN_COMMON)
    symbol = 'C';
  else if (start[symtab->st_shndx].sh_type == SHT_NOBITS &&
	   start[symtab->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    symbol = 'B';
  else if (start[symtab->st_shndx].sh_type == SHT_PROGBITS &&
	   start[symtab->st_shndx].sh_flags == SHF_ALLOC)
    symbol = 'R';
  else if (start[symtab->st_shndx].sh_type == SHT_PROGBITS &&
	   start[symtab->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    symbol = 'D';
  else if (start[symtab->st_shndx].sh_type == SHT_PROGBITS &&
	   start[symtab->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    symbol = 'T';
  else if (start[symtab->st_shndx].sh_type == SHT_DYNAMIC)
    symbol = 'D';
  else
    symbol = '?';
  return (symbol);
}

char	get_flag64(Elf64_Sym *symtab, Elf64_Shdr *start)
{
  char	symbol;

  if (ELF64_ST_BIND(symtab->st_info) == STB_GNU_UNIQUE)
     symbol = 'u';
  if (ELF64_ST_BIND(symtab->st_info) == STB_WEAK)
    symbol = symtab->st_shndx == SHN_UNDEF ? 'w' : 'W';
  else if (ELF64_ST_BIND(symtab->st_info) == STB_WEAK &&
	   ELF64_ST_TYPE(symtab->st_info))
    symbol = symtab->st_shndx == SHN_UNDEF ? 'v' : 'V';
  else
    symbol = get_global_flags64(symtab, start);
  if (ELF64_ST_BIND(symtab->st_info) == STB_LOCAL && symbol != '?')
    symbol += 32;
  if ((start[symtab->st_shndx].sh_type == SHT_FINI_ARRAY ||
       start[symtab->st_shndx].sh_type == SHT_INIT_ARRAY) &&
      start[symtab->st_shndx].sh_flags == 3)
    symbol = 't';
  return (symbol);
}

char	get_global_flags32(Elf32_Sym *symtab, Elf32_Shdr *start)
{
  char	symbol;

  if (symtab->st_shndx == SHN_UNDEF)
    symbol = 'U';
  else if (symtab->st_shndx == SHN_ABS)
    symbol = 'A';
  else if (symtab->st_shndx == SHN_COMMON)
    symbol = 'C';
  else if (start[symtab->st_shndx].sh_type == SHT_NOBITS &&
	   start[symtab->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    symbol = 'B';
  else if (start[symtab->st_shndx].sh_type == SHT_PROGBITS &&
	   start[symtab->st_shndx].sh_flags == SHF_ALLOC)
    symbol = 'R';
  else if (start[symtab->st_shndx].sh_type == SHT_PROGBITS &&
	   start[symtab->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    symbol = 'D';
  else if (start[symtab->st_shndx].sh_type == SHT_PROGBITS &&
	   start[symtab->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    symbol = 'T';
  else if (start[symtab->st_shndx].sh_type == SHT_DYNAMIC)
    symbol = 'D';
  else
    symbol = '?';
  return (symbol);
}

char	get_flag32(Elf32_Sym *symtab, Elf32_Shdr *start)
{
  char	symbol;

  if (ELF32_ST_BIND(symtab->st_info) == STB_GNU_UNIQUE)
     symbol = 'u';
  if (ELF32_ST_BIND(symtab->st_info) == STB_WEAK)
    symbol = symtab->st_shndx == SHN_UNDEF ? 'w' : 'W';
  else if (ELF32_ST_BIND(symtab->st_info) == STB_WEAK &&
	   ELF32_ST_TYPE(symtab->st_info))
    symbol = symtab->st_shndx == SHN_UNDEF ? 'v' : 'V';
  else
    symbol = get_global_flags32(symtab, start);
  if (ELF32_ST_BIND(symtab->st_info) == STB_LOCAL && symbol != '?')
    symbol += 32;
  if ((start[symtab->st_shndx].sh_type == SHT_FINI_ARRAY ||
       start[symtab->st_shndx].sh_type == SHT_INIT_ARRAY) &&
      start[symtab->st_shndx].sh_flags == 3)
    symbol = 't';
  return (symbol);
}
