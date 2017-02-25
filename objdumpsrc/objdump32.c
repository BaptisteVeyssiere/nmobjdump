/*
** objdump32.c for objdump32 in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump/objdumpsrc
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Wed Feb 22 17:03:37 2017 Baptiste Veyssiere
** Last update Sat Feb 25 16:35:43 2017 Baptiste Veyssiere
*/

#include "objdump.h"

static uint32_t	get_flags(Elf32_Ehdr *data)
{
  uint32_t	flags;

  flags = 0;
  if (data->e_type == ET_REL)
    flags |= HAS_RELOC;
  else if (data->e_type == ET_EXEC)
    flags |= EXEC_P;
  else if (data->e_type == ET_DYN)
    flags |= DYNAMIC;

  if (has_symtab32(data))
    flags |= HAS_SYMS;
  if (has_paged32(data))
    flags |= D_PAGED;
  return (flags);
}

static void	print_string(unsigned int i, char *buffer, unsigned int *newline)
{
  printf(" ");
  while (*newline < i)
    {
      if (isprint(buffer[*newline]))
	printf("%c", buffer[*newline]);
      else
	printf(".");
      ++(*newline);
    }
  while ((*newline)++ % 16)
    printf(" ");
  *newline = i;
  printf("\n");
}

static void	print_section32(Elf32_Ehdr *data, Elf32_Shdr section_header)
{
  char	*buffer;
  int	address;
  unsigned int	newline;
  unsigned int	i;

  newline = 0;
  address = section_header.sh_addr;
  buffer = (char*)((char*)data + section_header.sh_offset);
  i = 0;
  while (i < section_header.sh_size)
    {
      printf(" %04x ", address);
      for (unsigned int j = 0; j < 4; j++)
	{
	  for (unsigned int k = 0; k < 4; k++)
	    if (i < section_header.sh_size)
	      printf("%02x", ((unsigned char*)buffer)[i++]);
	    else
	      printf("  ");
	  printf(" ");
	}
      address += 16;
      print_string(i, buffer, &newline);
    }
}

static void	print_sections32(Elf32_Ehdr *data)
{
  Elf32_Shdr	*start;
  char		*namestring;
  Elf32_Shdr	section_header;
  char		*name;

  start = (Elf32_Shdr*)((void*)data + data->e_shoff);
  namestring = (char*)((void*)data + start[data->e_shstrndx].sh_offset);
  for (int i = 1; i < data->e_shnum; i++)
    {
      section_header = start[i];
      name = namestring + section_header.sh_name;
      if (strcmp(name, ".strtab") == 0 ||
	  strcmp(name, ".shstrtab") == 0 ||
	  strcmp(name, ".symtab") == 0 ||
	  strcmp(name, ".bss") == 0 ||
	  strcmp(name, ".rela.text") == 0 ||
	  strcmp(name, ".rela.eh_frame") == 0 ||
	  strcmp(name, ".rel.text") == 0 ||
	  strcmp(name, ".rel.eh_frame") == 0 ||
	  section_header.sh_size == 0)
	continue;
      printf("Contents of section %s:\n", name);
      print_section32(data, section_header);
    }
}

void	objdump32(void *data, char *filename)
{
  Elf32_Ehdr	*header;
  char		*architecture;
  uint32_t	flags;

  header = (Elf32_Ehdr*)data;
  if (!header)
    return ;
  if (header->e_machine == EM_X86_64)
    architecture = "i386:x86-64";
  else if (header->e_machine == EM_386)
    architecture = "i386";
  else
    architecture = "notf";
  flags = get_flags(header);
  printf("\n%s:     file format elf32-i386\n", filename);
  printf("architecture: %s, flags 0x%08x:\n", architecture, flags);
  print_flags(flags);
  printf("start address 0x%08x\n\n", (int)header->e_entry);
  print_sections32(data);
}
