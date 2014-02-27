HADOOP_HOME=/home/shumin/softwares/hadoop
HADOOP_EXAMPLE_JAR=$(HADOOP_HOME)/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.2.0.jar
CLASSPATH1=`hadoop classpath`:`hbase classpath`:.
JC_OPTS=-nowarn
SRC=DataBulkLoader.java ImportFromFile.java
CLASSES=$(SRC:.java=.class)

all:$(CLASSES)

.SUFFIX: .java .class

run: $(CLASSES)
	@echo "Loading data into hbase ..."
	java -cp $(CLASSPATH1) DataBulkLoader ratings.dat ratings1 :key,info:mid,info:rating,info:ts
	java -cp $(CLASSPATH1) DataBulkLoader input m :key,info:title,info:genres
#	

%.class: %.java
	@echo "Compiling source file --> " $<
	@javac $(JC_OPTS) -cp $(CLASSPATH1) $<

clean:
	@rm -v -rf $(CLASSES)
