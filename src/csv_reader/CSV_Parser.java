

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;


public class CSV_Parser {
	 
	  public static void main(String[] args) {
	 
		CSV_Parser obj = new CSV_Parser();
		obj.run();
	 
	  }
	 
	  public void run() {
	 
		String csvFile = "/home/david/secureRT/aes.csv";
		BufferedReader br = null;
		String line = "";
		String csvToken = ",";
	 
		try {
	 
			br = new BufferedReader(new FileReader(csvFile));
			while ((line = br.readLine()) != null) {
	 
			        // use comma as separator
				String[] country = line.split(csvToken);
	 
				System.out.println("Country [code= " + country[4] 
	                                 + " , name=" + country[5] + "]");
	 
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
