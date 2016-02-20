NAME =		asteroidzz

SRCS =		src/main.cpp \
			src/Game.cpp \
			src/Player.cpp \
			src/SerialReader.cpp

OBJS =		$(SRCS:.cpp=.o)

LIBDIR=		-L/usr/local/lib/
INCDIR=		-I/usr/local/include/

LIBS =		$(LIBDIR) -lsfml-graphics -lsfml-window -lsfml-system -lboost_system
INCLUDES =	$(INCDIR) -I./inc

CXX =		g++
CXXFLAGS =	-Wall -Wextra -W -Werror
CXXFLAGS += $(INCLUDES)

target:		$(NAME)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) -o $(NAME) $(CXXFLAGS) $(OBJS) $(LIBS)
			@terminal-notifier -title "$(NAME)" -message "Build complete !"

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

run:		$(NAME)
			@./$(NAME)

.PHONY:		fclean clean all re run
