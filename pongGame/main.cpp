#include <iostream>
#include <stdlib.h>
#include "sfwdraw.h"
#include <stdio.h>
#include <cmath>
#include <ctime>
#include <Windows.h>

const int screenWidth = 1400;
const int screenHeight = 1000;
const int paddleWidth = 50;
const int PaddleHeight = 150;
bool buffOnScreen = false;
int Player1Score = 0;
int Player2Score = 0;
int totalScore = Player1Score + Player2Score;
float buffMovementX;
float buffMovementY = 1 * sfw::getDeltaTime();
int boundingBoxLeft = screenWidth / 3;
int boundingBoxRight = (2 * screenWidth) / 3;
int Radius = 25;
float ballRadius = 20;
float Circle[10]; // gate Circles  y Pos
//float gateRadius[10];
float gateRadius = 1 * sfw::getDeltaTime();
bool collidedLeft = false;
bool collidedTop = false;
bool collidedBottom = false;
bool collidedRight = false;
bool Player1HasBuff = false;
bool Player2HasBuff = false;




//Openings
float topGate = 400;
float bottomGate = 600;

struct Player
{
	float x, y, sizeX, sizeY;
	float speed;

};
Player testPlayer = {};
struct Point
{
	float x;
	float y;
};
Point BuffPos = {};


void DrawLine()
{
	Point a = {};
	Point b = {};
	sfw::drawLine(a.x, a.y, b.x, b.y);
}

////struct Rectangle
//{
//	Point A;
//	Point B;
//	Point C;
//	Point D;
//
//
//};
//Rectangle leftPaddle = {};


//
//Rectangle Left(Point A, Point B, Point C, Point D)
//{
//	sfw::drawLine(A.x, A.y, B.x, B.y);
//	sfw::drawLine(C.x, C.y, D.x, D.y);
//	sfw::drawLine(A.x, A.y, C.x, C.y);
//	sfw::drawLine(B.x, B.y, D.x, D.y);
//	/*
//	A--------B
//	|        |
//	|        |
//	C--------D
//	*/
//}
void DrawRectangle(float x, float y, float xSize, float ySize)
{
	sfw::drawLine(x, y, x + xSize, y); //A-B
	sfw::drawLine(x, y, x, y + ySize);//A-C
	sfw::drawLine(x + xSize, y, x + xSize, y + ySize);//B-D
	sfw::drawLine(x, y + ySize, x + xSize, y + ySize);//C-D
}

//void DrawTriangle(float x, float y)

struct Position
{
	float x;
	float y;


};
Position CirclePos = {};


Position speedBoostA = {};

void drawLetterA()
{
	float playerCenterX = 100;
	float playerCenterY = 100;

	sfw::drawLine(playerCenterX, playerCenterY - 50, playerCenterX - 100, playerCenterY + 100);
	testPlayer.x += 5;
};

void LeftPowerUpLines()
{

	//width 1400
	//height 1000
	if (buffOnScreen == true)
	{
		if (Circle[1] && gateRadius == 10)
		{
			sfw::drawLine(boundingBoxLeft, Circle[1] + buffMovementY, (screenWidth / 2) + buffMovementX, buffMovementY);
		}
		if (Circle[2] && gateRadius == 10)
		{
			sfw::drawLine(boundingBoxLeft, Circle[2] + buffMovementY, (screenWidth / 2) + buffMovementX, buffMovementY);
		}
	}
}

void RightPowerUpLines()
{
	if (buffOnScreen == true)
	{
		if (Circle[3] && gateRadius == 10)
		{
			sfw::drawLine(boundingBoxRight, Circle[3] + buffMovementY, (screenWidth / 2) + buffMovementX, buffMovementY);
		}
		if (Circle[4] && gateRadius == 10)
		{
			sfw::drawLine(boundingBoxRight, Circle[4] + buffMovementY, (screenWidth / 2) + buffMovementX, buffMovementY);
		}
	}
}

void DrawPlayerScores(int P1Score, int P2Score)
{
	Point a, b;
	a.x = screenWidth / 10;
	a.y = screenHeight / 20;
	b.x = a.x;
	b.y = screenHeight / 15;
	Point c, d;
	c.x = 5 * (screenWidth / 10);
	c.y = a.y;
	d.x = c.x;
	d.y = b.y;
	switch (P1Score)
	{
	case 4:
		sfw::drawLine((a.x + a.x) - 100, a.y, (b.x + b.x) - 100, b.y);
	case 3:
		sfw::drawLine((a.x + a.x) - 50 , a.y, (b.x + b.x) - 50, b.y);
	case 2:
		sfw::drawLine((a.x + a.x), a.y, (b.x + b.x), b.y);
	case 1:
		sfw::drawLine(a.x, a.y, b.x, b.y);
		break;
	}
	switch (P2Score)
	{
	case 4:

	case 3:

	case 2:

	case 1:
		sfw::drawLine(c.x, c.y, d.x, d.y);
		break;
	}
	
}

void DrawBall(float x, float y)
{
	
	int randomX = rand() % 2;// + or - for x
	int RNGXDirection = rand() % 2; // initial speed for that x direction
	int RandomY = rand() % 2;
	int RNGYDirection = rand() % 10;


	/*switch (randomX)
	{
	case 0:
		x -= RNGXDirection;
		break;
	case 1:
		x += RNGXDirection;
		break;
	}
	switch (RandomY)
	{
	case 0:
		y -= RNGYDirection;
		break;
	case 1:
		y += RNGYDirection;
		break;
	}*/
	if (x + ballRadius > screenWidth)
	{
		//collidedRight = true;
	}

	
	sfw::drawCircle(x,y,ballRadius);
 
}

float DrawStickySpikesRight(float startXPos, float startYPos)
{
	Point TSpikeT;
	TSpikeT.x = startXPos - 30;
	TSpikeT.y = startYPos + (PaddleHeight / 6);

	Point TM;
	TM.x = startXPos;
	TM.y = (PaddleHeight / 3) + startYPos;
	Point MSpikeT;
	MSpikeT.x = TSpikeT.x;
	MSpikeT.y = (PaddleHeight / 2) + startYPos;
	Point MB;
	MB.x = startXPos;
	MB.y = ((2 * PaddleHeight) / 3) + startYPos;
	Point BSpikeT;
	BSpikeT.x = TSpikeT.x;
	BSpikeT.y = ((5 * PaddleHeight) / 6) + startYPos;

	sfw::drawLine(startXPos, startYPos, TSpikeT.x, TSpikeT.y);
	sfw::drawLine(TSpikeT.x, TSpikeT.y, TM.x, TM.y);
	sfw::drawLine(TM.x, TM.y, MSpikeT.x, MSpikeT.y);
	sfw::drawLine(MSpikeT.x, MSpikeT.y, MB.x, MB.y);
	sfw::drawLine(MB.x, MB.y, BSpikeT.x, BSpikeT.y);
	sfw::drawLine(BSpikeT.x, BSpikeT.y, startXPos, PaddleHeight + startYPos);
	/*
	__
	<|  |
	<|  |
	<|  |
	<|__|
	*/
	return startXPos, startYPos;
}
float DrawStickySpikesLeft(float startXPos, float startYPos)
{
	Point TSpikeT;
	TSpikeT.x = startXPos + paddleWidth + 30;
	TSpikeT.y = startYPos + (PaddleHeight / 6);

	Point TM;
	TM.x = startXPos + paddleWidth;
	TM.y = (PaddleHeight / 3) + startYPos;
	Point MSpikeT;
	MSpikeT.x = TSpikeT.x;
	MSpikeT.y = (PaddleHeight / 2) + startYPos;
	Point MB;
	MB.x = startXPos + paddleWidth;
	MB.y = ((2 * PaddleHeight) / 3) + startYPos;
	Point BSpikeT;
	BSpikeT.x = TSpikeT.x;
	BSpikeT.y = ((5 * PaddleHeight) / 6) + startYPos;

	sfw::drawLine(startXPos + paddleWidth, startYPos, TSpikeT.x, TSpikeT.y);
	sfw::drawLine(TSpikeT.x, TSpikeT.y, TM.x, TM.y);
	sfw::drawLine(TM.x, TM.y, MSpikeT.x, MSpikeT.y);
	sfw::drawLine(MSpikeT.x, MSpikeT.y, MB.x, MB.y);
	sfw::drawLine(MB.x, MB.y, BSpikeT.x, BSpikeT.y);
	sfw::drawLine(BSpikeT.x, BSpikeT.y, startXPos + paddleWidth, PaddleHeight + startYPos);
	/*
	__
	|  |>
	|  |>
	|  |>
	|__|>
	*/


	return startXPos, startYPos;
}

float DrawFrozenBuff(float xPos, float yPos)
{
	/*
   A _ B _
	| | | |
	|_| |_|
   C  D
	*/

	Point a;
	a.x = -25 + (screenWidth /2);
	a.y = 0;
	Point b;
	b.x = -12.5 + (screenWidth / 2);
	b.y = 0;
	Point c;
	c.x = -25 + (screenWidth / 2);
	c.y = 35;
	Point d;
	d.x = -12.5 + (screenWidth / 2);
	d.y = 35;
	
	Point a1, b1, c1, d1;
	a1.x = 12.5 + (screenWidth / 2);
	a1.y = 0;
	b1.x = 25 + (screenWidth / 2);
	b1.y = 0;
	c1.x = 12.5 + (screenWidth / 2);
	c1.y = 35;
	d1.x = 25 + (screenWidth / 2);
	d1.y = 35;
	//BOX 1
	sfw::drawLine(a.x + xPos, a.y + yPos, b.x + xPos, b.y + yPos);
	sfw::drawLine(a.x + xPos, a.y + yPos, c.x + xPos, c.y + yPos);
	sfw::drawLine(c.x + xPos, c.y + yPos, d.x + xPos, d.y + yPos);
	sfw::drawLine(b.x + xPos, b.y + yPos, d.x + xPos, d.y + yPos);
	//BOX 2
	sfw::drawLine(a1.x + xPos, a1.y + yPos, b1.x + xPos, b1.y + yPos);
	sfw::drawLine(a1.x + xPos, a1.y + yPos, c1.x + xPos, c1.y + yPos);
	sfw::drawLine(c1.x + xPos, c1.y + yPos, d1.x + xPos, d1.y + yPos);
	sfw::drawLine(b1.x + xPos, b1.y + yPos, d1.x + xPos, d1.y + yPos);


	return xPos, yPos;
}

float DrawSpikeBuff(float xMovement, float yMovement)
{
	Point Center;
	Center.x = (screenWidth / 2) + xMovement;
	Center.y = 0 + yMovement;
	Point LeftSide;
	LeftSide.x = Center.x - 25;
	LeftSide.y = Center.y + 30;
	Point RightSide;
	RightSide.x = Center.x + 25;
	RightSide.y = LeftSide.y;

	sfw::drawLine(Center.x, Center.y, LeftSide.x, LeftSide.y);
	sfw::drawLine(LeftSide.x, LeftSide.y, RightSide.x, RightSide.y);
	sfw::drawLine(Center.x, Center.y, RightSide.x, RightSide.y);

	/*

	/\

	*/
	return xMovement, yMovement;
}
float DrawSpeedBoost(float xMovement, float yMovement)
{

	Point TLT;
	TLT.x = screenWidth / 2;
	TLT.y = 0;
	Point TLB;
	TLB.x = (screenWidth / 2) + 15;
	TLB.y = 25;

	Point TRT;
	TRT.x = TLT.x + 20;
	TRT.y = TLT.y;
	Point TRB;
	TRB.x = TLB.x + 20;
	TRB.y = TLB.y;

	Point BLT;
	BLT.x = TLB.x;
	BLT.y = TLB.y;
	Point BLB;
	BLB.x = TLT.x;
	BLB.y = 50;

	Point BRT;
	BRT.x = BLT.x + 20;
	BRT.y = BLT.y;
	Point BRB;
	BRB.x = BLB.x + 20;
	BRB.y = BLB.y;

	sfw::drawLine(TLT.x + xMovement, TLT.y + yMovement, TLB.x + xMovement, TLB.y + yMovement);
	sfw::drawLine(TRT.x + xMovement, TRT.y + yMovement, TRB.x + xMovement, TRB.y + yMovement);
	sfw::drawLine(BLT.x + xMovement, BLT.y + yMovement, BLB.x + xMovement, BLB.y + yMovement);
	sfw::drawLine(BRT.x + xMovement, BRT.y + yMovement, BRB.x + xMovement, BRB.y + yMovement);

	/*

	\ \
	/ /

	*/
	return xMovement, yMovement;
}

float xChange = 0;
float yChange = 0;


//void drawLeftPaddle()
//{
//	sfw::drawLine(leftPaddle.A.x + xChange, leftPaddle.A.y + yChange, leftPaddle.B.x - xChange, leftPaddle.B.y - yChange);
//	sfw::drawLine(leftPaddle.C.x - xChange, leftPaddle.C.y - yChange, leftPaddle.D.x + xChange, leftPaddle.D.y + yChange);
//};

int *NewLineInstance;

struct BuffDurations
{
	float speedBoostDuration = 10;
	float frozenBuffDuration = 10;
	float spikeBuffDuration  = 10;

};

int main()
{
	Circle[1] = BuffPos.y - 25;
	Circle[2] = BuffPos.y + 25;
	Circle[3] = Circle[1];
	Circle[4] = Circle[2];
	/*gateRadius[1] = 1 * sfw::getDeltaTime();
	gateRadius[2] = 1 * sfw::getDeltaTime();
	gateRadius[3] = 1 * sfw::getDeltaTime();
	gateRadius[4] = 1 * sfw::getDeltaTime();*/
	BuffDurations buffDurations = {};
	Position LeftPlayer = {};
	LeftPlayer.y = screenHeight / 2;
	LeftPlayer.x = 50;
	Position RightPlayer = {};
	RightPlayer.y = screenHeight / 2;
	RightPlayer.x = screenWidth - 100;
	CirclePos.x = 700;
	CirclePos.y = 500;
	Point BallPos;
	BallPos.x = screenWidth / 2;
	BallPos.y = screenHeight / 2;

	bool countingUP = false;
	bool approachingCenter = true;

	sfw::initContext(screenWidth, screenHeight, "Window");

	int radius;
	radius = Radius;
	int Timer = radius;

	float circleX = CirclePos.x;
	float circleY = CirclePos.y;



	//const int resetTimer = 5000;
	//400
	//600
	
	bool isIncreasing = false;
	
	bool buffDeleted = false;
	int pickRandomBuff;
	int numberOfBuffs = 3;
	srand(time(NULL));
	pickRandomBuff = rand() % numberOfBuffs;
	float buffMovementTimer = 500;
	buffMovementTimer += sfw::getDeltaTime();
	float timer = 1 * sfw::getDeltaTime();
	bool tuggingLeft = false;
	bool buffMovement = false;
	bool isKeyPressed = false;
	float tugOWar = 25 * sfw::getDeltaTime();
	float scale = 1;
	int InitialballDirection = rand() % 2;
	bool BallHasSpawned = false;
	static int bounce = 0;


	 float tempBallPos = BallPos.x;
		
	while (sfw::stepContext())
	{
		Player1Score = 3;
		std::cout << buffDurations.speedBoostDuration << "\n";
		LeftPowerUpLines();
		RightPowerUpLines();
		DrawRectangle(LeftPlayer.x, LeftPlayer.y, paddleWidth, PaddleHeight); //Left Paddle
		DrawRectangle(RightPlayer.x, RightPlayer.y, paddleWidth, PaddleHeight);//Right Paddle
		DrawPlayerScores(Player1Score, Player2Score);
		sfw::drawLine(boundingBoxLeft, 0, boundingBoxLeft, screenHeight);//boundLeft
		sfw::drawLine(boundingBoxRight, 0, boundingBoxRight, screenHeight);//boundRight
		DrawBall(BallPos.x, BallPos.y); // Pong Ball
		if (BallPos.x + ballRadius > screenWidth)
		{
			//BallPos.x -= 200 * sfw::getDeltaTime();
			collidedRight = true;
		}
		if (BallPos.x - ballRadius < 0)
		{
			collidedLeft = true;
		}
		if (BallPos.y + ballRadius > screenHeight)
		{
			collidedBottom = true;
		}
		if (BallPos.y - ballRadius < 0)
		{
			collidedTop = true;
		}
		if (collidedBottom == true)
		{
			BallPos.y -= 25;
		}
		if (collidedTop == true)
		{
			BallPos.y += 25;
		}
		
		switch (InitialballDirection)
		{
		case 0:
			BallPos.x += 150 * sfw::getDeltaTime();
			/*if (collidedRight == true)
			{
				BallPos.x -= 200 * sfw::getDeltaTime();
				collidedRight = false;
			}*/
			break;
		case 1:
			BallPos.x -= 150 * sfw::getDeltaTime();
			/*if (collidedLeft == true)
			{
				BallPos.x += 200 * sfw::getDeltaTime();
				collidedLeft = false;
			}*/
			break;
		}
		switch (InitialballDirection)
		{
		case 0:
			BallPos.y += 150 * sfw::getDeltaTime();
			break;
		case 1:
			BallPos.y -= 150 * sfw::getDeltaTime();
			break;
		}
		
		
		
		if (BallPos.x + ballRadius < boundingBoxRight && BallPos.x - ballRadius > boundingBoxLeft)
		{
			if (collidedLeft == true)
			{
				BallPos.x -= 250 * sfw::getDeltaTime();
				BallPos.x += 200 * sfw::getDeltaTime();
				collidedRight = false;
			}
			if (collidedRight == true)
			{
				BallPos.x -= 100 * sfw::getDeltaTime();
				collidedLeft = false;
			}
		}

		if (collidedTop == true)
		{
			BallPos.y += 200 * sfw::getDeltaTime();
			BallPos.y -= 100 * sfw::getDeltaTime();
		}
		if (collidedBottom == true)
		{
			BallPos.y -= 200 * sfw::getDeltaTime();
		}

		//if (BallPos.x + ballRadius >= screenWidth)
		//{
		//	collidedRight = true;
		//	//BallPos.x = -(BallPos.x * 2);

		//}
		

		if (buffOnScreen == true)
		{
			Player1HasBuff = true;
			if (Player1HasBuff == true)
			{
				//pickRandomBuff = 1;
				if (pickRandomBuff == 0)
				{
					if (!(RightPlayer.x + paddleWidth > screenWidth))
					{
						RightPlayer.x += 100 * sfw::getDeltaTime();
						RightPlayer.y += 100 * sfw::getDeltaTime();
					}
					if (!(RightPlayer.y + PaddleHeight > screenHeight))
					{
						
						RightPlayer.y += 100 * sfw::getDeltaTime();
					}
				}
				if (pickRandomBuff == 1)
				{
					if (sfw::getKey('c') == true)
					{
						BallPos.x = LeftPlayer.x + paddleWidth + ballRadius;
						BallPos.y = LeftPlayer.y + (PaddleHeight / 2);
					}
					DrawStickySpikesLeft(LeftPlayer.x, LeftPlayer.y);
					
					if (BallPos.x - ballRadius <= LeftPlayer.x + paddleWidth && BallPos.y + (ballRadius / 2) <= LeftPlayer.y && BallPos.y - (ballRadius / 2) >= LeftPlayer.y)
					{
						BallPos.x = LeftPlayer.x + paddleWidth;
						BallPos.y = LeftPlayer.y + (PaddleHeight / 2);
					}
				}
				if (pickRandomBuff == 2)
				{
					RightPlayer.x = RightPlayer.x;
					RightPlayer.y = RightPlayer.y;
				}
				//speed 0   spike 1 frozen 2

			}
			sfw::drawCircle(boundingBoxLeft, Circle[1] + buffMovementY, gateRadius);
			//Left PowerGrabLines
			sfw::drawLine(boundingBoxLeft, Circle[1] + buffMovementY,boundingBoxLeft - 25, (Circle[1] + buffMovementY) + 12.5);
			sfw::drawLine(boundingBoxLeft, Circle[2] + buffMovementY, boundingBoxLeft - 25, (Circle[2] + buffMovementY) - 12.5);
			sfw::drawLine(boundingBoxLeft - 25, (Circle[3] + buffMovementY) + 12.5, boundingBoxLeft - 25, (Circle[4] + buffMovementY) - 12.5);
			//Right PowerGrabLines
			sfw::drawLine(boundingBoxRight, Circle[3] + buffMovementY, boundingBoxRight + 25, (Circle[3] + buffMovementY) + 12.5);
			sfw::drawLine(boundingBoxRight, Circle[4] + buffMovementY, boundingBoxRight + 25, (Circle[4] + buffMovementY) - 12.5);
			sfw::drawLine(boundingBoxRight + 25, (Circle[3] + buffMovementY) + 12.5, boundingBoxRight + 25, (Circle[4] + buffMovementY) - 12.5);
			gateRadius += .5;
			if (gateRadius >= 10)
			{
				gateRadius = 10;

			}
			sfw::drawCircle(boundingBoxLeft, Circle[2] + buffMovementY, gateRadius);
		 
			sfw::drawCircle(boundingBoxRight, Circle[3] + buffMovementY, gateRadius);
		
			sfw::drawCircle(boundingBoxRight, Circle[4] + buffMovementY, gateRadius);
			if (isKeyPressed == true)
			{
				
			}
		
		}
		else if (buffOnScreen == false)
		{
			sfw::drawCircle(boundingBoxLeft, Circle[1], gateRadius);
			gateRadius -= .5;
			if (gateRadius <= 0)
			{
				gateRadius = 0;

			}
			sfw::drawCircle(boundingBoxLeft, Circle[2], gateRadius);
		
			sfw::drawCircle(boundingBoxRight, Circle[3], gateRadius);
			
			sfw::drawCircle(boundingBoxRight, Circle[4], gateRadius);
		
		}

	
		/*switch (totalScore)
		{
		case 0:
			break;
		case 4:
			sfw::drawCircle(boundingBoxRight, Circle[4], gateRadius[4]);
			gateRadius[4] += .5;
			if (gateRadius[4] >= 10)
			{
				gateRadius[4] = 10;

			}
		case 3:
			sfw::drawCircle(boundingBoxRight, Circle[3], gateRadius[3]);
			gateRadius[3] += .5;
			if (gateRadius[3] >= 10)
			{
				gateRadius[3] = 10;

			}
		case 2:
			sfw::drawCircle(boundingBoxLeft, Circle[2], gateRadius[2]);
			gateRadius[2] += .5;
			if (gateRadius[2] >= 10)
			{
				gateRadius[2] = 10;

			}
		case 1:
			sfw::drawCircle(boundingBoxLeft, Circle[1], gateRadius[1]);
			gateRadius[1] += .5;
			if (gateRadius[1] >= 10)
			{
				gateRadius[1] = 10;

			}
			break;
		
			
		}*/
		//if (buffOnScreen == true)
		//{
		//	//LeftPowerUpLines();
		//	RightPowerUpLines();
		//}

		//sfw::drawLine(boundingBoxLeft, 0, boundingBoxLeft, topGate); // Left Top Gate
		//sfw::drawLine(boundingBoxLeft, screenHeight, boundingBoxLeft, bottomGate); // Left Bottom Gate
		//sfw::drawLine(boundingBoxRight, 0, boundingBoxRight, topGate); // Right Top Gate
		//sfw::drawLine(boundingBoxRight, screenHeight, boundingBoxRight, bottomGate); // Right Bottom Gate
		sfw::drawCircle(circleX, circleY, sin(timer)*Radius); //Pulsating Circle
		
		if (sfw::getKey('q') == false && sfw::getKey('/') == false)
		{
			buffMovementTimer--;
		}
			
		
		
		if (buffMovementTimer <= 0)
		{
			buffMovementTimer = 500;
			buffOnScreen = true;
			totalScore++;
		}
		if (buffOnScreen == true)
		{
			//buffMovementX -= sfw::getDeltaTime() * sfw::getDeltaTime();

			if (sfw::getKey('8'))
			{
				pickRandomBuff = 0;
			}


			switch (pickRandomBuff)
			{
			case 0:
			default:
				DrawSpeedBoost(buffMovementX, buffMovementY);//Speed Boost Buff
				if (sfw::getKey('q') == false && sfw::getKey('/') == false)
				{
					buffDurations.speedBoostDuration -= sfw::getDeltaTime();
				}
				break;
			case 1:
			
				DrawSpikeBuff(buffMovementX, buffMovementY);//Spike Buff
				if (sfw::getKey('q') == false && sfw::getKey('/') == false)
				{
					buffDurations.spikeBuffDuration -= sfw::getDeltaTime();
				}
				break;
			case 2:
				DrawFrozenBuff(buffMovementX, buffMovementY);//frozen buff
				if (sfw::getKey('q') == false && sfw::getKey('/') == false)
				{
					buffDurations.frozenBuffDuration -= sfw::getDeltaTime();
				}
				break;

			}
			
			
		}
		else if (buffOnScreen == false)
		{
			//buffMovementX -= sfw::getDeltaTime() * sfw::getDeltaTime();
			buffMovementY = BuffPos.y * sfw::getDeltaTime();
			BuffPos.x = screenWidth / 2;
			BuffPos.y -= 0;
			buffDurations.speedBoostDuration = 9;
			buffDurations.spikeBuffDuration = 9;
			buffDurations.frozenBuffDuration = 9;
		}
		if (buffDurations.speedBoostDuration <= -2 || buffDurations.spikeBuffDuration <= -2 || buffDurations.frozenBuffDuration <= -2)
		{
			buffDeleted = true;
			pickRandomBuff = rand() % numberOfBuffs;
			buffOnScreen = false;
			
		    

		}
	
		  							                /*if (buffMovementY < screenHeight / 2)
													{
													DrawStickySpikesRight(RightPlayer.x, RightPlayer.y);
													}
													if (buffMovementY > screenHeight / 2)
													{
													DrawStickySpikesLeft(LeftPlayer.x, LeftPlayer.y);
													}*/

		buffMovementY += 100 * sfw::getDeltaTime(); // get the buff to move down the screen initially
		if (sfw::getKey('q') == false && sfw::getKey('/') == false)
		{
			static float OriginalBuffMoveXPos = BuffPos.x;
			buffMovementX = sin(timer * 10);// *tugOWar;
			//scale = 1;
		}

		

		if (sfw::getKey('q'))
		{
			isKeyPressed = true;
			if (buffMovementY > screenHeight / 2)
			{
				buffMovementY -= 150 * sfw::getDeltaTime();
				buffMovementX -= 150 * sfw::getDeltaTime();
			}
			if (buffMovementY < screenHeight / 2)
			{
				//buffMovementY += 150 * sfw::getDeltaTime();
				buffMovementY += 150 * sfw::getDeltaTime();
				buffMovementX -= 150 * sfw::getDeltaTime();
			}
			buffMovementY -= 100 * sfw::getDeltaTime();
			//buffMovementX -= (10 * sfw::getDeltaTime()) * scale;
			//buffMovementX -= scale;
			//scale += .1;

			/*if (buffMovementX  < boundingBoxLeft + (boundingBoxLeft - buffMovementX))
			{
				buffMovementX = 0;
				scale = 0;
			}*/
			

		}
		
		if (sfw::getKey('/'))
		{
			isKeyPressed = true;
			if (buffMovementY > screenHeight / 2)
			{
				buffMovementY -= 150 * sfw::getDeltaTime();
				buffMovementX += 150 * sfw::getDeltaTime();
			}
			if (buffMovementY < screenHeight / 2)
			{
				buffMovementY += 150 * sfw::getDeltaTime();
				buffMovementX += 150 * sfw::getDeltaTime();
			}
			buffMovementY -= 100 * sfw::getDeltaTime();
			/*buffMovementX -= (10 * sfw::getDeltaTime()) * scale;
			buffMovementX += scale;*/
			//scale += .1;

		}
//
//		if (buffMovementX > screenWidth / 3 && buffOnScreen == true)
//		{
//			if(buffDurations.spikeBuffDuration >= 0)
//			DrawStickySpikesRight(RightPlayer.x, RightPlayer.y);
//		}
//
//
//		if (buffMovementY + 50 > screenHeight)
//		{
//			buffMovementY = 0;
//		}
//		if (approachingCenter)
//		{
//			buffMovementY -= 400 * sfw::getDeltaTime();
//		}
//		if (sfw::getKey('-'))
//		{
//			buffMovementX -= 200 * sfw::getDeltaTime();
//		}
//		if (sfw::getKey('='))// '+' key
//		{
//			buffMovementX += 200 * sfw::getDeltaTime();
//		}
		

		timer += sfw::getDeltaTime();
		
		sin(timer)*Radius;
		circleX -= (sin(timer) * 5); // Circle path

									 //circleY++;
		CirclePos.x = circleX;
		CirclePos.y = circleY;
		if (sfw::getKey(','))//  <
		{
			topGate -= 300 * sfw::getDeltaTime();
			bottomGate -= 300 * sfw::getDeltaTime();
		}
		if (sfw::getKey('.'))// >
		{
			topGate += 300 * sfw::getDeltaTime();
			bottomGate += 300 * sfw::getDeltaTime();
		}

		if (!buffMovement)
		{
			tugOWar--;
			if (tugOWar < -19)
				buffMovement = true;
		}
		else
		{
			tugOWar++;
			if (tugOWar >= 20)
				buffMovement = false;

		}



		//////////////////////////////
		//if (Timer > 10)
		//{
		//	Timer--;
		//}
		//if (Timer <= 10)
		//{
		//	Timer = (radius -= 50);
		//	if (radius <= 0)
		//	{
		//		radius = Radius;
		//	}
		//}
		///////////////////////////

		if (sfw::getKey('w'))
		{
			LeftPlayer.y -= 500 * sfw::getDeltaTime();;
			if (LeftPlayer.y + PaddleHeight <= 0)
			{
				LeftPlayer.y = screenHeight;
			}

		}
		if (sfw::getKey('s'))
		{
			LeftPlayer.y += 500 * sfw::getDeltaTime();
			if (LeftPlayer.y >= screenHeight)
			{
				LeftPlayer.y = 0 - PaddleHeight;
			}
		}

		if (sfw::getKey('a'))
		{
			LeftPlayer.x -= 500 * sfw::getDeltaTime();;
			if (LeftPlayer.x < 0)
			{
				LeftPlayer.x = 0;
			}
		}

		if (sfw::getKey('d'))
		{
			LeftPlayer.x += 500 * sfw::getDeltaTime();;
			if (LeftPlayer.x + paddleWidth >= boundingBoxLeft)
			{
				LeftPlayer.x = 0 - paddleWidth;
			}
		}

		if (Player1HasBuff == false || pickRandomBuff != 2)
		{
			
			if (sfw::getKey('u'))
			{
				RightPlayer.y -= 500 * sfw::getDeltaTime();;
				if (RightPlayer.y + PaddleHeight <= 0)
				{
					RightPlayer.y = screenHeight;
				}

			}
			if (sfw::getKey('j'))
			{
				RightPlayer.y += 500 * sfw::getDeltaTime();
				if (RightPlayer.y >= screenHeight)
				{
					RightPlayer.y = 0 - PaddleHeight;
				}
			}

			if (sfw::getKey('h'))
			{
				RightPlayer.x -= 500 * sfw::getDeltaTime();
				if (RightPlayer.x <= boundingBoxRight)
				{
					RightPlayer.x = screenWidth;
				}
			}
			if (sfw::getKey('k'))
			{
				RightPlayer.x += 500 * sfw::getDeltaTime();
				if (RightPlayer.x + paddleWidth >= screenWidth)
				{
					RightPlayer.x = screenWidth - paddleWidth;
				}
			}
		}


	}
	sfw::termContext();



}