class Producer extends Thread{
	int Consumerunique_id;
	int actualquota;
	BoundedBuffer b1;
	int counterquotap;
	int randomnumtoproduce;
	int randomnumtosleep;
	int totalproduce;
	int totalsleep;

	private Object itemtoinsert = new Object();
	public Producer(int quota){
		actualquota = quota;
		totalsleep=0;
		totalproduce=0;
		counterquotap = 0;
	}

	public void run(){

		while(true){
			//System.out.println("counterquoutap: " + counterquotap);
			randomnumtoproduce = (int) (Math.random() * 5); 
			randomnumtosleep = (int) (Math.random() * 101);
			totalsleep+=randomnumtosleep;
			totalproduce+=randomnumtoproduce;
			System.out.println(toString() + " ready to produce " + randomnumtoproduce + " items.");
			for(int i = 0; i < randomnumtoproduce; i++){
				b1.insert(itemtoinsert,this);
			}
			try{
				System.out.println(toString() + " is napping for " + randomnumtosleep + "ms");
				Thread.sleep(randomnumtosleep);
			}
			catch(Exception delta){

				//System.out.println(toString() + " is napping for " + randomnumtosleep + " time");
				break;
				//System.out.println("Producer did not sleep");
				//do this
			}


			//counterquotap+=1;
		}
	}
	public void setuniqueid(int uniqueid){
		Consumerunique_id = uniqueid;
		//System.out.println(Consumerunique_id);
	}

	public void pluscounterquotap(){
		counterquotap +=1;
	}

	public int getuniqueid(){

		return Consumerunique_id;
	}

	public void getboundedbuffer(){

	}

	public void setboundedbuffer(BoundedBuffer buffer){
		b1 = buffer;
	}

	public String toString(){
		String number = Integer.toString(Consumerunique_id);

		return "Producer " + number;
	}

	public String getStatus(){
		
		return "Producer ";
	}
}