#pragma once
#include<glm/glm.hpp>

class Camera {
public:
	Camera(float aspect);
	
	void Update(float deltaTime);

	//Input hooks
	void MoveForward(float amount);
	void MoveBack(float amount);
	void MoveRight(float amount);
	void MoveLeft(float amount);

	void MoveUp(float amount);
	void MoveDown(float amount);

	void RotateRight(float degrees);
	void RotateLeft(float degrees);
	void RotateUp(float degrees);
	void RotateDown(float degrees);

	void ResetCamera();

	const glm::vec3& GetPosition() const { return position; }
	glm::mat4 GetView() const;
	glm::mat4 GetProjection() const;
private:
	void UpdateVectors();

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 worldUp;

	float yaw; //left/right
	float pitch; //up/down

	float fov;
	float aspect;
	float nearPlane;
	float farPlane;
};
