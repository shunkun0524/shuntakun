import java.io.*;
public class ScoreAnalyzer1{
    void run(String[] args) throws IOException{
	this.prepation(args);
    }
    void prepation(String[] args) throws IOException{
	File readFile=new File(args[1]);
	BufferedReader fileRead=new BufferedReader(new FileReader(readFile));
	String line;
	while((line=fileRead.readLine())!=null){
	    String[] row=line.split(",");
	    
	}
    }
    public static void main(String[] args) throws IOException{
	ScoreAnalyzer1 scoreAnalyzer=new ScoreAnalyzer1();
	scoreAnalyzer.run(args);
    }
