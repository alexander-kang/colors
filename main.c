#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

#include <SDL.h>
#include <SDL_error.h>
#include <SDL_log.h>

volatile sig_atomic_t exit_out = false;

void sig_handler(int sig)
{
    exit_out = true;
}

[[noreturn]] void bad_cleanup_and_exit(void)
{
    SDL_Quit();
    exit(EXIT_FAILURE);
}

int main(void)
{
    struct sigaction act;
    act.sa_handler = sig_handler;
    // Block all signals while handling (no good beating a dead horse)
    sigfillset(&act.sa_mask);
    // No special features needed (read manual to see more)
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);
    sigaction(SIGHUP, &act, NULL);

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
        bad_cleanup_and_exit();
    }

    // For audio driver:
    // https://wiki.libsdl.org/SDL2/FAQUsingSDL#how_do_i_choose_a_specific_audio_driver

    while (!exit_out)
    {
        // main stuff here
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}

