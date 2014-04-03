HADOOP_HOME=/home/shumin/softwares/hadoop
HADOOP_EXAMPLE_JAR=$(HADOOP_HOME)/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.2.0.jar
CLASSPATH1=`hadoop classpath`:./classes
JC_OPTS=-nowarn
SRC=WordCountMap.java WordCountReduce.java WordCount.java
CLASSES=$(SRC:.java=.class)
JAR=./wc.jar

all:$(CLASSES)

.SUFFIX: .java .class

makejar: $(CLASSES)
	jar -cvf $(JAR) -C classes .

geninput: 
	-hadoop fs -rm -r teraout
	hadoop jar $(HADOOP_EXAMPLE_JAR) teragen 10000000 teraout

run: $(JAR)
	@echo "Deleting the target directory....."
	-hadoop fs -rm -r terasort.out 
	@echo "Running the word count example ..."
	hadoop jar $(JAR) com.packt.shumin.wordcount.WordCount ratings.dat wc.out

%.class: %.java
	@echo "Compiling source file --> " $<
	@javac $(JC_OPTS) -cp $(CLASSPATH1) $< -d classes

clean:
	@rm -v -rf $(CLASSES)
