#include "Framework.h"
#include "OrbitCamera.h"


OrbitCamera::OrbitCamera()
	: Camera()
{
	
	Position(&P);
	tmpRt = 50.0f;
	
}

OrbitCamera::~OrbitCamera()
{
	//SafeDelete(ccw);
}

void OrbitCamera::Update()
{   
	 Position(&P);
	 val = Mouse::Get()->GetMoveValue();
	
	
	// tmpRt = val.z*Time::Delta();
	 Vector3 f = Forward();
	 Vector3 u = Up();
	 Vector3 r = Right();
	 //ccw->cross(,);
	 if (Mouse::Get()->Press(1) == false)
	{
		Vector3 point;
		Vector3 R;
		
		Position(&point);
		Rotation(&R);
		if(Keyboard::Get()->Press(VK_SHIFT)){
		//if (Keyboard::Get()->Press('W')) {

			//P = P + f * move * Time::Delta();
			tmpRt= tmpRt+val.y*move * Time::Delta();


		//}
		//if (Keyboard::Get()->Press('S')) {
			//P = P - f * move * Time::Delta();
			if(tmpRt>=5){
			  tmpRt = tmpRt - val.y*move * Time::Delta();
			}
		//}
		}
		else{
		phi = R.x;//val.x*atanf(val.x / val.z);
		theta = R.y; //val.y*acosf(val.y / r);
		
		point.x = target.x - tmpRt *sinf(theta)*cos(phi);//
		point.y = target.y + tmpRt *sinf(phi);//
		point.z = target.z - tmpRt *cosf(theta)*cosf(phi);//
		//point = Vector3(target.x-rt, target.y - rt, target.z - rt);
		Position(point);
		}
		return;
	}

	

	//Vector3 f = Vector3(0, 0, 1);
	//Vector3 u = Vector3(0, 1, 0);
	//Vector3 r = Vector3(1, 0, 0);

	//Move
	{
		
		
		Position(P);
		//Rotation(R);
	}
	if (Keyboard::Get()->Press(VK_SHIFT)) {
		//if (Keyboard::Get()->Press('W')) {

			//P = P + f * move * Time::Delta();
		if (Keyboard::Get()->Press('W')) {
		tmpRt = tmpRt + move * Time::Delta();
		}

		if (Keyboard::Get()->Press('S')) {
			if (tmpRt >= 5 && val.y < 0) {
				tmpRt = tmpRt - move * Time::Delta();
			}
		}
		
		//}
	}else{
	//Rotation
	
		Vector3 R;
	
		//Position(&P);
		
		Rotation(&R);
	
		
		
		R.x = R.x + val.y * rotation * Time::Delta();
		R.y = R.y + val.x * rotation * Time::Delta();
		R.z = 0.0f;
		Rotation(R);
		phi = R.x;
		theta = R.y;
	}
		
	   
		
		P.x = target.x - tmpRt *sinf(theta)*cos(phi);
		P.y = target.y + tmpRt * sinf(phi);
		P.z = target.z - tmpRt *cosf(theta)*cosf(phi);

		

	
		
	
	
	
	Position(P);
}

void OrbitCamera::Render()
{
	ImGui::SliderFloat("theta", &theta, -10000000, 10000000);
	ImGui::SliderFloat("phi", &phi, -10000000, 10000000);
	ImGui::SliderFloat("oPositionx", &P.x, -10000000, 10000000);
	ImGui::SliderFloat("oPositiony", &P.y, -10000000, 10000000);
	ImGui::SliderFloat("oPositionz", &P.z, -10000000, 10000000);
	ImGui::SliderFloat("val.x", &val.x, -10000000, 10000000);
	ImGui::SliderFloat("val.y", &val.y, -10000000, 10000000);
	ImGui::SliderFloat("val.z", &val.z, -10000000, 10000000);

	ImGui::SliderFloat("rt", &tmpRt, -10000000, 10000000);
}

void OrbitCamera::Speeds(float move, float rotation)
{
	this->move = move;
	this->rotation = rotation;
}

void OrbitCamera::GetTargePoisition(Vector3 targets)
{
	target = targets;
}
