package com.packt.hadoop;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.util.Bytes;
import org.apache.hadoop.hbase.client.Get;
import org.apache.hadoop.hbase.client.Scan;
import org.apache.hadoop.hbase.client.Result;
import org.apache.hadoop.hbase.client.ResultScanner;


import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Random;
import java.io.IOException;

class KDDUserLoader {
    private static Configuration conf = HBaseConfiguration.create();
    private static HTable table = null; 
    private static HTable tablePref = null; 
    private static Put put = null; 
    private static Get get = null; 
    private static BufferedReader br = null; 
    private static Scan scan = null; 
    private static ResultScanner resultScan = null; 

    public static void main(String[] args) throws Exception {
	
		if(args.length < 1) {
			System.err.println("Usage: KDDUserLoader <op> \n" + 
					   "<op> can be load or pref."); 
			return; 
		}
		if (args[0].equals("load")) loadData(); 
		if (args[0].equals("pref")) calcPreference(); 
		else System.out.println("Wrong operation!"); 
		}

		public static void loadData() throws IOException {
		// format: (UserId)\t(kw1:weight1;kw2:weight2;…kw3:weight3)
		
		table = new HTable(conf, "user_keywords"); 
		br = new BufferedReader(new FileReader("user_key_word.txt"));
		String line = null;
		String [] fields = null; 
		String [] columns = null; 
		double norm = 0; // compute the norm of vector. 

		while((line = br.readLine()) != null) {
			norm = 0; 
			fields = line.split("\t"); 
			if(fields.length != 2) continue; 

			put = new Put(Bytes.toBytes(fields[0])); 
			
			columns = fields[1].split(";");

			for (int i = 0; i < columns.length; i++) {
				String [] column = columns[i].split(":"); 

				if (column.length != 2) continue; 
				double preference = Double.parseDouble(column[1]); 
				norm += preference * preference; 

				put.add(Bytes.toBytes("keyword"), // col family
					Bytes.toBytes(column[0]), 
					Bytes.toBytes(column[1]));
			}
			// put the norm to the table. 
			put.add(Bytes.toBytes("keyword"), // col family
				Bytes.toBytes("norm"),
				Bytes.toBytes(Double.toString(Math.sqrt(norm))));
			table.put(put);
		}
    }

    public static void calcPreference() throws IOException {
		// format of item: (ItemId)\t(Item-Category)\t(id1;id2;...;idN)
		table = new HTable(conf, "user_keywords"); 
		tablePref = new HTable(conf, "preferences"); 
		br = new BufferedReader(new FileReader("item.txt"));	
		String line = null; 
		String itemid = null; 
		String [] fields = null; 
		String [] ids = null; 
		double itemnorm = 0, usernorm = 0;
		double prod = 0; 
		while((line = br.readLine()) != null) {
			itemnorm = 0; prod = 0; 
			fields = line.split("\t"); 
			if(fields.length != 3) continue; 
			itemid = fields[0]; 
			ids = fields[2].split(";"); 
			if(ids.length < 1) continue; 
			itemnorm = Math.sqrt(ids.length); 

			// get value from user_keywords table 
			// and compute vector product. 
			scan = new Scan(); 
			resultScan = table.getScanner(scan); 
			for(Result r : resultScan) {
				prod = 0; 
				String userid = Bytes.toString(r.getRow());
				for (int i = 0; i < ids.length; ++i) {
					try {
					String val = Bytes.toString(r.getValue(Bytes.toBytes("keyword"), 
										   Bytes.toBytes(ids[i]))); 
					prod += Double.parseDouble(val); // prod += val * 1; 
					// System.out.println("value: " + val); 
					} catch (Exception e) {} 
				}
				String normstr = Bytes.toString(r.getValue(Bytes.toBytes("keyword"), 
									 Bytes.toBytes("norm")));

				usernorm = Double.parseDouble(normstr); 
				double pref = prod / (itemnorm * usernorm); 
				if (pref > 0) 
				System.out.println(userid + "," + itemid + "," + pref); 
			}
		}
    }
}
