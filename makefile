# Name:Yair Shlomo
# ID: 308536150
# Name:Gal Eini
# ID: 305216962


server.out: compileAll
	g++ -o ../../exe/server/server.out *.o
	rm -f *.o

compileAll: *.h *.cpp
	g++ -Iinclude -c *.cpp

