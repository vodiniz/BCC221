all: main.o horario.o pessoa.o ponto.o supervisor.o venda.o vendedor.o data.o excecao.o funcionario.o chefe.o menu.o
	@g++ -o exe main.o horario.o pessoa.o ponto.o supervisor.o venda.o vendedor.o data.o excecao.o funcionario.o chefe.o menu.o -Wall -g 
	@rm -r *.o
main.o: main.cpp
	@g++ -c main.cpp -Wall
horario.o: horario.cpp
	@g++ -c horario.cpp -Wall
pessoa.o: pessoa.cpp
	@g++ -c pessoa.cpp -Wall
ponto.o: ponto.cpp
	@g++ -c ponto.cpp -Wall
supervisor.o: supervisor.cpp
	@g++ -c supervisor.cpp -Wall
venda.o: venda.cpp
	@g++ -c venda.cpp -Wall
vendedor.o: vendedor.cpp
	@g++ -c vendedor.cpp -Wall
data.o: data.cpp
	@g++ -c data.cpp -Wall
excecao.o: excecao.cpp
	@g++ -c excecao.cpp -Wall
funcionario.o: funcionario.cpp
	@g++ -c funcionario.cpp -Wall
chefe.o: chefe.cpp
	@g++ -c chefe.cpp -Wall
menu.o: menu.cpp
	@g++ -c menu.cpp -Wall

run:
	@./exe