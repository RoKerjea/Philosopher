# This is a minimal set of ANSI/VT100 color codes
_END=$'\033[0m
_BOLD=$'\033[1m
_UNDER=$'\033[4m
_REV=$'\033[7m

# Colors
_GREY=$'\033[30m
_RED=$'\033[31m
_GREEN=$'\033[32m
_YELLOW=$'\033[33m
_BLUE=$'\033[34m
_PURPLE=$'\033[35m
_CYAN=$'\033[36m
_WHITE=$'\033[37m

# Inverted, i.e. colored backgrounds
_IGREY=$'\033[40m
_IRED=$'\033[41m
_IGREEN=$'\033[42m
_IYELLOW=$'\033[43m
_IBLUE=$'\033[44m
_IPURPLE=$'\033[45m
_ICYAN=$'\033[46m
_IWHITE=$'\033[47m

SRCS		=	${addprefix srcs/, \
				philomain.c \
				philo_loop.c \
				philo_create.c \
				time.c \
				problem_manager.c \
				thread_monitor.c \
				mutex_print.c \
				stop.c \
				parsing.c} \
				${addprefix not_libft/, \
				ft_atol.c \
				ft_split.c \
				ft_strdup.c \
				ft_strlen.c \
				ft_freetab.c}


HEADER		= include/philosopher.h
RM			= rm -rf
NAME		= philo
CC			= gcc $(CFLAGS)

OBJECTS = $(subst /,/build/,${SRCS:.c=.o})
#OBJECTS = ${SRCS:%.c=.build/%.o}
DEPEND	= ${OBJECTS:.o=.d}

CFLAGS		= -Wall -Werror -Wextra -lpthread -pthread


all:	$(NAME)  printstart printfirst

printstart :
	@echo "${_UNDER}${_RED}"Creating Objects Directories"${_END}"

printfirst:
	@echo "${_UNDER}${_YELLOW}"I\'m first!"${_END}"
	touch $@
	ls -la


${NAME}:	${OBJECTS}
	@echo "${_UNDER}${_RED}Creating Executable${_END}"
	@echo "${_BOLD}${_GREEN}${CC} -o ${NAME} ${OBJECTS}${_END}"
	@${CC} -o ${NAME} ${OBJECTS}

-include ${DEPEND}

## src = philo/src/parsing.c		philo/src/%.c  philo/src/titi/prout.c
## obj = philo/src/build/parsing.o	$(@D)/build/%.o
## % = parsing						philo/src/titi/build/titi/prout.o
## $(dir /build/parsing.o) = /build/
## $(@D) de /build/parsing.o = /build



${OBJECTS}: $(subst .o,.c,$(subst /build/,/,$@))
	@if [ ! -d "./$(dir $@)" ]; then\
		echo "${_BOLD}${_UNDER}${_BLUE}"mkdir -p $(dir $@)"${_END}";\
		mkdir -p $(dir $@);\
	fi
	@echo "${_BOLD}${_BLUE}"$(CC) -MMD -c $(subst .o,.c,$(subst /build/,/,$@)) -o $@"${_END}"
	@$(CC) -MMD -c $(subst .o,.c,$(subst /build/,/,$@)) -o $@

clean:
	@echo "${_UNDER}${_RED}Deleting Objects and Dependencies${_END}"
	@echo "${_BOLD}${_YELLOW}"${RM} ${OBJECTS} ${DEPEND}"${_END}"
	@${RM} ${OBJECTS} ${DEPEND}
	@echo "${_BOLD}${_YELLOW}"${RM} srcs/build"${_END}"
	@${RM} srcs/build
	@echo "${_BOLD}${_YELLOW}"${RM} not_libft/build"${_END}"
	@${RM} not_libft/build

fclean: clean
	@echo "${_UNDER}${_RED}Deleting Executable${_END}"
	@echo "${_BOLD}${_RED}"${RM} ${NAME}"${_END}"
	@${RM} ${NAME}

gitm: fclean
	git add .
	git commit
	git push

VER_H = include/Version_philo.h
USER := $(shell env | grep USER | tail --bytes=+6)
TIME=$(shell date +"%d %m %Y %Hh%M %Z")

git: fclean
	$(eval MIN=$(shell expr $$(awk '/# define MINOR_VERSION/' $(VER_H) | tr -cd "[0-9]") + 1))
	$(eval MAJ=$(shell awk '/# define MAJOR_VERSION/' $(VER_H) | tr -cd "[0-9]"))
	sed -i 's/# define MINOR_VERSION .*/# define MINOR_VERSION \"$(MIN)\"/' $(VER_H)
	sed -i 's/# define BUILD_DATE .*/# define BUILD_DATE \"$(TIME)\"/' $(VER_H)
	git add .
	git commit -m "V$(MAJ).$(MIN) by $(USER) at $(TIME)"
	git push

re:	fclean all

.PHONY:		all clean fclean re gitm git printstart
