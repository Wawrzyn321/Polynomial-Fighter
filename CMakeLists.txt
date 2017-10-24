cmake_minimum_required(VERSION 3.8)
project(Polynomial_Fighter)

set(CMAKE_CXX_STANDARD 11)

link_libraries(GL sfml-network sfml-audio sfml-graphics sfml-window sfml-system)

set(SOURCE_FILES
        "Polynomial-Fighter/Asset Manager.h"
        Polynomial-Fighter/AssetManager.cpp
        Polynomial-Fighter/Debug.cpp
        Polynomial-Fighter/Debug.h
        Polynomial-Fighter/Entity.h
        Polynomial-Fighter/EntityManager.cpp
        Polynomial-Fighter/EntityManager.h
        Polynomial-Fighter/EquationProvider.cpp
        Polynomial-Fighter/EquationProvider.h
        Polynomial-Fighter/GameData.h
        Polynomial-Fighter/GUILabel.cpp
        Polynomial-Fighter/GUILabel.h
        Polynomial-Fighter/IDamageable.h
        Polynomial-Fighter/IMouseEventsListener.h
        Polynomial-Fighter/ITransformable.h
        Polynomial-Fighter/main.cpp
        Polynomial-Fighter/ParticleSystem.cpp
        Polynomial-Fighter/ParticleSystem.h
        Polynomial-Fighter/ScoresManager.cpp
        Polynomial-Fighter/ScoresManager.h
        Polynomial-Fighter/ScoresManagerGUI.cpp
        Polynomial-Fighter/ScoresManagerGUI.h
        Polynomial-Fighter/SoundManager.cpp
        Polynomial-Fighter/SoundManager.h
        Polynomial-Fighter/Timer.cpp
        Polynomial-Fighter/Timer.h
        Polynomial-Fighter/Utility.cpp
        Polynomial-Fighter/Utility.h Polynomial-Fighter/RandomGenerator.cpp Polynomial-Fighter/RandomGenerator.h)

add_executable(Polynomial_Fighter ${SOURCE_FILES})