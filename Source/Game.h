
#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include <map>
#include "Math.h"
#include "AudioSystem.h"
#include "Actors/Player.h"
#include "Actors/Teachers/Teacher.h"
#include "Actors/Projectiles/Projectile.h"

class Game
{
public:
    Game(int windowWidth, int windowHeight);

    bool Initialize();
    void RunLoop();
    void Shutdown();
    void Quit() { mIsRunning = false; }

    // Actor functions
    void InitializeActors();
    void UpdateActors(float deltaTime);
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    // Draw functions
    void AddDrawable(class DrawComponent* drawable);
    void RemoveDrawable(class DrawComponent* drawable);

    // Collider functions
    void AddCollider(class CircleColliderComponent* collider);
    void RemoveCollider(class CircleColliderComponent* collider);
    std::vector<class CircleColliderComponent*>& GetColliders() { return mColliders; }

    Vector2& GetCameraPos() { return mCameraPos; };
    void SetCameraPos(const Vector2& position) { mCameraPos = position; };

    // Window functions
    int GetWindowWidth() const { return mWindowWidth; }
    int GetWindowHeight() const { return mWindowHeight; }
    int GetGameWindowWidth() const { return mGameWindowWidth; }
    int GetGameWindowHeight() const { return mGameWindowHeight; }

    AudioSystem* GetAudio() { return mAudio; }

    SDL_Texture* LoadTexture(const std::string& texturePath);

    // Game-specific
    class Player * GetPlayer1() { return mPlayer1; }
    class Player* GetPlayer2() { return mPlayer2; }
    bool p1Exists() {return mPlayer1!= nullptr && mPlayer1->GetState() != ActorState::Destroy; }
    bool p2Exists() {return mPlayer2 != nullptr && mPlayer2->GetState() != ActorState::Destroy; }
    float GetNota(const std::string& materia) { return mNotas[materia]; }
    void SetNota(const float newNota, const std::string& materia) { mNotas[materia] = newNota; }
    bool Passou(const std::string& materia) { return mNotas[materia] >= 60; }

    std::vector<class Task *> GetTasks() {return mTasks;}
    void AddTask(class Task * task) { mTasks.push_back(task); }
    void RemoveTask(class Task * task);

    class Teacher * GetTeacher(int i) { return mTeachers[i]; }
    std::vector<Teacher*> GetTeachers() { return mTeachers; }
    void AddTeacher(class Teacher* teacher) { mTeachers.push_back(teacher); }


    void SetActiveTeacher(int teacherIndex);

    Teacher *GetActiveTeacher();

private:
    void ProcessInput();
    void UpdateGame();
    void UpdateCamera();
    void GenerateOutput();


    // All the actors in the game
    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;

    // All the draw components
    std::vector<class DrawComponent*> mDrawables;

    // All the collision components
    std::vector<class CircleColliderComponent*> mColliders;

    // SDL stuff
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    AudioSystem* mAudio;

    // Window properties
    int mWindowWidth;
    int mWindowHeight;
    int mGameWindowWidth;
    int mGameWindowHeight;

    // Track elapsed time since game start
    Uint32 mTicksCount;

    // Track if we're updating actors right now
    bool mIsRunning;
    bool mUpdatingActors;

    Vector2 mCameraPos;

    // Game-specific
    class Player* mPlayer1;
    class Player* mPlayer2;
    class std::map<std::string, float> mNotas;

    class Teacher* activeTeacher;
    Actor* mLimiterMenu;

    std::vector<class Teacher*> mTeachers;
    std::vector<class Task*> mTasks;

};
