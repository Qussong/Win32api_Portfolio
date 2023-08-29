#pragma once
#include "vanScene.h"
#include "vanYggdrasill.h"

namespace van
{
	class Stage1BossScene : public Scene
	{
	public:
		Stage1BossScene();
		virtual ~Stage1BossScene();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void SceneIN() override;
		virtual void SceneOut() override;
		virtual void CameraMove() override;
		virtual void MakeWorld() override;
		virtual void MakeFloor() override;
		virtual void MakeWall() override;
		virtual void MakeDoor() override;

		void BossTurn();

	private:
		Yggdrasill* mYgg;
		bool mbPhase1 = true;
		bool mbPhase2 = true;
	};
}

