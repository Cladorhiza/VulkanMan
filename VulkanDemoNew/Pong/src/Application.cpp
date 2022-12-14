#include "Hubbsi.h"
#include "components/PlayerControllerPaddleComponent.h"
#include "systems/PlayerControllerPaddleSystem.h"
#include "components/AIControllerPaddleComponent.h"
#include "systems/AIControllerPaddleSystem.h"

#include <iostream>

int main()
{

    Renderer renderer;
    InputManager inputManager;
    Scene scene;

    //load rendering framework
    renderer.Init();

    Window window{ renderer.GetWindow() };
    Camera camera(window);
    inputManager.Init(window);
    scene.Init(&renderer);

    PlayerControllerPaddleSystem paddleSystem;
    paddleSystem.Init(&inputManager, &scene);
    AIControllerPaddleSystem aiPaddleSystem;
    aiPaddleSystem.Init(&scene);
    PhysicsSystem physicsSystem(&scene.transformSystem, &scene);

    uint32_t entityIds[10]{ 0 };
    for (int i{ 0 }; i < 10; i++) {
        entityIds[i] = scene.AddEntity();
        scene.GetEntity(i).SetHasTransform(true);
        scene.transformSystem.AddTransformComponent(i);
    }

    //pong ball
    scene.GetEntity(2).SetHasSprite(true);
    scene.GetEntity(2).SetTag("ball");
    scene.spriteSystem.AddSpriteComponent(2, "res/textures/ball.png");
    scene.transformSystem.GetTransformComponent(2).SetScale(glm::vec3(0.5f, 0.5f, 1.f));
    physicsSystem.AddPhysicsComponent(2);
    physicsSystem.GetComponent(2).SetVelocity(glm::vec3(-3.f, 1.f, 0.f));
    //paddleSystem.AddComponent(2, GLFW_KEY_W, GLFW_KEY_S, 5.f, 4.25f, -4.25f);
    
    
    //background sprite
    scene.GetEntity(3).SetHasSprite(true);
    scene.spriteSystem.AddSpriteComponent(3, "res/textures/background.png");
    scene.transformSystem.GetTransformComponent(3).SetPosition(glm::vec3(0.f, 0.f, -1.f));
    scene.transformSystem.GetTransformComponent(3).SetScale(glm::vec3(16.f, 9.f, 1.f));

    //playerpaddle
    scene.GetEntity(4).SetHasSprite(true);
    scene.GetEntity(4).SetTag("paddle");
    scene.spriteSystem.AddSpriteComponent(4, "res/textures/paddle.png");
    scene.transformSystem.GetTransformComponent(4).SetScale(glm::vec3(0.5f,2.5f,1.f));
    scene.transformSystem.GetTransformComponent(4).SetPosition(glm::vec3(-7.f, 0.f, 0.f));
    physicsSystem.AddPhysicsComponent(4);
    paddleSystem.AddComponent(4, GLFW_KEY_W, GLFW_KEY_S, 5.f, 3.25f, -3.25f);
    //enemypaddle
    scene.GetEntity(5).SetHasSprite(true);
    scene.GetEntity(5).SetTag("paddle");
    scene.spriteSystem.AddSpriteComponent(5, "res/textures/enemypaddle.png");
    scene.transformSystem.GetTransformComponent(5).SetScale(glm::vec3(0.5f, 2.5f, 1.f));
    scene.transformSystem.GetTransformComponent(5).SetPosition(glm::vec3(7.f, 0.f, 0.f));
    physicsSystem.AddPhysicsComponent(5);
    aiPaddleSystem.AddComponent(5, 5.f, 3.25f, -3.25f);
    aiPaddleSystem.SetBallTransform(&scene.transformSystem.GetTransformComponent(2));
    //ceiling
    scene.GetEntity(6).SetHasSprite(true);
    scene.GetEntity(6).SetTag("wall");
    scene.spriteSystem.AddSpriteComponent(6, "res/textures/wall.png");
    scene.transformSystem.GetTransformComponent(6).SetScale(glm::vec3(20.f, .5f, 1.f));
    scene.transformSystem.GetTransformComponent(6).SetPosition(glm::vec3(0.f, 4.5f, 0.f));
    physicsSystem.AddPhysicsComponent(6);
    //floor
    scene.GetEntity(7).SetHasSprite(true);
    scene.GetEntity(7).SetTag("wall");
    scene.spriteSystem.AddSpriteComponent(7, "res/textures/wall.png");
    scene.transformSystem.GetTransformComponent(7).SetScale(glm::vec3(20.f, .5f, 1.f));
    scene.transformSystem.GetTransformComponent(7).SetPosition(glm::vec3(0.f, -4.5f, 0.f));
    physicsSystem.AddPhysicsComponent(7);



    for (int i{ 0 }; i < 10; i++) {
        std::cout << "Entity " << i << ((scene.GetEntity(i).HasTransform()) ? " Has a transform component.\n" : " Has not got a transform component.\n");
    }
    
    //delta-time storage
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<float> elapsed;
    //used to test how many frames per second
    double cumulativeSecond = 0.0;
    float timeStep = 0.05f;
    int framesCount = 0;

    double degs = 0.0;

    bool isOrtho = true;

    
    double cumulativeTime = 0.0f;
    uint32_t physicsTickRate = 60;
    double recipPhysicsTickRate = 1.0 / physicsTickRate;
    physicsSystem.SetTickRate(physicsTickRate);


    //main game loop
    while (!window.WindowShouldClose() && (inputManager.GetKeyState(GLFW_KEY_ESCAPE) != GLFW_PRESS)) {

        start = std::chrono::high_resolution_clock::now();

        //poll inputs
        window.PollEvents();
        inputManager.Poll();

        if (inputManager.GetKeyToggle(GLFW_KEY_T)) {
            isOrtho = !isOrtho;
            camera.SetOrthographic(isOrtho);
        }
        
        //game logic update
        paddleSystem.Update(timeStep);
        aiPaddleSystem.Update(timeStep);


        while (cumulativeTime > recipPhysicsTickRate) {

            physicsSystem.Update(recipPhysicsTickRate);
            cumulativeTime -= recipPhysicsTickRate;
        }

        physicsSystem.GetComponent(2).SetVelocity(physicsSystem.GetComponent(2).GetVelocity() + (glm::vec3(0.01f) * timeStep));

        
        camera.Update(timeStep, inputManager);
        scene.spriteSystem.Update();

        //draw
        renderer.SetViewMatrix(camera.GetViewingMatrix());
        glm::mat4 proj{ camera.GetProjectionMatrix() };
        renderer.SetProjMatrix(proj);
        renderer.Render();


        //calc delta time
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        timeStep = elapsed.count();
        cumulativeTime += elapsed.count();

        //framerate calculation
        cumulativeSecond += elapsed.count();
        framesCount++;
        if (cumulativeSecond > std::chrono::seconds(1).count()) {
            cumulativeSecond -= std::chrono::seconds(1).count();
            std::cout << framesCount << std::endl;
            framesCount = 0;
        }

    }
    
    
}