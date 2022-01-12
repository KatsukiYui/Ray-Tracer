#include "Camera.h"

#include <iostream>

Camera::Camera(glm::vec3 _pos, glm::vec3  _lookAtDir)//constructor
{
	camPosition = _pos;

	lookAtDir = _lookAtDir;

	lookAtPos = camPosition + lookAtDir; //target position for the camera to look at

};

//creates a ray that is passed to the tracer function
Ray Camera::createRay(glm::vec2 _coord, glm::ivec2 _window)
{
	glm::vec3 Up(0, 1, 0);// y = 1 used to make the viewing matrix

	Projection = glm::perspective(glm::radians(45.0f), ((float)_window.x / (float)_window.y), 1.0f, 1000.0f);
	//creates the perspective projection matrix based on the ratio between the window x and y
	// the z far and z near.. and the angle of the lens
	//the inverse of it converts things from clip space to camera space

	invViewing = makeViewing(Up); //tried to make my own simple viewing(inverse viewing actually) matrix before i found the built in one.. it works the same :3
	//converting things from camera space to world space


	//invViewing = glm::mat4(1); //no viewing matrix applied
	//invViewing = glm::lookAt(camPosition, lookAtPos, Up); //built in function
	invProjection = glm::inverse(Projection);


	//normalizing 
	glm::vec2 NDC(NDC(_coord, _window));//maps the pixel position to -1 to 1
	
	glm::vec4 Start(NDC, -1, 1); //adding w = 1 //start and end are just the near and far planes

	glm::vec4 End(NDC, 1, 1);//start and end points of the ray

	Start = invViewing * invProjection * Start; //convert to world space
	End = invViewing *invProjection * End;//convert to world space

	Start /= Start.w; //divide by w to put things into perspective
	End /= End.w;

	//removing w ... automatically cuz life hurts

	glm::vec3 Origin = Start; //origin of the ray is just the start point

	glm::vec3 Direction;//direction of the ray
	Direction = End - Start; //getting the vector from the near plane (Start rn) to far plane (End rn)

	//normalising the Direction into a unit vector
	Direction = glm::normalize(Direction);

	Ray ray(Origin,Direction); //create the ray and return it.. this is passed to the tracer's function

	return ray;
};

//maps pixel coordinates to -1 to 1
glm::vec2 Camera::NDC(glm::vec2 _coord, glm::ivec2 _window)
{
	//0.25 because half a pixel
	glm::vec2 NDC((_coord.x + 0.25) / _window.x, (_coord.y + 0.25) / _window.y);// +0.5 to get the centre of the pixel

	NDC = glm::vec2((2*NDC.x) -1 , (2* NDC.y)-1);

	return NDC;//return the mapped coordinates
};


/*creates a viewing matrix based on the camera's position, the point you wanna look at
and the up vector (0,1,0) which points toward +ve Y */
glm::mat4 Camera::makeViewing(glm::vec3 _up) //cuz using glm lookat wouldve been too efficient XD
{
	lookAtPos = camPosition + lookAtDir; //target position to look at

	//creating the 3 perpendicular axis (change of basis)
	glm::vec3 Forward = glm::normalize(camPosition - lookAtPos); //forward direction aka direction to the target
	glm::vec3 Right = glm::normalize(glm::cross(_up, Forward));
	glm::vec3 Up = glm::cross(Forward, Right); //calculating the 3rd axis from the cross product of the other 2 ...making Y / Up perpendicular to the others
											   //theyre both already normalized so no need to normalize R

    //the inverse of rotation is just the Transposition since theyre "orthonormalized"

	glm::mat4 Rotation{ glm::vec4(Right.x, Up.x, Forward.x , 0),  glm::vec4(Right.y, Up.y, Forward.y, 0),  glm::vec4(Right.z, Up.z, Forward.z, 0),  glm::vec4(0, 0, 0, 1) }; //inverse of the rotation

	glm::mat4 Translation{ glm::vec4(1,0,0,0),  glm::vec4(0,1,0,0),  glm::vec4(0,0,1,0),  glm::vec4(-camPosition.x, -camPosition.y, -camPosition.z, 1)}; //inverse of the translation

	return (Rotation * Translation); //opposite order to return the inverse
}



//setters
void Camera::setPosition(glm::vec3 _pos)
{
	camPosition = _pos;
}
void Camera::setLookAtPos(glm::vec3 _pos)
{
	lookAtPos = _pos;
}
void Camera::setLookAtDir(glm::vec3 _dir)
{
	lookAtDir = _dir;
}


//getters
glm::vec3 Camera::getPosition() { return camPosition; }
glm::vec3 Camera::getLookAtPos() { return lookAtPos; }
glm::vec3 Camera::getLookAtDir(){ return lookAtDir; }
