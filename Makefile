NAME =		asteroidzz

SRCS =		src/main.cpp

OBJS =		$(SRCS:.cpp=.o)

LIBDIR=		-L/usr/local/lib/
INCDIR=		-I/usr/local/include/

LIBS =		$(LIBDIR) -lsfml-graphics -lsfml-window -lsfml-system
INCLUDES =	$(INCDIR) -I./inc

CXX =		g++
CXXFLAGS =	-Wall -Wextra -W -Werror
CXXFLAGS += $(INCLUDES)

target:		$(NAME)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) -o $(NAME) $(CXXFLAGS) $(OBJS) $(LIBS)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

run:		$(NAME)
			@./$(NAME)

.PHONY:		fclean clean all re run
