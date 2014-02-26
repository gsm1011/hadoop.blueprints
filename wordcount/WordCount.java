import java.io.IOException; 
import java.lang.InterruptedException; 

import org.apache.hadoop.util.GenericOptionsParser;
import org.apache.hadoop.fs.Path; 
import org.apache.hadoop.io.Text; 
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
//import org.apache.hadoop.mapred.JobConf;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat; 
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat; 
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.conf.Configuration; 
/**
 * Main class for the word count example. 
 */
class WordCount {
    public static void main(String [] args) 
        throws IOException, InterruptedException, ClassNotFoundException {
        // New API. 
        System.out.println(args.length); 
        if (args.length < 1) {
            System.err.println("Usage: WordCount <input> <output>"); 
            System.exit(1); 
        }
        Configuration conf = new Configuration(); 
        String [] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs(); 
        Job job = Job.getInstance(conf); //new Job(conf, "Word Count example"); 
        job.setJobName("WordCount");
        job.setJarByClass(WordCount.class); 
        job.setMapperClass(WordCountMap.class); 
        job.setReducerClass(WordCountReduce.class); 
        job.setOutputKeyClass(Text.class); 
        job.setOutputValueClass(IntWritable.class); 
        FileInputFormat.addInputPath(job, new Path(otherArgs[0])); 
        FileOutputFormat.setOutputPath(job, new Path(otherArgs[1])); 
        System.exit(job.waitForCompletion(true) ? 0 : 1); 

        // The following code snippet is already deprecated. 
        // The right way to configure a mapreduce job is 
        // to use the Configuration API. 
        // 
        // JobConf conf = new JobConf(WordCount.class); 
        // String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs(); 

        // conf.setJobName("wordcount"); 
        
        // conf.setOutputKeyClass(Text.class); 
        // conf.setOutputValueClass(IntWritable.class); 
        // conf.setMapperClass(WordCountMap.class); 
        // conf.setCombinerClass(WordCountReduce.class); 
        // conf.setReducerClass(WordCountReduce.class); 
        // conf.setInputFormat(TextInputFormat.class); 
        // conf.setOuputFormat(TextOutputFormat.class); 
        // FileInputFormat.setInputPaths(conf, new Path(otherArgs[0])); 
        // FileOutputFormat.setOutputPaths(conf, new Path(otherArgs[1]));
        // JobClient.runJob(conf); 
    }
}
