#include "GameScene.h"

GameScene::GameScene()
{
	currentScene = 1;
}

GameScene::~GameScene()
{

}

void GameScene::ChangeScene(int newScene)
{
	currentScene = newScene;
}

int GameScene::getCurrentScene()
{
	return currentScene;
}
