import java.awt.*;
import java.awt.geom.*;

public class BrickConfiguration {
	
	//location and size variables
	private static final int xStart = 0;
	private static final int yStart = 0;	
	private static final int numCols = 10;
	private static final int numRows = 5;
	private static final int brickHeight = 30;
	private static final int brickWidth = 55;

	// 2D array containing brick objects
	private static Brick[][] bricks = new Brick[numCols][numRows];

	// 2D array telling us whether the brick should be painted (has it been hit?)
	public static boolean[][] paintBricks = new boolean[numCols][numRows];
	
	// constructor
	public BrickConfiguration() {
		
		// create new bricks and store them in bricks array
		for (int i = 0; i < numCols; i++) {
			for (int j = 0; j < numRows; j++) {
				// initialize paintBricks[i][j]
				paintBricks[i][j]=true;
				
				// initialize bricks[i][j]
				bricks[i][j]= new Brick(xStart+(i*(brickWidth+5)),yStart+(j*(brickHeight+5)),brickWidth,brickHeight);


			}
		}		
	}

	// paint the bricks array to the screen
	public void paint(Graphics2D brush) {
		for (int i = 0; i < numCols; i++) {
			for (int j = 0; j < numRows; j++) {
				if(paintBricks[i][j] == true){

				paintBrick(bricks[i][j],brush);
			}
				// determine if brick should be painted
				// if so, call paintBrick()
			}
		}
	}

	// paint an individual brick
	public void paintBrick(Brick brick, Graphics2D brush) {
		// call brick's paint method
		
		brick.paint(brush);

	}

	public void removeBrick(int row, int col) {
		// update paintBricks array for destroyed brick
		paintBricks[row][col]=false;
	}

	public Brick getBrick(int row, int col) {
		return bricks[col][row];
	}

	public boolean exists(int row, int col) {
		return paintBricks[col][row];
	}

	public int getRows() {
		return numRows;
	}

	public int getCols() {
		return numCols;
	}
	public void brickRestart(){
		for (int i = 0; i < numCols; i++) {
			for (int j = 0; j < numRows; j++) {
				// initialize paintBricks[i][j]
				paintBricks[i][j]=true;
				
				// initialize bricks[i][j]
				bricks[i][j]= new Brick(xStart+(i*(brickWidth+5)),yStart+(j*(brickHeight+5)),brickWidth,brickHeight);


			}
		}		

	}

}