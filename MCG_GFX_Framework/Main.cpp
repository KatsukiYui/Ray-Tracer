#include "Main.h"

int main( int argc, char *argv[] )
{

	Menu();

	return 0;
	
}


void Animate(Sphere *_sph, Axis _axis)
{
	glm::vec3 newCentre = _sph->getCentre();

	switch (_axis)
	{
	case y:
		//moving the sphere around Y axis

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

void Menu()
{
	bool Exit= false;

	std::string Choice;

	std::cout << "1: RayTracer" << std::endl << "2: Rasterisation: Circle" <<
		std::endl << "3: Rasterisation: Square" << std::endl << "4: Rasterisation: Triangle " 
		<< std::endl << "5: Exit" << std::endl;

	std::getline(std::cin, Choice);

	while (!Exit)
	{

		while (Choice != "1" && Choice != "2" && Choice != "3" && Choice != "4" && Choice != "5" && Choice != "6")
		{

			std::cout << "1: RayTracer: Sphere Animation" << std::endl << "2: Rasterisation: Circle" <<
				std::endl << "3: Rasterisation: Square" << std::endl << "4: Rasterisation: Triangle "
				<< std::endl << "5: Exit" << std::endl;

			std::getline(std::cin, Choice);
		}

		if (Choice == "6")
		{
			Exit = true;
		}

		// Call MCG::Init to initialise and create your window
		// Tell it what size you want the window to be
		if (!MCG::Init(windowSize))
		{
			// We must check if something went wrong
			// (this is very unlikely)
			return;
		}


		if (Choice == "1")
		{
			std::cout << "Press escape to exit the Window";
			RayTracerSphereAnimation();
		}


		if (Choice == "2")
		{
			std::cout << "Press escape to exit the Window";
			RayTracerCameraAnimation();
		}


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

		Choice = "";

		MCG::Cleanup();
	}
};

void RayTracerSphereAnimation()
{
	Cam = new Camera(glm::vec3(0, 0, -500), glm::vec3(0, 0, 0));//camera position and position to look at

	Trace = new Tracer();

	L = new Light();

	L->setCol(glm::vec3(255, 255, 255));

	L->setPos(glm::vec3(0.0f, -140.0f, -200.0f));

	//mapping the _light's color to 0-1

	L->setCol(Trace->mapColor(L->getCol(), 1));

	//creating the spheres and adding them to the vector

	Sphere Sphere1(glm::vec3(0.0f, -100.0f, 0.0f), 20.0f, glm::ivec3(250, 100, 90), Rough);//position, radius, color, surface type

	sVec.push_back(Sphere1);

	Sphere Sphere2(glm::vec3(-200.0f, 0.0f, 0.0f), 20.0f, glm::ivec3(47, 32, 66), Smooth);

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

	while (MCG::ProcessFrame())
	{

		Animate(&(sVec[1]), y);//rotate the sphere around the y axis
		//sVec[1] = Sphere2;


		Animate(&(sVec[0]), x);//rotate the sphere around the x axis
		//sVec[0] = Sphere1;

		MCG::getWindowSize(&windowSize);

		for (int j = 0; j < windowSize.y; j++)
		{

			for (int i = 0; i < windowSize.x; i++)
			{
				MCG::DrawPixel(glm::ivec2(i, j), Trace->rayTrace(Cam->createRay(glm::ivec2(i, j), windowSize), &sVec, Cam->getPosition(), L, backgroundColor));
			}

		}
	}

	delete Cam;
	delete Trace;
	delete L;
}
void RayTracerCameraAnimation()
{
	Cam = new Camera(glm::vec3(0, 0, -500), glm::vec3(0, 0, 0));//camera position and position to look at

	Trace = new Tracer();

	L = new Light();

	L->setCol(glm::vec3(255, 255, 255));

	L->setPos(glm::vec3(0.0f, -140.0f, -200.0f));

	//mapping the _light's color to 0-1

	L->setCol(Trace->mapColor(L->getCol(), 1));

	//creating the spheres and adding them to the vector

	Sphere Sphere1(glm::vec3(0.0f, -100.0f, 0.0f), 20.0f, glm::ivec3(250, 100, 90), Rough);//position, radius, color, surface type

	sVec.push_back(Sphere1);

	Sphere Sphere2(glm::vec3(-200.0f, 0.0f, 0.0f), 20.0f, glm::ivec3(47, 32, 66), Smooth);

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


	glm::vec3 Pos = Cam->getPosition(); 
	glm::vec3 lPos = Cam->getLookAtPos();


	while (MCG::ProcessFrame())
	{

		Animate(&(sVec[1]), y);//rotate the sphere around the y axis

		Animate(&(sVec[0]), x);//rotate the sphere around the x axis

		Pos.z = Cam->getPosition().z * glm::cos(glm::radians(1.0f)) - Cam->getPosition().x * glm::sin(glm::radians(1.0f));
		Pos.x = Cam->getPosition().x * glm::cos(glm::radians(1.0f)) + Cam->getPosition().z * glm::sin(glm::radians(1.0f));
		
		lPos.z = Cam->getLookAtPos().z * glm::cos(glm::radians(1.0f)) - Cam->getLookAtPos().x * glm::sin(glm::radians(1.0f));
		lPos.x = Cam->getLookAtPos().x * glm::cos(glm::radians(1.0f)) + Cam->getLookAtPos().z * glm::sin(glm::radians(1.0f));

		Cam->setPosition(Pos);
		Cam->setLookAtPos(lPos);

/*
		Cam->setPosition(Pos);

		Angle += 0.01f;

		*/
		MCG::getWindowSize(&windowSize);

		for (int j = 0; j < windowSize.y; j++)
		{

			for (int i = 0; i < windowSize.x; i++)
			{
				MCG::DrawPixel(glm::ivec2(i, j), Trace->rayTrace(Cam->createRay(glm::ivec2(i, j), windowSize), &sVec, Cam->getPosition(), L, backgroundColor));
			}

		}
	}

	delete Cam;
	delete Trace;
	delete L;
};

void drawCircle()
{
	glm::ivec2 C(windowSize.x / 2, windowSize.y / 2);
	float R = 50;//radius
	glm::ivec2 Pos = C;

	glm::ivec2 startPt(C.x + R * glm::cos(glm::radians(0.0f)), C.y + R * glm::sin(glm::radians(0.0f)));

	double Angle = 0;

	while (MCG::ProcessFrame())
	{
		while (R >0)
		{
			//draw circle
			if (Angle >= 2 * glm::pi<double>())//if the circle is completed..
			{
				R = R - 0.01;//draw a smaller circle
				Pos.x = C.x + R * glm::cos(Angle);
				Pos.y = C.y + R * glm::sin(Angle);

				Angle = 0.0f;//reset Angle
			}

			Pos.x = C.x + R * glm::cos(Angle);
			Pos.y = C.y + R * glm::sin(Angle);


			MCG::DrawPixel(Pos, glm::ivec3(255, 0, 255));

			Angle += 0.01;

		}
	}

};

void drawSquare()
{
	//draw square or rectangle
	int Height = 60;
	int Width = 100;

	while (MCG::ProcessFrame())
	{
		for (int i = 0; i < Height; i++)
		{
			for (int j = 0; j < Width; j++)
			{
				MCG::DrawPixel(glm::ivec2(j+ (windowSize.x/2) - Width/2, i + (windowSize.y/2) - Height/2), glm::ivec3(0, 200, 255));
			}
		}
	}
};

void drawTriangle()//draw triangle 
{
	int Height = 60;
	int curWidth = 60;
	int Width = 60;
	while (MCG::ProcessFrame())
	{

		for (int i = Height - 1; i > 0; i--)
		{
			for (int j = 0; j < curWidth; j++)
			{
				MCG::DrawPixel(glm::ivec2(j + (windowSize.x / 2) - curWidth / 2, i + (windowSize.y / 2) - Height / 2), glm::ivec3(0, 200, 255));
			}

			if (curWidth > 0)
			{
				curWidth--;
			}

		}
	}
};
