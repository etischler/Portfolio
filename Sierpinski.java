

public class Sierpinski{
	

	public static void main(String args[]){

		int recursionNumber = Integer.parseInt(args[0]);
		
		drawSierpinski(.5,0,.5,recursionNumber);
		


	}

	public static void filledTriagnle(double x, double y, double len){
		double[] xCoordinate = {x,x+(0.5*len),x-(.5*len)};
		double[] yCoordinate = {y,y+((Math.sqrt(3)/2)*len),y+((Math.sqrt(3)/2)*len)};
		StdDraw.setPenColor(StdDraw.BLACK);
		StdDraw.filledPolygon(xCoordinate,yCoordinate);


	}
	public static void drawSierpinski(double x, double y, double len, int n){
		if(n>0){
			filledTriagnle(x,y,len);
			drawSierpinski(x-(.5*len),y,.5*len,n-1);
			drawSierpinski(x+(.5*len),y,.5*len,n-1);
			drawSierpinski(x,y+(len*((Math.sqrt(3))/2)),.5*len,n-1);

			

		}

		
	}
	



}