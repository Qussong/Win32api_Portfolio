#include "vanYggdrasillHead.h"
#include "vanAnimator.h"
#include "vanResourceManager.h"
#include "vanTexture.h"
#include "vanCollider.h"

#include "vanYggdrasill.h"

#define INIT_POS_X	-10.0f
#define INIT_POS_Y	-60.0f
#define IDLE_SPEED	15.0f
#define SHAKE_SPEED	50.0f
#define SHOOT_MAGICORB_SHAKE_SPEED 200.0f

namespace van
{
	YggdrasillHead::YggdrasillHead()
	{
		// nothing
	}

	YggdrasillHead::~YggdrasillHead()
	{
		// nothing
	}

	void YggdrasillHead::Init()
	{
		GameObject::Init();

		MakeAnimation();

		Animator* at = GetComponent<Animator>();
		at->SetScale(math::Vector2(2.0f, 2.0f));
		at->PlayAnimation(L"Head", true);

		Collider* col = GetComponent<Collider>();
		col->SetSize(math::Vector2(200.0f, 300.0f));
		col->SetOffset(math::Vector2(25.0f, 40.0f));

		mInitAddPos = math::Vector2(INIT_POS_X, INIT_POS_Y);
		mAddPos = mInitAddPos;
	}

	void YggdrasillHead::Update()
	{
		GameObject::Update();

		FollowBodyPos();

		if (mPastState != mState)
		{
			mbPlayAnimation = true;
			// 행동패턴의 수행이 끝났음을 알리는 mbEnd를 초기화
			if (mbEnd == true)
			{
				mbEnd = false;
			}
		}

		switch (mState)
		{
		case HeadState::Gen:
			Gen();
			break;
		case HeadState::Idle:
			Idle();
			break;
		case HeadState::AttackReady:
			AttackReady();
			break;
		case HeadState::Attack:
			Attack();
			break;
		case HeadState::AttackEnd:
			AttackEnd();
			break;
		case HeadState::Dead:
			Dead();
			break;
		default:
			__noop;
		}

		mPastState = mState;	// 현재의 상태와 미래의 상태를 비교하여 애니메이션 재생여부를 결정한다.(다르면 mPlayAnimation = true)
	}

	void YggdrasillHead::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void YggdrasillHead::MakeAnimation()
	{
		Animator* at = GetComponent<Animator>();
		at->CreateAnimation(L"Head", ResourceManager::Find<Texture>(L"Yggdrasill_Head"), math::Vector2(0.0f, 0.0f), math::Vector2(241.0f, 168.0f), 2, math::Vector2::Zero, 1.0F);
	}
	
	void YggdrasillHead::OnCollisionEnter(Collider* _other)
	{
		// 피격판정
	}

	void YggdrasillHead::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void YggdrasillHead::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void YggdrasillHead::Gen()
	{
	}

	void YggdrasillHead::Idle()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		mTime += Time::GetDeltaTime();
		if (mTime >= 1.0f)
		{
			mTime = 0.0f;
			if (mUpDownFlag == false)
			{
				mUpDownFlag = true;
			}
			else
			{
				mUpDownFlag = false;
			}
		}

		if (mUpDownFlag == true)
		{
			mAddPos.y += IDLE_SPEED * Time::GetDeltaTime();
		}
		else
		{
			mAddPos.y -= IDLE_SPEED * Time::GetDeltaTime();
		}
	}

	void YggdrasillHead::AttackReady()
	{
		Yggdrasill* boss = dynamic_cast<Yggdrasill*>(mOwner);

		if (boss == nullptr)
		{
			return;
		}

		switch (boss->GetAttackCase())
		{
		case Yggdrasill::BossSkill::FistSlam:
			FistSlamReady();
			break;
		case Yggdrasill::BossSkill::Swipe:
			SwipeReady();
			break;
		case Yggdrasill::BossSkill::MagicOrbs:
			MagicOrbsReady();
			break;
		default:
			__noop;
		}
	}

	void YggdrasillHead::Attack()
	{
		Yggdrasill* boss = dynamic_cast<Yggdrasill*>(mOwner);

		if (boss == nullptr)
		{
			return;
		}

		switch (boss->GetAttackCase())
		{
		case Yggdrasill::BossSkill::FistSlam:
			FistSlamAttack();
			break;
		case Yggdrasill::BossSkill::Swipe:
			SwipeAttack();
			break;
		case Yggdrasill::BossSkill::MagicOrbs:
			MagicOrbsAttack();
			break;
		default:
			__noop;
		}
	}

	void YggdrasillHead::AttackEnd()
	{
		Yggdrasill* boss = dynamic_cast<Yggdrasill*>(mOwner);

		if (boss == nullptr)
		{
			return;
		}

		switch (boss->GetAttackCase())
		{
		case Yggdrasill::BossSkill::FistSlam:
			FistSlamEnd();
			break;
		case Yggdrasill::BossSkill::Swipe:
			SwipeEnd();
			break;
		case Yggdrasill::BossSkill::MagicOrbs:
			MagicOrbsEnd();
			break;
		default:
			__noop;
		}
	}

	void YggdrasillHead::Dead()
	{
	}

	void YggdrasillHead::FistSlamReady()
	{
	}

	void YggdrasillHead::SwipeReady()
	{
	}

	void YggdrasillHead::MagicOrbsReady()
	{
		Transform* tr = GetComponent<Transform>();

		if (mbEnd == false)
		{
			mAddPos.y += 100.0f * Time::GetDeltaTime();

			float gap = fabs(mInitAddPos.y - mAddPos.y);
			if (gap >= 30.0f)
			{
				mbFinish = true;
				mbEnd = true;
			}
		}
	}

	void YggdrasillHead::FistSlamAttack()
	{
	}

	void YggdrasillHead::SwipeAttack()
	{
	}

	void YggdrasillHead::MagicOrbsAttack()
	{
		Transform* tr = GetComponent<Transform>();

		if (mbEnd == false)
		{
			mAddPos.y -= 700.0f * Time::GetDeltaTime();

			float gap = fabs(mInitAddPos.y - mAddPos.y);
			if (gap >= 120.0f)
			{
				mbFinish = true;
				mbEnd = true;
			}
		}
	}

	void YggdrasillHead::FistSlamEnd()
	{
	}

	void YggdrasillHead::SwipeEnd()
	{
	}

	void YggdrasillHead::MagicOrbsEnd()
	{
		/*Transform* tr = GetComponent<Transform>();
		Transform* tr_owner = GetOwner()->GetComponent<Transform>();
		math::Vector2 ownerPos = tr_owner->GetPosition();

		if (mbEnd == false)
		{
			mAddPos.y += 50.0f * Time::GetDeltaTime();

			float gap = mInitAddPos.y - mAddPos.y;
			if (gap <= 0.0f)
			{
				mbFinish = true;
				mbEnd = true;
			}
		}*/
		InitHeadPos();
	}

	void YggdrasillHead::FollowBodyPos()
	{
		Transform* tr = GetComponent<Transform>();
		Transform* tr_owner = GetOwner()->GetComponent<Transform>();
		math::Vector2 ownerPos = tr_owner->GetPosition();

		math::Vector2 newPos = ownerPos + mAddPos;
		
		tr->SetPosition(newPos);
	}

	void YggdrasillHead::ShakeHead()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		mTime += Time::GetDeltaTime();
		if (mTime >= 0.05f)
		{
			mTime = 0.0f;
			if (mUpDownFlag == false)
			{
				mUpDownFlag = true;
			}
			else
			{
				mUpDownFlag = false;
			}
		}

		if (mUpDownFlag == true)
		{
			mAddPos.y += SHAKE_SPEED * Time::GetDeltaTime();
		}
		else
		{
			mAddPos.y -= SHAKE_SPEED * Time::GetDeltaTime();
		}
	}

	void YggdrasillHead::ShootEnerge()
	{
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();

		mTime += Time::GetDeltaTime();
		if (mTime >= 0.1f)
		{
			mTime = 0.0f;
			++mMagicOrbShootMotion;
		}

		if (mMagicOrbShootMotion == 0)
		{
			mAddPos.y -= SHOOT_MAGICORB_SHAKE_SPEED * Time::GetDeltaTime();
		}
		else if(mMagicOrbShootMotion == 1)
		{
			mAddPos.y += SHOOT_MAGICORB_SHAKE_SPEED * Time::GetDeltaTime();
		}
		else
		{
			mbMagicOrbShoot = true;
		}
	}

	void YggdrasillHead::InitHeadPos()
	{
		//Transform* tr = GetComponent<Transform>();
		//Yggdrasill* owner = dynamic_cast<Yggdrasill*>(GetOwner());
		//math::Vector2 ownerInitPos = owner->GetInitPos();

		//math::Vector2 goalPos = ownerInitPos + mInitAddPos;
		//math::Vector2 nowPos = tr->GetPosition();
		if (mbEnd == false)
		{
			mbFinish = false;
			mAddPos.y += 50.0f * Time::GetDeltaTime();

			float goalPosY = mInitAddPos.y;
			float nowPosY = mAddPos.y;

			if (goalPosY - nowPosY <= 0)
			{
				mbFinish = true;
				mbEnd = true;
			}

		}
	}
}