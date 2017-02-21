/*
** objdump.h for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Mon Feb 20 15:34:06 2017 Baptiste Veyssiere
** Last update Mon Feb 20 21:07:57 2017 Baptiste Veyssiere
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

void	objdump64(void*, char*);
void	objdump32(void*, char*);

#endif /* !OBJDUMP_H_ */
