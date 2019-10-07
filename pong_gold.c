/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
typedef enum GameScreen {TITLE, GAMEPLAY, OPTIONS, WIN, LOSE} GameScreen;

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1920;
    int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Pong 4K 100% REAL no FAKE");
    
    InitAudioDevice();
    
    Texture2D playerTexture = LoadTexture ("resources/PlayerOne.png");
    Texture2D player2Texture = LoadTexture ("resources/PlayerTwo.png");
    Texture2D fieldTexture = LoadTexture ("resources/Campo.png");
    Texture2D playerTextureP = LoadTexture ("resources/PlayerOne'.png");
    Texture2D player2TextureP = LoadTexture ("resources/PlayerTwo'.png");
    Texture2D fieldTextureP = LoadTexture ("resources/Campo'.png");
    Texture2D Ball = LoadTexture ("resources/Bola.png");
    Music MainMusic = LoadMusicStream ("resources/Saturn2.ogg");
    Music MenuMusic = LoadMusicStream ("resources/MenuMusic.ogg");
    Music OptionsMusic = LoadMusicStream ("resources/OptionsTheme.ogg");
    Music PauseMusic = LoadMusicStream ("resources/MusicaPause.ogg");
    Music Winner = LoadMusicStream ("resources/VictoryRoyale.ogg");
    Music Loser = LoadMusicStream ("resources/Loser.ogg");
    
    Vector2 center = {960, 540};
    float radius = 50;
    Rectangle Rec = {15, 320, 60, 420};
    Rectangle Rec2 = {1845, 320, 60, 420};
    int speed = 10;
    int speed2 = 10;
    Rectangle Play = {710, 330, 500, 150};
    Rectangle Options = {710, 600, 500, 150};
    Rectangle Quit = {710, 870, 500, 150};
    Rectangle Back = {100, 870, 200, 75};
    Rectangle Multi = {700, 285, 275, 125};
    Rectangle Default = {700, 485, 420, 125};
    Rectangle Premium = {1250, 485, 420, 125};
    Rectangle Menu = {100, 870, 200, 75};
    Rectangle Restart = {710, 550, 500, 150};
    Rectangle VolumeUp = {700, 700, 100, 100};
    Rectangle VolumeDown = {850, 700, 100, 100};
    Rectangle Vol1 = {500, 777, 70, 23};
    Rectangle Vol2 = {500, 752, 70, 23};
    Rectangle Vol3 = {500, 727, 70, 23};
    Rectangle Vol4 = {500, 702, 70, 23};
    
    float rotation = 0;
    float alpha = 1.0f;
    float volume = 1.0f;
    
    int FramesCounter = 0;
    
    bool fade = false;
    bool pause = true;
    bool multi = false;
    bool options = false;
    bool skin = false;
    bool victory = false;
    
    int Pl_Points = 0;
    int IA_Points = 0;
    
    GameScreen currentScene = TITLE;


    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        SetMasterVolume (volume);
        
        if (volume >= 1.0f) volume = 1.0f;
        if (volume <= 0.0f) volume = 0.0f;
       
        if(fade) alpha += 0.01f;
        else if(!fade) alpha -= 0.01f;
       
        if(alpha >= 1.0f) alpha = 1.0f;
        else if (alpha <= 0.0f) alpha = 0.0f;
         
         switch(currentScene)
        {
            case TITLE:
            
            UpdateMusicStream(MenuMusic);
            PlayMusicStream(MenuMusic);
            
            if(CheckCollisionPointRec(GetMousePosition(), Play) && (IsMouseButtonReleased(0))) 
            {
                Rec.x = 15;
                Rec.y = 320;
                Rec2.x = 1845;
                Rec2.y = 320;
                center = (Vector2){960,540};
                Pl_Points = 0;
                IA_Points = 0;
                fade = !fade;               
            }
            if((alpha == 1.0f) && (options == false)) currentScene = GAMEPLAY, fade = !fade;

            if(CheckCollisionPointRec(GetMousePosition(), Options) && (IsMouseButtonReleased(0)))
            {
              fade = !fade;
              options = true;
            }
            if ((alpha == 1.0f) && (options == true)) currentScene = OPTIONS, fade = !fade;
            
            if(CheckCollisionPointRec(GetMousePosition(), Quit) && (IsMouseButtonReleased(0))) CloseWindow();
            break;
            
            case GAMEPLAY:
            
            UpdateMusicStream(MainMusic);
            PlayMusicStream(MainMusic);
            
            UpdateMusicStream(PauseMusic);
            
            if(IsKeyPressed(KEY_BACKSPACE))
            {
                pause = true;
                fade = !fade;
                PlayMusicStream(PauseMusic);
            }
            
            if (pause == true) PlayMusicStream(PauseMusic);
                    else StopMusicStream(PauseMusic);
                    
            if (pause == true) PauseMusicStream(MainMusic);
                    else ResumeMusicStream(MainMusic);
                    
            if((alpha == 1.0f) && (options == false) && (currentScene == GAMEPLAY)) currentScene = TITLE, fade = !fade;
            
                if (IsKeyPressed(KEY_SPACE)) 
                {
                    pause = !pause;
                    
                    FramesCounter = 30;
                }
                
                if (!      pause)
                {
                   
                    center.x += speed;
                    center.y += speed2;
                    
                    rotation ++;
                    
                    if (center.x + radius >= screenWidth) 
                    {
                       center = (Vector2){960,540};
                       speed = -10;
                       speed2 = 10;
                       Pl_Points += 1;
                    }
                    if (center.y + radius >= screenHeight) speed2 *=-1;
                    if (center.x - radius <= 0)
                    {
                        center = (Vector2){960,540};
                        speed = 10;
                        speed2 = 10;
                        IA_Points += 1;
                    }
                    if (center.y - radius <= 0) speed2 *=-1;
                    
                    if (CheckCollisionCircleRec (center, radius, Rec))
                    {
                        if (center.x + radius >= Rec.x || center.x - radius <= Rec.x + Rec.width)
                            
                        speed *= -1.1;
                        speed2 *= 1.1;
                    }
                    if (CheckCollisionCircleRec (center, radius, Rec2))
                    {
                        if (center.x + radius >= Rec2.x || center.x - radius <= Rec2.x + Rec2.width)
                            
                        speed *= -1.1;
                        speed2 *= 1.1;
                    }
                    
                    if (multi == false)
                    {
                        if(center.x >= screenWidth/2)
                        {
                            if(speed >= 0)
                            {
                            if(center.y <= Rec2.y + Rec2.height/2) Rec2.y -= 10;
                            else if(center.y >= Rec2.y + Rec2.height/2) Rec2.y += 10;
                            }
                        } 
                    }
                    
                    
                    if (Rec.y <= 0) Rec.y = 0;
                    if (Rec.y + Rec.height >=screenHeight) Rec.y = screenHeight - Rec.height;
                    if (IsKeyDown(KEY_W)) Rec.y -= 10;
                    if (IsKeyDown(KEY_S)) Rec.y += 10;
                    
                    if (Rec2.y <= 0) Rec2.y = 0;
                    if (Rec2.y + Rec2.height >=screenHeight) Rec2.y = screenHeight - Rec2.height;
                    
                    if (multi == true)
                    {
                        if (IsKeyDown(KEY_UP)) Rec2.y -= 10;
                        if (IsKeyDown(KEY_DOWN)) Rec2.y += 10;
                    }
                    
                }
                
                if (Pl_Points == 7)
                {
                    pause = true;
                    currentScene = WIN;
                    Pl_Points = 0;
                    IA_Points = 0;
                }
                
                if (IA_Points == 7)
                {
                    pause = true;
                    currentScene = LOSE;
                    Pl_Points = 0;
                    IA_Points = 0;
                }
                
            
                else
                {
                   FramesCounter++;
                   
                }
            break;
            
            case OPTIONS:
            
            UpdateMusicStream(OptionsMusic);
            PlayMusicStream(OptionsMusic);
            
            if(CheckCollisionPointRec(GetMousePosition(), Back) && (IsMouseButtonReleased(0)))
            {
                fade = !fade;
                options = false;
            }
            if((alpha == 1.0f) && (currentScene == OPTIONS))  currentScene = TITLE, fade = !fade;
            
            if(CheckCollisionPointRec(GetMousePosition(), Multi) && (IsMouseButtonReleased(0)))
            {
                multi = !multi;
            }
            
            if(CheckCollisionPointRec(GetMousePosition(), Default) && (IsMouseButtonReleased(0)))
            {
                skin = false;
            }
            
            if(CheckCollisionPointRec(GetMousePosition(), Premium) && (IsMouseButtonReleased(0)) && (victory == true))
            {
                skin = true;
            }
            
            if(CheckCollisionPointRec(GetMousePosition(), VolumeUp) && (IsMouseButtonReleased(0)))
            {
                volume += 0.25f;
            }
            
            if(CheckCollisionPointRec(GetMousePosition(), VolumeDown) && (IsMouseButtonReleased(0)))
            {
                volume -= 0.25f;
            }
            
            break;
            
            
            case WIN:
            
            UpdateMusicStream(Winner);
            PlayMusicStream(Winner);
            
            victory = true;
            if(CheckCollisionPointRec(GetMousePosition(), Menu) && (IsMouseButtonReleased(0)))
            {
                fade = !fade;
            }
            if((alpha == 1.0f) && (currentScene == WIN))  currentScene = TITLE, fade = !fade;
            
            if(CheckCollisionPointRec(GetMousePosition(), Restart) && (IsMouseButtonReleased(0)))
            {
                Rec.x = 15;
                Rec.y = 320;
                Rec2.x = 1845;
                Rec2.y = 320;
                center = (Vector2){960,540};
                Pl_Points = 0;
                IA_Points = 0;
                currentScene = GAMEPLAY;
            }
            
            break;
            
            case LOSE:
            
            UpdateMusicStream(Loser);
            PlayMusicStream(Loser);
            
            if(CheckCollisionPointRec(GetMousePosition(), Menu) && (IsMouseButtonReleased(0)))
            {                
                fade = !fade;
            }
            if((alpha == 1.0f) && (currentScene == LOSE))  currentScene = TITLE, fade = !fade;
            
            if(CheckCollisionPointRec(GetMousePosition(), Restart) && (IsMouseButtonReleased(0)))
            {
                Rec.x = 15;
                Rec.y = 320;
                Rec2.x = 1845;
                Rec2.y = 320;
                center = (Vector2){960,540};
                Pl_Points = 0;
                IA_Points = 0;
                currentScene = GAMEPLAY;
            }
            
            break;
        }
        
        
    
            
            
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            
             switch(currentScene)
            {
     
                case TITLE:
                if(CheckCollisionPointRec(GetMousePosition(), Play)) DrawRectangleRec (Play, DARKGREEN);
                else DrawRectangleRec (Play, GREEN);
                if(CheckCollisionPointRec(GetMousePosition(), Options)) DrawRectangleRec (Options, DARKBLUE);
                else DrawRectangleRec (Options, BLUE);
                if(CheckCollisionPointRec(GetMousePosition(), Quit)) DrawRectangleRec (Quit, MAROON);
                else DrawRectangleRec (Quit, RED);
                DrawText ("PONG", 620, 50, 250, WHITE);
                if(CheckCollisionPointRec(GetMousePosition(), Play)) DrawText ("Play", 850, 350, 100, GRAY);
                else DrawText ("Play", 850, 350, 100, WHITE);
                if(CheckCollisionPointRec(GetMousePosition(), Options)) DrawText ("Options", 780, 620, 100, GRAY);
                else DrawText ("Options", 780, 620, 100, WHITE);
                if(CheckCollisionPointRec(GetMousePosition(), Quit)) DrawText ("Quit", 865, 890, 100, GRAY);
                else DrawText ("Quit", 865, 890, 100, WHITE);
                DrawText ("© Victor Arabi", 1500, 900, 30, WHITE);
                DrawText ("Escola Sant Marc 2018", 1500, 950, 30, WHITE);
               
                break;
                
                case GAMEPLAY:
                    if (skin == false)
                    {
                        DrawTexture (fieldTexture, 0, 0, WHITE);
                
                        DrawCircle (center.x, center.y, radius, GREEN);
                        DrawRectangleRec (Rec, BLUE);
                        DrawRectangleRec (Rec2, GREEN);
                    
                        DrawTexture (playerTexture, Rec.x, Rec.y, WHITE);
                        DrawTexture (player2Texture, Rec2.x, Rec2.y, WHITE);
                        DrawTexture (Ball, center.x - 50, center.y - 50, WHITE);
                        DrawTexturePro (Ball, (Rectangle){0, 0, Ball.width, Ball.height}, (Rectangle){center.x, center.y, Ball.width, Ball.height}, (Vector2){Ball.width/2, Ball.height/2}, rotation, WHITE);  
                    }
                    
                    if (skin == true)
                    {
                        DrawTexture (fieldTextureP, 0, 0, WHITE);
                
                        DrawCircle (center.x, center.y, radius, GREEN);
                        DrawRectangleRec (Rec, BLUE);
                        DrawRectangleRec (Rec2, GREEN);
                    
                        DrawTexture (playerTextureP, Rec.x, Rec.y, WHITE);
                        DrawTexture (player2TextureP, Rec2.x, Rec2.y, WHITE);
                        DrawTexture (Ball, center.x - 50, center.y - 50, WHITE);
                        DrawTexturePro (Ball, (Rectangle){0, 0, Ball.width, Ball.height}, (Rectangle){center.x, center.y, Ball.width, Ball.height}, (Vector2){Ball.width/2, Ball.height/2}, rotation, WHITE);  
                    }
                    
                    DrawText ("-", 932, 100, 140, WHITE);
                    
                    
                    if(Pl_Points == 0)
                    {
                        DrawText ("0", 840, 100, 140, DARKBLUE);
                    }
                    if(Pl_Points == 1)
                    {
                        DrawText ("1", 840, 100, 140, DARKBLUE);
                    }
                    if(Pl_Points == 2)
                    {
                        DrawText ("2", 840, 100, 140, DARKBLUE);
                    }
                    if(Pl_Points == 3)
                    {
                        DrawText ("3", 840, 100, 140, DARKBLUE);
                    }
                    if(Pl_Points == 4)
                    {
                        DrawText ("4", 840, 100, 140, DARKBLUE);
                    }
                    if(Pl_Points == 5)
                    {
                        DrawText ("5", 840, 100, 140, DARKBLUE);
                    }
                    if(Pl_Points == 6)
                    {
                        DrawText ("6", 840, 100, 140, DARKBLUE);
                    }
                    if(Pl_Points == 7)
                    {
                        DrawText ("7", 840, 100, 140, DARKBLUE);
                    }
                    
                    
                    if(IA_Points == 0)
                    {
                        DrawText ("0", 1010, 100, 140, RED);
                    }
                    if(IA_Points == 1)
                    {
                        DrawText ("1", 1010, 100, 140, RED);
                    }
                    if(IA_Points == 2)
                    {
                        DrawText ("2", 1010, 100, 140, RED);
                    }
                    if(IA_Points == 3)
                    {
                        DrawText ("3", 1010, 100, 140, RED);
                    }
                    if(IA_Points == 4)
                    {
                        DrawText ("4", 1010, 100, 140, RED);
                    }
                    if(IA_Points == 5)
                    {
                        DrawText ("5", 1010, 100, 140, RED);
                    }
                    if(IA_Points == 6)
                    {
                        DrawText ("6", 1010, 100, 140, RED);
                    }
                    if(IA_Points == 7)
                    {
                        DrawText ("7", 1010, 100, 140, RED);
                    }
                    
                    if(pause)
                    {
                       if((FramesCounter/30)%2) DrawText ("PAUSE", (screenWidth - MeasureText("PAUSE", 40))/2, screenHeight/2 - 20, 40, MAGENTA);
                    
                    }
                    
                    
                break;
                
                case OPTIONS:
                DrawRectangle (0, 0, screenWidth, screenHeight, BLACK);
                if(CheckCollisionPointRec(GetMousePosition(), Back)) DrawRectangleRec (Back, MAROON);
                else DrawRectangleRec (Back, RED);
                if(CheckCollisionPointRec(GetMousePosition(), Back))DrawText ("Back", 140, 885, 50, GRAY);
                else DrawText ("Back", 140, 885, 50, WHITE);
                DrawText ("OPTIONS", 610, 50, 150, WHITE);
                DrawText ("Multiplayer", 100, 300, 100, WHITE);
                if (multi == false)
                {
                    if (CheckCollisionPointRec(GetMousePosition(), Multi)) DrawRectangleRec (Multi, MAROON);
                    else DrawRectangleRec (Multi, RED);
                    if(CheckCollisionPointRec(GetMousePosition(), Multi))DrawText ("OFF", 740, 300, 100, GRAY);
                    else DrawText ("OFF", 740, 300, 100, WHITE);
                }
                if (multi == true)
                {
                    if (CheckCollisionPointRec(GetMousePosition(), Multi)) DrawRectangleRec (Multi, DARKGREEN);
                    else DrawRectangleRec (Multi, GREEN);
                    if(CheckCollisionPointRec(GetMousePosition(), Multi))DrawText ("ON", 760, 300, 100, GRAY);
                    else DrawText ("ON", 760, 300, 100, WHITE);
                }
                DrawText ("Theme", 100, 500, 100, WHITE);
                if (skin == false)
                {
                  if (CheckCollisionPointRec(GetMousePosition(), Default)) DrawRectangleRec (Default, DARKGREEN);
                    else DrawRectangleRec (Default, GREEN);
                    if(CheckCollisionPointRec(GetMousePosition(), Default)) DrawText ("Ice vs Fire", 770, 525, 50, GRAY);
                    else DrawText ("Ice vs Fire", 770, 525, 50, WHITE);  
                }
                if (skin == true)
                {
                    if (CheckCollisionPointRec(GetMousePosition(), Default)) DrawRectangleRec (Default, MAROON);
                    else DrawRectangleRec (Default, RED);
                    if(CheckCollisionPointRec(GetMousePosition(), Default)) DrawText ("Ice vs Fire", 770, 525, 50, GRAY);
                    else DrawText ("Ice vs Fire", 770, 525, 50, WHITE);
                }
                if (victory == false)
                {
                    DrawRectangleRec (Premium, GRAY);
                    DrawText ("WIN TO UNLOCK", 1255, 525, 50, BLACK);
                }
                if (victory == true)
                {
                    if (skin == false)
                    {
                        if (CheckCollisionPointRec(GetMousePosition(), Premium)) DrawRectangleRec (Premium, MAROON);
                        else DrawRectangleRec (Premium, RED);
                        if(CheckCollisionPointRec(GetMousePosition(), Premium)) DrawText ("Gold vs Silver", 1280, 525, 50, GRAY);
                        else DrawText ("Gold vs Silver", 1280, 525, 50, WHITE);    
                    }
                    if (skin == true)
                    {
                        if (CheckCollisionPointRec(GetMousePosition(), Premium)) DrawRectangleRec (Premium, DARKGREEN);
                        else DrawRectangleRec (Premium, GREEN);
                        if(CheckCollisionPointRec(GetMousePosition(), Premium)) DrawText ("Gold vs Silver", 1280, 525, 50, GRAY);
                        else DrawText ("Gold vs Silver", 1280, 525, 50, WHITE);
                    }
                }
                DrawText ("Volume", 100, 700, 100, WHITE);
                if (CheckCollisionPointRec(GetMousePosition(), VolumeUp)) DrawRectangleRec (VolumeUp, LIGHTGRAY);
                else DrawRectangleRec (VolumeUp, WHITE);
                if(CheckCollisionPointRec(GetMousePosition(), VolumeUp)) DrawText ("+", 710, 685, 150, GRAY);
                else DrawText ("+", 710, 685, 150, BLACK);
                if (CheckCollisionPointRec(GetMousePosition(), VolumeDown)) DrawRectangleRec (VolumeDown, LIGHTGRAY);
                else DrawRectangleRec (VolumeDown, WHITE);
                if(CheckCollisionPointRec(GetMousePosition(), VolumeDown)) DrawText ("-", 870, 685, 150, GRAY);
                else DrawText ("-", 870, 685, 150, BLACK);
                if (volume == 0.25f)
                {
                DrawRectangleRec (Vol1, YELLOW);
                }
                if (volume == 0.5f)
                {
                DrawRectangleRec (Vol1, YELLOW);
                DrawRectangleRec (Vol2, ORANGE);
                }
                if (volume == 0.75f)
                {
                DrawRectangleRec (Vol1, YELLOW);
                DrawRectangleRec (Vol2, ORANGE);
                DrawRectangleRec (Vol3, RED);
                }
                if (volume == 1.0f)
                {
                DrawRectangleRec (Vol1, YELLOW);
                DrawRectangleRec (Vol2, ORANGE);
                DrawRectangleRec (Vol3, RED);
                DrawRectangleRec (Vol4, MAROON);
                }
                

                break;
                
                
                case WIN:
                DrawText ("PLAYER 1 WINS", 450, 40, 150, WHITE);
                if(CheckCollisionPointRec(GetMousePosition(), Menu)) DrawRectangleRec (Menu, MAROON);
                else DrawRectangleRec (Menu, RED);
                if(CheckCollisionPointRec(GetMousePosition(), Menu))DrawText ("Menu", 140, 885, 50, GRAY);
                else DrawText ("Menu", 140, 885, 50, WHITE);
                if(CheckCollisionPointRec(GetMousePosition(), Restart)) DrawRectangleRec (Restart, DARKBLUE);
                else DrawRectangleRec (Restart, BLUE);
                if(CheckCollisionPointRec(GetMousePosition(), Restart)) DrawText ("RESTART", 740, 580, 90, GRAY);
                else DrawText ("RESTART", 740, 580, 90, WHITE);

                break;
                
                
                case LOSE:
                DrawText ("PLAYER 2 WINS", 450, 40, 150, WHITE);
                if(CheckCollisionPointRec(GetMousePosition(), Menu)) DrawRectangleRec (Menu, MAROON);
                else DrawRectangleRec (Menu, RED);
                if(CheckCollisionPointRec(GetMousePosition(), Menu))DrawText ("Menu", 140, 885, 50, GRAY);
                else DrawText ("Menu", 140, 885, 50, WHITE);
                if(CheckCollisionPointRec(GetMousePosition(), Restart)) DrawRectangleRec (Restart, DARKBLUE);
                else DrawRectangleRec (Restart, BLUE);
                if(CheckCollisionPointRec(GetMousePosition(), Restart)) DrawText ("RESTART", 740, 580, 90, GRAY);
                else DrawText ("RESTART", 740, 580, 90, WHITE);
                
                break;

            }
            
            DrawRectangle (0, 0, screenWidth, screenHeight, Fade(BLACK, alpha));
            
            
        EndDrawing();
        
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture (playerTexture);
    UnloadTexture (player2Texture);
    UnloadTexture (fieldTexture);
    UnloadTexture (playerTextureP);
    UnloadTexture (player2TextureP);
    UnloadTexture (fieldTextureP);
    UnloadTexture (Ball);
    UnloadMusicStream (MainMusic);
    UnloadMusicStream (MenuMusic);
    UnloadMusicStream (OptionsMusic);
    UnloadMusicStream (PauseMusic);
    UnloadMusicStream (Winner);
    UnloadMusicStream (Loser);
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}