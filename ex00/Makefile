NAME = Bitecoin
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

SRCDIR = src
INCDIR = include
LIBDIR = lib

SOURCES = $(SRCDIR)/main.cpp \
			$(SRCDIR)/Exchange.cpp \
			$(SRCDIR)/utils.cpp


OBJECTS = $(SOURCES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
		clear && valgrind --leak-check=full ./Bitecoin ./test/input.txt

.PHONY: all clean fclean re test