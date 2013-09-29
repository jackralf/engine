#include "StateManager.h"
#include "..\Helpers\Helpers.h"
#include "..\Context.h"
#include "State.h"

namespace star
{
	StateManager::StateManager(void)
	: m_States()
		, m_pCurrentState(nullptr)
		, m_CurrentStateName()
		, m_PreviousStateName()
	{

	}

	StateManager::~StateManager(void)
	{
		Clear();
	}

	void StateManager::Initialize()
	{
		// do nothing, sad story of one interface
	}

	void StateManager::Update(const Context& context)
	{
		if(m_pCurrentState != nullptr)
		{
			m_pCurrentState->Update(context);
		}
	}

	void StateManager::Draw()
	{
		if(m_pCurrentState != nullptr)
		{
			m_pCurrentState->Draw();
		}
	}

	void StateManager::AddState(const tstring & name, State * pState)
	{
		UINT id = star::GenerateHash(name);
		m_States[id] = pState;
	}

	bool StateManager::RemoveState(const tstring & name)
	{
		if(m_CurrentStateName == name)
		{
			DeactiveCurrentState();
		}
		UINT id = star::GenerateHash(name);
		auto it = m_States.find(id);
		if(it != m_States.end())
		{
			m_States.erase(it);
			return true;
		}
		return false;
	}

	void StateManager::Clear()
	{
		DeactiveCurrentState();
		for ( auto pair : m_States ) 
		{
			delete pair.second;
		}
		m_States.clear();
		m_pCurrentState = nullptr;
	}

	void StateManager::SetState(const tstring & name)
	{
		DeactiveCurrentState();
		UINT id = star::GenerateHash(name);

		m_pCurrentState = m_States[id];
		if(!m_pCurrentState->IsActive())
		{
			m_pCurrentState->Activate();
		}
		m_PreviousStateName = m_CurrentStateName;
		m_CurrentStateName= name;
	}	

	void StateManager::SetPreviousState()
	{
		SetState(m_PreviousStateName);
	}

	void StateManager::DeactiveCurrentState()
	{
		if(m_pCurrentState != nullptr && m_pCurrentState->IsActive())
		{
			m_pCurrentState->Deactivate();
			m_pCurrentState = nullptr;
		}
	}
}
