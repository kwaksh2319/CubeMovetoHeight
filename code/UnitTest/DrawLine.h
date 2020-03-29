#pragma once


class DrawLine 
{
public:
      void Initialize() ;
	 void Destroy() ;
	 void Update() ;
	
	 void Render() ;
	

	//void Position(Vector3 start, Vector3 end);
	//void Position(Vector3 point);
	//void Rotation(Vector3 rot);
	//void Sale(Vector3 scal);
private:
	Shader* shader;

	Vertex vertices[2];
	ID3D11Buffer* vertexBuffer;
	/*
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Color color = Color(0, 0, 1, 1);*/
};