#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name) : GameObject(name)
{
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
	cellCount = count;
	cellSize = size;

	// VertexArray �ʱ�ȭ
	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4);

	// ��, �� ��� ��, �� �ϴ� Ÿ�� �ϳ��� ������
	sf::Vector2f posOffset[4] =
	{
		{ 0.f,0.f },		// �� ���
		{ size.x, 0.f },	// �� ���
		{ size.x, size.y }, // �� �ϴ�
		{ 0.f,size.y }		// �� �ϴ�
	};

	// �� ó�� Ÿ���� ��ǥ
	sf::Vector2f texCoords[4] =
	{
		{ 0.f, 0.f },
		{ 50.f, 0.f },
		{ 50.f, 50.f },
		{ 0.f, 50.f }
	};
	
	for (int i = 0; i < count.y; i++)
	{
		for (int j = 0; j < count.x; j++)
		{
			int texIndex = Utils::RandomRange(0, 3);
			if (i == 0 || j == 0 || i == count.y - 1 || j == count.x - 1)  // ������ Ÿ��
			{
				texIndex = 3;    // ������ ����
			}

			int quadIndex = i * count.x + j;			   // VertexArray �ε���
			sf::Vector2f quadPos(j * size.x, i * size.y);  // j = 0 * 50 = 0, i = 0 * 50 = 0

			for (int k = 0; k < 4; k++)
			{
				int vertexIndex = quadIndex * 4 + k;	// �� ��° �������� �˷��ִ� �ڵ�
				va[vertexIndex].position = quadPos + posOffset[k];    // ȭ�鿡 ������ ��ǥ ����
				va[vertexIndex].texCoords = texCoords[k];			  // Ÿ�� ��Ʈ�� ��ǥ �ʱ�ȭ
				va[vertexIndex].texCoords.y += texIndex * 50.f;		  // Ÿ�� ���ϴ� �ڵ�
			}
		}
	}
		
}

void TileMap::UpdateTransform() // ���� �������� ����
{
	transform = sf::Transform::Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}

void TileMap::Init()
{
	// ���̾� �� �ڿ� ����
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;

	Set({ 50, 50 }, { 50.f, 50.f });
}

void TileMap::Release()
{
}

void TileMap::Reset()
{
	texture = &TEXTURE_MGR.Get(spriteSheetId);

	SetOrigin(Origins::MC);
	SetScale({ 1.f,1.f });
	SetPosition({ 0.f,0.f });
}

void TileMap::Update(float dt)
{
}

void TileMap::Draw(sf::RenderWindow& window)
{
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;
	window.draw(va, state);
}

bool TileMap::IsCollision(sf::FloatRect rect)  
{  
	return 0;
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
}

void TileMap::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
}

void TileMap::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
}

void TileMap::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	// ��ü Ÿ���� ������ ����� ��� �ڵ�
	if (preset != Origins::Custom)
	{
		sf::FloatRect rect;
		rect.width = cellCount.x * cellSize.x;
		rect.height = cellCount.y * cellSize.y;

		origin.x = rect.width * ((int)preset % 3) * 0.5f;
		origin.y = rect.height * ((int)preset / 3) * 0.5f;
	}
}
