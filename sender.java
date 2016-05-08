import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.File;
import java.io.FileReader;
import java.util.Scanner;

import java.io.BufferedOutputStream;
import java.io.BufferedInputStream;

import java.io.DataOutputStream;
import java.io.DataInputStream;
//import java.lang.*;

class sender{

	

	public static void main(String[] args) throws Exception{

		    BufferedReader newconsole;
    		

			//take in the filename
			String fileName = args[2];

			//make a socket.
			String ipchoice = args[0];
			int port = Integer.parseInt(args[1]);

			Socket socket = new Socket(ipchoice,port);

			//read the file

			Scanner console = new Scanner(new File(fileName)); //remember to close this

			int count = 0;

			while(console.hasNext()){ //got the count of how many words in the message
				count++;
				console.next();
			}
			
			Boolean done = false;
			//System.out.println(count);

			//make an array based on number of words in the file

			String[] message = new String[count];

			console = new Scanner(new File(fileName)); //remember to close this

			for(int i = 0; i < count; i++){
				message[i] = console.next();
				//System.out.print(message[i] + " ");
			}

			//first case
			int terminator = -1;
			int totalsent = 0;
			int currentPacket = 1;
			String packetText;
			byte[] byteText;
			byte sequence;
			byte id;
			int checkSum;
			byte[] byteSum;

			int ascii;
			int actualCheckSum;

			int oldoutboundlength=4;
			byte[] oldoutboundMessage = new byte[5];

			byte[] response = new byte[5];

			byte expectedSequence = 0;
			int increment = 0;

			try{
				DataOutputStream out = new DataOutputStream(socket.getOutputStream());
				packetText = message[0];
				byteText = packetText.getBytes();
				sequence = 0;
				id = 1;

				actualCheckSum = 0;
				for(int i=0; i < packetText.length(); i++){
					ascii = packetText.charAt(i);
					actualCheckSum += ascii;
				}
				byteSum = java.nio.ByteBuffer.allocate(4).putInt(actualCheckSum).array();

				oldoutboundlength = 6 + byteText.length;
				oldoutboundMessage = new byte[oldoutboundlength];
				oldoutboundMessage[0] = sequence;
				oldoutboundMessage[1] = id;
				oldoutboundMessage[2] = byteSum[0];
				oldoutboundMessage[3] = byteSum[1];
				oldoutboundMessage[4] = byteSum[2];
				oldoutboundMessage[5] = byteSum[3];
				//System.out.println("before");
				for(int i = 6; i < oldoutboundlength; i++){
					oldoutboundMessage[i] = byteText[i-6];
				}
				//System.out.println("after");
				totalsent++;
				out.writeInt(oldoutboundlength);
				out.write(oldoutboundMessage);
				//System.out.println("Waiting ACK" + expectedSequence)

			}catch(Exception e){
				System.out.println(e);
			}

			//after first case 

			while(!done){

				try{
					DataInputStream in = new DataInputStream(socket.getInputStream());
					//System.out.println("Reading");
					int messagelength = in.readInt();
					response = new byte[messagelength];
					in.readFully(response,0,response.length);


					//System.out.println("Read");
					//Thread.sleep(2000);
					if(messagelength == 2){
						//System.out.println("Ack Received");
						//Ack Received
						DataOutputStream out = new DataOutputStream(socket.getOutputStream());
						if(response[0] == 2){ //in case it was dropped

							System.out.println("Waiting ACK" + expectedSequence + ", " + totalsent + ". " + "DROP, resend Packet" + currentPacket );
							totalsent++;

							out.writeInt(oldoutboundlength);
							out.write(oldoutboundMessage);

						}

						else if(response[0] == expectedSequence && currentPacket != count){ //in the case the right ack came back
							System.out.println("Waiting ACK" + expectedSequence + ", " + totalsent + ". " + "ACK" + response[0] +  ", send Packet" + (currentPacket+1) );
							currentPacket++;
							if(expectedSequence ==1){
								expectedSequence=0;
							}
							else{
								expectedSequence = 1;
							}
							increment++;
							packetText = message[increment];
							byteText = packetText.getBytes();
							sequence = expectedSequence;
							id = (byte) (currentPacket);

							actualCheckSum = 0;
							for(int i=0; i < packetText.length(); i++){
								ascii = packetText.charAt(i);
								actualCheckSum += ascii;
							}
							byteSum = java.nio.ByteBuffer.allocate(4).putInt(actualCheckSum).array();

							oldoutboundlength = 6 + byteText.length;
							oldoutboundMessage = new byte[oldoutboundlength];
							oldoutboundMessage[0] = sequence;
							oldoutboundMessage[1] = id;
							oldoutboundMessage[2] = byteSum[0];
							oldoutboundMessage[3] = byteSum[1];
							oldoutboundMessage[4] = byteSum[2];
							oldoutboundMessage[5] = byteSum[3];

							for(int i = 6; i < oldoutboundlength; i++){
								oldoutboundMessage[i] = byteText[i-6];
							}
							totalsent++;
							out.writeInt(oldoutboundlength);
							out.write(oldoutboundMessage);


						}
						else if(response[0] == expectedSequence && currentPacket == count){
							System.out.println("Waiting ACK" + expectedSequence + ", " + totalsent + ". " + "ACK" + response[0] +  ", no more packets to send");
							out.writeInt(terminator);
							done = true;
							//System.exit(0);
						}
						else{ //not expected and therefore resend needed
							System.out.println("Waiting ACK" + expectedSequence + ", " + totalsent + ". " + "ACK" + response[0] +  ", resend Packet" + currentPacket );
							totalsent++;
							out.writeInt(oldoutboundlength);
							out.write(oldoutboundMessage);
						}


					}
					else{
						System.out.println("Something went wrong. NON ACK Received.");
					}


				}catch(Exception e){
					System.out.println(e);
				}
			

			}
			

			

	}





}