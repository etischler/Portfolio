import java.awt.Color;
public class Art{
	

	public static void main(String args[]){

		int numberofsetsoffourCircles = Integer.parseInt(args[0]);
		
		drawCircles(.5,.5,.1,numberofsetsoffourCircles);
		


	}

	public static void filledCircle(double x, double y, double r){
		
		StdDraw.setPenColor( new Color( (int)(255*Math.random()), (int)(255*Math.random()), (int)(255*Math.random()) ) ); //recieved help from interenet for this line of code. Credit to reddit page
		StdDraw.filledCircle(x,y,r);
	}

	public static void drawCircles(double x, double y, double r, double n){
		if(n>0){
			filledCircle(x,y,r);
			drawCircles((x+(1.75*r)),y,(r*3)/4,n-1);
			drawCircles((x-(1.75*r)),y,(r*3)/4,n-1);
			drawCircles(x,y+(1.75*r),(r*3)/4,n-1);
			drawCircles(x,y-(1.75*r),(r*3)/4,n-1);
		}
	}
}