#pragma once
class VertexBuffer
{
private:
	unsigned int bufferID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer() = default;

	void bind();
	void unbind();
	inline unsigned int getId() { return bufferID; };
};

