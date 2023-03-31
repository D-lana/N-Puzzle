NAME		= n_puzzle

SRCS		= main.cpp \
			Puzzle.cpp \
			PuzzleSolver.cpp \

HEADERS		= Library.hpp 

OBJS		=	$(SRCS:.cpp=.o)

CC			=	g++

RM				= rm -Rf
FLAGS			= -Wall -Wextra -Werror -g -std=c++98

all:			$(NAME)

$(NAME):		$(OBJS) $(HEADERS)
				$(CC) -o $(NAME) $(OBJS)

%.o: %.cpp		Makefile $(HEADERS)
				$(CC) $(FLAGS) -c $< -o $@

clean:			
				$(RM) $(OBJS) 

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re