#pragma
#include "BaseObject.h"
#include "SpriteAnimation.h"
class Bird :public BaseObject
{
public: 
	Bird();
	~Bird();
	void Fly();
	void Init();
	void Update();
	void Draw();
};
