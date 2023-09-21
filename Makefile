NAME		=	ft_irc_server

# DIRECTORIES
S_DIR	=	srcs/
I_DIR	=	include/
BIN_DIR	=	temp/
O_DIR	=	temp/obj/

# COMPILE
CXX			=	g++ -std=c++98
CFLAGSXX	=	-Wall -Wextra -Werror -Iinclude/ -g3 -D DEBUG
DEPEND		=

# SOURCES
S_FILES		=	main.cpp	\
				Server.cpp	\
				Utils.cpp	\
				User.cpp	\
				Network.cpp	\
				Command.cpp	\
				Message_Format.cpp \
				cap.cpp	\
				join.cpp	\
				pass.cpp	\
				Nick.cpp	\
				user_cmd.cpp \
				Debug_ft_IRC.cpp \
				Channel.cpp \
				topic.cpp \
				invite.cpp \
				mode.cpp \
				whois.cpp

SRCS	=	$(addprefix $(S_DIR), $(S_FILES))

#OBJS
OBJECTS		=	$(S_FILES:.cpp=.opp)
OBJS		=	$(addprefix $(O_DIR), $(OBJECTS))

all			:
				@echo "Building $(NAME):"
				@make --no-print-directory $(NAME)

$(NAME)		:	$(OBJS)
				@echo "Linking $(NAME)..."
				@$(CXX) $(CFLAGSXX) $^ -o $@
				@echo "$(NAME) built successfully!"

$(OBJS)		:	$(O_DIR)%.opp: $(S_DIR)%.cpp $(DEPENDS)
				@echo "Compiling $<"
				@mkdir -p $(@D)
				@$(CXX) $(CFLAGSXX) -c $< -o $@

debugflags	:	$(eval CFLAGSXX=-D DEBUG)

debug		:	debugflags all

clean			:
				@echo "$(NAME): cleaning objs"
				rm -rf $(BIN_DIR)

fclean			:	clean
				@echo "$(NAME): cleaning binary"
				rm -rf $(NAME)

re				:	fclean all

.PHONY			: all, clean, fclean, re, debug, debugflags
