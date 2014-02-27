//package com.packt.hadoop;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.io.ImmutableBytesWritable;
import org.apache.hadoop.mapred.lib.NullOutputFormat;
import org.apache.hadoop.mapred.lib.IdentityReducer;
import org.apache.hadoop.mapred.FileInputFormat; 
import org.apache.hadoop.io.Text; 
import org.apache.hadoop.io.LongWritable; 
import org.apache.hadoop.mapred.TextInputFormat; 
import org.apache.hadoop.mapred.JobClient; 
import org.apache.hadoop.fs.Path; 
import org.apache.hadoop.mapred.*; 
import org.apache.hadoop.io.LongWritable; 
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.mapred.Reporter; 
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapred.JobConf; 
import org.apache.hadoop.io.WritableComparable; 
import org.apache.hadoop.io.Writable; 
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.util.Bytes;
import org.apache.hadoop.mapred.Mapper;

import java.io.IOException;
import java.util.Iterator;

class DataBulkLoader {

    public class MapLoader<K extends WritableComparable, V extends Writable> 
	extends MapReduceBase 
	implements Mapper<K, V, K, V> {
	private Configuration conf = HBaseConfiguration.create();

	    public void map(K key, V value, OutputCollector<K, V> output, 
			    Reporter reporter) throws IOException {
	     
			String tableName = conf.get("hbase.table.name", null); 
			String columns = conf.get("hbase.column.names", null); 

			if (null == tableName || null == columns) 
			throw new IOException("Table/Colum name not specified."); 

			HTable table = new HTable(conf, tableName); 

			String [] colNames = columns.split(","); 
			String [] cols = value.toString().split("\t"); 

			if(colNames.length != cols.length) 
			throw new IOException("Column names and data columns does not match!"); 

			if(!"HBASE_ROW_KEY".equals(colNames[0])) {
				throw new IOException("You must specify the first column with HBASE_ROW_KEY.");
			}

			Put put = new Put(Bytes.toBytes(cols[0])); // row key. 
			for(int i = 0; i < cols.length - 1; i++) {
				String []tmp = colNames[i].split(":");
				if (tmp.length == 2) {
					put.add(Bytes.toBytes(tmp[0]), Bytes.toBytes(tmp[1]),
						Bytes.toBytes(cols[i]));
				} else if ( tmp.length == 1) {
					put.add(Bytes.toBytes(""), Bytes.toBytes(tmp[1]),
						Bytes.toBytes(cols[i]));
				} else {
					throw new IOException("Column name error" + colNames[i]); 
				}
			}
		}
    }

    public static void main(String[] args) throws Exception {

		if (args.length != 3) {
			System.out.println("Usage: BulkLoader <input> <hbase_table> <hbase_columns>");
			throw new IOException("Error running the job.");  
		}
		JobConf conf = new JobConf(DataBulkLoader.class);
		conf.setJobName("HbaseBulkLoad");
		conf.setJarByClass(MapLoader.class); 
		conf.setMapperClass(MapLoader.class);
		conf.setReducerClass(IdentityReducer.class);
		conf.setInputFormat(TextInputFormat.class);
		conf.setOutputFormat(NullOutputFormat.class);
		FileInputFormat.setInputPaths(conf, new Path(args[1]));

		// set the hbase table and column names. 
		conf.setStrings("hbase.table.name", args[2]); 
		conf.setStrings("hbase.column.names", args[3]); 
		JobClient.runJob(conf);
    }
}
