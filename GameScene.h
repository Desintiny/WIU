#pragma once
class GameScene
{
private:
	int currentScene;

public:
	GameScene();
	~GameScene();

	void ChangeScene(int newScene);
	int getCurrentScene(void);
};

