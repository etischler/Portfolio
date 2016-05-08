import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;

public class Ball extends ColorShape {
	
	// location and size variables
	private int xPos;
	private int yPos;
	private int xSpeed;
	private int ySpeed;
	private static final int height = 10;
	private static final int width = 10;
	private static final Ellipse2D.Double shape = new Ellipse2D.Double(100, 100, width, height);

	// constructor
	public Ball() {
		super(shape);

		// set ball color
		super.setFillColor(Color.RED);
		super.setBorderColor(Color.RED);
		
		// set initial values for x and y position and speed
		xPos=(int)(Math.random()*400);
		yPos=200;
		xSpeed=(int)(Math.random()*3)+1;
		ySpeed=(int)(Math.random()*3)+1;
		shape.setFrame(xPos,yPos,width,height);
		double xdirectiondecider= Math.random();
		if(xdirectiondecider>=.5){
			xSpeed=-xSpeed;
		}
	}

	public void move() {
		// move ball
		xPos= xPos+xSpeed;
		yPos= yPos+ySpeed;

		
		// detect if ball should bounce off an edge
		if(yPos<0){
			ySpeed=-ySpeed;
		}
		
		if(xPos<0){
			xSpeed=-xSpeed;
		}
		if(xPos>580){
			xSpeed=-xSpeed;
		}

		// update shape to new values
		shape.setFrame(xPos, yPos, width, height);
	}
	public void movewithPowerup() {
		// move ball
		xPos= xPos+xSpeed;
		yPos= yPos+ySpeed;

		
		// detect if ball should bounce off an edge
		if(yPos<0){
			ySpeed=-ySpeed;
		}
		
		if(xPos<0){
			xSpeed=-xSpeed;
		}
		if(xPos>580){
			xSpeed=-xSpeed;
		}

		// update shape to new values
		shape.setFrame(xPos, yPos, width+15, height+15);
	}

	public void setXspeed(int newSpeed) {
		xSpeed = newSpeed;
	}
	public void scoreisTenpowerup(){
		
		Color color = new Color((int)(255*Math.random()), (int)(255*Math.random()), (int)(255*Math.random()));
		
		super.setFillColor(color);
		super.setBorderColor(color);
	
	}
	public void resetColor(){
		super.setFillColor(Color.RED);
		super.setBorderColor(Color.RED);
	}


	public void setYspeed(int newSpeed) {
		ySpeed = newSpeed;
	}

	public int getX() {
		return xPos;
	}

	public int getY() {
		return yPos;
	}
	public int getXspeed(){
		return xSpeed;
	}
	public int getYspeed(){
		return ySpeed;
	}

	public int getWidth() {
		return width;
	}

	public int getHeight() {
		return height;
	}

	public Ellipse2D.Double getShape() {
		return shape;
	}
	public void restartBall(){
xPos=(int)(Math.random()*400);
		yPos=200;
		xSpeed=(int)(Math.random()*3)+1;
		ySpeed=(int)(Math.random()*3)+1;
		shape.setFrame(xPos,yPos,width,height);
		double xdirectiondecider= Math.random();
		if(xdirectiondecider>=.5){
			xSpeed=-xSpeed;
		} 	

	}
}