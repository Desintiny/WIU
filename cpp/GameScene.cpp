#include "GameScene.h"

GameScene::GameScene()
{
	currentScene = 1;
}

GameScene::~GameScene()
{

}

void GameScene::SceneForest()
{

}

void GameScene::SceneVillage()
{

}

void GameScene::SceneBoss()
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
