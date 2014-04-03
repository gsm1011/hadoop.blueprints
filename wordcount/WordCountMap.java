package com.packt.shumin.wordcount; 

import java.io.IOException; 
import java.lang.InterruptedException; 

import org.apache.hadoop.io.IntWritable; 
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text; 
import org.apache.hadoop.conf.Configuration; 
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import java.util.StringTokenizer;


public class WordCountMap extends Mapper<LongWritable, Text, Text, IntWritable> {
    static enum Words {START_WITH_LETTER, START_WITH_DIGIT}

    private final static IntWritable one = new IntWritable(1); 
    private Text word = new Text(); 

    public void map(LongWritable key, Text value, Context context) 
        throws IOException, InterruptedException {
        StringTokenizer tokenizer = new StringTokenizer(value.toString()); 
        while(tokenizer.hasMoreTokens()) {
            word.set(tokenizer.nextToken()); 

            // increment counters. 
            if(Character.isDigit(word.charAt(0))) {
                context.getCounter(Words.START_WITH_DIGIT).increment(1);
            } else if (Character.isLetter(word.charAt(0))) {
                context.getCounter(Words.START_WITH_LETTER).increment(1); 
            }
            context.write(word, one); 
        }
    }
}
