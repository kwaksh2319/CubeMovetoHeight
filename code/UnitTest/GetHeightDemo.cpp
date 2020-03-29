#include "stdafx.h"
#include "GetHeightDemo.h"
#include"CubeTmp.h"

void GetHeightDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(4, 0, 0);
	Context::Get()->GetCamera()->Position(29, 6, -19);
	((OrbitCamera *)Context::Get()->GetCamera())->Speeds(20, 2);
	//((Freedom *)Context::Get()->GetCamera())->Speed(20, 2);

	shader = new Shader(L"11_Terrain.fx");

	terrain = new Terrain(shader, L"Terrain/Gray256.png");
	terrain->BaseMap(L"Terrain/Dirt3.png");


	triShader = new Shader(L"05_World.fx");
	cube = new CubeTmp();
	Vertex vertices[6];
	vertices[0].Position = Vector3(+0, +1, 0);
	vertices[1].Position = Vector3(+3, +1, 0);

	vertices[2].Position = Vector3(+0, +1, 0);
	vertices[3].Position = Vector3(+0, +1, +3);

	vertices[4].Position = Vector3(+0, +1, 0);
	vertices[5].Position = Vector3(+0, +4, 0);
	//vertices[2].Position = Vector3(+1, +0, 0);

	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(Vertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}
}

void GetHeightDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(terrain);

	SafeDelete(triShader);
	SafeRelease(vertexBuffer);

	SafeDelete(cube);
}

void GetHeightDemo::Update()
{
	terrain->Update();
	Vector3 tmpCubPoint = cube->Position();
	
	tmpCubPoint.y=terrain->GetHeight(tmpCubPoint);//높이
	
	vector<UINT>tmpIndex=terrain->GetIndex(tmpCubPoint);//index
	
	
	cube->Position(tmpCubPoint);//cube 높이 업데이트 
    
	cube->GetIndex(tmpIndex);
	
	cube->GetNormData(terrain->NormData());
	


	cube->Update();
	position = cube->Position();
	Vector3 rot = cube->Rotation();
	/*
	if (Keyboard::Get()->Press(VK_RIGHT))
		position.x += 20.0f * Time::Delta();
	else if (Keyboard::Get()->Press(VK_LEFT))
		position.x -= 20.0f * Time::Delta();

	if (Keyboard::Get()->Press(VK_UP))
		position.z += 20.0f * Time::Delta();
	else if (Keyboard::Get()->Press(VK_DOWN))
		position.z -= 20.0f * Time::Delta();
		
	position.y = terrain->GetHeight(position) + 1.0f;
	*/
	
	Matrix R, T;
	D3DXMatrixRotationYawPitchRoll(&R, rot.y, rot.x, rot.z);
	
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	Matrix world = R * T;

	//triShader->AsVector("Color")->SetFloatVector(color)
	triShader->AsMatrix("World")->SetMatrix(world);
	triShader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	triShader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void GetHeightDemo::Render()
{
	terrain->Render();
	cube->Render();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	triShader->Draw(0, 0, 6);
	ImGui::SliderFloat("LinePointX", &position.x, -10000000, 100000000);
	ImGui::SliderFloat("LinePointY", &position.y, -10000000, 100000000);
	ImGui::SliderFloat("LinePointZ", &position.z, -10000000, 100000000);

	string str = to_string(position.x) + ", " + to_string(position.y) + ", " + to_string(position.z);
	Gui::Get()->RenderText(5, 60, str);
}
