import java.io.IOException;
import java.lang.InterruptedException;

import org.apache.hadoop.io.IntWritable; 
import org.apache.hadoop.io.Text; 
import org.apache.hadoop.conf.Configuration; 
import org.apache.hadoop.mapreduce.Reducer;

public class WordCountReduce
    extends Reducer<Text, IntWritable, Text, IntWritable> {

    public void reduce(Text key, Iterable<IntWritable> values, Context context) 
        throws IOException, InterruptedException {
        int cnt = 0; 
        for(IntWritable value : values) {
            cnt += value.get(); 
        }
        context.write(key, new IntWritable(cnt)); 
    }
}
