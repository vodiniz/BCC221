all: main.o horario.o pessoa.o ponto.o supervisor.o venda.o vendedor.o data.o excecao.o funcionario.o chefe.o menu.o
	@g++ -o sistema main.o horario.o pessoa.o ponto.o supervisor.o venda.o vendedor.o data.o excecao.o funcionario.o chefe.o menu.o -Wall -g 
	@rm -r *.o
main.o: main.cpp
	@g++ -c main.cpp -Wall  -g
horario.o: horario.cpp
	@g++ -c horario.cpp -Wall -g
pessoa.o: pessoa.cpp
	@g++ -c pessoa.cpp -Wall -g
ponto.o: ponto.cpp
	@g++ -c ponto.cpp -Wall -g
supervisor.o: supervisor.cpp
	@g++ -c supervisor.cpp -Wall -g
venda.o: venda.cpp
	@g++ -c venda.cpp -Wall -g
vendedor.o: vendedor.cpp
	@g++ -c vendedor.cpp -Wall -g
data.o: data.cpp
	@g++ -c data.cpp -Wall -g
excecao.o: excecao.cpp
	@g++ -c excecao.cpp -Wall -g
funcionario.o: funcionario.cpp
	@g++ -c funcionario.cpp -Wall -g
chefe.o: chefe.cpp
	@g++ -c chefe.cpp -Wall -g
menu.o: menu.cpp
	@g++ -c menu.cpp -Wall -g

run:
	@./sistema