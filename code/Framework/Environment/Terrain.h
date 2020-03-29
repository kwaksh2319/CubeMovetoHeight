#pragma once

class Terrain
{
public:
	typedef VertexTextureNormal TerrainVertex;

public:
	Terrain(Shader* shader, wstring heightFile);
	~Terrain();

	void Update();
	void Render();

	void BaseMap(wstring file);

	void Pass(UINT val) { pass = val; }

	float GetHeight(Vector3& position);
	vector<UINT> GetIndex(Vector3& position);
	vector<Vector3>NormData();
	vector<Vector3>HeightData();
	float GetVerticalRaycast(Vector3& position);
private:
	void CreateVertexData();
	void CreateIndexData();
	void CreateNormalData();
	void CreateBuffer();

private:
	UINT pass = 0;
	Shader* shader;
	vector<Vector3>normData;
	vector<Vector3>heightData;
	
	UINT width, height;

	UINT vertexCount;
	TerrainVertex* vertices;
	ID3D11Buffer* vertexBuffer;

	UINT indexCount;
	UINT* indices;
	ID3D11Buffer* indexBuffer;

	Texture* heightMap;
	Texture* baseMap = NULL;
};
