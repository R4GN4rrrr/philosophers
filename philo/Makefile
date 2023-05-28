NAME = philo


SOURCES = main.c\
		time.c\
		utils.c\
		init.c\
			
OBJECTS = $(SOURCES:.c=.o)


CC = cc

CFLAGS = -Werror -Wextra -Wall #-fsanitize=thread -g3


$(NAME) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -pthread


all : $(NAME)

clean :
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all