#include "stdafx.h"
#include "CubeTmp.h"



CubeTmp::CubeTmp()
{
	Initialize();
	

}

CubeTmp::~CubeTmp()
{
	
	Destroy();
	
}

void CubeTmp::Initialize()
{
	shader = new Shader(L"07_Cube.fx");

	
	vertexCount = 24;
	vertices = new Vertex[vertexCount];


	float w = 0.5f, h = 0.5f, d = 0.5;

	//Front
	vertices[0].Position = Vector3(-w, -h, -d);
	vertices[1].Position = Vector3(-w, +h, -d);
	vertices[2].Position = Vector3(+w, -h, -d);
	vertices[3].Position = Vector3(+w, +h, -d);

	//Back
	vertices[4].Position = Vector3(-w, -h, +d);
	vertices[5].Position = Vector3(+w, -h, +d);
	vertices[6].Position = Vector3(-w, +h, +d);
	vertices[7].Position = Vector3(+w, +h, +d);

	//Top
	vertices[8].Position = Vector3(-w, +h, -d);
	vertices[9].Position = Vector3(-w, +h, +d);
	vertices[10].Position = Vector3(+w, +h, -d);
	vertices[11].Position = Vector3(+w, +h, +d);

	//Bottom
	vertices[12].Position = Vector3(-w, -h, -d);
	vertices[13].Position = Vector3(+w, -h, -d);
	vertices[14].Position = Vector3(-w, -h, +d);
	vertices[15].Position = Vector3(+w, -h, +d);

	//Left
	vertices[16].Position = Vector3(-w, -h, +d);
	vertices[17].Position = Vector3(-w, +h, +d);
	vertices[18].Position = Vector3(-w, -h, -d);
	vertices[19].Position = Vector3(-w, +h, -d);

	//Right
	vertices[20].Position = Vector3(+w, -h, -d);
	vertices[21].Position = Vector3(+w, +h, -d);
	vertices[22].Position = Vector3(+w, -h, +d);
	vertices[23].Position = Vector3(+w, +h, +d);
	

	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(Vertex) * vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}
	

	indexCount = 36; 
	indices = new UINT[indexCount]
	{
		0, 1, 2, 2, 1, 3,
		4, 5, 6, 6, 5, 7,
		8, 9, 10, 10, 9, 11,
		12, 13, 14, 14, 13, 15,
		16, 17, 18, 18, 17, 19,
		20, 21, 22, 22, 21, 23,
	};
	
	//Create IndexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT) * indexCount;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
	}


	D3DXMatrixIdentity(&world);
}

void CubeTmp::Destroy()
{
	SafeDelete(shader);

	SafeDeleteArray(vertices);
	SafeRelease(vertexBuffer);

	SafeDeleteArray(indices);
	SafeRelease(indexBuffer);
}

void CubeTmp::Update()
{
	ImGui::SliderFloat("Speed", &speed, 5, 20);
	((OrbitCamera *)Context::Get()->GetCamera())->GetTargePoisition(position);
	//Vector3 normal = terrain->GetNormal(position);

	if (Keyboard::Get()->Press(VK_SHIFT))
	{
		if (Keyboard::Get()->Press(VK_RIGHT))
			rotation.y += speed * Time::Delta();
		else if (Keyboard::Get()->Press(VK_LEFT))
			rotation.y -= speed * Time::Delta();

		if (Keyboard::Get()->Press(VK_UP))
			rotation.x += speed * Time::Delta();
		else if (Keyboard::Get()->Press(VK_DOWN))
			rotation.x -= speed * Time::Delta();
	}
	else
	{
		
		
		if (Keyboard::Get()->Press(VK_RIGHT)){
			
			rotation.y += speed * Time::Delta();
		}
		else if (Keyboard::Get()->Press(VK_LEFT)){
			rotation.y -= speed  * Time::Delta();
		}

		if (Keyboard::Get()->Press(VK_UP)){

			//position.x+= speed * sinf(rotation.y)* Time::Delta();
			//////////////////
	        position.z += speed* cosf(rotation.y)* cosf(rotation.x)* Time::Delta();
			position.x += speed * sinf(rotation.y)*cos(rotation.x)* Time::Delta();
			////////////////////
			
		
			//position.x += speed * cosf(rotation.y)*cosf(rotation.x)* Time::Delta();
			//position.y += speed * sinf(rotation.y)* Time::Delta();// *cosf(rotation.x)* Time::Delta();
		    //오일러 앵글
			
		
		
		
		}
		else if (Keyboard::Get()->Press(VK_DOWN)){

			//position.x -= speed * sinf(rotation.y)* Time::Delta();
			/////////////////
			position.z -= speed * cosf(rotation.y)* cosf(rotation.x) * Time::Delta();
			position.x -= speed * sinf(rotation.y)*cos(rotation.x)* Time::Delta();
			/////////////////////////
			//position.y -= speed * sinf(rotation.y)* Time::Delta();
			 
		}
		
		
		
		//y축 기준으로 xy 벡터 회전 각도 계산  atanf(y/x)
		//rotation.x = -atanf(avgNorm.x / avgNorm.y);// *360 / D3DX_PI * 2;
		//rotation.z = atanf(avgNorm.z/ avgNorm.y);// *360 / D3DX_PI * 2;
		//rotation.x = -atan2f(avgNorm.x, avgNorm.y);
		//rotation.z = atan2f(avgNorm.z, avgNorm.y);

		//y회전 메트릭스 y축으로 기준으로 x,z 회전 벡터 구하기 
		float rotVectorx = cosf(rotation.y)*avgNorm.z + sinf(rotation.y)*avgNorm.x; //x와 z 회전 벡터 
		
		float rotVectorz = -sinf(rotation.y)*avgNorm.z+ cosf(rotation.y)*avgNorm.x ;//x와 z 회전 벡터 

		//y축 기준으로 xz 회전된 벡터  y 사이 각도 계산  atanf(y/x)
		rotation.x = atanf(rotVectorx/ avgNorm.y);// *360 / D3DX_PI * 2; //y축 벡터와 x와 z 회전 벡터의 각도 
		rotation.z = -atanf(rotVectorz/ avgNorm.y);
     
		//rotation.z = -atanf(gamma /avgNorm.y);// *360 / D3DX_PI * 2; //x축 벡터와 y와 z회전 벡터의 각도 

	

		//rotation.x = avgNorm.z *cosf(rotation.y)* cosf(rotation.x);
		//rotation.z = avgNorm.z *sinf(rotation.y)*cosf(rotation.x);
		//rotation.x = avgNorm.z *cosf(rotation.y)* cosf(rotation.x);
		//rotation.z = avgNorm.z *sinf(rotation.y)*cosf(rotation.x);

		//rotation.x = avgNorm.z * acosf(rotation.z);
		
		//rotation.x = avgNorm.z *atan2(position.y, position.z);

		//result.x = atan2((p[3].y - p[2].y), (p[3].z - p[2].z));
		//result.z = atan2((p[3].y - p[1].y), (p[3].x - p[1].x));
		

		



	}

	
	
	Matrix S,R, T;
	D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&T, position.x, position.y + 1.0f, position.z);
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z*2);

	world = S* R * T;


	shader->AsVector("Color")->SetFloatVector(color);
	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void CubeTmp::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	static bool bWireframe = true;
	ImGui::Checkbox("CubeWireframe", &bWireframe);
	ImGui::SliderFloat("avgNormX", &avgNorm.x,-10000000,100000000);
	ImGui::SliderFloat("avgNormY", &avgNorm.y, -10000000, 100000000);
	ImGui::SliderFloat("avgNormZ", &avgNorm.z, -10000000, 100000000);
	ImGui::SliderFloat("rotX", &rotation.x, -10000000, 100000000);
	ImGui::SliderFloat("rotY", &rotation.y, -10000000, 100000000);
	ImGui::SliderFloat("rotZ", &rotation.z, -10000000, 100000000);
	shader->DrawIndexed(0, bWireframe == true ? 1 : 0, indexCount);
}

void CubeTmp::Position(Vector3 position)
{
	this->position = position;
}

void CubeTmp::Rotation(Vector3 rotation)
{
	this->rotation = rotation;
}

void CubeTmp::GetNormData(vector<Vector3> norm)
{
	Vector3 tmp[4];
	for(int i=0;i<4;i++){
	tmp[i] = norm[index[i]];
	}
	
	avgNorm = (tmp[0] + tmp[1] + tmp[2] + tmp[3]) / 4;

	//normData = norm;
}

void CubeTmp::GetIndex(vector<UINT> index)
{
	this->index = index;
}

Vector3 CubeTmp::EulerAngle(Vector3 position)
{



	return Vector3();
}
