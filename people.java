import java.util.Random;

class people extends Thread{
	static private Random random = new Random();
	static actualbathroom bathroom;
	int sleepduration;
	int bathroomduration;
	int id;
	Boolean running;
	Boolean male;
	//Bathroom bathroom;
	public people(int num, Boolean genderismale, actualbathroom therealdeal){
		id = num+1;
		bathroom = therealdeal;
		running = true;
		if(genderismale){
			male = true;
		}
		else{
			male = false;
		}
		
	}

	public void run(){
		//System.out.println("He ran " + id);
		while(running){
			int sleepduration = random.nextInt( 7000 ) + 1000 ;
			int bathroomduration = random.nextInt( 7000 ) + 1000 ;
			running = true;
    	  	try{
	    	   this.sleep(sleepduration);
	    	   if(this.male){
	    	   		bathroom.wants_to_enter(true);
	    	   		System.out.println("Male " + id + " has entered the bathroom");
	    	   		
	    	   }
	    	   else{

	    	   		bathroom.wants_to_enter(false);
	    	   		System.out.println("Female " + id + " has entered the bathroom");
	    	   		
	    	   }
	    	   this.sleep(bathroomduration);
	    	   if(this.male){
	    	   		bathroom.leaves(true);
	    	   		System.out.println("Male " + id + " has left the bathroom");
	    	   	}
	    	   		
	    	   else{

	    	   		bathroom.leaves(false);
	    	   		System.out.println("Female " + id + " has left the bathroom");
	    	   	
	    	   }
	    	   
      		}
        	catch(InterruptedException forjoin){
        		//System.out.println("exception thrown");
        		this.running = false;
       			 
       	    }
  	    }
  	}

	

}


