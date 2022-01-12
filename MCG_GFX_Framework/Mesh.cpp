#include "Mesh.h"


Mesh::Mesh(glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale, glm::vec3 _color, surfaceType _sType, std::string _filename)
{
	Position = _position;
	Rotation = _rotation;
	Scale = _scale;
	Color = _color;
	surfType = _sType;

	loadOBJ(_filename);
}

void Mesh::setPosition(glm::vec3 _position)
{
	Position = _position;
}

void Mesh::setRotation(glm::quat _rotation)
{
	Rotation = _rotation;
}

void Mesh::setScale(glm::vec3 _scale)
{
	Scale = _scale;
}

Triangle Mesh::getTriangle(int _index)
{
	if (Triangles.size() > _index)
	{
		return Triangles[_index];
	}
}

glm::vec3 Mesh::getPosition()
{
	return Position;
}

glm::quat Mesh::getRotation()
{
	return Rotation;
}

glm::vec3 Mesh::getScale()
{
	return Scale;
}

void Mesh::loadOBJ(std::string _filename)
{
	// Find file
	std::ifstream inputFile(_filename);

	if (inputFile.is_open())
	{
		// OBJ files can store texture coordinates, positions and normals
		std::vector<glm::vec2> rawUVData;
		std::vector<glm::vec3> rawPositionData;
		std::vector<glm::vec3> rawNormalData;

		std::vector<glm::vec2> orderedUVData;
		std::vector<glm::vec3> orderedPositionData;
		std::vector<glm::vec3> orderedNormalData;

		std::string currentLine;

		while (std::getline(inputFile, currentLine))
		{
			std::stringstream currentLineStream(currentLine);
			//std::cout<< currentLine <<std::endl;

			if (!currentLine.substr(0, 2).compare(0, 2, "vt"))
			{
				std::string junk;
				float x, y;
				currentLineStream >> junk >> x >> y;
				rawUVData.push_back(glm::vec2(x, y));
			}
			else if (!currentLine.substr(0, 2).compare(0, 2, "vn"))
			{
				std::string junk;
				float x, y, z;
				currentLineStream >> junk >> x >> y >> z;
				rawNormalData.push_back(glm::vec3(x, y, z));
			}
			else if (!currentLine.substr(0, 2).compare(0, 1, "v"))
			{
				std::string junk;
				float x, y, z;
				currentLineStream >> junk >> x >> y >> z;
				rawPositionData.push_back(glm::vec3(x, y, z));
			}
			else if (!currentLine.substr(0, 2).compare(0, 1, "f"))
			{
				std::string junk;
				std::string verts[4];

				currentLineStream >> junk >> verts[0] >> verts[1] >> verts[2] >> verts[3];

				if (verts[3].empty())
				{
					for (unsigned int i = 0; i < 3; i++)
					{
						std::stringstream currentSection(verts[i]);

						// There is just position data
						unsigned int posID = 0;
						unsigned int uvID = 0;
						unsigned int normID = 0;

						if (verts[i].find('/') == std::string::npos)
						{
							// No texcoords or normals
							currentSection >> posID;
						}
						else if (verts[i].find("//") != std::string::npos)
						{
							// No texcoords
							char junk;
							currentSection >> posID >> junk >> junk >> normID;
						}
						else
						{
							char junk;
							currentSection >> posID >> junk >> uvID >> junk >> normID;
						}

						if (posID > 0)
						{
							orderedPositionData.push_back(rawPositionData[posID - 1]);
						}
						if (uvID > 0)
						{
							orderedUVData.push_back(rawUVData[uvID - 1]);
						}
						if (normID > 0)
						{
							orderedNormalData.push_back(rawNormalData[normID - 1]);
						}
					}
				}
				else
				{
					std::cerr << "WARNING: This OBJ loader only works with triangles but a quad has been detected. Please triangulate your mesh." << std::endl;
					inputFile.close();
					return;
				}

			}
		}

		//convert data into triangles and adding them to the vector

		glm::vec3 positions[3];
		glm::vec3 normals[3];

		for (int i = 0; i < orderedPositionData.size(); i += 3)
		{
			positions[0] = orderedPositionData[i];
			positions[1] = orderedPositionData[i + 1];
			positions[2] = orderedPositionData[i + 2];

			normals[0] = orderedNormalData[i];
			normals[1] = orderedNormalData[i + 1];
			normals[2] = orderedNormalData[i + 2];

			Triangle temp(positions, normals);
			Triangles.push_back(temp);
		}

		inputFile.close();
	}
	else
	{
		std::cerr << "WARNING: File not found: " << _filename << std::endl;
	}
}

//shading function.. for now just returns the colour of the mesh..
glm::vec3 Mesh::Shade(Light _light, glm::vec3 _intersection, glm::vec3 _camPos)
{
	glm::vec3 Normal(0, 0, 0);//normal to the surface at the intersection pt

	glm::vec3 PttoLight(0, 0, 0);//vector from the intersection pt to the light

	Normal = tri

	Normal = glm::normalize(Normal);

	PttoLight = _light.getPos() - _intersection; //vector from the intersection pt to the light source

	PttoLight = glm::normalize(PttoLight);

	glm::vec3 reColor; //color to be returned

	switch (surfType)
	{
	case Rough:

		//Diffuse lighting for rough surfaces
		reColor = Color * _light.getCol() * (glm::max(glm::dot(Normal, PttoLight), 0.0f));
		//change if overflow
		reColor.x = glm::min(reColor.x, 1.0F);
		reColor.y = glm::min(reColor.y, 1.0F);
		reColor.z = glm::min(reColor.z, 1.0F);


		return reColor;

		break;

	case Smooth:

		//Specular lighting & diffuse for smooth surfaces

		glm::vec3 PttoCam(0, 0, 0);//vector from 1st intersection pt to the camera

		PttoCam = glm::normalize(_camPos - _intersection);

		glm::vec3 Halfway(0, 0, 0);

		Halfway = glm::normalize(PttoLight + PttoCam);//the halfway vector.. used to get the reflection ray's direction

		float Facing = 0;

		if ((glm::dot(Normal, PttoLight) > 0)) //stops specular lighting on surfaces that face away from the light
		{
			Facing = 1;
		}
		else
		{
			Facing = 0;
		}

		glm::vec3 Spec = Color * _light.getCol() * Facing * float(glm::pow((glm::max(glm::dot(Normal, Halfway), 0.0f)), 20)); //specular part
		glm::vec3 Diff = Color * _light.getCol() * (glm::max(glm::dot(Normal, PttoLight), 0.0f));//diffuse part

		reColor = Spec + Diff; //add them to get the return color

		//avoid overflow
		reColor.x = glm::min(reColor.x, 1.0F);
		reColor.y = glm::min(reColor.y, 1.0F);
		reColor.z = glm::min(reColor.z, 1.0F);

		return reColor;

		break;
	}
}

int Mesh::getTrianglesSize()
{
	return Triangles.size();
}

glm::vec3 Mesh::multiplyByModelMatrix(glm::vec3 _point)
{
	glm::mat4 translationMatrix = glm::translate(glm::identity<glm::mat4>(), Position);
	glm::mat4 rotationMatrix = glm::mat4_cast(Rotation);
	glm::mat4 scaleMatrix = glm::scale(glm::identity<glm::mat4>(), Scale);

	glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	glm::vec4 point(_point, 1); // adding a w to multiple by the model matrix
	point = modelMatrix * point;

	return glm::vec3(point.x, point.y, point.z);
};