import java.io.*;
//import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import  java.util.Scanner;
//import java.io.InputStreamReader;


class receiver{

	public static void main(String[] args) throws Exception{
			//make a socket.
			String ipchoice = args[0];
			int port = Integer.parseInt(args[1]);

			Socket socket = new Socket(ipchoice,port);

			//make connection
			int messagelength=2;

			byte[] message = new byte[2];

			String messageType;
			
			int packetsTotal=0;;

			int acceptedPackets=0;

			byte id;

			byte sequence;
			int checksum;

			int lastsequence = 0;

			int actualCheckSum;

			String messageString;

			String finalString="Message: ";

			byte[] reply;

			while(true){
				try{
	    			DataInputStream in = new DataInputStream(socket.getInputStream());
	    			//System.out.println("Reading");
	    			 messagelength =  in.readInt();

	    			 if(messagelength == -1){
	    			 	DataOutputStream out = new DataOutputStream(socket.getOutputStream());
	    			 	out.writeInt(42);

	    			 	System.out.println(finalString);
	    			 	//socket.close();
	    			 	System.exit(0);
	    				
	    			}
	    			// System.out.println("Read");
	    			if(messagelength>0){
	    					message = new byte[messagelength];
	    					in.readFully(message,0,message.length);
	    			}
	    			//Thread.sleep(2000);

	    			//CATCH NEEDS TO BE HERE
	    			}catch(Exception e){
	    			System.out.println(e);
	    			}

	    			if(messagelength==2){
	    				messageType = "ACK";
	    				System.out.println("Something went wrong ACK received");
	    			}
	    			else{
	    				messageType = "Packet";
	    				packetsTotal++;

	    				//extract info

	    				sequence = message[0];
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

    					int ascii;
    					actualCheckSum = 0;
    					for(int i=0; i < messageString.length(); i++){
    						ascii = messageString.charAt(i);
    						actualCheckSum += ascii;
    					}
    					//System.out.println(id + " " + (acceptedPackets+1));
    					if( id < (acceptedPackets+1)){
							reply = new byte[2];
							reply[0] = sequence;
							reply[1] = 0;


						}
    					else if(checksum == actualCheckSum && id == (acceptedPackets+1)){ //conditions for an accepted packet
    						finalString+=messageString + " ";
    						//System.out.println("accepted");
    						acceptedPackets++;
    						reply = new byte[2];
    						if(lastsequence==1){
    							reply[0]=1;
    							lastsequence = 0;
    						}
    						if(lastsequence == 0){
    							reply[0] = 0;
    							lastsequence = 1;
    						}
    						reply[1] = 0;	
    						
    					}
    					else{
    						//System.out.println("Packet not accepted" + packetsTotal);
    						reply = new byte[2];
    						if(sequence==1){
    							reply[0]=0;
    							//lastsequence = 0;
    						}
    						if(sequence == 0){
    							reply[0] = 1;
    							//lastsequence = 1;
    						}
    						reply[1] = 1;
    						
    					}
    					System.out.println("Waiting " + lastsequence + ", " + packetsTotal + ", " + sequence + " " + id + " " + checksum + " " + messageString + ", " + "ACK" + reply[0]);

    					try{
    					DataOutputStream out = new DataOutputStream(socket.getOutputStream());
    					//System.out.println("here");
    					out.writeInt(2);
    					out.write(reply);
    					out.flush();
    					//System.out.println("sent");
    					//Thread.sleep(2000);
    					}catch(Exception e){
    						System.out.println(e);
    					}

	    			}


	    		


			}








	}





}