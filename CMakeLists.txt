cmake_minimum_required(VERSION 3.26)
project(DPIBulletHell)

set(CMAKE_CXX_STANDARD 17)

add_executable(DPIBulletHell
        Source/Game.h
        Source/Actors/Actor.h
        Source/Components/Component.h
        Source/Game.cpp
        Source/Main.cpp
        Source/Actors/Actor.cpp
        Source/Actors/Player.h
        Source/Actors/Teachers/Teacher.h
        Source/Components/ColliderComponents/CircleColliderComponent.cpp
        Source/Components/Component.cpp
        Source/Actors/Player.cpp
        Source/Actors/Player.h
        Source/Actors/Teachers/Teacher.cpp
        Source/Actors/Teachers/Teacher.h
        Source/Components/DrawComponents/DrawComponent.cpp
        Source/Components/DrawComponents/DrawAnimatedComponent.cpp
        Source/Components/RigidBodyComponent.cpp
        Source/Random.cpp
        Source/Math.cpp
        Source/Components/DrawComponents/DrawPolygonComponent.cpp
        Source/Components/DrawComponents/DrawSpriteComponent.cpp
        Source/Actors/Projectiles/Projectile.cpp
        Source/Actors/Projectiles/Projectile.h
        Source/Actors/PowerUp.cpp
        Source/Actors/PowerUp.h
        Source/Actors/PowerUp.h
        Source/Actors/Projectiles/Question.cpp
        Source/Actors/Projectiles/Question.h
        Source/Actors/Projectiles/Question.h
        Source/Actors/Projectiles/Task.cpp
        Source/Actors/Projectiles/Task.h
        Source/Actors/Projectiles/Task.h
        Source/AudioSystem.cpp
        Source/AudioSystem.h
        Source/Components/AIComponents/FSMComponent.cpp
        Source/Components/AIComponents/FSMState.cpp
        Source/Actors/Teachers/TStates/StartState.cpp
        Source/Actors/Teachers/TStates/StartState.h
        Source/Actors/Teachers/TStates/TState.cpp
        Source/Actors/Teachers/TStates/TState.h
        Source/Actors/Teachers/TStates/StateOne.cpp
        Source/Actors/Teachers/TStates/StateOne.h
        Source/Actors/Teachers/TStates/StateTwo.cpp
        Source/Actors/Teachers/TStates/StateTwo.h
        Source/Actors/Teachers/Drone.cpp
        Source/Actors/Teachers/Drone.h
        Source/Actors/LimiterMenu.cpp
        Source/Actors/LimiterMenu.h
        Source/Scenes/Scene.cpp
        Source/Components/DrawComponents/DrawTextComponent.cpp
        Source/Font.cpp
        Source/CSV.h
        Source/Components/DrawComponents/DrawSpriteWColorEffect.cpp
        Source/Components/DrawComponents/DrawSpriteWColorEffect.h
        Source/Actors/Teachers/TStates/StateThree.cpp
        Source/Actors/Teachers/TStates/StateThree.h
        Source/Scenes/MainMenu.cpp
        Source/Scenes/MainMenu.h
        Source/Scenes/StageSelect.cpp
        Source/Scenes/StageSelect.h
        Source/Scenes/Battle.cpp
        Source/Scenes/Battle.h
        Source/Scenes/SelectPlayers.cpp
        Source/Scenes/SelectPlayers.h
        Source/Scenes/Win.cpp
        Source/Scenes/Win.h
        Source/Scenes/Lose.cpp
        Source/Scenes/Lose.h
)

find_package(SDL2 2.28.2 EXACT REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf)
