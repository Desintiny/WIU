#pragma once
class GameScene
{
private:
	int currentScene;

public:
	GameScene();
	~GameScene();

	void SceneForest();
	void SceneVillage();
	void SceneBoss();

	void ChangeScene(int newScene);
	int getCurrentScene(void);
};

