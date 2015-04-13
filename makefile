#
# Author: Tim Robinson
# Date: 3/16/2015
# Last modification date: 3/16/2015 11:12 AM PST
#

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
OBJS = final
SRCS = final_project.cpp final_project_functions.cpp
HEADERS = final_project.hpp

all: final

final:
	${CXX} ${CXXFLAGS} ${SRCS} -o ${OBJS}

clean:
	rm final
	echo Clean done