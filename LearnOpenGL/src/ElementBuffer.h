#pragma once
class ElementBuffer
{
private:
	unsigned int bufferID;
	int count;
public:
	ElementBuffer(const unsigned int* data, int count);
	~ElementBuffer() = default;

	void bind();
	void unbind();
	inline unsigned int getId() { return bufferID; };
	inline int getCount() { return count; };
};

