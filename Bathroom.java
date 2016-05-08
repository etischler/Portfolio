public class Bathroom{
		private people[]  men;
		private people[] women;
		int bathroomsize = 3;
		actualbathroom actbath = new actualbathroom(3);
	public Bathroom(int numpeople){
		men = new people[numpeople];
		women = new people[numpeople];
		

		initialize();
		sleep(1200000);
		killthreads();



	}
	public void initialize(){
		System.out.println("Men and women will now begin the process of attempting to use the unisex bathroom");
		for(int i = 0 ; i < 3; i ++){
			men[i] = new people(i,true, actbath);
			women[i] = new people(i,false, actbath);
		}

		for(int i = 0; i<3; i++){
			men[i].start();
			women[i].start();
		}
		

	}

	private void sleep( int duration )
  {
    try
    {
      Thread.currentThread().sleep( duration );
    }
    catch ( InterruptedException e )
    {
      Thread.currentThread().interrupt();
    }
  }

  	public void killthreads(){
  		try{
  			for(int i = 0; i < 3; i++){
  				men[i].interrupt();
  				women[i].interrupt();

  				men[i].join();
  				women[i].join();
  			}
  		}
  		catch(Exception alpha){
  			System.out.println("this somehow did not work");	
  		}
  	} 


	public static void main(String args[]){
		new Bathroom(3);
	}

	
}