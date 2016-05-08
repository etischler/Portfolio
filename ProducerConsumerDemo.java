
class ProducerConsumerDemo{
	public static void main(String[] args){
		int countp = 1;
		int countc = 1;
		Producer p1 = new Producer(20);
		Producer p2 = new Producer(20);
		Consumer c1 = new Consumer(20);
		Consumer c2 = new Consumer(20);

		BoundedBuffer bb = new BoundedBuffer(3);
		bb.getproducers(p1,p2);
		bb.getconsumers(c1,c2);
		p1.setboundedbuffer(bb);
		p2.setboundedbuffer(bb);
		c1.setboundedbuffer(bb);
		c2.setboundedbuffer(bb);

		p1.setuniqueid(countp++);
		p2.setuniqueid(countp++);
		c1.setuniqueid(countc++);
		c2.setuniqueid(countc++);
		Thread p1thread = new Thread(p1);
		
		Thread p2thread = new Thread(p2);
		
		Thread c1thread = new Thread(c1);
		Thread c2thread = new Thread(c2);

		bb.getthreads(p1thread, p2thread, c1thread, c2thread);

		p1thread.start();
		p2thread.start();

		c1thread.start();
		c2thread.start();

		//System.out.println("Process ProducerConsumerDemo1 finished");
		try {
    		Thread.sleep(5000);                  //1000 milliseconds is one second.
		} 
		catch(InterruptedException ex) {
   			 Thread.currentThread().interrupt();
		}
		//System.out.println("interruption starting");

		try{
			p1thread.interrupt();
			p2thread.interrupt();
			c1thread.interrupt();
			c2thread.interrupt();
		}
		catch(Exception alpha){
			System.out.println("Interrupt failed");
		}
		try{
			p1thread.interrupt();
			p2thread.interrupt();
			c1thread.interrupt();
			c2thread.interrupt();
		}
		catch(Exception alpha){
			System.out.println("Interrupt failed");
		}
		try{
			p1thread.join();
			p2thread.join();
			c1thread.join();
			c2thread.join();
		}
		catch(Exception quatro){
			System.out.println("failed to terminiate");
		}
		System.out.println("Producer 1 TERMINATING");
		System.out.println("Producer 2 TERMINATING");
		System.out.println("Consumer 1 TERMINATING");
		System.out.println("Consumer 2 TERMINATING");


		System.out.println(bb.toString());
		
	}
}





/*--the constructor takes a quota—the number of items that will
 be produced/consumed before terminating
--each instance has a unique_id
--has a toString() which returns a String of the form
"Producerunique_id"
or
"Consumerunique_id"
--run in a cycle until the quota has been reached
produce an item and insert() it/remove() an item and consume
 it [consumption will do nothing]
before terminating
--print total number of items produced/consumed
"Producerunique_id FINISHED producing quota items"
or
"Consumerunique_id FINISHED consuming quota items"*/





/* Sample run
Consumer1 waiting to remove an item
Consumer2 waiting to remove an item
Producer1 inserted Item #1	(1 of 3 slots full)
Producer1 inserted Item #2	(2 of 3 slots full)
Producer1 inserted Item #3	(3 of 3 slots full)
Producer1 waiting to insert Item #4
Producer2 waiting to insert Item #5
Consumer1 removed  Item #3	(2 of 3 slots full)
Consumer1 removed  Item #2	(1 of 3 slots full)
Consumer1 removed  Item #1	(0 of 3 slots full)
Consumer1 waiting to remove an item
Producer2 inserted Item #5	(1 of 3 slots full)
Producer2 inserted Item #6	(2 of 3 slots full)
Producer2 inserted Item #7	(3 of 3 slots full)
Producer2 waiting to insert Item #8
Producer1 waiting to insert Item #4
Consumer2 removed  Item #7	(2 of 3 slots full)
Consumer2 removed  Item #6	(1 of 3 slots full)
Consumer2 removed  Item #5	(0 of 3 slots full)
Consumer2 waiting to remove an item
Producer1 inserted Item #4	(1 of 3 slots full)
Producer1 inserted Item #9	(2 of 3 slots full)
Producer1 inserted Item #10	(3 of 3 slots full)
Producer1 waiting to insert Item #11
Consumer2 removed  Item #10	(2 of 3 slots full)
Consumer2 removed  Item #9	(1 of 3 slots full)
Consumer2 removed  Item #4	(0 of 3 slots full)
Consumer2 waiting to remove an item
Producer1 inserted Item #11	(1 of 3 slots full)
Producer1 inserted Item #12	(2 of 3 slots full)
Producer1 inserted Item #13	(3 of 3 slots full)
Producer1 waiting to insert Item #14
Consumer2 removed  Item #13	(2 of 3 slots full)
Consumer2 removed  Item #12	(1 of 3 slots full)
Consumer2 removed  Item #11	(0 of 3 slots full)
Consumer2 waiting to remove an item
Producer2 inserted Item #8	(1 of 3 slots full)
Producer2 inserted Item #15	(2 of 3 slots full)
Producer2 inserted Item #16	(3 of 3 slots full)
Producer2 waiting to insert Item #17
Consumer2 removed  Item #16	(2 of 3 slots full)
Consumer2 removed  Item #15	(1 of 3 slots full)
Consumer2 removed  Item #8	(0 of 3 slots full)
Consumer2 waiting to remove an item
Consumer1 waiting to remove an item
Producer1 inserted Item #14	(1 of 3 slots full)
Producer1 inserted Item #18	(2 of 3 slots full)
Producer1 inserted Item #19	(3 of 3 slots full)
Producer1 waiting to insert Item #20
Producer2 waiting to insert Item #17
Consumer2 removed  Item #19	(2 of 3 slots full)
Consumer2 removed  Item #18	(1 of 3 slots full)
Consumer2 removed  Item #14	(0 of 3 slots full)
Consumer2 waiting to remove an item
Producer2 inserted Item #17	(1 of 3 slots full)
Producer2 inserted Item #21	(2 of 3 slots full)
Producer2 inserted Item #22	(3 of 3 slots full)
Producer2 waiting to insert Item #23
Producer1 waiting to insert Item #20
Consumer1 removed  Item #22	(2 of 3 slots full)
Consumer1 removed  Item #21	(1 of 3 slots full)
Consumer1 removed  Item #17	(0 of 3 slots full)
Consumer1 waiting to remove an item
Consumer2 waiting to remove an item
Producer2 inserted Item #23	(1 of 3 slots full)
Producer2 inserted Item #24	(2 of 3 slots full)
Producer2 inserted Item #25	(3 of 3 slots full)
Producer2 waiting to insert Item #26
Consumer2 removed  Item #25	(2 of 3 slots full)
Consumer2 removed  Item #24	(1 of 3 slots full)
Consumer2 removed  Item #23	(0 of 3 slots full)
Consumer2 waiting to remove an item
Producer2 inserted Item #26	(1 of 3 slots full)
Producer2 inserted Item #27	(2 of 3 slots full)
Producer2 inserted Item #28	(3 of 3 slots full)
Producer2 waiting to insert Item #29
Producer1 waiting to insert Item #20
Consumer1 removed  Item #28	(2 of 3 slots full)
Consumer1 removed  Item #27	(1 of 3 slots full)
Consumer1 removed  Item #26	(0 of 3 slots full)
Consumer1 waiting to remove an item
Consumer2 waiting to remove an item
Producer2 inserted Item #29	(1 of 3 slots full)
Producer2 inserted Item #30	(2 of 3 slots full)
Producer2 inserted Item #31	(3 of 3 slots full)
Producer2 waiting to insert Item #32
Producer1 waiting to insert Item #20
Consumer1 removed  Item #31	(2 of 3 slots full)
Consumer1 removed  Item #30	(1 of 3 slots full)
Consumer1 removed  Item #29	(0 of 3 slots full)
Consumer1 waiting to remove an item
Producer2 inserted Item #32	(1 of 3 slots full)
Producer2 inserted Item #33	(2 of 3 slots full)
Producer2 FINISHED producing 20 items
Producer1 inserted Item #20	(3 of 3 slots full)
Producer1 waiting to insert Item #34
Consumer2 removed  Item #20	(2 of 3 slots full)
Consumer2 removed  Item #33	(1 of 3 slots full)
Consumer2 FINISHED consuming 20 items
Producer1 inserted Item #34	(2 of 3 slots full)
Producer1 inserted Item #35	(3 of 3 slots full)
Producer1 waiting to insert Item #36
Consumer1 removed  Item #35	(2 of 3 slots full)
Consumer1 removed  Item #34	(1 of 3 slots full)
Consumer1 removed  Item #32	(0 of 3 slots full)
Consumer1 waiting to remove an item
Producer1 inserted Item #36	(1 of 3 slots full)
Producer1 inserted Item #37	(2 of 3 slots full)
Producer1 inserted Item #38	(3 of 3 slots full)
Producer1 waiting to insert Item #39
Consumer1 removed  Item #38	(2 of 3 slots full)
Consumer1 removed  Item #37	(1 of 3 slots full)
Consumer1 removed  Item #36	(0 of 3 slots full)
Consumer1 waiting to remove an item
Producer1 inserted Item #39	(1 of 3 slots full)
Producer1 inserted Item #40	(2 of 3 slots full)
Producer1 FINISHED producing 20 items
Consumer1 removed  Item #40	(1 of 3 slots full)
Consumer1 removed  Item #39	(0 of 3 slots full)
Consumer1 FINISHED consuming 20 items

Process ProducerConsumerDemo1 finished*/