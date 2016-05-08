import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.BufferedReader;
import java.io.InputStreamReader;


import java.util.Date;

class server{

	public static void main(String[] args) throws IOException{
		String socketNumberString = args[0];
		int socketNumber = Integer.parseInt(socketNumberString);	
		//System.out.println("Socket number specified: " +socketNumber);

		ServerSocket listener = new ServerSocket(socketNumber);

		String clientMessage = "";

		Boolean newConnection = false;
		
		Socket socket;

		socket = listener.accept();


		//socket = new Socket("storm.cise.ufl.edu" , 1694);
		try{
			
			PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
			BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream())); //get input from client

			System.out.println("connection from " + socket.getRemoteSocketAddress().toString()); //prints where connection is recieved from (IP)

					 //sends hello after connection is recieved
        	out.println("Hello!");
			while(!clientMessage.equals("terminate")){
				
				if(newConnection){
					socket = listener.accept();
					 out = new PrintWriter(socket.getOutputStream(), true);
					 input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
					System.out.println("connection from " + socket.getRemoteSocketAddress().toString()); //prints where connection is recieved from (IP)

					 //sends hello after connection is recieved
        			out.println("Hello!");
        			//firstOut.close(); //close socket now cuz both operations done first before socket needs to be closed
        			newConnection = false;
        		}
				//System.out.println("this happens");
				//socket = listener.accept();
				//	System.out.println("after happens");
				//socket = listener.accept();

				clientMessage = input.readLine();
				//input.close();
				//socket = listener.accept();

				//socket = new Socket("storm.cise.ufl.edu" , 1694);

				System.out.println(clientMessage);
				String[] words = clientMessage.split("\\s+");
					for (int i = 0; i < words.length; i++){
					    words[i] = words[i].replaceAll("[^\\w]", ""); //take out all punctuation in the message. put words into an array
					}
					//System.out.println(words.length);

				/*NOW BEGIN THE LOGIC WITH THE MESSAGE*/
				Boolean error = false;

				if(!error && (clientMessage.equals("terminate") || clientMessage.equals("bye"))){
					error = true;

					//PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                    out.println(-5);
                   // out.close();

                    error = true;
                    newConnection = true;
				}


				if(!words[0].equals("add") && !words[0].equals("subtract") && !words[0].equals("multiply") && !error){ //for the case of -1 error code
					error = true;
					//System.out.println("addition asked");
					//PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                    out.println(-1);
                    //out.close();
				}

				//for the case of -2 error code

				if(words.length < 3 && !error){
					error = true;

					//PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                    out.println(-2);
                    //out.close();
				}

				//for the case of -3 error code

				if(words.length > 5 && !error){
					error = true;

					//PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                    out.println(-3);
                    //out.close();
				}

				//for the case of -4 error code

				if(!error){ //must check length of numbers in comparison to length of words at this point
					int numbers = 0;
					for(int i = 0; i < words.length; i++){
						Boolean isNumber = true;
						for(int j = 0; j<words[i].length(); j++){
							if(words[i].charAt(j) >= 48 && words[i].charAt(j) <= 57){
								//do nothing
							}
							else{
								isNumber = false;
							}
						}
						if(isNumber){
							++numbers;
						}
						
					}

					//numbers should be 1 more than words based on convention
					if(words.length - numbers != 1){
						//PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
	                    out.println(-4);
	                    //out.close();
	                    error = true;
					}
					
				}
				/*BEGIN WRITTING CODE FOR COMPUTATION*/
				if(!error){

					//handeling case of addition

					if(words[0].equals("add")){
						int sum = 0;
						for(int i = 1; i < words.length; i++){
							try{
								sum += Integer.parseInt(words[i]);
							}
							catch(Exception e){
								//do nothing
							}
						}
						//PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
	                   	    out.println(sum);
	                   	    //out.close();
					}

					if(words[0].equals("subtract")){
						int diff = Integer.parseInt(words[1]);
						for(int i = 2; i < words.length; i++){
							diff -= Integer.parseInt(words[i]);
							
						}

						//PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
	                   	    out.println(diff);
	                   	    //out.close();

					}

					if(words[0].equals("multiply")){
						int firstNum = Integer.parseInt(words[1]);
						int total = firstNum;
						for(int i = 2; i < words.length; i++){
							total = total * Integer.parseInt(words[i]);
						}
						//PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
	                   	    out.println(total);
	                   	    //out.close();
					}

				}



				
				
			}

			out.close();
				input.close();
				socket.close();


		}
		finally{
			listener.close();
			
			
		}
       
    }


	








}