#pragma once
#include "GameStateBase.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;
class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;
	int m_Test;
	
private:
	std::shared_ptr<Sprite2D>	m_background, m_background2,m_pause_bg;
	GLint score = 0, tmp = 0;
	std::string s = "score: 0";
	std::shared_ptr<Text>		m_score, m_gameOver;
	std::list<std::shared_ptr<Text>>	m_text_pause;
	std::shared_ptr<Sprite2D>	m_base, m_base2;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Sprite2D> treeUp, treeDown;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	bool status_pause = false, status_GO =false;
	std::shared_ptr<GameButton> m_close, m_restart;
};

