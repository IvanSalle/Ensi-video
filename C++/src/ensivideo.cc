#include <SDL2/SDL.h>
#include <cassert>
#include <string>
#include <thread>
#include <iostream>

#include "ensivideo.hpp"
#include "oggstream.hpp"
#include "stream_common.hpp"

using namespace std;

unique_ptr<thread> theorathread;
unique_ptr<thread> vorbisthread;
unique_ptr<thread> thread_affichage;

int main(int argc, char *argv[]) {
  int res;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s FILE", argv[0]);
    exit(EXIT_FAILURE);
  }
  assert(argc == 2);

  // Initialisation de la SDL
  res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
  atexit(SDL_Quit);
  assert(res == 0);

  // Your code HERE
  // start the two stream readers (theoraStreamReader and vorbisStreamReader)
  // each in a threadc
  theorathread = make_unique<thread>(theoraStreamReader,argv[1]);
  vorbisthread = make_unique<thread>(vorbisStreamReader,argv[1]);
  // wait for vorbis thread
  vorbisthread->join();
  // 1 seconde of sound in advance, thus wait 1 seconde
  // before leaving
  this_thread::sleep_for(1s);

  // Wait for theora and theora2sdl threads
  if (theorathread && theorathread->joinable()) {
    cout << "theorathread  existe et peut être joint\n";
    theorathread->join();
  } else {
      cout << " theorathread n'a pas été créé\n";
  }
  
  if (thread_affichage && thread_affichage->joinable()) {
    cout << "Thread affichage existe et peut être joint\n";
    thread_affichage->join();
  } else {
      cout << "Thread affichage n'a pas été créé\n";
  }
  // TODO
  /* liberer des choses ? */

  exit(EXIT_SUCCESS);
}
