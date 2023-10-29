#pragma once

#include <glad/glad.h>

namespace Renderer {
	class IndexBuffer {
	public:
		//�����������
		IndexBuffer();
		//����������
		~IndexBuffer();

		//�������
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;

		IndexBuffer& operator=(IndexBuffer&& indexBuffer);
		IndexBuffer(IndexBuffer&& indexBuffer) noexcept;

		//������� ��� ����������� EBO
		void init(const void* data, const unsigned int size); //��������� ������ �� ������
		
		//������� ��� �������� � ������� ������
		void bind() const;
		void unBind() const;

	private:
		GLuint m_id;
	};
}

