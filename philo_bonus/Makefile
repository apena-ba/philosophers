NAME = philo_bonus

BONUS_NAME = checker

CFLAGS = -Wall -Wextra -Werror

SRC = main_bonus.c action_bonus.c init_bonus.c parser_bonus.c utils_bonus.c utils2_bonus.c

OBJ = $(SRC:.c=.o)

all: ${NAME}

${NAME}: ${OBJ}
	@gcc ${CFLAGS} -o ${NAME} ${OBJ}
	@echo "\n๐ Programa creado ๐\n"

${OBJ}:	$(SRC)
	@gcc ${CFLAGS} -c philo_bonus.h $(SRC)
	@echo "\n๐จ Objetos creados โ\n"

clean:
	@rm -rf ${OBJ}
	@rm -rf philo_bonus.h.gch
	@echo "\n๐งจ Objetos destruidos โ\n"

fclean: clean
	@rm -f ${NAME}
	@echo "\n๐ฅ Archivos binarios destruidos โ\n"

re: fclean all

sre: re

.PHONY: bonus all clean fclean sclean re sre
