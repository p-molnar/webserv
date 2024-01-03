#=== Variables ===#

NAME 		:= 		webserv

SRCSDIR 	:= 		srcs
OBJDIR 		:= 		obj


CPP_FLAGS	:= 		-Wall -Werror -Wextra -std=c++98 -g

INC_DIR		:= 		includes
INC_FLAGS	:= 		-I$(INC_DIR)

#=== Sources ===#
SRCS		:=		socket/ASocket.cpp							\
					socket/ServerSocket.cpp						\
					socket/ClientSocket.cpp 					\
					PollManager.cpp 							\
					Webserver.cpp 								\
					Log.cpp										\
					main.cpp									\

OBJ			:= 		$(addprefix $(OBJDIR)/,$(SRCS:.cpp=.o))

#=== COLORS ===#

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

#=== Targets ===#

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	@echo "$(GREEN)Building $(NAME) ...$(RESET)"
	@c++ $(CPP_FLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Building completed$(RESET)"

$(OBJDIR)/%.o: $(SRCSDIR)/%.cpp
	@mkdir -p $(dir $@)
	@c++ $(CPP_FLAGS) $(INC_FLAGS) -c $< -o $@


$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR)
	@echo "$(RED)Cleaning ...$(RESET)"

fclean: clean
	@rm -rf $(NAME) $(OBJDIR)

re: fclean all