CXX = g++
CXXFLAGS = -Wall -Wextra -g

all: loadbalancer

loadbalancer: main.o request.o webserver.o loadbalancer.o
	$(CXX) $(CXXFLAGS) -o loadbalancer main.o request.o webserver.o loadbalancer.o

main.o: main.cpp loadbalancer.h request.h
	$(CXX) $(CXXFLAGS) -c main.cpp

request.o: request.cpp request.h
	$(CXX) $(CXXFLAGS) -c request.cpp

webserver.o: webserver.cpp webserver.h request.h
	$(CXX) $(CXXFLAGS) -c webserver.cpp

loadbalancer.o: loadbalancer.cpp loadbalancer.h webserver.h
	$(CXX) $(CXXFLAGS) -c loadbalancer.cpp

clean:
	rm -f *.o loadbalancer
