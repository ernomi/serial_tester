NAME = serial_tester

CPP = c++
STANDARD = -std=c++17
CPPFLAGS = -Wall -Wextra -Werror -O2 $(STANDARD) -Iserialib

SRCS = serialib/serialib.cpp \
       src/main.cpp

OBJS := ${SRCS:.cpp=.o}

all: $(NAME)

%.o: %.cpp
	@$(CPP) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "Compiling $(NAME)..."
	@$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@echo "Done!"

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJS)

fclean: clean
	@echo "Cleaning everything else..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
