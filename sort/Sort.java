import java.io.IOException;
import java.lang.InterruptedException;
import java.net.URI;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.util.GenericOptionsParser;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.NullWritable; 
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapred.lib.IdentityReducer; 

class Sort {
    public static void main(String [] args)
        throws IOException, InterruptedException, ClassNotFoundException {

        if (args.length < 1) {
            System.err.println("Usage: Sort <input> <output>");
            System.exit(1);
        }
        Configuration conf = new Configuration();
        String [] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
        Job job = Job.getInstance(conf); //new Job(conf, "Word Count example");
        job.setJobName("Sort");
        job.setJarByClass(Sort.class);
        job.setMapperClass(SortMap.class);
        job.setReducerClass(SortReduce.class);
        //job.setNumReduceTasks(0);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(IntWritable.class);

        FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
        FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}
