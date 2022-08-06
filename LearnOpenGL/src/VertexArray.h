#pragma once
class VertexArray
{
private:
	unsigned int arrayID;
public:
	VertexArray();
	~VertexArray() = default;

	void bind();
	void unbind();
	inline unsigned int getId() { return arrayID; };
};

