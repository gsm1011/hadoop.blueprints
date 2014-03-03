CC=g++
HADOOP_INSTALL=/home/shumin/softwares/hadoop
CPPFLAGS=-m64 -I$(HADOOP_INSTALL)/include -Wall -g -O2 
LIB_PATHS=-L$(HADOOP_INSTALL)/lib/native -lhadooppipes -lhadooputils -lpthread -lcrypto

wordcount: WordCount.cpp
	libtool --mode=link --tag=CXX $(CC) $(CPPFLAGS) $(LIB_PATHS) $< -o $@ 
