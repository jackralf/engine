#include "RectangleColliderComponent.h"
#include "..\Logger.h"

namespace star
{
	RectangleColliderComponent::RectangleColliderComponent(uint16 width, uint16 height):
		m_CollisionRect(0,0, width, height),
		m_bIsTrigger(false),
		BaseComponent()
	{
		Logger::GetInstance()->Log(LogLevel::Info, _T("RectCollisionComponent initialized"));
	}

	RectangleColliderComponent::~RectangleColliderComponent(void)
	{
	}

	void RectangleColliderComponent::Initialize()
	{
	}

	void RectangleColliderComponent::InitializeComponent()
	{
		m_bInitialized = true;
	}

	void RectangleColliderComponent::Update(const Context& context)
	{
		if(!m_bInitialized)
		{
			return;
		}
	}

	void RectangleColliderComponent::Draw()
	{
	}
}
