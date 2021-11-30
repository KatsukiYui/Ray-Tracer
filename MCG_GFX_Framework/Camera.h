#ifndef _CAM_
#define _CAM_

#include <cmath>

#include "MCG_GFX_Lib.h"

#include "Ray.h"

#include "Tracer.h"

class Camera
{

private:

	glm::vec3 camPosition;
	glm::vec3 lookAtPos;//the point the camera will be looking at
	glm::mat4 Viewing;
	glm::mat4 Projection;
	glm::mat4 invViewing;
	glm::mat4 invProjection;


public:

	Camera(glm::vec3 _pos, glm::vec3 _lookAtPos);

	Ray createRay(glm::ivec2 _coord, glm::ivec2 _window);

	glm::vec2 NDC(glm::ivec2 _coord, glm::ivec2 _window);

	glm::mat4 makeViewing(glm::vec3 _camPos, glm::vec3 _target, glm::vec3 _up);

	void setPosition(glm::vec3 _pos);
	void setLookAtPos(glm::vec3 _pos);

	glm::vec3 getPosition();
	glm::vec3 getLookAtPos();



};


#endif // !_CAM_
