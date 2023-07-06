#include "vanApplication.h"
#include "vanInput.h"		// Update���� key���� ���� ó���� ���ֱ����� �߰�
#include "vanTime.h"		// Update���� Time ���� ����ϱ� ���� �߰�

#include "vanSceneManager.h"

namespace van
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		//, mWidth(0)
		//, mHeight(0)
		, mBackBuffer(NULL)
		, mBackHdc(NULL)
	{
	}

	Application::~Application()
	{
	}

	void Application::Init(HWND hwnd) 
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);									// WinUser.h
		//mWidth = 1600;										// FHD_X �� ��ü
		//mHeight = 900;										// FHD_Y �� ��ü

		RECT rect = { 0, 0, FHD_X, FHD_Y };						// ���� ������ ũ�� 
																//	-> �ش� ũ�Ⱑ Ŭ���̾�Ʈ ������ ũ�Ⱑ �Ǳ� ����
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);	// ���� �������� ũ�Ⱑ Ŭ���̾�Ʈ ������ �ǵ��� ũ�⸦ ����

		// rect ������ ������ ������� ������ ������ ����
		SetWindowPos(mHwnd, nullptr,
					0, 0,										// ������ ��ġ (x,y)
					rect.right - rect.left,						// ������ ũ��(����)
					rect.bottom - rect.top,						// ������ ũ��(����)
					0);											// ?
		ShowWindow(mHwnd, true);

		mBackBuffer 
			= CreateCompatibleBitmap(mHdc, FHD_X, FHD_Y);		// ������ �ػ� ������ ��Ʈ�� ����

		mBackHdc = CreateCompatibleDC(mHdc);					// ���� ������ ��Ʈ���� ����Ű�� DC ����

		HBITMAP defaultBitmap									// ���� ������ ��Ʈ�ʰ� DC�� ���� ����
			= (HBITMAP)SelectObject(mBackHdc, mBackBuffer);		// �̶� DC�� ������ �ִ� �⺻ ��Ʈ���� ��ȯ�ȴ�.
		DeleteObject(defaultBitmap);							// ��ȯ�� �⺻ ��Ʈ���� ����� ���̾��⿡ �޸� ����

		Time::Init();
		Input::Init();											
		SceneManager::Init();
	}

	void Application::Proc()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		SceneManager::Update();
	}

	void Application::Render()
	{
		/*	
			2��° ��Ʈ�ʿ� ū �簢���� �׷��ش�.
			�翷���� 1�� ���� �簢���� ���� ���� : 
			�׵θ� ���� ���̱� ������ �� ���̰� �Ϸ���
		*/
		Rectangle(mBackHdc, -1, -1, FHD_X + 1, FHD_Y + 1);			
		Time::Render(mBackHdc);

		SceneManager::Render(mBackHdc);
		// 2�� ��Ʈ��(mBackHdc)�� 1�� ��Ʈ��(mHdc)�� �����Ѵ�.
		BitBlt(mHdc, 0, 0, FHD_X, FHD_Y,
				mBackHdc, 0, 0, SRCCOPY);	
	}
}