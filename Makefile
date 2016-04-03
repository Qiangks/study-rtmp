#! /usr/bin/bash

CXX			= g++

DEPTH		= .

OBJDIR		= $(DEPTH)
INCDIR		= $(DEPTH)/st
LIBST		= $(INCDIR)/libst.a
HEADER		= $(INCDIR)/st.h

OBJ			= $(OBJDIR)/rtmp_server

.PHONY: $(OBJ)

obj = main.o logger.o rtmp_server.o st_thread.o st_connection.o utility.o srs_kernel_buff.o

rtmp_server: $(obj)
	$(CXX) $(obj) $(LIBST) -o $@

main.o:
	$(CXX) -c -g main.cpp

logger.o:
	$(CXX) -c -g logger.cpp

rtmp_server.o:
	$(CXX) -c -g rtmp_server.cpp

st_thread.o:
	$(CXX) -c -g st_thread.cpp

st_connection.o:
	$(CXX) -c -g st_connection.cpp

utility.o:
	$(CXX) -c -g utility.cpp

srs_kernel_buff.o:
	$(CXX) -c -g srs_kernel_buff.cpp


clean:
	rm $(OBJ) $(obj)

