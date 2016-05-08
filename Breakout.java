import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;

public class Breakout {
	public static void main(String[] args) {
		

		JFrame frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(600,500);
        frame.setTitle("Breakout");
        frame.setResizable(false);
        frame.add(new GamePanel());
        frame.setVisible(true);



        
	}

	private static class GamePanel extends JPanel {
		
		Ball ball;
		Paddle paddle;
		BrickConfiguration bconfig;
		Timer timer;
		int score;


		public GamePanel() {
			super();

			// call initializeGameObjects()
			initializeGameObjects();
			// add PaddleMover as a keyListener
			addKeyListener(new PaddleMover());
			setFocusable(true);
			score=0;

			



		}

		public void initializeGameObjects() {
			// instantiate ball, paddle, and brick configuration
			ball= new Ball();
			paddle = new Paddle();
			bconfig= new BrickConfiguration();
			
			
			// set up timer to run GameMotion() every 10ms
			timer = new Timer(10, new GameMotion());
			timer.start();
		}

		@Override
		public void paintComponent(Graphics g) {
			super.paintComponent(g);
			g.setColor(Color.WHITE);
			Graphics2D g2 = (Graphics2D)g;
			paddle.paint(g2);
			ball.paint(g2);
			bconfig.paint(g2);				//go back to this and add brink.paint(g2)
			g2.setColor(Color.BLACK);
				g2.setFont(new Font("Serif", Font.PLAIN, 20));
				g2.drawString("Score: " + score, 25,450);

			// paint ball, paddle, and brick configuration
			
		}


		private class GameMotion implements ActionListener {
			public GameMotion() {

			}

			public void actionPerformed(ActionEvent evt) {
				//move ball automatically


				

				//move paddle according to key press
				if(score>=10 && score<=15){
							paddle.movewithPowerup();
							ball.move();

						}
							if(score>=25 && score<=30){
								ball.movewithPowerup();
								paddle.move();
							}
							 if(score<10){
							 	paddle.move();
							 	ball.move();
							 }
							 if(score>15&&score<25){
							 	paddle.move();
							 	ball.move();
							 }
							 if(score>30){
							 	paddle.move();
							 	ball.move();
							 }
				

				//check if the ball hits the paddle or a brick
				checkForHit();
			
				
				//call repaint
				repaint();
			}
		}


		private class PaddleMover implements KeyListener {
			public void keyPressed(KeyEvent evt) {
				// change paddle speeds for left and right key presses
				int key = evt.getKeyCode();
				if (key==KeyEvent.VK_LEFT){
					paddle.setSpeed(-4);
				}

				if(key==KeyEvent.VK_R){
					ball.restartBall();
					bconfig.brickRestart();
					score=0;
					paddle.restartPaddle();
				}
				if (key==KeyEvent.VK_UP){
					if(ball.getXspeed()>0){
					ball.setXspeed(ball.getXspeed()+1);
					}
					if(ball.getXspeed()<0){
						ball.setXspeed(ball.getXspeed()-1);
					}
					if(ball.getYspeed()<0){
						ball.setYspeed(ball.getYspeed()-1);
					}
					if(ball.getYspeed()>0){
						ball.setYspeed(ball.getYspeed()+1);
					}
				}
				if (key==KeyEvent.VK_DOWN){
					if(ball.getXspeed()>0){
					ball.setXspeed(ball.getXspeed()-1);
					}
					if(ball.getXspeed()<0){
						ball.setXspeed(ball.getXspeed()+1);
					}
					if(ball.getYspeed()<0){
						ball.setYspeed(ball.getYspeed()+1);
					}
					if(ball.getYspeed()>0){
						ball.setYspeed(ball.getYspeed()-1);
					}
				}

				if (key==KeyEvent.VK_RIGHT){
					paddle.setSpeed(4);
				}
			}
			public void keyReleased(KeyEvent evt) {
				// set paddle speed to 0

				paddle.setSpeed(0);
				
			}
			public void keyTyped(KeyEvent evt) {}
		}

		public void checkForHit() {
			
			// change ball speed when ball hits paddle
			if (ball.getShape().intersects(paddle.getShape())) {
				int leftSide = paddle.getX();
				int middleLeft = paddle.getX() + (int)(paddle.getWidth()/3);
				int middleRight = paddle.getX() + (int)(2*paddle.getWidth()/3);
				int rightSide = paddle.getX() + paddle.getWidth();

				if ((ball.getX() >= leftSide) && (ball.getX() < middleLeft)) {
					// change ball speed
					ball.setXspeed(-(Math.abs(ball.getXspeed())));
					ball.setYspeed(-ball.getYspeed());
				}
				if ((ball.getX() >= middleLeft) && (ball.getX() <= middleRight)) {
					// change ball speed
					ball.setXspeed(ball.getXspeed());
					ball.setYspeed(-ball.getYspeed());


				}
				if ((ball.getX() > middleRight) && (ball.getX() <= rightSide)) {
					// change ball speed
					ball.setXspeed((Math.abs(ball.getXspeed())));
					ball.setYspeed(-ball.getYspeed());
				}

				
				
			}
				

			// change ball speed when ball hits brick
			for (int i = 0; i < bconfig.getRows(); i++) {
				for (int j = 0; j < bconfig.getCols(); j++) {
					if (bconfig.exists(i,j)) {
						if (ball.getShape().intersects(bconfig.getBrick(i,j).getShape())) {
							Point ballLeft = new Point((int)ball.getShape().getX(), (int)(ball.getShape().getY() + ball.getShape().getHeight()/2));
							Point ballRight = new Point((int)(ball.getShape().getX() + ball.getShape().getWidth()), (int)(ball.getShape().getY() + ball.getShape().getHeight()/2));
							Point ballTop = new Point((int)(ball.getShape().getX() + ball.getShape().getWidth()/2), (int)ball.getShape().getY());
							Point ballBottom = new Point((int)(ball.getShape().getX() + ball.getShape().getWidth()/2), (int)(ball.getShape().getY() + ball.getShape().getHeight()));
							if (bconfig.getBrick(i,j).getShape().contains(ballLeft)) {
								
								ball.setXspeed(-(ball.getXspeed()));
							}
							else if(bconfig.getBrick(i,j).getShape().contains(ballRight)) {
								
								ball.setXspeed(-(ball.getXspeed()));
							}
							if (bconfig.getBrick(i,j).getShape().contains(ballTop)) {
								ball.setYspeed(-(ball.getYspeed()));
								
							}
							else if (bconfig.getBrick(i,j).getShape().contains(ballBottom)) {
								ball.setYspeed(-(ball.getYspeed()));
								
							}
							
							

							// remove brick
							bconfig.removeBrick(j,i);
							score++;
							if(score>=10 && score<=15){
							ball.scoreisTenpowerup();

						}
							if(score>=25 && score<=30){
								ball.scoreisTenpowerup();
							}
							 if(score<10){
							 	ball.resetColor();
							 }
							 if(score>15&&score<25){
							 	ball.resetColor();
							 }
							 if(score>30){
							 	ball.resetColor();
							 }

							
						}
					}
				}
			}
		}
	}
}