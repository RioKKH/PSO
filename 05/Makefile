CC = gcc
CPP = g++

CFLAGS = -g -Wall
CINCLUDES = -I./include

CPPFLAGS = -g -Wall -std=c++14
CPPINCLUDES = -I./include

APP = pso
OBJS = Dataset.o Particle.o Swarm.o sample05.o

all: $(APP)
build: $(APP)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) $(CPPINCLUDES) -c $< -o $@

$(APP): $(OBJS)
	$(CPP) $(CPPFLAGS) $(CPPINCLUDES) $(OBJS) -o $(APP)

clean:
	rm -f $(OBJS) $(APP)

.PHONY: all build clean
