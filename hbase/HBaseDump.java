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

        if(!validateColumnStr(args[1])) {
            System.err.println("Column string error, should be: " + 
                               "cf1:q1,cf1:q2,cf2:q4......" ); 
            System.exit(1); 
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

            // compile all the column names into Get. 			
            for(int i = 0; i < columns.length; ++i) {
                String [] colName = columns[i].split(":");
                get.addColumn(Bytes.toBytes(colName[0]), Bytes.toBytes(colName[1]));
            }

            result = table.get(get);

            printRow(result, columns); 

        } else {
            // dump the table. 
            System.out.println("Dumping the whole table.");
            scan = new Scan(); 
            resultScan = table.getScanner(scan); 
            for(Result r : resultScan) {
                printRow(r, columns); 
            }
            resultScan.close(); 
        }
    }

    public static void printRow(Result r, String columnStr) {
        printRow(r, columnStr.split(",")); 
    }

    public static void printRow(Result r, String [] columns) {
        byte [] rowkey = r.getRow(); 

        System.out.println("Row: " + Bytes.toString(rowkey)); 

        // print column cells. 
        for ( int i = 0; i < columns.length; ++i) {
            String [] colName = columns[i].split(":"); 

            byte [] colValue = r.getValue(Bytes.toBytes(colName[0]), 
                                     Bytes.toBytes(colName[1]));
            System.out.println(columns[i] + " " + Bytes.toString(colValue)); 
        }

        System.out.println();
    }

    public static boolean validateColumnStr(String colStr) {
        String [] columns = colStr.split(","); 
        for(String col : columns) {
            String [] colName = col.split(":"); 
            if(colName.length != 2 || 
               colName[0].equals("") || 
               colName[1].equals("")) return false; 
        }
        return true; 
    }
}
