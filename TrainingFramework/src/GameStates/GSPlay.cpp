#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "SpriteAnimation.h"
#include <GameStates/GSMenu.h>

std::string soundFLy = "fly.wav";
extern bool statusSound, statusMusic;
GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	m_Test = 1;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg1.tga");
	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_background2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_background2->Set2DPosition((float)Globals::screenWidth + 240, (float)Globals::screenHeight / 2);
	m_background2->SetSize(Globals::screenWidth, Globals::screenHeight);
	//base
	texture = ResourceManagers::GetInstance()->GetTexture("base.tga");
	m_base = std::make_shared<Sprite2D>(model, shader, texture);
	m_base->Set2DPosition(Vector2((float)Globals::screenWidth / 2, 770));
	m_base->SetSize(480, 238);
	m_base2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_base2->Set2DPosition(Vector2((float)Globals::screenWidth / 2, 770));
	m_base2->SetSize(480, 238);

	// pause background
	texture = ResourceManagers::GetInstance()->GetTexture("GSPlay_bg.tga");
	m_pause_bg = std::make_shared<Sprite2D>(model, shader, texture);
	m_pause_bg->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_pause_bg->SetSize(300, 300);

	// tree
	texture = ResourceManagers::GetInstance()->GetTexture("tree_up.tga");
	treeUp = std::make_shared<Sprite2D>(model, shader, texture);
	treeUp->Set2DPosition(Vector2(800, 0));
	treeUp->SetSize(89, 401);
	texture = ResourceManagers::GetInstance()->GetTexture("tree_down.tga");
	treeDown = std::make_shared<Sprite2D>(model, shader, texture);
	treeDown->Set2DPosition(Vector2(800, 630));
	treeDown->SetSize(89, 401);

	// button pause
	texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		status_pause = !status_pause;
		});
	m_listButton.push_back(button);

	// close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	m_close = std::make_shared<GameButton>(model, shader, texture);
	m_close->Set2DPosition(Globals::screenWidth / 2 - 50, Globals::screenHeight / 2);
	m_close->SetSize(50, 50);
	m_close->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	// restart

	texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	m_restart = std::make_shared<GameButton>(model, shader, texture);
	m_restart->Set2DPosition(Globals::screenWidth / 2 + 50, Globals::screenHeight / 2);
	m_restart->SetSize(50, 50);
	m_restart->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});


	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("AngryBirds.ttf");
	m_score = std::make_shared< Text>(shader, font, "0", TextColor::WHITE, 4.0f);
	m_score->Set2DPosition(Globals::screenWidth / 2 - 20, Globals::screenHeight / 2 - 250);

	// text pause
	std::shared_ptr<Text> text_pause = std::make_shared< Text>(shader, font, "restart", TextColor::WHITE, 1.0f);
	text_pause->Set2DPosition(Globals::screenWidth / 2 + 15, Globals::screenHeight / 2 + 50);
	m_text_pause.push_back(text_pause);

	text_pause = std::make_shared< Text>(shader, font, "exit", TextColor::WHITE, 1.0f);
	text_pause->Set2DPosition(Globals::screenWidth / 2 - 75, Globals::screenHeight / 2 + 50);
	m_text_pause.push_back(text_pause);
	// gameover
	m_gameOver = std::make_shared< Text>(shader, font, "Game Over", TextColor::RED, 1.5f);
	m_gameOver->Set2DPosition(Globals::screenWidth / 2 - 90, Globals::screenHeight / 2 - 70);

	//bird
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("bird_0.tga");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 3, 1, 0, 0.08f);
	obj->Set2DPosition(240, 350);
	obj->SetSize(194.4f, 148.8f);
	//obj->SetRotation(Vector3(0.0f, 3.14f, 0.0f));
	m_listAnimation.push_back(obj);
}

void GSPlay::Exit()
{
	printf("%d", m_Test);
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (!status_pause) {
		Vector2 m;
		for (auto it : m_listAnimation) {
			if (bIsPressed && y > 75) {
				m = it->Get2DPosition();
				it->Set2DPosition(m.x, m.y - 110);
				if (Globals::statusSound)
					ResourceManagers::GetInstance()->PlaySound(soundFLy);
			}
		}
	}
	else {
		m_close->HandleTouchEvents(x, y, bIsPressed);
		m_restart->HandleTouchEvents(x, y, bIsPressed);
	}
	if (!status_GO)
		for (auto button : m_listButton) {
			if (button->HandleTouchEvents(x, y, bIsPressed))
			{
				break;
			}
		}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	if (!status_pause) {
		Vector3 m1 = m_background->GetPosition();
		if (m1.x == -240) m1.x = 240 + 480;
		m_background->Set2DPosition(m1.x - 3, m1.y);
		m_base->Set2DPosition(m1.x - 3, 770);
		Vector3 m2 = m_background2->GetPosition();
		if (m2.x == -240) m2.x = 240 + 480;
		m_background2->Set2DPosition(m2.x - 3, m2.y);
		m_base2->Set2DPosition(m2.x - 3, 770);

		//tree
		Vector3 m3 = treeUp->GetPosition();
		if (m3.x <= -45) m3.x = 480 + 45, m3.y = (rand() % 8 - 3) * 30;
		treeUp->Set2DPosition(m3.x - 5, m3.y);

		Vector3 m4 = treeDown->GetPosition();
		if (m4.x <= -45) m4.x = 480 + 45, m4.y = m3.y + 630;
		treeDown->Set2DPosition(m4.x - 5, m4.y);
		if (m4.x + 45 == (float)Globals::screenWidth / 2) {
			score++;
			if (Globals::statusSound)
				ResourceManagers::GetInstance()->PlaySound("ping.wav");
		}
		Vector2 m;
		for (auto it : m_listAnimation) {
			m = it->Get2DPosition();
			if (m.y > 700)m.y = 700;
			it->Set2DPosition(m.x, m.y + 300 * deltaTime);
			it->Update(deltaTime);
		}
		if ((m.y <= m3.y + 230 || m.y >= m4.y - 230) && m.x + 97 >= m3.x && m.x + 97 <= m3.x + 194) {
			status_GO = true; status_pause = true;
			if (Globals::statusSound)
				ResourceManagers::GetInstance()->PlaySound("dead.wav");
		}
	}
	if (status_GO) {
		Vector2 m;
		for (auto it : m_listAnimation) {
			m = it->Get2DPosition();
			if (m.y > 850)break;
			it->Set2DPosition(m.x, m.y + 500 * deltaTime);
			it->Update(deltaTime);
		}
	}
	//button
	for (auto it : m_listButton) {
		it->Update(deltaTime);
	}

	auto toString = [&](GLint score) {
		std::string ss;
		while (score > 0) {
			ss = (char)(score % 10 + '0') + ss;
			score /= 10;
		}
		return ss;
	};
	if (score > tmp) {
		tmp = score;
		s = toString(tmp);
	}
	m_score->SetText(s);

}

void GSPlay::Draw()
{
	m_background->Draw();
	m_background2->Draw();
	treeDown->Draw();
	treeUp->Draw();
	m_score->Draw();
	m_base->Draw();
	m_base2->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
	if (status_pause) {
		m_pause_bg->Draw();
		m_close->Draw();
		m_restart->Draw();
		if (status_GO)
			m_gameOver->Draw();
		for (auto it : m_text_pause) {
			it->Draw();
		}

	}
}