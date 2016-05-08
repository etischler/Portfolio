import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.io.PrintWriter;
import java.util.Scanner;
import java.net.ServerSocket;


class client{
	

	 public static void main(String[] args) throws IOException {
	        //System.out.println("new");
	 	String ipChoice = args[0];
	 	int port = Integer.parseInt(args[1]);
	 	//System.out.println("marker");
	 	Socket socket = new Socket(ipChoice , port);
	 	 
	 	BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream())); //get input from server
		String responseMessage = input.readLine();
		//input.close();
		System.out.println(responseMessage);

		Scanner clientInput = new Scanner(System.in);

		ServerSocket listener = new ServerSocket(port); /*CHANGE THIS TO BE AN ARG*/
		PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

		input = new BufferedReader(new InputStreamReader(socket.getInputStream())); //get input from server
		
		while(!responseMessage.equals("-5")){

			String clientMessage = clientInput.nextLine();
			//socket = new Socket(ipChoice , port);
			
			//System.out.println("client messsage: " + clientMessage);
            out.println(clientMessage);
           // out.close();
            //System.out.println("here");
            //socket = listener.accept();
            //System.out.println("here it fucks");
            
			responseMessage = input.readLine();
			//input.close();
			//System.out.println(responseMessage);
			if(responseMessage.equals("-1")){
				System.out.println("incorrect operation command.");
			}
			else if(responseMessage.equals("-2")){
				System.out.println("number of inputs is less than two.");
			}
			else if(responseMessage.equals("-3")){
				System.out.println("number of inputs is more than four.");
			}
			else if(responseMessage.equals("-4")){
				System.out.println("one or more of the inputs contain(s) non-number(s).");
			}
			else if(responseMessage.equals("-5")){
				System.out.println("exit.");
			}
			else{
				System.out.println(responseMessage);
			}

            
		}
	 	
		socket.close();
		input.close();
		out.close();
		clientInput.close();


		//socket.close();
		//input.close();
		//out.close();
		//clientInput.close();
	}

}