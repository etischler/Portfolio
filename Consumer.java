class Consumer extends Thread{
	int Consumerunique_id;
	int actualquota;
	int counterquotac;
	BoundedBuffer b1;
	int randomnumtoconsume;
	int randomnumtosleep;
	public Consumer(int quota){
		counterquotac = 0;
		actualquota = quota;

	}

	public void run(){
		//System.out.println("consumer");
		//System.out.println(Consumerunique_id);
		//b1.countplus();
		while(true){
			//System.out.println("counterquoutap: " + counterquotap);
			 randomnumtoconsume = (int) (Math.random() * 5); 
			 randomnumtosleep = (int) (Math.random() * 101);
			System.out.println(toString() + " ready to consume " + randomnumtoconsume + " items.");
			for(int i = 0; i < randomnumtoconsume; i++){
				b1.remove(this);
			}
			try{
				System.out.println(toString() + " is napping for " + randomnumtosleep + "ms");
				Thread.sleep(randomnumtosleep);
			}
			catch(Exception delta){
				//System.out.println(toString() + " is napping for " + randomnumtosleep + " time");
				break;
			}


			//counterquotap+=1;
		}
		//}
		//b1.remove(this);

	}

	public void setuniqueid(int uniqueid){
		Consumerunique_id = uniqueid;

		//System.out.println(Consumerunique_id);
	}

	public void pluscounterquotac(){
		counterquotac+=1;
	}

	public int getuniqueid(){

		return Consumerunique_id;
	}

	public void setboundedbuffer(BoundedBuffer buffer){
		b1 = buffer;
	}

	public String toString(){
		String number = Integer.toString(Consumerunique_id);

		return "Consumer " + number;
	}

	//string get status code done in run code like in producer
}