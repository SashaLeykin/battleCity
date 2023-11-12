#pragma once

#include "Sprite.h"

#include <map>
#include <vector>

namespace RenderEngine {	

	class AnimatedSprite : public Sprite {
	public:
		AnimatedSprite(std::shared_ptr<Texture2D> pTexture,
			 std::string initialSubTexturw,
			 std::shared_ptr<ShaderProgram> pShaderProgram);

		//��� ��������� ������ ���������
		void insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration);

		void render(const glm::vec2& position, const glm::vec2& size, const float rotation) const override;

		//������� ����� ������������� ����������� ��������� �����
		void setState(const std::string& newState);

		//������� ����� ���������
		void update(const uint64_t delta);

	private:
		//��� �������� ��������� � ������������ ������ ������� 
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> m_stateMap;
		//
		size_t m_currentFrame = 0;
		//����� ��������� � ������ ���������
		uint64_t m_currentAnimationTame = 0;

		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator m_currentAnimationDuration;

		//�������� ��������� (mutable - ����������� ������ ��� ����� �������)
		mutable bool m_dirty = false;

	};
}