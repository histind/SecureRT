

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;


public class CSV_Parser {
	  public static double threshold = 3.0;
	  public static boolean debug = false;
	  public static String cipher  = "aes";
	  public static void main(String[] args) {
	 
		CSV_Parser obj = new CSV_Parser();
		obj.readAndParse();
	 
	  }
	 
	  public void readAndParse() {
	 
		String csvFile = "/home/david/Desktop/data/" + cipher + ".csv";
		String output = "/home/david/Desktop/data/" + cipher + "_output.csv";
		BufferedReader br = null;
		BufferedWriter bw = null;
		FileWriter fw = null;
		File file = null;
		
		double increment;
		ArrayList<Integer> seqList = new ArrayList<Integer>();
		ArrayList<Integer> adjList = new ArrayList<Integer>();
		ArrayList<Double> resultInMicroseconds = new ArrayList<Double>();
		
		String line = "";
		String comma = ",";
	 
		try {
			
			br = new BufferedReader(new FileReader(csvFile));
			file = new File(output);
			if(!file.exists()){
				file.createNewFile();
			}
			fw = new FileWriter(file.getAbsoluteFile());
			bw = new BufferedWriter(fw);
			//get header tokens
			line = br.readLine();
			//store increment
			line = br.readLine();
			String[] incr = line.split(comma);
			// incr[3] is a string of increment value, convert to double
			increment = Double.valueOf(incr[3]);
			while ((line = br.readLine()) != null) {
			    // use comma as separator
				String[] dataPoint = line.split(comma);
				// store in sequence list
				if(Double.valueOf(dataPoint[1]) >= threshold){
					seqList.add(new Integer(Integer.parseInt(dataPoint[0])));
				}
				
				if(debug){
					//bw.write(dataPoint[0] + ", " + dataPoint[1] + "\n");
				}
			}
			if(debug){
				for(int i = 0; i < seqList.size(); i++){
					//bw.write(seqList.get(i).toString() + "\n");
				}
			}
			
			//int i = 0;
			int numAdjacent = 0;
			for(int i = 0; i < seqList.size()-2; i++){
				if(seqList.get(i+1).intValue()-seqList.get(i).intValue() == 1){
					// increment
					numAdjacent++;
				}
				else{
					// reached signal boundary
					numAdjacent++;
					adjList.add(numAdjacent);
					numAdjacent = 0;
				}
			}
			// must be end of file
			numAdjacent++;
			adjList.add(numAdjacent);
			if(debug){
				//bw.write(numAdjacent);
			}
			
			// get timings in microseconds
			for(int i = 0; i < adjList.size(); i++){
				double seconds = adjList.get(i) * increment;
				double microSec = seconds * 1000000;
				resultInMicroseconds.add(microSec);
				bw.write(microSec + ", ");
			}
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (br != null) {
				try {
					br.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
	 
		System.out.println("Done");
	  }
	 
	}
