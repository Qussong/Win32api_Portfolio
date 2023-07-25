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
		Player* player = dynamic_cast<Player*>(_other->GetOwner());	// Collider �Ӽ��� ���� �ش� GameObject ��ü�� ������ �����´�
		Transform* tr = player->GetComponent<Transform>();			// Transform
		RigidBody* rb = player->GetComponent<RigidBody>();			// RigidBody
		math::Vector2 objPos = tr->GetPosition();					// Floor ��ü�� �浹�� ��ü�� ��ġ�� ����

		float gap = fabs(_other->GetPos().y - this->GetComponent<Collider>()->GetPos().y);	// ���� �����ӿ��� �浹ü���� �������ִ� �Ÿ� (�߽���ǥ ����)
		float mazino = fabs(_other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);	// �ι�ü�� �������� �������ֱ� ���� �ּҰŸ�

		if (gap < mazino)	// �� ��ü�� ���� �ִ� ���
		{
			objPos.y -= (mazino - gap) - 1.0f;
			tr->SetPosition(objPos);
		}
		else  // �� ��ü�� ��ġ�� ���� ���
		{
			__noop;
		}

		rb->SetGround(true);	// Floor ��ü�� �浹�� ��ü�� ���� �پ��ִ� ���·� ������ش�.
								// Floor �� �浹 == ���� �پ��ִ�.
	}

	void Floor::OnCollisionStay(Collider* _other)
	{

	}

	void Floor::OnCollisionExit(Collider* _other)
	{

	}
}