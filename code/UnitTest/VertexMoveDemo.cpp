#include "stdafx.h"
#include "VertexMoveDemo.h"


void VertexMoveDemo::Initialize()
{
	shader = new Shader(L"02_VertexColor.fx");

	vertices[0].Position = Vector3(0.0f, 0.0f, 0.0f);
	vertices[1].Position = Vector3(0.3f, 0.0f, 0.0f);

	

   

	
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(VertexColor)*2 ;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;

	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
}

void VertexMoveDemo::Destroy()
{
	SafeDelete(shader);
	
	SafeRelease(vertexBuffer);
}

void VertexMoveDemo::Update()
{
	
	
	//vertices[0].Position = position;
	//vertices[1].Position = position2;

	
	
	
	//D3D::GetDC()->UpdateSubresource(vertexBuffer, 0, NULL, vertices, sizeof(VertexColor), 0);
}

void VertexMoveDemo::Render()
{
	UINT stride = sizeof(VertexColor);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	shader->Draw(0, 0, 2);
}
