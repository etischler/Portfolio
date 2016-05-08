import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

class linkstate{
	
	public static void main(String[] args) throws Exception{

		String filename = args[0];
		File file = new File(filename);
		Scanner sc = new Scanner(file); //creating a means of reading the text file
		int numlines = 0;

		while(sc.hasNextLine()){
			sc.nextLine();
			numlines++;
		}		
		int nodecount = numlines-1; //because of eof line
		sc = new Scanner(file);
		String[] lines = new String[nodecount];
		String [][] originalNetworkString = new String[nodecount][nodecount]; //must take in as a string first due to N possibility
		int[][] originalNetwork = new int[nodecount][nodecount];
		
		for(int i = 0; i < nodecount; i++){ //get the lines doe
			lines[i] = sc.nextLine();
		}
		
		for(int i = 0; i < nodecount; i++){
			lines[i] = lines[i].replaceAll("[^0-9a-zA-Z ]", ""); //gets rid of punctuation in lines[]
			for(int j = 0; j <nodecount;j++){		
				originalNetworkString[i][j] = String.valueOf(lines[i].charAt(j));
				try{
					originalNetwork[i][j] = Integer.parseInt(originalNetworkString[i][j]); //try to put it into the int array
				}
				catch(Exception e){
					originalNetwork[i][j] = -1; // if not make it a non edge because of N
				}
			}
			
		}

		int tabsneeded = nodecount + 1;
		int totaldashes = (tabsneeded *8) + (nodecount * 8); //helps calculate how big the lines should be

		dashLine(totaldashes);
		printColumnHeaders(nodecount); //print original header
		dashLine(totaldashes);

		int[] dist = new int[nodecount]; //needed for dijkstra
		int sortedlist[] = new int[nodecount];
		int n = nodecount;
		int currentcount = 1;
		int sortlistcount = 0;
		int[] dp = new int[nodecount]; //will hold the distance values for each node
		ArrayList<Integer> vdone = new ArrayList<Integer>();  //will hold whether the p() is done
		int[] old = new int[nodecount];
		int oldu[] =  new int[nodecount]; //needed to determine which p(v) column needs to change
		for(int i = 0;i<nodecount;i++){
			oldu[i] = Integer.MAX_VALUE; //so i know that there is a change
		}

		Boolean done[] = new Boolean[nodecount]; //this code is dijkstra's algorithm. Source from http://www.cs.cornell.edu/~wdtseng/icpc/notes/graph_part2.pdf
		int s = 0;
		for( int i = 0; i < n; i++ ) {
			dist[i] = Integer.MAX_VALUE;
			done[i] = false;
		}
		dist[s] = 0;
		while( true ) {
		// find the vertex with the smallest dist[] value
			int u = -1;
			int bestDist = Integer.MAX_VALUE;
			for( int i = 0; i < n; i++ ) if( !done[i] && dist[i] < bestDist ) {
				u = i;
				bestDist = dist[i];
			}
			//System.out.println("u: "+u);
			if( bestDist == Integer.MAX_VALUE ) 
				break;
		// relax neighbouring edges
			for( int v = 0; v < n; v++ ) if( !done[v] && originalNetwork[u][v] != -1 ) {
				if( dist[v] > dist[u] + originalNetwork[u][v] ){
					dist[v] = dist[u] + originalNetwork[u][v];

				}
				
					//System.out.println("("+v+","+dist[v]+","+u+")");
					dp[v] = dist[v];
					//System.out.println("("+dist[v]+","+(u)+")");
				
			}
			done[u] = true;

			System.out.print("   "+sortlistcount+"    \t"); //will be the step
			sortedlist[sortlistcount] = u+1;
			sortlistcount++;

			
			for(int k = 0;k <sortlistcount;k++){ //this code lists the values in n'
				Arrays.sort(sortedlist, 0,sortlistcount);
				if(k != sortlistcount-1)
					System.out.print(sortedlist[k]+",");
				else if(k<4)
					System.out.print(sortedlist[k] + "\t\t");
				else
					System.out.print(sortedlist[k]+"\t");
			}

			vdone.add(u);
			for(int l = 1; l < nodecount; l++){
				if(!vdone.contains(l)){
					if(dp[l]==0)
						System.out.print("    N   \t");
					else if(dp[l]!=old[l]){
						//System.out.print("("+dp[l]+","+old[l]+")"); //if a non finished column print a certain way based on whether distance has changed or nah
						System.out.print("   "+dp[l]+","+(u+1)+"  \t");
						old[l]=dp[l];
						oldu[l] = u+1;
					}
					else
						System.out.print("   "+old[l]+","+(oldu[l])+"  \t");
				}
				else
					System.out.print("        \t");

				
			}

			
			System.out.println();
			dashLine(totaldashes); //finish out the step
			
		}

	}

	public static void dashLine(int totalDashes){
		//System.out.println();
		for(int i = 0; i < totalDashes; i++){
			System.out.print("-");
		}	
		System.out.println();
	}

	public static void printColumnHeaders(int numnodes){			//just helper functions to prevent writing excess code
		System.out.print("  Step  \t   N'   \t");
		for(int i = 2; i < numnodes+1;i++){
			System.out.print("D("+i+")"+",p("+i+")\t");
		}
		System.out.println();

	}



}