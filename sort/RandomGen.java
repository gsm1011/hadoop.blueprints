import java.util.Random; 
import java.io.IOException; 
import java.io.UnsupportedEncodingException;
import java.net.URISyntaxException;
import java.net.URI; 
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.fs.FileSystem; 
import java.io.OutputStream;
import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import org.apache.hadoop.util.Progressable; 

class RandomGen {

    public static void main(String [] args) 
        throws URISyntaxException,UnsupportedEncodingException,IOException {
        if (args.length != 2) {
            System.out.println("Usage: RandomGen <lines> <outfile>"); 
            System.exit(1); 
        }

        String absolutePath = args[1]; 
        String hdfsFs = "hdfs://localhost:54310";
        String numStrs = "";
        Random rnd = new Random(); 
        long bytesCnt = 0;

        Configuration conf = new Configuration(); 
        FileSystem fs = FileSystem.get(new URI(hdfsFs), conf); 
        if(!absolutePath.startsWith("/")) {
            absolutePath = "/user/shumin/" + absolutePath;
        } 

        Path path = new Path(hdfsFs + absolutePath); 
        if(fs.exists(path)) { fs.delete(path, true); } 

        OutputStream os = 
            fs.create(path, new Progressable() {
                    public void progress() {
                        // System.out.println("Writing ......");
                    }
                });

        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(os, "UTF-8")); 

        // write the content.
        for(int i = 0; i < Integer.parseInt(args[0]); i++) {
            numStrs = ""; 
            // generate 100 random numbers. 
            for( int j = 0; j < 100; j++) {
                numStrs += " " + Integer.toString(rnd.nextInt(100)); 
            }
            bytesCnt += numStrs.length(); 
            writer.write(numStrs + "\n"); 
            // System.out.println("Wrote " + bytesCnt + "."); 
        }

        writer.close(); 
        fs.close();
    }
}
