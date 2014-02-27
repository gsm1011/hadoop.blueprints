//package com.packt.hadoop;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.util.Bytes;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Random;
import java.io.IOException;

class SimpleWriter {

    public static void main(String[] args) throws Exception {

        if (args.length != 3) {
            System.err.println("Usage: SimpleWriter " +
                               " <table> <colstring> <datafile>");
            return;
        }

        String tableName = args[0];
        String [] columns = args[1].split(",");
        String datafile = args[2];

        Configuration conf = HBaseConfiguration.create();
        HTable table = new HTable(conf, tableName);
        Put put = null;

        BufferedReader br = new BufferedReader(new FileReader(datafile));
        String line = null;
        String [] vals = null;

        while((line = br.readLine()) != null) {

            vals = line.split("\t");
            if(columns.length != vals.length) continue;

            for (int i = 0; i < columns.length; i++) {
                System.out.println(columns[i]);
                String [] colName = columns[i].split(":");
                if (colName.length != 2) {
                    System.err.println("Error column format! "
				       + "Should be \":key,cf1:col1,cf1:col2,cf2:col1\"");
                    return;
                }
                if(colName[0].equals("")) {
                    // the first column should be the row key.
                    put = new Put(Bytes.toBytes(vals[0]));

                } else {
                    put.add(Bytes.toBytes(colName[0]),
                            Bytes.toBytes(colName[1]),
                            Bytes.toBytes(vals[i]));
                    table.put(put);
                }

            }
        }
    }
}
