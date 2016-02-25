NAME =		asteroidzz

SRCS =		src/main.cpp \
			src/Game.cpp \
			src/Player.cpp \
			src/Asteroid.cpp \
			src/SerialReader.cpp

OBJS =		$(SRCS:.cpp=.o)

LIBDIR=		-L/usr/local/lib/
INCDIR=		-I/usr/local/include/

LSFML =		-lsfml-graphics -lsfml-window -lsfml-system
LBOOST =	-lboost_system -lboost_filesystem

LIBS =		$(LIBDIR)
LIBS +=		$(LSFML)
LIBS +=		$(LBOOST)

INCLUDES =	$(INCDIR) -I./inc

CXX =		g++
CXXFLAGS =	-Wall -Wextra -W -Werror
CXXFLAGS += $(INCLUDES)
CXXFLAGS += -std=c++11

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

run:		re
			@./$(NAME)

.PHONY:		fclean clean all re run
