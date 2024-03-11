CC = cc

CFLAGS = -g -Wall -Wextra -Werror

# Base
CLIENT = client
SERVER = server

FUNC_CLIENT = client.c utils/printf.c utils/printf_utils.c utils/minitalk_utils.c
FUNC_SERV =	server.c utils/printf.c utils/printf_utils.c utils/minitalk_utils.c

OBJS_CLIENT = ${FUNC_CLIENT:.c=.o}
OBJS_SERVER = ${FUNC_SERV:.c=.o}

# Bonus
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

FUNC_CLIENT_BONUS = bonus/client_bonus.c bonus/utils/printf_bonus.c bonus/utils/printf_utils_bonus.c bonus/utils/minitalk_utils_bonus.c
FUNC_SERVER_BONUS = bonus/server_bonus.c bonus/utils/printf_bonus.c bonus/utils/printf_utils_bonus.c bonus/utils/minitalk_utils_bonus.c

OBJS_CLIENT_BONUS = ${FUNC_CLIENT_BONUS:.c=.o}
OBJS_SERVER_BONUS = ${FUNC_SERVER_BONUS:.c=.o}


all: 	${CLIENT} ${SERVER}

${CLIENT}: ${OBJS_CLIENT}
	${CC} ${CFLAGS} ${OBJS_CLIENT} -o ${CLIENT}

${SERVER}: ${OBJS_SERVER}
	${CC} ${CFLAGS} ${OBJS_SERVER} -o ${SERVER}


bonus:	${CLIENT_BONUS} ${SERVER_BONUS}

${CLIENT_BONUS}: ${OBJS_CLIENT_BONUS}
	${CC} ${CFLAGS} ${OBJS_CLIENT_BONUS} -o ${CLIENT_BONUS}

${SERVER_BONUS}: ${OBJS_SERVER_BONUS}
	${CC} ${CFLAGS} ${OBJS_SERVER_BONUS} -o ${SERVER_BONUS}


clean:	
	rm -f ${OBJS_CLIENT} ${OBJS_SERVER}
	rm -f ${OBJS_CLIENT_BONUS} ${OBJS_SERVER_BONUS}

fclean:	clean
	rm -f ${CLIENT} ${SERVER}
	rm -f ${CLIENT_BONUS} ${SERVER_BONUS}

re:	fclean all

.PHONY: all clean fclean re bonus