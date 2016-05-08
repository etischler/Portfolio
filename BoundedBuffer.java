class BoundedBuffer<E>{

 	
	private E buffer[];
	static int count;
	Item item = new Item();

	int itemnumber;
	int buffersize;

	Thread p1thread;
	Thread p2thread;
	Thread c1thread;
	Thread c2thread;

	Producer p1producer;
	Producer p2producer;
	Consumer c1consumer;
	Consumer c2consumer;

 	private Object pLock = new Object(); // producer lock
 	private Object cLock = new Object(); // consumer lock


	public BoundedBuffer(int size){
		buffersize = 3;
		itemnumber = 1;
		count = 0;
		buffer = (E[]) new Object[size];
		item.getitemnumber(itemnumber);

		
		//initialize actual buffer
		//Item item = new Item();
	}
	//Generic generic = new Generic(3);
	

	public int buffersize(){

		return buffer.length;
	}

	public void getproducers(Producer p1, Producer p2){
		p1producer = p1;
		p2producer = p2;
	}

	public void getconsumers(Consumer c1, Consumer c2){
		c1consumer = c1;
		c2consumer = c2;
	}

	public void getthreads(Thread p1, Thread p2, Thread c1, Thread c2){
		p1thread = p1;
		p2thread = p2;
		c1thread = c1;
		c2thread = c2;
	}

	public int count(){
		return count;
	}

	public void countminus(){
		count-=1;
	}

	public void countplus(){
		count +=1;
	}

						//should be E
	public void insert( E itemtoinsert, Producer p){

		//when there is no space available (before the
		//producer blocks) print
		//System.out.println(generic.length());


		synchronized(cLock){
			try{
			
			cLock.notifyAll();	
			}
			catch(Exception f){
				//System.out.println("insert exception");
			}	
			
			//System.out.println("Count on insert: " + count());
			if(count() == 3){
				System.out.println(p.toString() + " waiting to insert an item");
				try{
				cLock.wait();
				
				}
				catch(Exception f){
					//System.out.println("caught insert");
				}
				//System.out.println("this happens");

				//this.wait();
				//System.out.print(" waiting to remove an item");

			}

			//after removing an item from the backing store
			//print
			//System.out.println("right before add count: " + count);
			if(count() < 3 && count() >= 0){				//System.out.print(c.toString());

				System.out.println(p.toString() + " inserted " + item.toString() + "\t(" + ((count()%buffersize)+1) + " of " + buffersize + " slots full)");
				//System.out.print(item.toString());
				buffer[count()%buffersize] = itemtoinsert;
				countplus();
				item.getitemnumber(++itemnumber);
				p.pluscounterquotap();



			}
			try{
			pLock.notifyAll();
			
			}
			catch(Exception f){
				//System.out.println("remove exception");
			}
			
		}
	}
			//supposed to be E
	public void remove( Consumer c){
		//when there is no item available (before the 
		//consumer blocks) print
		//System.out.print("count: " + count);
		synchronized(cLock){
			try{
			cLock.notifyAll();
			
			}
			catch(Exception f){
				//System.out.println("remove exception");
			}		
			//System.out.println("Count on remove: " + count());
			//System.out.println(count());
			if(count() == 0){
				System.out.println(c.toString() + " waiting to remove an item");
				try{
				cLock.wait();
				
				}
				catch(Exception e){
					//System.out.println("caught remove");
				}
				//System.out.println("this happens");

				//this.wait();
				//System.out.print(" waiting to remove an item");

			}

			//after removing an item from the backing store
			//print
			if(count() > 0 && count() < 4){
				
				//System.out.print(c.toString());

				System.out.println(c.toString() + " removed " + (item.itemnum()-count()) + "\t(" + ((count()-1%buffersize)+1) + " of " + buffersize + " slots full)");
				//System.out.print(item.toString());
				buffer[(item.itemnum()-count())%buffersize] = null;
				countminus();
				//item.getitemnumber(++itemnumber);
				c.pluscounterquotac();



			}
			//System.out.println("out");
			try{
			cLock.notifyAll();
			
			}
			catch(Exception f){
				//System.out.println("remove exception");
			}
			
		}
		//return ;
	}

	public String toString(){
		int value1 = item.itemnum()-3;
		int value2 = item.itemnum()-2;
		int value3 = item.itemnum()-1;
		String s1 = Integer.toString(value1);
		String s2 = Integer.toString(value2);
		String s3 = Integer.toString(value3);

		/*returns a square bracketed, comma separated string
		representing the buffer and its contents. non-empty 
		slots will be denoted by the toString() value of that
		 slot, while empty slots will be denoted by the string
		  "---"; for example: [Item #393, ---, Item #395]*/

		  return ("BoundedBuffer := [Item #" + s1 + ", Item #" + s2 + ", Item #" + s3 + "]" );
	}

}