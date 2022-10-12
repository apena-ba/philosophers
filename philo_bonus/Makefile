NAME = philo_bonus

BONUS_NAME = checker

CFLAGS = -Wall -Wextra -Werror

SRC = main.c action.c init.c parser.c utils.c utils2.c

OBJ = $(SRC:.c=.o)

all: ${NAME}

${NAME}: ${OBJ}
	@gcc ${CFLAGS} -o ${NAME} ${OBJ}
	@echo "\n🎊 Programa creado 🎊\n"

${OBJ}:	$(SRC)
	@gcc ${CFLAGS} -c philo.h $(SRC)
	@echo "\n🔨 Objetos creados ✅\n"

clean:
	@rm -rf ${OBJ}
	@rm -rf philo.h.gch
	@echo "\n🧨 Objetos destruidos ✅\n"

fclean: clean
	@rm -f ${NAME}
	@echo "\n💥 Archivos binarios destruidos ✅\n"

re: fclean all

sre: re

.PHONY: bonus all clean fclean sclean re sre
