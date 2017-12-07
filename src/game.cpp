#include "../include/engine.hpp"
#include "../include/engine_constants.hpp"
#include "../include/engine_types.hpp"
#include <fstream>
#include <iostream>
#include <cmath>

int main(int /*argn*/, char* /*args*/ [])
{
    ge::IEngine* gameEngine = ge::getInstance();
    std::string errMsg      = gameEngine->init_engine(ge::everything);

    if (!errMsg.empty())
    {
        std::cerr << errMsg << std::endl;
        return EXIT_FAILURE;
    }

    bool run_loop = true;
    ge::event event;
    while (run_loop)
    {
        while (gameEngine->read_event(event))
        {
            if (!event.msg.empty())
            {
                std::cout << event.msg << std::endl;
            }
            if (event.type == ge::events_t::shutdown)
            {
                run_loop = false;
                break;
            }
        }
        const std::string vertexes_path = "./config/vertexes.txt";

        ge::triangle trSrc1;
        ge::triangle trSrc2;
        ge::triangle trDest1;
        ge::triangle trDest2;
        ge::triangle trLeft;
        ge::triangle trRight;

        std::ifstream file(vertexes_path);
        if (!file.is_open())
        {
            std::cerr << "Can't open file with vertexes values" << std::endl;
            continue;
        }

        float alpha = std::sin(gameEngine->get_time()) * 0.5f + 0.5f;

        std::cout << alpha << std::endl;

        file >> trSrc1 >> trSrc2;
        file >> trDest1 >> trDest2;
        trLeft  = gameEngine->transform_triangle(trSrc1, trDest1, alpha);
        trRight = gameEngine->transform_triangle(trSrc2, trDest2, alpha);

        gameEngine->render_triangle(trLeft);
        gameEngine->render_triangle(trRight);

        gameEngine->swap_buffers();
    }
    gameEngine->uninit_engine();
    return EXIT_SUCCESS;
}
