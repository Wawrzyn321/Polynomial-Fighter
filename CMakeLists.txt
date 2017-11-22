cmake_minimum_required(VERSION 3.8)
project(Polynomial_Fighter)

set(CMAKE_CXX_STANDARD 11)

link_libraries(GL sfml-network sfml-audio sfml-graphics sfml-window sfml-system)

set(SOURCE_FILES
        "Polynomial-Fighter/Asset Manager.h"
        Polynomial-Fighter/AdvancedParticleSystem.h
        Polynomial-Fighter/AdvancedParticle.cpp
        Polynomial-Fighter/AdvancedParticleSystem.cpp
        Polynomial-Fighter/AdvancedParticleSystemData.h
        Polynomial-Fighter/APSBuilder.cpp
        Polynomial-Fighter/Delegate.h
        Polynomial-Fighter/ExampleEntities.h
        Polynomial-Fighter/FloatColor.h
        Polynomial-Fighter/InputField.cpp
        Polynomial-Fighter/InputFieldParser.cpp
        Polynomial-Fighter/PowerfulText.cpp
        Polynomial-Fighter/Request.h
        Polynomial-Fighter/RequestHandlers.cpp
        Polynomial-Fighter/StringPreprocessor.cpp
        Polynomial-Fighter/AssetManager.cpp
        Polynomial-Fighter/Debug.cpp
        Polynomial-Fighter/Debug.h
        Polynomial-Fighter/Entity.h
        Polynomial-Fighter/EntityManager.cpp
        Polynomial-Fighter/EntityManager.h
        Polynomial-Fighter/GameData.h
        Polynomial-Fighter/GUILabel.cpp
        Polynomial-Fighter/GUILabel.h
        Polynomial-Fighter/IDamageable.h
        Polynomial-Fighter/IMouseEventsListener.h
        Polynomial-Fighter/ITransformable.h
        Polynomial-Fighter/main.cpp
        Polynomial-Fighter/RandomGenerator.cpp
        Polynomial-Fighter/RandomGenerator.h
        Polynomial-Fighter/ScoresManager.cpp
        Polynomial-Fighter/ScoresManager.h
        Polynomial-Fighter/ScoresManagerGUI.cpp
        Polynomial-Fighter/ScoresManagerGUI.h
        Polynomial-Fighter/SoundManager.cpp
        Polynomial-Fighter/SoundManager.h
        Polynomial-Fighter/Timer.cpp
        Polynomial-Fighter/Timer.h
        Polynomial-Fighter/Utility.cpp

        Polynomial-Fighter/Utility.h Polynomial-Fighter/PolynomialProductForm.cpp Polynomial-Fighter/PolynomialProductForm.h Polynomial-Fighter/PolynomialGenerator.cpp Polynomial-Fighter/PolynomialGenerator.h Polynomial-Fighter/PolynomialFactor.cpp Polynomial-Fighter/PolynomialFactor.h Polynomial-Fighter/PolynomialGeneralForm.cpp Polynomial-Fighter/PolynomialGeneralForm.h Polynomial-Fighter/PolynomialMultipler.cpp Polynomial-Fighter/PolynomialMultipler.h)

add_executable(Polynomial_Fighter ${SOURCE_FILES})