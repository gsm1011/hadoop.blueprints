//package com.packt.hadoop;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Get;
import org.apache.hadoop.hbase.client.Scan;
import org.apache.hadoop.hbase.util.Bytes;
import org.apache.hadoop.hbase.client.Result;
import org.apache.hadoop.hbase.client.ResultScanner; 

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Random;
import java.io.IOException;

class HBaseDump {

    public static void main(String[] args) throws Exception {

		if (args.length < 2) {
			System.err.println("Usage: HBaseDump " + 
					   " <table> <colstring> [rowkey]"); 
			return; 
		}

		String tableName = args[0];  
		String [] columns = args[1].split(","); 
		String rowkey = null; 

		if (args.length >= 3) rowkey = args[2]; 
		
		Configuration conf = HBaseConfiguration.create();
		HTable table = new HTable(conf, tableName); 
		Get get = null; 
		Result result = null; 
		Scan scan = null; 
		ResultScanner resultScan = null; 

		if(null != rowkey) {
			get = new Get(Bytes.toBytes(rowkey)); 
			
			for(int i = 0; i < columns.length; ++i) {
				String [] colName = columns[i].split(":");
				if(colName[0].equals("") || (colName.length != 2)) continue; 
				get.addColumn(Bytes.toBytes(colName[0]), Bytes.toBytes(colName[1]));
			}

			result = table.get(get);
			byte[] res = null; 
			for(int i = 0; i < columns.length; ++i) {
				String [] colName = columns[i].split(":");
				if(colName[0].equals("") || (colName.length != 2)) continue; 
				res = result.getValue(Bytes.toBytes(colName[0]), Bytes.toBytes(colName[1]));
				System.out.println("Result: " + Bytes.toString(res)); 		
			}
		} else {
			// dump the table. 
			System.out.println("Dumping the whole table.");
			scan = new Scan(); 
			resultScan = table.getScanner(scan); 
			for(Result r : resultScan) {
				System.out.println(r); 
			}
			resultScan.close(); 
		}
	}
}
