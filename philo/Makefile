NAME = philo

BONUS_NAME = checker

CFLAGS = -Wall -Wextra -Werror

SRC = main.c action.c execution.c init.c parser.c utils.c utils2.c

OBJ = $(SRC:.c=.o)

all: ${NAME}

${NAME}: ${OBJ}
	@gcc ${CFLAGS} -o ${NAME} ${OBJ}
	@echo "\n๐ Programa creado ๐\n"

${OBJ}:	$(SRC)
	@gcc ${CFLAGS} -c philo.h $(SRC)
	@echo "\n๐จ Objetos creados โ\n"

clean:
	@rm -rf ${OBJ}
	@rm -rf philo.h.gch
	@echo "\n๐งจ Objetos destruidos โ\n"

fclean: clean
	@rm -f ${NAME}
	@echo "\n๐ฅ Archivos binarios destruidos โ\n"

re: fclean all

sre: re

.PHONY: bonus all clean fclean sclean re sre
