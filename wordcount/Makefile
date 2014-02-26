HADOOP_HOME=/home/shumin/softwares/hadoop
HADOOP_EXAMPLE_JAR=$(HADOOP_HOME)/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.2.0.jar
CLASSPATH1=`hadoop classpath`:.
JC_OPTS=-nowarn
SRC=WordCount.java WordCountMap.java WordCountReduce.java
CLASSES=$(SRC:.java=.class)

all:$(CLASSES)

.SUFFIX: .java .class

geninput: 
	-hadoop fs -rm -r teraout
	hadoop jar $(HADOOP_EXAMPLE_JAR) teragen 10000000 teraout

run: $(CLASSES)
	@echo "Deleting the target directory....."
	-hadoop fs -rm -r terasort.out 
	@echo "Running the word count example ..."
	java -cp $(CLASSPATH1) WordCount teraout terasort.out

%.class: %.java
	@echo "Compiling source file --> " $<
	@javac $(JC_OPTS) -cp $(CLASSPATH1) $<

clean:
	@rm -v -rf $(CLASSES)
