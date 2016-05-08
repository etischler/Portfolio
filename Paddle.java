import java.awt.*;
import java.awt.geom.*;

public class Paddle extends ColorShape{
	
	// location and size variables
	private static int speed;
	private static int xPos;
	private static final int yPos = 460;
	private static final int width = 100;
	private static final int height = 10;

	private static final Rectangle2D.Double shape = new Rectangle2D.Double(0,yPos,width,height);
	

	public Paddle() {
		super(shape);

		// set paddle color
		setFillColor(Color.BLACK);
		setBorderColor(Color.BLACK);

		// set paddle position and speed
		xPos=200;
		speed=0;
		
	}

	public void move() {
		// move paddle
		xPos= xPos+speed;
		
		// stop the paddle from moving at the edges
		if(xPos>500){
			
			xPos=500;
		}
		if(xPos<0){
			xPos=0;
		}

		
		// update shape
		shape.setRect(xPos, yPos, width, height);

	}
	public void movewithPowerup() {
		// move paddle
		xPos= xPos+speed;
		
		// stop the paddle from moving at the edges
		if(xPos>500){
			
			xPos=500;
		}
		if(xPos<0){
			xPos=0;
		}

		
		// update shape
		shape.setRect(xPos, yPos, width+50, height);
	}

	public void setSpeed(int newSpeed) {
		speed = newSpeed;
	}
	public void restartPaddle(){
		xPos=300;
	}

	public int getWidth() {
		return width;
	}

	public int getHeight() {
		return height;
	}

	public int getX() {
		return xPos;
	}
	

	public Rectangle2D.Double getShape() {
		return shape;
	} 

}