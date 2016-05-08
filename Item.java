class Item{
	//each instance has unique_id
	int itemnumber;
	//returns string of form Item #unique_id
	public String toString(){
		String theitemnumber = Integer.toString(itemnumber);
		return theitemnumber;

	}

	public void getitemnumber(int number){
		itemnumber = number;

	}

	public int itemnum(){
		return itemnumber;
	}

}
