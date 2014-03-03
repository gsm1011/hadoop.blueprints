HADOOP_HOME=/home/shumin/softwares/hadoop
HADOOP_EXAMPLE_JAR=$(HADOOP_HOME)/share/hadoop/mapreduce/hadoop-mapreduce-examples-2.2.0.jar
HADOOP_STREAMING_JAR=$(HADOOP_HOME)/share/hadoop/tools/lib/hadoop-streaming-2.2.0.jar
JAR_FILE=./chapter1.jar
# CLASSPATH1=`hadoop classpath`:./chapter1.jar
CLASSPATH1=`hbase classpath`:./chapter1.jar
JC_OPTS=-nowarn
SRC=DataBulkLoader.java HBaseDump.java KDDUserLoader.java SimpleWriter.java WordCount.java
CLASSES=$(SRC:.java=.class)

all:$(CLASSES)

.SUFFIX: .java .class

geninput: 
	-hadoop fs -rm -r wc.input
	@hadoop jar $(HADOOP_EXAMPLE_JAR) randomtextwriter wc.input

runwcjava: $(JAR_FILE)
	@echo "Deleting the target directory....."
	-hadoop fs -rm -r wc.output
	@echo "Running the random sort ..."
	@hadoop jar $(JAR_FILE) com.packt.hadoop.WordCount wc.input wc.output

# run wordcount with hadoop streaming with python.
runwcpy:
	@echo "Deleting the target directory....."
	-hadoop fs -rm -r wc.output
	@echo "Running the random sort with python streaming..."
	hadoop jar $(HADOOP_STREAMING_JAR) \
  -input wc.input \
  -output wc.output \
  -mapper "python map.py" \
  -reducer "python reduce.py" \
  -file map.py \
  -file reduce.py

# run wordcount with hadoop streaming with perl.
runwcpl:
	@echo "Deleting the target directory....."
	-hadoop fs -rm -r wc.output
	@echo "Running the random sort using perl streaming..."
	hadoop jar $(HADOOP_STREAMING_JAR) \
  -input wc.input \
  -output wc.output \
  -mapper "perl map.pl" \
  -reducer "perl reduce.pl" \
  -file map.pl \
  -file reduce.pl

runwcbash:
	@echo "Deleting the target directory....."
	-hadoop fs -rm -r wc.output
	@echo "Running the random sort using perl streaming..."
	hadoop jar $(HADOOP_STREAMING_JAR) \
  -input wc.input \
  -output wc.output \
  -mapper map.sh \
  -combiner "sort" \
  -reducer "uniq -c" \
  -file map.sh

makejar: $(CLASSES)
	jar -cvf $(JAR_FILE) -C classes .

%.class: %.java
	@echo "Compiling source file --> " $<
	@javac $(JC_OPTS) -cp $(CLASSPATH1) $< -d classes

clean:
	@rm -v -rf ./classes/*
