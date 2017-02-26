##
## Makefile for 42sh in /home/VEYSSI_B/rendu/Programmation_Shell/test/test_42tree
##
## Made by Baptiste veyssiere
## Login   <VEYSSI_B@epitech.net>
##
## Started on  Wed May 18 21:26:30 2016 Baptiste veyssiere
##

OBJDUMP		= objdump

NM		= nm

RM		= rm -f

CC		= gcc

MKDIR		= mkdir -p

OBJDUMPSRC	= objdumpsrc/objdump64.c \
		objdumpsrc/objdump32.c \
		objdumpsrc/objdump.c \
		objdumpsrc/ar_parser.c \
		objdumpsrc/checks.c \
		objdumpsrc/check_r.c \
		objdumpsrc/flags.c

NMSRC		= nmsrc/nm64.c \
		nmsrc/nm32.c \
		nmsrc/nm.c \
		nmsrc/ar_parser.c \
		nmsrc/flag.c \
		nmsrc/printer.c \
		nmsrc/checks.c

OBJDUMPSRCDIR	= objdumpsrc

OBJDUMPOBJDIR	= objdumpobj

NMSRCDIR	= nmsrc

NMOBJDIR	= nmobj

NMOBJ		= $(NMSRC:$(NMSRCDIR)/%.c=$(NMOBJDIR)/%.o)

OBJDUMPOBJ	= $(OBJDUMPSRC:$(OBJDUMPSRCDIR)/%.c=$(OBJDUMPOBJDIR)/%.o)

CFLAGS	= -W -Werror -Wextra -Wall -Iinclude

$(OBJDUMP): $(OBJDUMPOBJ)
	@$(CC) -o my_objdump $(OBJDUMPOBJ)
	@echo "Linking complete!"

$(NM): $(NMOBJ)
	@$(CC) -o my_nm $(NMOBJ)
	@echo "Linking complete!"

$(OBJDUMPOBJ): $(OBJDUMPOBJDIR)/%.o : $(OBJDUMPSRCDIR)/%.c
	@$(MKDIR) $(OBJDUMPOBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(NMOBJ): $(NMOBJDIR)/%.o : $(NMSRCDIR)/%.c
	@$(MKDIR) $(NMOBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

all: $(NM) $(OBJDUMP)

clean:
	@$(RM) $(OBJDUMPOBJ)
	@$(RM) $(NMOBJ)
	@echo "Cleanup complete!"

fclean: clean
	@$(RM) my_objdump
	@$(RM) my_nm

re: fclean all

.PHONY: all clean fclean re
