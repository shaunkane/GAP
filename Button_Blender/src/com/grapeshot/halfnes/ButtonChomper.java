package com.grapeshot.halfnes;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class ButtonChomper {

	public static SimpleDateFormat LONG_DATE = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS");
	public static SimpleDateFormat COMPRESSED_DATE = new SimpleDateFormat("yyyyMMddHHmmssSSS");
	public static SimpleDateFormat SHORT_TIME = new SimpleDateFormat("HH:mm:ss.SSS");
	
	private Date log_date;
	private File log_file;
	private BufferedWriter buffered_writer;
	private FileWriter file_writer;
	
	public ButtonChomper(){
		
		log_date = new Date(); // Right... Now!
		String intro = "Button Chomper is Ready to Chomp Some Buttons!";
		StringBuilder sb = new StringBuilder(COMPRESSED_DATE.format(log_date));
		
		try{
			log_file = new File("C:/Users/Karim Said/Desktop/Button_Chomper_" + sb.toString() + ".txt");
			
			if(!log_file.exists()){
				log_file.createNewFile();
			}
			
			file_writer = new FileWriter(log_file.getAbsoluteFile());
			buffered_writer = new BufferedWriter(file_writer);
			
			print_to_log(intro);
		}catch (IOException e){
			e.printStackTrace();
		}
	}
	
	public boolean print_to_log(int controller_number, String event, String main_line)
	{
		Date print_date = new Date(); // Right... Now!
		StringBuilder sb = new StringBuilder(
				LONG_DATE.format(print_date) + "," +
				controller_number + "," +
				event + "," +
				main_line);
		
		try{
			buffered_writer.write(sb.toString());
			buffered_writer.newLine();
			buffered_writer.flush();
			
			System.out.println(sb.toString());
		}catch(IOException e){
			e.printStackTrace();
		}
		
		return true;
	}
	public boolean print_to_log(String main_line)
	{
		Date print_date = new Date(); // Right... Now!
		StringBuilder sb = new StringBuilder(
				LONG_DATE.format(print_date) + ":\t" +
				main_line);
		
		try{
			buffered_writer.write(sb.toString());
			buffered_writer.newLine();
			buffered_writer.flush();
			System.out.println(sb.toString());
		}catch(IOException e){
			e.printStackTrace();
			return false;
		}
		
		return true;
	}
	
	public boolean close_chomper(){
		try{
			buffered_writer.close();
		}catch(IOException e){
			e.printStackTrace();
			return false;
		}
		
		return true;
	}
}
