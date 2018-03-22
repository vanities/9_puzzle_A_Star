# make build for p1
all:random_board.cpp a-star.cpp 
	g++ random_board.cpp -o random_board
	g++ a-star.cpp -o a-star

clean: 
	$(RM) random_board a-star
