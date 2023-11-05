#pragma once

#include <glad/glad.h>

namespace RenderEngine {
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
		void init(const void* data, const unsigned int count); //��������� ������ �� ������
		
		//������� ��� �������� � ������� ������
		void bind() const;
		void unBind() const;

		unsigned int getCount() const { return m_count; };

	private:
		GLuint m_id;
		//
		unsigned int m_count;
	};
}

