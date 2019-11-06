#ifndef _CAM_
#define _CAM_

#include <cmath>

#include "MCG_GFX_Lib.h"

#include "Ray.h"

#include "Tracer.h"

class Camera
{

protected:

	glm::vec3 camPosition;//position of the camera
	glm::vec3 lookAtPos;//the point the camera will be looking at
	glm::vec3 lookAtDir; //direction the camera will be looking at
	glm::mat4 Viewing;//viewing matrix
	glm::mat4 Projection;//perspective projection matrix
	glm::mat4 invViewing;//inverse of viewing matrix
	glm::mat4 invProjection;//inverse of projection matrix


public:

	Camera(glm::vec3 _pos, glm::vec3 _lookAtDir);//constructor

	Ray createRay(glm::ivec2 _coord, glm::ivec2 _window);//creates a ray

	glm::vec2 NDC(glm::ivec2 _coord, glm::ivec2 _window);//maps pixel coordinates to -1 to 1

	glm::mat4 makeViewing(glm::vec3 _up);//creates the inverse of the viewing matrix
	//using the camera position, the look at direction and the up vector(0,1,0)

	//setters
	void setPosition(glm::vec3 _pos);
	void setLookAtPos(glm::vec3 _pos);
	void setLookAtDir(glm::vec3 _dir);

	//getters
	glm::vec3 getPosition();
	glm::vec3 getLookAtPos();
	glm::vec3 getLookAtDir();

};


#endif // !_CAM_
