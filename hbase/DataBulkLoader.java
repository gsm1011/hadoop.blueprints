//package com.packt.hadoop;
import org.apache.hadoop.hbase.io.ImmutableBytesWritable;
import java.lang.InterruptedException;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text; 
import org.apache.hadoop.io.LongWritable; 
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat; 
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.hbase.mapreduce.TableOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;
import org.apache.hadoop.fs.Path; 
import org.apache.hadoop.io.LongWritable; 
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.conf.Configuration; 
import org.apache.hadoop.io.WritableComparable; 
import org.apache.hadoop.io.Writable; 
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.util.Bytes;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer; 
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import java.io.IOException;
import java.util.Iterator;

class DataBulkLoader {
    // Set mapper class to be static, otherwise, you will get error.
    // java.lang.Exception: java.lang.RuntimeException: java.lang.NoSuchMethodException: 
    static class MapLoader extends Mapper<LongWritable, Text, ImmutableBytesWritable, Put> {
        //private static Configuration conf = HBaseConfiguration.create();

        public void map(LongWritable key, Text value, Context context) 
            throws IOException, InterruptedException {
	     
            Configuration conf = context.getConfiguration(); 
            String tableName = conf.get("hbase.table.name"); 
            String columns = conf.get("hbase.column.names"); 

            //System.out.println(tableName + " " + columns + " ------------------------- "); 

            if (null == tableName || null == columns) 
                throw new IOException("Table/Colum name not specified."); 

            HTable table = new HTable(conf, tableName); 

            String [] colNames = columns.split(","); 
            String [] cols = value.toString().split("\t"); 

            if(colNames.length != cols.length) 
                throw new IOException("Column names and data columns does not match!"); 

            if(!":key".equals(colNames[0])) {
                throw new IOException("You must specify the first column with key.");
            }

            byte [] rowkey = Bytes.toBytes(cols[0]); 
            Put put = new Put(rowkey); // row key. 

            // row key should not be put again. so i start from 1; 
            for(int i = 1; i < cols.length; i++) {
                String []tmp = colNames[i].split(":");
                // System.out.println(tmp[0] + " " + tmp[1] + " +++++++++++++++++++++" ); 
                if (tmp.length == 2) {
                    put.add(Bytes.toBytes(tmp[0]), Bytes.toBytes(tmp[1]),
                            Bytes.toBytes(cols[i]));
                } else {
                    throw new IOException("Column name error" + colNames[i]); 
                }
            }
            //System.out.println(put);
            context.write(new ImmutableBytesWritable(rowkey), put);
        }
    }

    public static void main(String[] args) throws Exception {

        if (args.length != 3) {
            System.out.println("Usage: BulkLoader <input_hdfs> <hbase_table> <hbase_columns>");
            throw new IOException("Error running loading data into hbase.");  
        }

        //
        Configuration conf = HBaseConfiguration.create(); 
        String [] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs(); 
        Job job = new Job(conf);
        // JobConf conf = new JobConf(DataBulkLoader.class);
        job.setJobName("HbaseBulkLoad");
        job.setJarByClass(DataBulkLoader.class); 
        job.setMapperClass(MapLoader.class);
        job.setOutputFormatClass(TableOutputFormat.class); 
        job.getConfiguration().set(TableOutputFormat.OUTPUT_TABLE, otherArgs[1]);
        // job.setInputFormat(TextInputFormat.class);
        job.setOutputKeyClass(ImmutableBytesWritable.class);
        job.setOutputValueClass(Put.class);
        job.setNumReduceTasks(0);
        // System.out.println("Input path: ::::::::::::::::: " + otherArgs[0]); 
        FileInputFormat.addInputPath(job, new Path(otherArgs[0]));

        // set the hbase table and column names. 
        job.getConfiguration().set("hbase.table.name", otherArgs[1]); 
        job.getConfiguration().set("hbase.column.names", otherArgs[2]); 
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}
