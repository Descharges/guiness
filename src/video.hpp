#ifndef VIDEO_H
#define VIDEO_H

#include <SDL2/SDL.h>

/**
 * @brief Handles the window and the input events
 */
class Video {
   public:
    /**
     * @brief Construct a new Video object
     *
     * Initialize the SDL2 context and window
     */
    Video(int width, int height);

    /**
     * @brief Destroys the Video object
     *
     * Destroys the window and quit the SDL2 context
     */
    ~Video();

   private:
    SDL_Window* window;
};

#endif  // __VIDEO_H__