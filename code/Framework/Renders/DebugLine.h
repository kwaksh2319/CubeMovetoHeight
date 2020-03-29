#pragma once
#define MAX_DEBUG_LINE 150000

class DebugLine
{
public:
	friend class Window;

private:
	static void Create();
	static void Delete();

public:
	static DebugLine* Get();

public:
	void RenderLine(Vector3& start, Vector3& end);
	void RenderLine(Vector3& start, Vector3& end, float r, float g, float b);
	void RenderLine(Vector3& start, Vector3& end, Color& color);
	void RenderLine(Vector3& start, Vector3& end, Color& color, Vector3 position);
	void RenderLine(float x, float y, float z, float x2, float y2, float z2);
	void RenderLine(float x, float y, float z, float x2, float y2, float z2, float r, float g, float b);
	void RenderLine(float x, float y, float z, float x2, float y2, float z2, Color& color);

private:
	void Update();
	void Render();


private:
	DebugLine();
	~DebugLine();

private:
	static DebugLine* instance;

private:
	Shader* shader;

	Matrix world;

	ID3D11Buffer* vertexBuffer;
	VertexColor* vertices;

	UINT drawCount = 0;
	Vector3 position;
	Vector3 rotation;
	Vector3 scale=Vector3(1.0f, 1.0f, 1.0f);

public:
	void Position(Vector3 poi);
	void Rotation(Vector3 rot);
	void Scale(Vector3 sca);
};