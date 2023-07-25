#include "vanFloor.h"
#include "vanPlayer.h"
#include "vanCollider.h"
#include "vanTransform.h"
#include "vanRigidBody.h"

namespace van
{
	Floor::Floor()
	{
		// nothing
	}

	Floor::~Floor()
	{
		// nothing
	}

	void Floor::Init()
	{
		// nothing
	}

	void Floor::Update()
	{
		GameObject::Update();
	}

	void Floor::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Floor::OnCollisionEnter(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());	// Collider 속성을 통해 해당 GameObject 객체의 정보를 가져온다
		Transform* tr = player->GetComponent<Transform>();			// Transform
		RigidBody* rb = player->GetComponent<RigidBody>();			// RigidBody
		math::Vector2 objPos = tr->GetPosition();					// Floor 객체와 충돌한 객체의 위치값 저장

		float gap = fabs(_other->GetPos().y - this->GetComponent<Collider>()->GetPos().y);	// 현재 프레임에서 충돌체들의 떨어져있는 거리 (중심좌표 기준)
		float mazino = fabs(_other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);	// 두물체가 떨어져가 떨어져있기 위한 최소거리

		if (gap < mazino)	// 두 물체가 겹쳐 있는 경우
		{
			objPos.y -= (mazino - gap) - 1.0f;
			tr->SetPosition(objPos);
		}
		else  // 두 물체가 겹치지 않은 경우
		{
			__noop;
		}

		rb->SetGround(true);	// Floor 객체와 충돌한 객체가 땅에 붙어있는 상태로 만들어준다.
								// Floor 와 충돌 == 땅에 붙어있다.
	}

	void Floor::OnCollisionStay(Collider* _other)
	{

	}

	void Floor::OnCollisionExit(Collider* _other)
	{

	}
}