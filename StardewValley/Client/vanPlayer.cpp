#include "vanPlayer.h"
#include "vanInput.h"
#include "vanTransform.h"	// Update()에서 Player 객체의 위치 옮겨준다. 때문에 Transform 객체의 값을 수정할 수 있어야 한다.

namespace van
{
	Player::Player()
	{
		// nothing
	}

	Player::~Player()
	{
		// nothing
	}

	void Player::Init()
	{
		// nothing
	}

	void Player::Update()
	{
		GameObject::Update();

		// Player 객체의 위치 수정
		
		// 1. Player 객체의 Tranfer Component로 현재 위치값 얻어온다.
		Transform* tr = GetComponent<Transform>();	// 값을 직접적으로 수정할 수 있어야 하기에 주소값으로 가져온다.
													// 참고로 Tranfer 객체는 GameObject가 생성될 때 생성된다.(GameObject 생성자 확인)
		math::Vector2 pos = tr->GetPosition();

		// 2. 키 입력을 받아 위치값 수정
		if (Input::GetKey(eKeyCode::W))	// top
		{
			if (pos.y > 0)
				pos.y -= SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::S))	// down
		{
			if (pos.y < Window_Y - DIAMETER)
				pos.y += SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::A))	// left
		{
			if (pos.x > 0)
				pos.x -= SPEED * Time::DeltaTime();
			else
				__noop;
		}
		if (Input::GetKey(eKeyCode::D))	// right
		{
			if (pos.x < Window_X - DIAMETER)
				pos.x += SPEED * Time::DeltaTime();
			else
				__noop;
		}

		// 3. 수정된 위치값을 Transfer Component에 넣어준다.
		tr->SetPosition(pos);
	}

	void Player::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}
}