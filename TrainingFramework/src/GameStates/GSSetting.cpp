
#include "GSSetting.h"

GSSetting::GSSetting(): GameStateBase(StateType::STATE_SETTING),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{})
{
}

GSSetting::~GSSetting()
{
}

void GSSetting::Init()
{
	m_Test = 1;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg1.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
	soundOn = std::make_shared<GameButton>(model, shader, texture);
	soundOn->Set2DPosition(Globals::screenWidth/2, Globals::screenHeight/ 2);
	soundOn->SetSize(70, 70);
	soundOn->SetOnClick([this]() {
		statusSound = !statusSound;
	});

	texture = ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga");
	soundOff = std::make_shared<GameButton>(model, shader, texture);
	soundOff->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	soundOff->SetSize(70, 70);
	soundOff->SetOnClick([this]() {
		statusSound = !statusSound;
	});

	
}

void GSSetting::Exit()
{
}

void GSSetting::Pause()
{
}

void GSSetting::Resume()
{
}

void GSSetting::HandleEvents()
{
}

void GSSetting::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSSetting::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
	soundOff->HandleTouchEvents(x, y, bIsPressed);
	soundOn->HandleTouchEvents(x, y, bIsPressed);
	
}

void GSSetting::HandleMouseMoveEvents(int x, int y)
{
}

void GSSetting::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	soundOff->Update(deltaTime);
	soundOn->Update(deltaTime);
}

void GSSetting::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	if (statusSound) {
		soundOn->Draw();
	}
	else {
		soundOff->Draw();
	}
}
