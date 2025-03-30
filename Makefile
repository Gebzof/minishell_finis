RED = \033[1;31m
GREEN = \e[32;1m
YELLOW = \033[1;33m
YELLOW1 = \e[93;5m
YELLOW2 = \e[1;93m
BLUE = \e[94;5m
PURPLE = \033[0;35m
PURPLE1 = \033[35;2m
PURPLE2 = \033[35;3m
PURPLE3 = \033[35;4m
PURPLE4 = \033[35;5m
PURPLE5 = \033[35;6m
PURPLE6 = \033[35;7m
PURPLE7 = \e[0;95m
PURPLE8 = \e[1;95m
PURPLE9 = \e[1;105m

CYAN = \033[1;36m
WHITE = \033[1;37m
RESET = \033[0m
RESET1 = \e[0m

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g3 -g -D_XOPEN_SOURCE=700

SRCDIR = srcs
OBJDIR = obj

USER_INPUT = default_value

CARAPUCE = 	echo "${CYAN}  				:::::::::::															\n"\
			 "		             -'            :.-.												\n"\
			 "		           '                   .-.											\n"\
			 "		         '                        \											\n"\
			 "		       '                           .										\n"\
			 "		      .'\                ::.       .										\n"\
			 "		     ._.'|             / |  .       \										\n"\
			 "		     |   |            .-.'  ||       ..										\n"\
			 "		     |   |            '-._ '||       | \									\n"\
			 "		     ... '             ... '.'         |.-.									\n"\
			 "		     l                       .'..  _/  |   ..								\n"\
			 "		     .-.._'-              _ _'   -: \  .     .								\n"\
			 "		..::	  '-..-... ---------' '         .. .....__.							\n"\
			 "		.'        .:-..___      __ '\          \  \     \							\n"\
			 "		\_ .          |   .:::'    ..           . \     \							\n"\
			 "		  ..          |              ..          |  .     \							\n"\
			 "		    ..        |.--...________.'.        j   |     |							\n"\
			 "		      .._    .'      |          ..     .|         |							\n"\
			 "		         .-- \       .            .7::' |         |							\n"\
			 "		            . .      .            /     |  |      |    _ -':::.-.			\n"\
			 "		             \ ..     .          /      |  '      |   '          ..			\n"\
			 "		              \  v.__  .        '       .   \    /| /              \		\n"\
			 "		               \/    .::\::::::..       \   \  /.''                |		\n"\
			 "		                .        .        .._ ___ j.  ./ .-        ---.     |		\n"\
			 "		                 .-.      \         .:     ..  |/        j     .    |		\n"\
			 "		               /    ..     \       /         \ /         |     /    j		\n"\
			 "		              |       .-.   7-.._ .          |:          '         /		\n"\
			 "		              |          ../_    .|          |            .     _ '			\n"\
			 "		              ..           / .----|          |-.............---'			\n"\
			 "		                \          \      |          |								\n"\
			 "		                '           )     ..         |								\n"\
			 "		                7____ ..--'      /          |								\n"\
			 "		                                  .---.__ --.'								\n${RESET}"\

SALAMECHE =  echo "${RED}				 	.--:::-..													\n"\
				 "			            ,'          :.											\n"\
				 "			          ,'          __  :.										\n"\
				 "			         /|          '' __   \										\n"\
				 "			        , |           / |.   .										\n"\
				 "			        |,'          !_.'|   |										\n"\
				 "			      ,'             '   |   |										\n"\
				 "			     /              |:--'|   |										\n"\
				 "			    |                :---'   |										\n"\
				 "			     .   ,                   |                       ,:.			\n"\
				 "			      ._     '           _'  |                    , ' \ :			\n"\
				 "			  :.. :.:-...___,...---::    |       __,.        ,::   L,|			\n"\
				 "			  |, :- .:._        _,-,.'   .  __.-'-. /        .   ,    \			\n"\
				 "			-:..     :. :-..--_.,.<       ::      / :.        :-/ |   .			\n"\
				 "			  :,         :::'     :.              ,'         |   |  ',,			\n"\
				 "			    :.      '            '            /          '    |'. |/		\n"\
				 "			      :.   |              \       _,-'           |       ''			\n"\
				 "			        :._'               \   ''\                .      |			\n"\
				 "			           |                '     \                :._  ,'			\n"\
				 "			           |                 '     \                 .'|			\n"\
				 "			           |                 .      \                | |			\n"\
				 "			           |                 |       L              ,' |			\n"\
				 "			           :                 |       |             /   '			\n"\
				 "			            \                |       |           ,'   /				\n"\
				 "			          ,' \               |  _.._ ,-..___,..-'    ,'				\n"\
				 "			         /     .             .      :!             ,j'				\n"\
				 "			        /       :.          /        .           .'/				\n"\
				 "			       .          :.       /         |        _.'.'					\n"\
				 "			        :.          7:'---'          |------:'_.'					\n"\
				 "			       _,.:,_     _'                ,''-----:'						\n"\
				 "			   _,-_    '       :.     .'      ,\								\n"\
				 "			   -: /:.         _,'     | _  _  _.|								\n"\
				 "			    ::--'---::::'        :' '! |! /									\n"\
				 "			                            :: : -'									\n${RESET}"\

BULBIZARRE = echo	 "${GREEN}		                        _,.------....___,.' ',.-.						\n"\
					 "		                     ,-'          _,.--        |						\n"\
					 "		                   ,'         _.-'              .\						\n"\
					 "	    	              /   ,     ,'                   '\						\n"\
					 "	        	         .   /     /                       \					\n"\
					 "	            	     |  |     .                       \.\					\n"\
					 "		       ____      |___._.  |       __                \  .				\n"\
					 "		     .'     ---         '' -.-- '   \               .  \				\n"\
					 "		    .  ,            __                              |   .				\n"\
					 "		     ,'         ,- '  .               \             |    L				\n"\
					 "		   ,'          '    _.'                -._          /    |				\n"\
					 "		  , -.    , .    --'                      >.      ,'     |				\n"\
					 "		 . .'\'   '-'       __    ,  ,-.         /   .__.-      ,'				\n"\
					 "		 ||:, .           ,'  ;  /  / \           .    .      .'/				\n"\
					 "		 j|:D  \           --'  ' ,'_  . .          .__, \   , /				\n"\
					 "		/ L:_  |                 .   ' :_;                 .'.'					\n"\
					 "		.      '                      '                    V					\n"\
					 "		 '.                                 .    	.   _,..  					\n"\
					 "		   ',_   .    .                _,-'/    ..  ,'   __  					\n"\
					 "		    ) \ ._        ___....---- '  ,'   .'  \ |   '  \  .					\n"\
					 "		   /    .   -.-- '         _,' ,'      ---' |     ./  |					\n"\
					 "		  .   _     '--.._____..--    ,             '         |					\n"\
					 "		  | .   .  -.                /-.           /          ,					\n"\
					 "		  |  ._.'     ,_            ;  /         ,'          .					\n"\
					 "		 .'          /|  -.        . ,'         ,           ,					\n"\
					 "		 '-.__ __ _,','    ' -..___;-...__   ,.'\ ____.___.'					\n"\
					 "		   ^--'..'   '- -^-' --     -^-' .''     .,^. .--'						\n"\
					 "																				\n${RESET}"\


SRCS = srcs/main.c \
	srcs/minishell_utils.c \
	srcs/minishell_utils2.c \
	srcs/lst_utils.c \
	srcs/builtins/export/export.c \
	srcs/builtins/export/export_utils.c \
	srcs/builtins/env.c \
	srcs/builtins/unset.c \
	srcs/builtins/pwd.c \
	srcs/builtins/echo.c \
	srcs/builtins/cd.c\
	srcs/builtins/exit.c\
	srcs/exec/exec.c \
	srcs/exec/exec_checks.c \
	srcs/exec/cmd.c \
	srcs/exec/pipe.c \
	srcs/exec/redirections.c \
	srcs/exec/heredoc/heredoc.c \
	srcs/exec/heredoc/ft_readline_doc.c \
	srcs/exec/heredoc/key_gest.c \
	srcs/parsing/parsline.c \
	srcs/ft_readline/ft_readline.c \
	srcs/ft_readline/ft_read.c \
	srcs/ft_readline/auto_completion_cmd.c \
	srcs/ft_readline/auto_completion_utils.c \
	srcs/ft_readline/print_directory.c \
	srcs/ft_readline/auto_completion_file.c \
	srcs/ft_readline/autofinish_files.c \
	srcs/ft_readline/history_utils.c \
	srcs/ft_readline/arrows.c \
	srcs/ft_readline/arrows2.c \
	srcs/ft_readline/manage_term.c \
	srcs/parsing/quote.c \
	srcs/parsing/quotes_tab.c \
	srcs/parsing/check_elem.c \
	srcs/parsing/dollard.c \
	srcs/parsing/dollard2.c \
	srcs/parsing/create_token.c \
	srcs/parsing/tree_redirect.c \
	srcs/parsing/clean_and_free.c \
	srcs/parsing/tree_utils.c \
	srcs/parsing/tree_cmd.c \
	srcs/parsing/tree_pipe.c \
	srcs/manage_exit/manage_exit.c\

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

LIBFTAR = libft/libft.a
FPRINTFTAR = ft_fprintf/printf.a

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@printf "$(GREEN)Compiling minishell : $(WHITE)$< $(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@
	@printf "\r\033[K"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(LIBFTAR) $(FPRINTFTAR) $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFTAR) $(FPRINTFTAR) -o $(NAME)
	@echo "choisissez votre starter parmit carapuce(c) ,salameche(s), bulbizarre(b) :"; \
    read user_input; \
	user_input=$$(echo "$$user_input" | tr '[:upper:]' '[:lower:]'); \
    if [ "$$user_input" = "s" ]; then \
        $(SALAMECHE);\
	elif [ "$$user_input" = "c" ]; then \
		$(CARAPUCE);\
	elif [ "$$user_input" = "b" ]; then \
		$(BULBIZARRE);\
    else \
        clear; \
    fi
	@printf	"	::          ::  ::  :::     ::  ::  ::::::  ::  ::  ::::::  ::      ::				\n"
	@printf	"	:::        :::  ::  ::::    ::  ::  ::      ::  ::  ::      ::      ::				\n"
	@printf	"	::::      ::::  ::  :: ::   ::  ::  ::      ::  ::  ::      ::      ::				\n"
	@printf	"	:: ::    :: ::  ::  ::  ::  ::  ::  ::::::  ::::::  ::::::  ::      ::				\n"
	@printf	"	::  ::  ::  ::  ::  ::   :: ::  ::      ::  ::  ::  ::      ::      ::				\n"
	@printf	"	::   ::::   ::  ::  ::    ::::  ::      ::  ::  ::  ::      ::      ::				\n"
	@printf	"	::    ::    ::  ::  ::     :::  ::  ::::::  ::  ::  ::::::  ::::::  ::::::			\n"

$(LIBFTAR):
	@make -sC libft

$(FPRINTFTAR):
	@make -sC ft_fprintf

clean:
	rm -rf $(OBJDIR)
	@make clean -sC libft
	@make clean -sC ft_fprintf

fclean: clean
	rm -f $(NAME)
	@make fclean -sC libft
	@make fclean -sC ft_fprintf

rebuild : all clean

re : fclean all

.PHONY: fclean all clean re rebuild