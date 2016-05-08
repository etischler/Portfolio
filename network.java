//import java.io.IOException;
//import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
//import  java.io.BufferedReader;
//import java.io.InputStreamReader;
import java.lang.*;

import java.io.*;
class network{

	public static void main(String[] args) throws Exception{
		//must create socket to listen on
		int port = Integer.parseInt	(args[0]);
		ServerSocket listener = new ServerSocket(port);

		opensocket socket1 = new opensocket(listener.accept(), 0);
		opensocket socket0 = new opensocket(listener.accept(),1);

		//must set up sibling connections
		socket0.setBrotherSocket(socket1);
		socket1.setBrotherSocket(socket0);


		socket0.start();
		socket1.start();


		//System.out.println("this happens");


	}



}

class opensocket extends Thread{

	private Socket socket;
    
    private int mark;
   
   	static Boolean stop;

   	byte sequencenumber;
   	byte id;
   	int checksum;
   	byte ackCheckSum;
    byte[] message;
    int packetlength;
    int messagelength;
    String messageType;
    String messageString;
    static Boolean timetoexit;

    int length1;
    int length0;

   /*int passcount;
   int corruptcount;
   int dropcount;*/
   private Socket brothersocket;

	public opensocket(Socket socket, int identifier){
		/*passcount = 0;
		corruptcount = 0;
		dropcount = 0;*/
		this.socket = socket;
		mark = identifier;
		stop = false;
		timetoexit = false;
           // System.out.println("new connection");
            
      

	}

	public void setBrotherSocket(opensocket sibling){
		brothersocket = sibling.socket;
	}

	public void brotherSocketPost(String message){
		//output.println(message);
	}

    public void run(){
    	/*//try{sleep(200);}catch(Exception e){}
    	try{
    	
    	DataOutputStream out = new DataOutputStream(socket.getOutputStream());
    	}
    	catch(Exception e){
    		System.out.println(e.getStackTrace));
    	}

    	try{
    		DataInputStream in = new DataInputStream(socket.getInputStream());

    		System.out.println(in.readInt());
    	}
    	catch(Exception e){
    		System.out.println(e.getStackTrace));
    	}*/

    	int count = 0;
    	while(true){
    	
	    	if(mark==1){
	    		//System.out.println("Thread 1 started"); 
	    		String randomDecision = random();
	    		try{
	    			DataInputStream in = new DataInputStream(socket.getInputStream());
		    		//System.out.println("Reading");
	    			messagelength = in.readInt(); //take in all necessary information
	    			//System.out.println("read int");
	    			if(messagelength == -1){

	    				DataOutputStream out = new DataOutputStream(brothersocket.getOutputStream());
	    				//this.socket.close();
	    				out.writeInt(-1);
	    				//in = new DataInputStream(brothersocket.getInputStream());
	    				//in.readInt();	
	    				System.exit(0);
	    			}
	    			//System.out.println(messagelength)
	    			//System.out.println("Read");
	    			if(messagelength == 2){
	    				//we have an ACK
	    				messageType = "ACK";
	    			}
	    			else{
	    				messageType = "Packet";
	    			}

	    			if(messageType.equals("ACK")){
	    				if(messagelength>0){
	    					message = new byte[messagelength];
	    					in.readFully(message,0,message.length);
	    					sequencenumber = message[0];
	    					ackCheckSum = message[1];

	    					System.out.println("Received: " + messageType + ackCheckSum + ", " + randomDecision);	    					
	    				}

	    			}
	    			//this.sleep(2000);

	    			if(messageType.equals("Packet")){
	    				if(messagelength>0){
	    					message = new byte[messagelength];
	    					in.readFully(message,0,message.length);
	    					sequencenumber = message[0];
	    					id = message[1];
	    					byte[] toGetIntArray = new byte[4];
	    					toGetIntArray[0] = message[2];
	    					toGetIntArray[1] = message[3];
	    					toGetIntArray[2] = message[4];
	    					toGetIntArray[3] = message[5];
	    					checksum = java.nio.ByteBuffer.wrap(toGetIntArray).getInt();
	    					byte[] toMakeIntoString = new byte[messagelength-6];
	    					for(int i = 0; i < messagelength-6; i++){
	    						toMakeIntoString[i] = message[i+6];
	    					}

	    					messageString = new String(toMakeIntoString);

	    					System.out.println("Recieved: " + messageType + sequencenumber + ", " + id + ", " + randomDecision);

	    				}
	    			}

					
				}catch(Exception e){
					e.getStackTrace()[2].getLineNumber();
				}
				if(length1!=0){System.out.println(length1);}
 			
				try{

	    			DataOutputStream out = new DataOutputStream(brothersocket.getOutputStream());
		    		if(randomDecision.equals("PASS")){

		    			out.writeInt(messagelength);
		    			out.write(message);
		    		}
		    			
	

		    		if(randomDecision.equals("CORRUPT")){
		    			if(messageType.equals("ACK")){
		    				message[1]++;
		    				out.writeInt(messagelength);
		    				out.write(message);
		    			}
		    			if(messageType.equals("Packet")){
		    				checksum++;
		    				byte[] alpha = java.nio.ByteBuffer.allocate(4).putInt(checksum).array();
		    				message[2] = alpha[0];
		    				message[3] = alpha[1];
		    				message[4] = alpha[2];
		    				message[5] = alpha[3];

		    				out.writeInt(messagelength);
		    				out.write(message);
		    			}
		    		}

		    		if(randomDecision.equals("DROP")){
		    			if(messageType.equals("ACK")){
		    				byte[] dropMessage = new byte[2];
		    				dropMessage[0] = 2;
		    				dropMessage[1] = 1; // this value doesnt really matter but keep ack format

		    				out.writeInt(2);
		    				out.write(dropMessage);
		    			}

		    			if(messageType.equals("Packet")){
		    				out = new DataOutputStream(socket.getOutputStream());
		    				byte[] dropMessage = new byte[2];
		    				dropMessage[0] = 2;
		    				dropMessage[1] = 1; // this value doesnt really matter but keep ack format

		    				out.writeInt(2);
		    				out.write(dropMessage);
		    			}

		    		}
		    		//if(message1!=null){System.out.println(message1.toString());}
		    		//if(length1!=0){System.out.println(length1);}
		    	
		    	}catch(Exception e){
		    		e.getStackTrace()[2].getLineNumber();
		    	}


		    }	
		    	if(mark==0){
		    		//System.out.println("Thread 0 started");
		    		String randomDecisionother = random();
	    		try{
	    			DataInputStream in = new DataInputStream(socket.getInputStream());
		    		//System.out.println("Reading other");
	    			messagelength = in.readInt(); //take in all necessary information
	    			//System.out.println("Read other");
	    			if(messagelength == -1){
	    				DataOutputStream out = new DataOutputStream(brothersocket.getOutputStream());
	    				out.write(-1);
	    				System.exit(0);
	    			}
	    			if(messagelength == 2){
	    				//we have an ACK
	    				messageType = "ACK";
	    			}
	    			else{
	    				messageType = "Packet";
	    			}

	    			if(messageType.equals("ACK")){
	    				//System.out.println("ACK RECEIVED");
	    				if(messagelength>0){
	    					message = new byte[messagelength];
	    					in.readFully(message,0,message.length);
	    					sequencenumber = message[0];
	    					ackCheckSum = message[1];
	    					//System.out.println("Makes it");

	    					System.out.println("Received: " + messageType + ackCheckSum + ", " + randomDecisionother);	    					
	    				}

	    			}
	    			//this.sleep(200);

	    			if(messageType.equals("Packet")){
	    				System.out.println("Packet Received");
	    				if(messagelength>0){
	    					message = new byte[messagelength];
	    					in.readFully(message,0,message.length);
	    					sequencenumber = message[0];
	    					id = message[1];
	    					byte[] toGetIntArray = new byte[4];
	    					toGetIntArray[0] = message[2];
	    					toGetIntArray[1] = message[3];
	    					toGetIntArray[2] = message[4];
	    					toGetIntArray[3] = message[5];
	    					checksum = java.nio.ByteBuffer.wrap(toGetIntArray).getInt();
	    					byte[] toMakeIntoString = new byte[messagelength-6];
	    					for(int i = 0; i < messagelength-6; i++){
	    						toMakeIntoString[i] = message[i+6];
	    					}

	    					messageString = new String(toMakeIntoString);

	    					System.out.println("Recieved: " + messageType + sequencenumber + ", " + id + ", " + randomDecisionother);

	    				}
	    			}

					
				}catch(Exception e){
					e.getStackTrace()[2].getLineNumber();
				}
				if(length1!=0){System.out.println(length1);}
 			
				try{

	    			DataOutputStream out = new DataOutputStream(brothersocket.getOutputStream());
		    		if(randomDecisionother.equals("PASS")){
		    			//System.out.println("sdcdsc");
		    			out.writeInt(messagelength);
		    			out.write(message);
		    			//System.out.println("PASS OUT");
		    		}
		    			
	

		    		if(randomDecisionother.equals("CORRUPT")){
		    			if(messageType.equals("ACK")){
		    			//	System.out.println("sdcsdc");
		    				message[1]++;
		    				out.writeInt(messagelength);
		    				out.write(message);
		    			}
		    			if(messageType.equals("Packet")){
		    			//	System.out.println("sdcdsc");
		    				checksum++;
		    				byte[] alpha = java.nio.ByteBuffer.allocate(4).putInt(checksum).array();
		    				message[2] = alpha[0];
		    				message[3] = alpha[1];
		    				message[4] = alpha[2];
		    				message[5] = alpha[3];

		    				out.writeInt(messagelength);
		    				out.write(message);
		    			}
		    			//System.out.println("Corrupt out");
		    		}

		    		if(randomDecisionother.equals("DROP")){
		    			if(messageType.equals("ACK")){
		    			//	System.out.println("ascac");
		    				byte[] dropMessage = new byte[2];
		    				dropMessage[0] = 2;
		    				dropMessage[1] = 1; // this value doesnt really matter but keep ack format

		    				out.writeInt(2);
		    				out.write(dropMessage);
		    			}

		    			if(messageType.equals("Packet")){
		    				//System.out.println("xasx");
		    				out = new DataOutputStream(socket.getOutputStream());
		    				byte[] dropMessage = new byte[2];
		    				dropMessage[0] = 2;
		    				dropMessage[1] = 1; // this value doesnt really matter but keep ack format

		    				out.writeInt(2);
		    				out.write(dropMessage);
		    			}
		    			//System.out.println("Drop out");

		    		}
		    		//if(message1!=null){System.out.println(message1.toString());}
		    		//if(length1!=0){System.out.println(length1);}
		    	
		    	}catch(Exception e){
		    		e.getStackTrace()[2].getLineNumber();
		    	}
		    	
	    	}
    	
    	}

	}


	public String random(){ // this will determine what we get for random probability
		double value = Math.random();
		if(value<.5){
			return "PASS";
		}
	    if(value>=.5 && value < .75){
			return "CORRUPT";
		}
		if(value>=.75){
			return "DROP";
		}
		else{
			System.out.println("the fuck");
			return "";
		}


	}


}