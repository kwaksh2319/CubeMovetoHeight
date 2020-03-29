#pragma once
#include "Camera.h"

class OrbitCamera : public Camera
{
public:
	OrbitCamera();
	~OrbitCamera();

	void Update() override;

	void Render();
	void Speeds(float move, float rotation = 2.0f);
	void GetTargePoisition(Vector3 targets);

private:

	float move = 50.0f;
	float rotation = 2.0f;
	Vector3 target;
	
	float theta;
	float phi;
	double rt;
	float frt;
	float tmpRt;
	
	Vector3 val;
	Vector3 P;
};