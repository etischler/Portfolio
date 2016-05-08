
class actualbathroom{
	int malecount;
	int femalecount;
	int count;
	Boolean femalewaiting;
	Boolean male;
	int totalcount;
	public actualbathroom(int tcount){
		count = tcount;
		femalewaiting = false;
		femalecount = 0;
		malecount = 0;
		count = 0;
		
	}
	//Object lock = new Object();


	synchronized public void wants_to_enter(Boolean genderismale) throws InterruptedException{

		if(!genderismale){
			//System.out.println("1");
			femalewaiting = true;
		}

		//System.out.println("for male wait " + genderismale + " " + femalecount + " " + femalewaiting + " " + count);
		while(genderismale && (femalecount > 0 || femalewaiting || count >= 3)){
			//System.out.println("wait male");
			if(femalecount == 0){
				this.notify();
			}
			this.wait();
			
		}
		if(genderismale){
			//System.out.println("3");
			++count;
			++malecount;
			//System.out.println(malecount + " this is male count");
			return;
		}
		//System.out.println("for female wait " + genderismale + " " + male + " " + femalewaiting + " " + count);
		while(!genderismale &&(malecount > 0 || count >=3)){
			//System.out.println("wait female");
			this.wait();
		}
		if(!genderismale){
			//System.out.println("5");
			++count;
			++femalecount;
			//System.out.println(femalecount + " this is female count");
			return;
		}
		

	}

	synchronized public void leaves(Boolean genderismale){
		if(genderismale){
			//System.out.println("6");
			--count;
			--malecount;
			//System.out.println(malecount + " this is male count");
		}

		if(!genderismale){
			//System.out.println("7");
			--count;
			--femalecount;
			//System.out.println(femalecount + " this is female count");
			if(femalecount == 0){
				//System.out.println("this change happens");
			femalewaiting = false;
			}
		}

		this.notifyAll();

	}





}