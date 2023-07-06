#pragma once
// �����Ǵ� ���̺귯��
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>	// �Լ� ������
#include <string>
#include "framework.h"

// �������� ���̺귯��
#include "vanMath.h"
#include "vanTime.h"

// ��ũ�� ����
#define SPEED		500.0f
#define DIAMETER	200
	/*
		[ �ػ� ]
		- HD	1280��720
		- FHD	1920x1080
	*/
#define FHD_X		/*1920*/ 1280
#define FHD_Y		/*1080*/ 720

// ?
namespace van::enums
{
	enum class eLayerType
	{
		Background,		// 0
		Player,
		Monster,
		Effect,
		UI,
		End,			// 5
	};

	enum class eComponentType
	{
		Transform,		// 0
		SpriteRenderer,
		End,			// 2
	};

	enum class eSceneType
	{
		TitleScene,		// 0 
		FirstStage,
		SecondStage,
		End,			// 3
	};
}