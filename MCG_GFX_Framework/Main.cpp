#include "Main.h"
#include <thread>

#define THREAD_COUNT 8


int main( int argc, char *argv[] )
{

	Menu(); 

	return 0;
	
}

//console menu
void Menu()
{
	//used to exit the while loop
	bool Exit = false;

	std::string Choice;//to take user input

	//print menu choices
	std::cout << "1: RayTracer: Sphere Animation" << std::endl << "2: RayTracer: Camera Animation" <<
		std::endl << "3: Rasterisation: Circle" <<
		std::endl << "4: Rasterisation: Square" << std::endl << "5: Rasterisation: Triangle "
		<< std::endl << "6: Rasterisation: Animated 2D Shapes "
		<< std::endl << "7: Exit" << std::endl;

	std::getline(std::cin, Choice);//read input

	while (!Exit)
	{

		while (Choice != "1" && Choice != "2" && Choice != "3" && Choice != "4" && Choice != "5" && Choice != "6" && Choice != "7")//keep asking for input if it was incorrect
		{

			std::cout << "1: RayTracer: Sphere Animation" << std::endl << "2: RayTracer: Camera Animation" <<
				std::endl << "3: Rasterisation: Circle" <<
				std::endl << "4: Rasterisation: Square" << std::endl << "5: Rasterisation: Triangle "
				<< std::endl << "6: Rasterisation: Animated 2D Shapes "
				<< std::endl << "7: Exit" << std::endl;

			std::getline(std::cin, Choice);
		}


		if (Choice == "7")//exit the loop and return to main
		{
			Exit = true;
		}

		if (!Exit) //open the sdl window
		{
			// Call MCG::Init to initialise and create your window
			// Tell it what size you want the window to be
			if (!MCG::Init(windowSize))
			{
				// We must check if something went wrong
				// (this is very unlikely)
				return;
			}

		}
		//2 ray tracing scenes
		if (Choice == "1")
		{
			std::cout << "Press escape to exit the Window";//close sdl window using Esc
			RayTracerSphereAnimation();
		}

		if (Choice == "2")
		{
			std::cout << "Press escape to exit the Window";
			RayTracerCameraAnimation();
		}

		//4 rasterization scenes

		if (Choice == "3")
		{
			std::cout << "Press escape to exit the Window";
			drawCircle();
		}

		if (Choice == "4")
		{
			std::cout << "Press escape to exit the Window";
			drawSquare();
		}

		if (Choice == "5")
		{
			std::cout << "Press escape to exit the Window";
			drawTriangle();
		}

		if (Choice == "6")
		{
			std::cout << "Press escape to exit the Window";
			Animated2D();//draws the 3 2D shapes and animates them
		}

		Choice = "";//reset choice

		MCG::Cleanup();//close the sdl window

	}
};

void calculateColour(glm::ivec2 &_startPos, glm::ivec2 &_endpos, glm::vec3 &_backgroundColor, std::vector<std::vector<glm::vec3>>&_pixelColours)
{
	for (int j = _startPos.y; j < _endpos.y; j++)
	{
		for (int i = _startPos.x; i < _endpos.x; i++)
		{
			glm::vec3 colour = Trace->antiAliasing(Cam->createRay(glm::vec2(i, j), windowSize), Cam->createRay(glm::vec2(i + 0.5f, j + 0.5f), windowSize), &sVec, Cam->getPosition(), L, _backgroundColor);
			_pixelColours[i][j] = colour;
		}
	}
};

//ray tracer with sphere rotations and fixed camera
void RayTracerSphereAnimation()
{
	Cam = new Camera(glm::vec3(0, 0, -400), glm::vec3(0, 0, 1));//camera position and dir to look at

	Trace = new Tracer(); //does all the intersection checks

	L = new Light();//point light source

	L->setCol(glm::vec3(255, 255, 255));

	L->setPos(glm::vec3(0.0f, -140.0f, -200.0f));

	//mapping the light's color to 0-1

	L->setCol(Trace->mapColor(L->getCol(), 1));

	//creating the spheres and adding them to the vector

	Sphere Sphere1(glm::vec3(0.0f, -100.0f, 0.0f), 20.0f, glm::ivec3(250, 100, 90), Rough);//position, radius, color, surface type

	sVec.push_back(Sphere1);

	Sphere Sphere2(glm::vec3(-150.0f, 0.0f, 0.0f), 20.0f, glm::ivec3(47, 32, 66), Smooth);

	sVec.push_back(Sphere2);

	Sphere Sphere3(glm::vec3(0.0f, 0.0f, 0.0f), 60.0f, glm::ivec3(0, 0, 0), Reflective);

	sVec.push_back(Sphere3);

	//set the backgroundColor
	glm::vec3 backgroundColor(72, 61, 139);
	MCG::SetBackground(backgroundColor);

	//mapping the spheres' color to 0-1
	for (int i = 0; i < sVec.size(); i++)
	{
		sVec[i].setColor(Trace->mapColor(sVec[i].getColor(), 1));
	}
	
	/*ializing with empty values
	for (int j = 0; j < windowSize.x; j++)
	{
		std::vector<glm::vec3> temp;

		for (int i = 0; i < windowSize.y; i++)
		{
			temp.push_back(glm::vec3(255, 0, 0));
		}

		pixelColours.push_back(temp);
	}
	*/



	std::vector<glm::ivec2> coordList;
	for (int x = 0; x < windowSize.x; x++)
	{
		for (int y = 0; y < windowSize.y; y++)
		{
			coordList.push_back(glm::ivec2(x, y));
		}
	}

	std::vector<std::vector<glm::ivec2>> threadCoordinates;
	int coordinateIndex = 0;
	for (int i = 0; i < THREAD_COUNT - 1; i++)
	{
		std::vector<glm::ivec2> subCoordinateList;
		for (int j = 0; j < (coordList.size() / THREAD_COUNT); j++)
		{
			subCoordinateList.push_back(coordList[coordinateIndex]);
			coordinateIndex++;
		}

		threadCoordinates.push_back(subCoordinateList);
	}




	std::vector<glm::ivec2> subCoordinateList;
	for (int i = 0; i < (coordList.size() / THREAD_COUNT + coordList.size() % THREAD_COUNT); i++)
	{
		subCoordinateList.push_back(coordList[coordinateIndex]);
		coordinateIndex++;
	}

	threadCoordinates.push_back(subCoordinateList);
	while (MCG::ProcessFrame())//draw frame, return false if Esc was pressed
	{
		//rotate the spheres
		Animate(&(sVec[1]), y);//rotate the sphere around the y axis

		Animate(&(sVec[0]), x);//rotate the sphere around the x axis

		MCG::getWindowSize(&windowSize);//used to enable changing the window size

		// THIS DIVIDES NICELY FOR NOW BUT ADD A REMAINDER THREAD FOR OTHER WINDOW SIZES
		int raysPerThread = (windowSize.x * windowSize.y) / 8; //38,400
		glm::ivec2 startPosition(0, 0);
		glm::ivec2 endPosition(0, 0);

		/*
		for (int i = 0; i < 8; i++)
		{
			//calculate the last pixel the thread will work on based on the raysPerThread value
			endPosition = glm::ivec2(windowSize.x, endPosition.y + (raysPerThread / windowSize.x));
			//myThreads.push_back(std::thread(&calculateColour, startPosition, endPosition, backgroundColor, pixelColours));
			calculateColour(startPosition, endPosition, backgroundColor, pixelColours);
			startPosition = glm::ivec2(0, endPosition.y);
		}
		*/



		std::vector<std::thread> myThreads;
		std::vector<std::shared_ptr<std::vector<glm::vec3>>> outputColours;
		
		for (int i = 0; i < THREAD_COUNT - 1; i++)
		{
			outputColours.push_back(std::make_shared<std::vector<glm::vec3>>());
			myThreads.push_back(std::thread(RayTracerThread, threadCoordinates[i], outputColours[i]));
		}

		outputColours.push_back(std::make_shared<std::vector<glm::vec3>>());
		myThreads.push_back(std::thread(RayTracerThread, threadCoordinates[THREAD_COUNT - 1], outputColours[THREAD_COUNT - 1]));
		
			   	



		for (std::thread& thread : myThreads)
		{
			if (thread.joinable())
			{
				thread.join();
			}
		}




		for (int i = 0; i < outputColours.size(); i++)
		{
			for (int j = 0; j < outputColours[i]->size(); j++)
			{
				MCG::DrawPixel(threadCoordinates[i][j], outputColours[i]->at(j));
			}
		}

		/*
		for (int j = 0; j < windowSize.y; j++)
		{

			for (int i = 0; i < windowSize.x; i++)
			{
				MCG::DrawPixel(threadCoordinates[], pixelColours[i][j]);
			}
		}*/




		/*
		for (int j = 0; j < windowSize.y; j++)
		{

			for (int i = 0; i < windowSize.x; i++)
			{
				MCG::DrawPixel(glm::ivec2(i, j), pixelColours[i][j]);
			}
		}
		*/
	}

	//deleting pointers, freeing memory
	delete Cam;
	delete Trace;
	delete L;

	//clearing the sphere vector
	sVec.clear();
	/*
	myThreads.clear();
	pixelColours.clear();
	*/
}

void RayTracerThread(std::vector<glm::ivec2> pixelCoordinates, std::shared_ptr<std::vector<glm::vec3>> outputColours)
{
	for (int i = 0; i < pixelCoordinates.size(); i++)
	{
		int x = pixelCoordinates[i].x, y = pixelCoordinates[i].y;
		glm::vec3 colour = Trace->antiAliasing(Cam->createRay(pixelCoordinates[i], windowSize), Cam->createRay(glm::vec2(x + 0.5f, y + 0.5f), windowSize), &sVec, Cam->getPosition(), L, glm::vec3(72, 61, 139));
		
		outputColours->push_back(colour);
	}
}






//ray tracer with camera rotations and fixed spheres
void RayTracerCameraAnimation()
{
	Cam = new Camera(glm::vec3(0, 0, -300), glm::vec3(0, 0, 1));//camera position and dir to look at

	Trace = new Tracer(); //does all the intersection checks

	L = new Light();//point light source

	L->setCol(glm::vec3(255, 255, 255));

	L->setPos(glm::vec3(0.0f, -140.0f, -200.0f));

	//mapping the _light's color to 0-1

	L->setCol(Trace->mapColor(L->getCol(), 1));

	//creating the spheres and adding them to the vector

	Sphere Sphere1(glm::vec3(0.0f, -100.0f, 0.0f), 20.0f, glm::ivec3(250, 100, 90), Rough);//position, radius, color, surface type

	sVec.push_back(Sphere1);

	Sphere Sphere2(glm::vec3(-150.0f, 0.0f, 0.0f), 20.0f, glm::ivec3(47, 32, 66), Smooth);

	sVec.push_back(Sphere2);

	Sphere Sphere3(glm::vec3(0.0f, 0.0f, 0.0f), 60.0f, glm::ivec3(0, 0, 0), Reflective);

	sVec.push_back(Sphere3);

	//set the backgroundColor
	glm::vec3 backgroundColor(72, 61, 139);


	//mapping the spheres' color to 0-1
	for (int i = 0; i < sVec.size(); i++)
	{
		sVec[i].setColor(Trace->mapColor(sVec[i].getColor(), 1));
	}


	//used for camera animation 
	glm::vec3 Pos = Cam->getPosition(); //current camera position
	glm::vec3 Dir = Cam->getLookAtDir(); //current look at direction (or rotation) .. used to make the forward vector in the look at function
	double Angle = 0.1f; //angle of rotation
	float Radius = 50.0f;//radius of rotation
	const glm::vec3 Start = Cam->getPosition(); //start position of the sphere
	const glm::vec3 lStart = Cam->getLookAtDir(); //start look at direction of the camera

	while (MCG::ProcessFrame())
	{
		//rotate the spheres
		//Animate(&(sVec[1]), y);//rotate the sphere around the y axis

	    //Animate(&(sVec[0]), x);//rotate the sphere around the x axis


		if (Angle >= 2 * glm::pi<double>())//if the circle is completed..
		{
			Angle = 0.1f;//reset Angle
		}

		//move the camera around the scene
		Pos.x = Start.x + sin(Angle) * Radius;
		Pos.z = Start.z + cos(Angle) * Radius;

		//rotate the direction the camera is looking in
		Dir.x = lStart.x + sin(Angle) * Radius;
		Dir.z = lStart.z + cos(Angle) * Radius;

		Cam->setPosition(Pos);//set the position
		Cam->setLookAtDir(glm::normalize(Dir));//normalise direction

		Angle += 0.1f;//incerement angle

		MCG::getWindowSize(&windowSize);//used to enable changing the window size

		for (int j = 0; j < windowSize.y; j++)
		{

			for (int i = 0; i < windowSize.x; i++)
			{
				MCG::DrawPixel(glm::ivec2(i, j), Trace->rayTrace(Cam->createRay(glm::ivec2(i, j), windowSize), &sVec, Cam->getPosition(), L, backgroundColor));
				//create a ray using the camera ptr and pass that ray to the tracer for intersection checks with the spheres vector.
				//The tracer then returns the color of that pixel.
			}

		}
	}

	//deleting pointers, freeing memory
	delete Cam;
	delete Trace;
	delete L;
	//clearing the sphere vector
	sVec.clear();
};

//used to animate the spheres
void Animate(Sphere *_sph, Axis _axis)
{
	glm::vec3 newCentre = _sph->getCentre();

	switch (_axis)
	{
	case y:
		//moving the sphere around Y axis
		//using parametric equations to move its centre

		newCentre.z = _sph->getCentre().z * glm::cos(glm::radians(3.0f)) - _sph->getCentre().x * glm::sin(glm::radians(3.0f));
		newCentre.x = _sph->getCentre().x * glm::cos(glm::radians(3.0f)) + _sph->getCentre().z * glm::sin(glm::radians(3.0f));

		_sph->setCentre(newCentre);

		break;

	case x:
		//moving the sphere around X axis

		newCentre.z = _sph->getCentre().z * glm::cos(glm::radians(3.0f)) - _sph->getCentre().y * glm::sin(glm::radians(3.0f));
		newCentre.y = _sph->getCentre().y * glm::cos(glm::radians(3.0f)) + _sph->getCentre().z * glm::sin(glm::radians(3.0f));

		_sph->setCentre(newCentre);


		break;
	}
};

//draw a circle pixel by pixel using trig
void drawCircle()
{
	glm::ivec2 C(windowSize.x / 2, windowSize.y / 2); //start position of the first pixel
	float R = 50;//radius
	glm::ivec2 Pos = C; //current position of the pixel being drawn

	double Angle = 0.01;//angle of rotation
	int Timer = 0;//times used to delay the loop

	bool Drawing = true; //used to stop the loop when user hits Esc and close the window


	while (R >0 && Drawing)//keep drawing circles till you reach the centre: R = 0
	{
			//draw circle
			if (Angle >= 2 * glm::pi<double>())//if the circle is completed..
			{
				R = R - 0.1;//draw a smaller circle
				Pos.x = C.x + R * glm::cos(Angle);
				Pos.y = C.y + R * glm::sin(Angle);

				Angle = 0.01f;//reset Angle
			}

			Pos.x = C.x + R * glm::cos(Angle);//move the current pixel along the circle
			Pos.y = C.y + R * glm::sin(Angle);


			MCG::DrawPixel(Pos, glm::ivec3(255, 0, 255));

			Angle += 0.01;//increment the angle to draw next pixel along the circle

			if (Timer %50 == 0)//delay
			{
				Drawing = MCG::ProcessFrame();//for exiting the loop
			}

			Timer++;

	}

};

//draw a square pixel by pixel using nested while loops
void drawSquare()
{
	//draw square or rectangle
	int Height = 100;
	int Width = 100;

	bool Drawing = true;//used to exit the loop and close the window

	int Timer = 0;//used to add a delay
	int i = 0;
	int j = 0;

	while (Drawing)//while !Esc
	{
		while (i < Height)//nested while loop
		{
			while (j < Width)
			{
				MCG::DrawPixel(glm::ivec2(j + (windowSize.x / 2) - Width / 2, i + (windowSize.y / 2) - Height / 2), glm::ivec3(0, 200, 255));
				//draw to the middle of the screen

				if (Timer % 10 == 0)//delay
				{
					Drawing = MCG::ProcessFrame();//draw this frame but also check for Esc pressed

				}

				Timer++;
				j++;
			}

			i++;
			j = 0;

		}

		Drawing = MCG::ProcessFrame(); //check for Esc button pressed
	}
};

//draw a trangle pixel by pixel using nested for loops
void drawTriangle()//draw triangle 
{
	int Height = 60;
	int curWidth = 60; //used to decrease the width to draw a triangle instead of square
	int Width = 60;

	bool Drawing = true;

	int Timer = 0;

	while (MCG::ProcessFrame())
	{

		for (int i = Height - 1; i > 0; i--)
		{
			for (int j = 0; j < curWidth; j++)
			{
				MCG::DrawPixel(glm::ivec2(j + (windowSize.x / 2) - curWidth / 2, i + (windowSize.y / 2) - Height / 2), glm::ivec3(0, 200, 255));
				//draw in the middle of the screen...Also draw and equilateral triangle

				if (Timer % 10 == 0)//delay
				{
					Drawing = MCG::ProcessFrame();//draw the frame
				}

				Timer++;
			}

			if (curWidth > 0)
			{
				curWidth--; //decrease the width of the next line
			}

		}
	}
}

//draw the 3 2D shapes and animate them
void Animated2D()
{
	//used for drawing the circle
	float R = 50;//radius
	glm::ivec2 C(windowSize.x / 2, (windowSize.y / 2) + R * 2);//start position of the first pixel to be drawn at max radius
	glm::ivec2 Pos = C;//current position of the pixel ebing drawn

	double Angle = 0.01;//angle of rotation around the z axis.. drawing the circle

	//growing and shrinking the circle
	int cTimer = 0;//timer used to increase and decrease the radius of the circle
	bool Grow = true;//when grow is true the radius of the circle is incremented each frame.. drawing larger circles

	//used for drawing the square
	int sHeight = 100;
	int sWidth = 100;

	//used for drawing the triangle
	int Height = 100;
	int curWidth = 100;//is decremented each line horizontal line to draw the triangle
	int Width = 100;

	//used for rotating them 
	double rAngle = 0.05;//angle of rotation around the z axis
	double rRadius = 20;//radius of rotation around the z axis
	glm::ivec2 sStart(windowSize.x / 2 + 150, windowSize.y / 2 - 100);//start position of the square
	glm::ivec2 tStart(windowSize.x / 2 - 150, windowSize.y / 2 - 100);//start pos of the triangle
	glm::ivec2 sPos = sStart;//current position of the square
	glm::ivec2 tPos = tStart;//current position of the triangle


	while (MCG::ProcessFrame())//WHile !Esc .. draw frames
	{
		if (rAngle >= 2 * glm::pi<double>())//if the circle is completed..
		{
			rAngle = 0.05f;//reset Angle of rotation
		}

		MCG::SetBackground(glm::ivec3(0, 0, 0)); //draw over the shapes to simulate movement

		//increasing and decreasing the circle radius
		if (cTimer == 50)//max radius
		{
			Grow = false;
		}
		if (cTimer == 0)//min radius
		{
			Grow = true;
		}

		if (!Grow)
		{
			cTimer--;
		}
		if (Grow)
		{
			cTimer++;
		}

		R = cTimer; //R is the maximum radius of the circles aka the radius of the outermost circle in the filled in circle

		while (R > 0) //break when circle is filled in
		{
			//draw circle
			if (Angle >= 2 * glm::pi<double>())//if the circle is completed..
			{
				R = R - 0.1;//draw a smaller circle
				Pos.x = C.x + R * glm::cos(Angle);//rotate around z
				Pos.y = C.y + R * glm::sin(Angle);

				Angle = 0.01f;//reset Angle
			}

			Pos.x = C.x + R * glm::cos(Angle);
			Pos.y = C.y + R * glm::sin(Angle);


			MCG::DrawPixel(Pos, glm::ivec3(255, 0, 255));

			Angle += 0.01; //increment angle
		}

		//draw square or rectangle
		for (int i = 0; i < sHeight; i++)
		{
			for (int j = 0; j < sWidth; j++)
			{
				MCG::DrawPixel(glm::ivec2(j + sPos.x - sWidth / 2, i + sPos.y - sHeight / 2), glm::ivec3(0, 200, 255));

			}
		}

		//rotate

		sPos.x = sStart.x + glm::cos(rAngle) * rRadius; //changing the position of the upper left most pixel
		sPos.y = sStart.y + glm::sin(rAngle) * rRadius;

		//draw triangle
		int curWidth = Width; //reset width to redraw it each frame
		for (int i = Height - 1; i > 0; i--)
		{
			for (int j = 0; j < curWidth; j++)
			{
				MCG::DrawPixel(glm::ivec2(j + tPos.x - curWidth / 2, i + tPos.y - Height / 2), glm::ivec3(0, 200, 255));

			}

			if (curWidth > 0)
			{
				curWidth--;
			}

		}
		
		//rotate
		tPos.x = tStart.x + cos(-rAngle) * rRadius;
		tPos.y = tStart.y + sin(-rAngle) * rRadius;

		rAngle += 0.05f; //increment the angle of rotation

	}
}

