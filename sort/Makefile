HADOOP_HOME=/home/shumin/softwares/hadoop
HADOOP_EXAMPLE_JAR=$(HADOOP_HOME)/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.2.0.jar
CLASSPATH1=`hadoop classpath`:.
JC_OPTS=-nowarn
SRC=RandomGen.java SortMap.java Sort.java
CLASSES=$(SRC:.java=.class)

all:$(CLASSES)

.SUFFIX: .java .class

geninput: 
	-hadoop fs -rm -r randomnum
	@java -cp $(CLASSPATH1) RandomGen 10000000 randomnum

run: $(CLASSES)
	@echo "Deleting the target directory....."
	-hadoop fs -rm -r sort.out
	@echo "Running the random sort ..."
	java -cp $(CLASSPATH1) Sort randomnum sort.out

%.class: %.java
	@echo "Compiling source file --> " $<
	@javac $(JC_OPTS) -cp $(CLASSPATH1) $<

clean:
	@rm -v -rf $(CLASSES)
