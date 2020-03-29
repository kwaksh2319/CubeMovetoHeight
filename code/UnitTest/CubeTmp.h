#pragma once

class CubeTmp 
{
public:
	CubeTmp();
	~CubeTmp();
	void Initialize();
	 void Destroy();
	void Update();
	//virtual void PreRender() override {}
	 void Render();
	 
	//virtual void PostRender() override {}
	//virtual void ResizeScreen() override {}

private:
	Shader* shader;
	Vector3 avgNorm;
	UINT vertexCount;
	Vertex* vertices;
	ID3D11Buffer* vertexBuffer;

	UINT indexCount;
	UINT* indices;
	ID3D11Buffer* indexBuffer;

	float speed = 10.0f;
	Vector3 position = Vector3(0, 0, 0);
	Vector3 scale = Vector3(1, 1, 1);
	Vector3 rotation = Vector3(0, 0, 0);
	vector<Vector3>normData;
	vector<UINT>index;
	Matrix world;
	Color color = Color(1, 0, 0, 1);
	


public:
	void Position(Vector3  position);
	Vector3  Position() { return position; }

	void Rotation(Vector3  rotation);
	Vector3 Rotation() { return rotation; }
	void GetNormData(vector<Vector3>norm);
	void GetIndex(vector<UINT>index);
	Vector3 EulerAngle(Vector3 position);
};