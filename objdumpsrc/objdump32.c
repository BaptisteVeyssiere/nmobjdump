/*
** objdump32.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Mon Feb 20 20:31:01 2017 Baptiste Veyssiere
** Last update Mon Feb 20 20:57:38 2017 Baptiste Veyssiere
*/

#include "objdump.h"

static void	print_string(unsigned int i, char *buffer)
{
  int			j;
  static unsigned int	newline = 0;

  j = i;
  while (j % 16)
    {
      if (j % 4 == 0 && j % 16)
	printf(" ");
      printf("  ");
      ++j;
    }
  printf("  ");
  while (newline < i)
    {
      if (isprint(buffer[newline]))
	printf("%c", buffer[newline]);
      else
	printf(".");
      ++newline;
    }
  while (newline++ % 16)
    printf(" ");
  newline = i;
  printf("\n");
}

static void	print_section32(void *data, Elf32_Shdr section_header)
{
  char	*buffer;
  int	address;

  address = section_header.sh_addr;
  buffer = (char*)((char*)data + section_header.sh_offset);
  for (unsigned int i = 0; i < section_header.sh_size; i += 0)
    {
      if (!(i % 16))
	printf(" %06x ", address);
      printf("%02x", buffer[i++]);
      if (!(i % 4) && (i % 16) && i < section_header.sh_size)
	printf(" ");
      if (!(i % 16))
	address += 16;
      if (!(i % 16) || i >= section_header.sh_size)
	print_string(i, buffer);
    }
}

static void	print_sections32(Elf32_Ehdr *data)
{
  Elf32_Shdr	*start;
  Elf32_Shdr	shstrtab_section;
  char		*namestring;
  Elf32_Shdr	section_header;
  char		*name;

  start = (Elf32_Shdr*)((void*)data + data->e_shoff);
  shstrtab_section = start[data->e_shstrndx];
  namestring = (char*)((void*)data + shstrtab_section.sh_offset);
  for (int i = 1; i < data->e_shnum; i++)
    {
      section_header = start[i];
      name = namestring + section_header.sh_name;
      printf("Section content %s :\n", name);
      print_section32(data, section_header);
    }
}

void	objdump32(void *data, char *filename)
{
  Elf32_Ehdr	*header;
  char		*architecture;

  header = (Elf32_Ehdr*)data;
  architecture = header->e_machine == EM_386 ? "i386" : "notf";
  printf("\n%s:     file format 'A Remplir'\n", filename);
  printf("architecture: %s, flags 0x%08x:\n", architecture, header->e_flags);
  printf("start adress 0x%016x\n\n", (int)header->e_entry);
  print_sections32(data);
}
