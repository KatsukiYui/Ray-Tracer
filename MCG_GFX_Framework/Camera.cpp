#include "Camera.h"

#include <iostream>

Camera::Camera(glm::vec3 _pos, glm::vec3 _lookAtPos)
{
	camPosition = _pos;

	lookAtPos = _lookAtPos;

};


Ray Camera::createRay(glm::ivec2 _coord, glm::ivec2 _window)
{

	glm::vec3 Up(0, 1, 0);
	Projection = glm::perspective(glm::radians(45.0f), ((float)_window.x / (float)_window.y), 1.0f, 1000.0f);

	invViewing = makeViewing(camPosition, lookAtPos, Up); //tried to make my own simple viewing(inverse viewing actually) matrix before i found the built in one.. it works the same :3

	//invViewing = glm::mat4(1);
	invViewing = glm::lookAt(camPosition, lookAtPos, Up);
	invProjection = glm::inverse(Projection);


	//normalizing 
	glm::vec2 NDC(NDC(_coord, _window));
	
	glm::vec4 Start(NDC, -1, 1); //adding w = 1 //start and end are just the near and far planes

	glm::vec4 End(NDC, 1, 1);

	//std::cout << Start.x << "  " << Start.y << "  " << Start.z << "  " << Start.w << std::endl << End.x << "  " << End.y << "  " << End.z << "  " << End.w << std::endl;


	Start = invViewing * invProjection * Start;
	End = invViewing *invProjection * End;

	Start /= Start.w;
	End /= End.w;

	//std::cout << Start.x << "  "<< Start.y << "  "<< Start.z << "  " << Start.w << std::endl << End.x << "  "<< End.y << "  "<< End.z << "  " << End.w << std::endl;

	//removing w ... automatically cuz life hurts

	glm::vec3 Origin = Start;

	glm::vec3 Direction;
	Direction = End - Start; //getting the vector from the near plane (Start rn) to far plane (End rn)

	//normalising the Direction into a unit vector

	Direction = glm::normalize(Direction);

	//std::cout << Origin.x << "  " << Origin.y << "  " << Origin.z << std::endl << Direction.x << "  " << Direction.y << "  " << Direction.z << std::endl;

	Ray ray(Origin,Direction);

	return ray;
};


glm::vec2 Camera::NDC(glm::ivec2 _coord, glm::ivec2 _window)
{

	glm::vec2 NDC((_coord.x + 0.5) / _window.x, (_coord.y + 0.5) / _window.y);

	NDC = glm::vec2((2*NDC.x) -1 , (2* NDC.y)-1);

	return NDC;
};


/*creates a viewing matrix based on the camera's position, the point you wanna look at
and the up vector (0,1,0) which points toward +ve Y */
glm::mat4 Camera::makeViewing(glm::vec3 _camPos, glm::vec3 _target, glm::vec3 _up) //cuz using glm lookat wouldve been too efficient XD
{
	//creating the 3 perpendicular axis
	glm::vec3 Forward = glm::normalize(_camPos - _target); //forward direction aka direction to the target
	glm::vec3 Right = glm::normalize(glm::cross(_up, Forward));
	glm::vec3 Up = glm::cross(Forward, Right); //calculating the 3rd axis from the cross product of the other 2 ...making Y / Up perpendicular to the others
											   //theyre both already normalized so no need to normalize R

     //the inverse of rotation is just the Transposition since theyre "orthonormalized"

	glm::mat4 Rotation{ glm::vec4(Right.x, Up.x, Forward.x , 0),  glm::vec4(Right.y, Up.y, Forward.y, 0),  glm::vec4(Right.z, Up.z, Forward.z, 0),  glm::vec4(0, 0, 0, 1) }; //inverse of the rotation

	glm::mat4 Translation{ glm::vec4(1,0,0,0),  glm::vec4(0,1,0,0),  glm::vec4(0,0,1,0),  glm::vec4(-_camPos.x, -_camPos.y, -_camPos.z, 1)}; //inverse of the translation

	return (Rotation * Translation);
}



void Camera::setPosition(glm::vec3 _pos)
{
	camPosition = _pos;
}



void Camera::setLookAtPos(glm::vec3 _pos)
{
	lookAtPos = _pos;
};


glm::vec3 Camera::getPosition() { return camPosition; }
glm::vec3 Camera::getLookAtPos() { return lookAtPos; };