cmake_minimum_required(VERSION 3.26)
project(cpp2024_Game_ponulio)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(assets)
include_directories(src)
include_directories(src/include)
include_directories(src/include/SDL2)

add_executable(cpp2024_Game_ponulio
        "assets/Animacijos/EnemyPngs/Rat/RatAttack/RatAttack (1).png"
        "assets/Animacijos/EnemyPngs/Rat/RatAttack/RatAttack (2).png"
        "assets/Animacijos/EnemyPngs/Rat/RatAttack/RatAttack (3).png"
        "assets/Animacijos/EnemyPngs/Rat/RatAttack/RatAttack (4).png"
        "assets/Animacijos/EnemyPngs/Rat/RatUp/RatUp (1).png"
        "assets/Animacijos/EnemyPngs/Rat/RatUp/RatUp (2).png"
        "assets/Animacijos/EnemyPngs/Rat/RatUp/RatUp (3).png"
        "assets/Animacijos/EnemyPngs/Rat/RatUp/RatUp (4).png"
        assets/Animacijos/Files/Branch.aseprite
        assets/Animacijos/Files/Player.aseprite
        assets/Animacijos/Files/Rat.aseprite
        assets/Animacijos/ItemPngs/Branch.png
        "assets/Animacijos/PlayerPngs/PlayerRunDown/PlayerRunDown (1).png"
        "assets/Animacijos/PlayerPngs/PlayerRunDown/PlayerRunDown (2).png"
        "assets/Animacijos/PlayerPngs/PlayerRunDown/PlayerRunDown (3).png"
        "assets/Animacijos/PlayerPngs/PlayerRunDown/PlayerRunDown (4).png"
        "assets/Animacijos/PlayerPngs/PlayerRunLeft/PlayerRunLeft (1).png"
        "assets/Animacijos/PlayerPngs/PlayerRunLeft/PlayerRunLeft (2).png"
        "assets/Animacijos/PlayerPngs/PlayerRunLeft/PlayerRunLeft (3).png"
        "assets/Animacijos/PlayerPngs/PlayerRunLeft/PlayerRunLeft (4).png"
        "assets/Animacijos/PlayerPngs/PlayerRunRight/PlayerRunRight (1).png"
        "assets/Animacijos/PlayerPngs/PlayerRunRight/PlayerRunRight (2).png"
        "assets/Animacijos/PlayerPngs/PlayerRunRight/PlayerRunRight (3).png"
        "assets/Animacijos/PlayerPngs/PlayerRunRight/PlayerRunRight (4).png"
        "assets/Animacijos/PlayerPngs/PlayerRunUp/PlayerRunUp (1).png"
        "assets/Animacijos/PlayerPngs/PlayerRunUp/PlayerRunUp (2).png"
        "assets/Animacijos/PlayerPngs/PlayerRunUp/PlayerRunUp (3).png"
        "assets/Animacijos/PlayerPngs/PlayerRunUp/PlayerRunUp (4).png"
        assets/player.png
        src/include/SDL2/begin_code.h
        src/include/SDL2/close_code.h
        src/include/SDL2/SDL.h
        src/include/SDL2/SDL_assert.h
        src/include/SDL2/SDL_atomic.h
        src/include/SDL2/SDL_audio.h
        src/include/SDL2/SDL_bits.h
        src/include/SDL2/SDL_blendmode.h
        src/include/SDL2/SDL_clipboard.h
        src/include/SDL2/SDL_config.h
        src/include/SDL2/SDL_cpuinfo.h
        src/include/SDL2/SDL_egl.h
        src/include/SDL2/SDL_endian.h
        src/include/SDL2/SDL_error.h
        src/include/SDL2/SDL_events.h
        src/include/SDL2/SDL_filesystem.h
        src/include/SDL2/SDL_gamecontroller.h
        src/include/SDL2/SDL_gesture.h
        src/include/SDL2/SDL_guid.h
        src/include/SDL2/SDL_haptic.h
        src/include/SDL2/SDL_hidapi.h
        src/include/SDL2/SDL_hints.h
        src/include/SDL2/SDL_image.h
        src/include/SDL2/SDL_joystick.h
        src/include/SDL2/SDL_keyboard.h
        src/include/SDL2/SDL_keycode.h
        src/include/SDL2/SDL_loadso.h
        src/include/SDL2/SDL_locale.h
        src/include/SDL2/SDL_log.h
        src/include/SDL2/SDL_main.h
        src/include/SDL2/SDL_messagebox.h
        src/include/SDL2/SDL_metal.h
        src/include/SDL2/SDL_misc.h
        src/include/SDL2/SDL_mouse.h
        src/include/SDL2/SDL_mutex.h
        src/include/SDL2/SDL_name.h
        src/include/SDL2/SDL_opengl.h
        src/include/SDL2/SDL_opengl_glext.h
        src/include/SDL2/SDL_opengles.h
        src/include/SDL2/SDL_opengles2.h
        src/include/SDL2/SDL_opengles2_gl2.h
        src/include/SDL2/SDL_opengles2_gl2ext.h
        src/include/SDL2/SDL_opengles2_gl2platform.h
        src/include/SDL2/SDL_opengles2_khrplatform.h
        src/include/SDL2/SDL_pixels.h
        src/include/SDL2/SDL_platform.h
        src/include/SDL2/SDL_power.h
        src/include/SDL2/SDL_quit.h
        src/include/SDL2/SDL_rect.h
        src/include/SDL2/SDL_render.h
        src/include/SDL2/SDL_revision.h
        src/include/SDL2/SDL_rwops.h
        src/include/SDL2/SDL_scancode.h
        src/include/SDL2/SDL_sensor.h
        src/include/SDL2/SDL_shape.h
        src/include/SDL2/SDL_stdinc.h
        src/include/SDL2/SDL_surface.h
        src/include/SDL2/SDL_system.h
        src/include/SDL2/SDL_syswm.h
        src/include/SDL2/SDL_test.h
        src/include/SDL2/SDL_test_assert.h
        src/include/SDL2/SDL_test_common.h
        src/include/SDL2/SDL_test_compare.h
        src/include/SDL2/SDL_test_crc32.h
        src/include/SDL2/SDL_test_font.h
        src/include/SDL2/SDL_test_fuzzer.h
        src/include/SDL2/SDL_test_harness.h
        src/include/SDL2/SDL_test_images.h
        src/include/SDL2/SDL_test_log.h
        src/include/SDL2/SDL_test_md5.h
        src/include/SDL2/SDL_test_memory.h
        src/include/SDL2/SDL_test_random.h
        src/include/SDL2/SDL_thread.h
        src/include/SDL2/SDL_timer.h
        src/include/SDL2/SDL_touch.h
        src/include/SDL2/SDL_types.h
        src/include/SDL2/SDL_version.h
        src/include/SDL2/SDL_video.h
        src/include/SDL2/SDL_vulkan.h
        src/lib/cmake/SDL2/sdl2-config-version.cmake
        src/lib/cmake/SDL2/sdl2-config.cmake
        src/lib/pkgconfig/sdl2.pc
        src/lib/libjpeg-9.dll
        src/lib/libpng16-16.dll
        src/lib/libSDL2.a
        src/lib/libSDL2.dll.a
        src/lib/libSDL2.la
        src/lib/libSDL2_test.a
        src/lib/libSDL2_test.la
        src/lib/libSDL2main.a
        src/lib/libSDL2main.la
        src/lib/libtiff-5.dll
        src/lib/libwebp-4.dll
        src/lib/LICENSE.jpeg.txt
        src/lib/LICENSE.png.txt
        src/lib/LICENSE.tiff.txt
        src/lib/LICENSE.webp.txt
        src/lib/LICENSE.zlib.txt
        src/lib/SDL2_image.dll
        src/lib/SDL2_image.lib
        src/lib/zlib1.dll
        game.exe
        game_loop.cpp
        game_loop.h
        game_object.cpp
        game_object.h
        item.cpp
        item.h
        libpng16-16.dll
        main.cpp
        Makefile
        player.cpp
        player.h
        savaitines_uzduotys.md
        SDL2.dll
        SDL2_image.dll
        texture_manager.cpp
        texture_manager.h
        zlib1.dll
        Map.h
        Map.cpp
        ECS/ECS.h
        ECS/Components.h
        ECS/SpriteComponent.h
        ECS/TransformComponent.h
        Vector2D.h
        Vector2D.cpp
        ECS/KeyboardController.h)