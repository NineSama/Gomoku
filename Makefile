NAME		=	Gomoku

CC			=	c++

FLAGS		=	-Wall -Werror -Wextra -std=c++98

SRCS		=	srcs/main.cpp	\
				srcs/utils/utils.cpp	\
				srcs/board/board.cpp

INCLUDES	=	-I include

OBJ_DIR		=	objs/

OBJS		=	$(SRCS:srcs/%.cpp=$(OBJ_DIR)%.o)

RM			=	rm -rf

all:		$(NAME)

$(OBJ_DIR)%.o: srcs/%.cpp
		mkdir -p $(dir $@)
		$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:		
			$(RM) $(OBJ_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re