#include "sprite.hpp"
#include "openai-helper.hpp"
#include "raylib-cpp.hpp"
#include <string>
#include <optional>
#include <vector>
#include <numeric> // std::iota
#include <iostream>

void update_prompt(std::string& prompt, const std::string& str, const int font_size,
                   const float max_text_width, int& tail_index_large,
                   int& tail_index_small, int& nchars_entered);

class NPC
{
public:
    NPC(const char* filepath, Vector2 position, int nCols, int nRows, int frames) : tex_{ filepath }, npcSprite_{ tex_, nCols, nRows, position, {frames}, 0 }
    {
       
    }
    
    Vector2 position{};
    int nCols{};
    int nRows{};
    int frames{};
    raylib::Texture tex_;
    aipfg::Sprite npcSprite_;
    bool npcColision = false;
    std::string npc_stop = "Lost Soul: ";
    std::string human_stop = "Knight: ";
    std::string new_lines = "\n\n\n\n\n\n\n\n\n";

    std::string prompt = new_lines + npc_stop +
        "Why are you here?\n" + human_stop;

    std::string nature_ = "The following is a conversation between a lost soul and a human, the"
        "lost soul is reasonable and respectful, and encourage the human to try to escape the room";
    void Draw()
    {
        npcSprite_.draw();
    }

    Vector2 getPosn()
    {
       return npcSprite_.get_posn();
    }
    void setPosn(Vector2 newPos)
    {
        npcSprite_.set_posn(newPos);
    }

    void SetPrompt(std::string newPrompt)
    {
        prompt = new_lines + npc_stop +
            newPrompt+ "\n" + human_stop;
    }

    void SetNature(std::string newNature)
    {
        nature_ = newNature;
    }

    void SetStop(std::string newStop)
    {
        npc_stop = newStop;
    }
};

int main(int argc, char* argv[])
{
    using namespace aipfg;
    bool candle0B = false;
    bool candle1B = false;
    bool candle2B = false;
    bool candle3B = false;

    bool candlesB[] = { false,false,false,false,false,false };
    bool scene1 = true;
    bool scene2 = false;
    bool scene3 = false;
    bool scene4 = false;
    bool dead = false;
    openai_helper oai_help;
    if (!oai_help.init())
    {
        return -1;
    }

    raylib::Window window(1024, 576, "Raylib OpenAI NPCs");

    SetTargetFPS(60);            // Set our game to run at 60 frames-per-second

    raylib::AudioDevice audio{}; // necessary: initialises the audio
    raylib::Sound coin_sound{ "../resources/audio/coin.wav" };
    raylib::Music music{ "../resources/audio/Magic-Clock-Shop.mp3" };
    float music_volume_normal = 1.0f, music_volume_quiet = 0.4f;
    music.Play();

   
    NPC reaper{ "../resources/time_fantasy/reaper_blade_3.png" ,Vector2{435,192 },3,4,0 };
    reaper.SetStop("Grim Reaper: ");
    reaper.SetPrompt("Why are you here ? ");
    reaper.SetNature("The following is a conversation between the grim reaper and a knight. The grim reaper is a "
        "personified force. In some mythologies, the grim reaper causes the "
        "victim's death by coming to collect that person's soul. The grim reaper knows the secret code to the room to be 1,4,2,3,6,5 but will not tell the human unless he says anything containing the word please\n\n");






    raylib::Texture tex4{ "../resources/Candles/candleA_01.png" };
    Vector2 candleOrigin{ -1, -1 };



    Sprite candles[] = { { tex4,1,1,{200,50},{0},0 },{ tex4,1,1,{300,50},{0},0 },{ tex4,1,1,{400,50},{0},0 },{ tex4,1,1,{500,50},{0},0 },{ tex4,1,1,{600,50},{0},0 },{ tex4,1,1,{700,50},{0},0 } };
    for (int i = 0; i < 6; i++)
    {
        candles[i].set_origin(candleOrigin);
    }

    raylib::Texture tex2{ "../resources/time_fantasy/knights_3x.png" };
    int ncols = 12, nrows = 8;
    int id = 3;
    Vector2 grey_posn{ 40.0f, 100.0f };
    Sprite grey_down{ tex2, ncols, nrows, grey_posn, { id, id + 1, id + 2 }, 6 };
    id += ncols;
    Sprite grey_left{ tex2, ncols, nrows, grey_posn, { id, id + 1, id + 2 }, 6 };
    id += ncols;
    Sprite grey_right{ tex2, ncols, nrows, grey_posn, { id, id + 1, id + 2 }, 6 };
    id += ncols;
    Sprite grey_up{ tex2, ncols, nrows, grey_posn, { id, id + 1, id + 2 }, 6 };

    NPC king{ "../resources/time_fantasy/knights_3x.png",Vector2{600,400 },12,8,1 };
    king.SetStop("King Zera: ");
    king.SetPrompt("Ah dear knight, might you explain where we are? ");
    king.SetNature("The following is a conversation between the king Zera and a knight,he is in a room with the green knight and the black knight but will not speak to them. The King is a "
        "powwerful ruler and once the humans king, he is unsure where he is, the last thing he remembers is drinking with the knight before being transported here"
        "He also knows that the black knight was once in service to another king.  And the green knight was once an alchemist."
    );

    NPC blackKnight{ "../resources/time_fantasy/knights_3x.png",Vector2{450,400 },12,8,1 };
    blackKnight.SetStop("Black Knight: ");
    blackKnight.SetPrompt("Ah it's you. ");
    blackKnight.SetNature("The following is a conversation between the black knight and a knight, he is in a room with the green knight and the king. The black knight is a "
        "man of few words and once the knights peer, he is unsure where he is, the last thing he remembers is eating breakfast before being transported here"
        "He also knows that the king had a mistress and was worried outhers might find out.  And the green knight was not on duty the night before he arrived here."
    );

    NPC greenKnight{ "../resources/time_fantasy/knights_3x.png",Vector2{300,400 },12,8,1 };
    greenKnight.SetStop("Green Knight: ");
    greenKnight.SetPrompt("Ah my old friend, perhaps you can share some information. \n"
        "on where we are");
    greenKnight.SetNature("The following is a conversation between the green knight and a knight, he is in a room with the black knight and the king. The green knight loves the sound of his own voice  "
        " and was once the knights peer, he is unsure where he is, the last thing he remembers is speaking to a shadowy man before being transported here"
        "He also knows that the king killed his brother a long time ago, but he has since forgiven him.  And the black knight was in service to his old lover."
    );

    Sprite king_candle = { tex4,1,1,{600,320},{0},0 };
    Sprite bKnight_candle = { tex4,1,1,{450,320},{0},0 };
    Sprite gKnight_candle = { tex4,1,1,{300,320},{0},0 };

    king_candle.set_origin(candleOrigin);
    bKnight_candle.set_origin(candleOrigin);
    gKnight_candle.set_origin(candleOrigin);


  raylib::Texture tex3{ "../resources/time_fantasy"
                        "/tf_ashlands/3x_RMMV/tf_A5_ashlands_3.png" };
  raylib::Texture tex6{ "../resources/autotiles/animatedwater.png" };
  
  raylib::Texture grassTex("../resources/forest/groundtileset.png");
  
 
  ncols = 8; nrows = 16;
  std::vector<int> frame_ids(ncols*nrows);
  std::iota(frame_ids.begin(), frame_ids.end(), 0);
  Sprite all_ground_cells { tex3, ncols, nrows, { 50,50 }, frame_ids, 5 };
  all_ground_cells.set_animation(true);
  Sprite grnd1 { tex3, ncols, nrows, { 450, 50 }, { 1,2,3,4 } };
  Sprite cave1 = { tex3,ncols,nrows,{460,95}, {104} };
  Sprite cave = { tex3,ncols,nrows,{460,50}, {96} };
  Sprite topWall = { tex3,ncols,nrows,{50,300}, {49} };
  Sprite topleftWall = { tex3,ncols,nrows,{50,300}, {48} };
  Sprite toprightWall = { tex3,ncols,nrows,{50,300}, {50} };
  Sprite leftWall = { tex3,ncols,nrows,{50,300}, {56} };
  Sprite rightWall = { tex3,ncols,nrows,{50,300}, {58} };
  Sprite bottomWall = { tex3,ncols,nrows,{50,300}, {65} };
  Sprite bottomLeftWall = { tex3,ncols,nrows,{50,300}, {64} };
  Sprite bottomRightWall = { tex3,ncols,nrows,{50,300}, {66} };
  Sprite grass = { tex3,ncols,nrows,{50,300}, {17,18,17,18} };
  Sprite* grey_knight = &grey_right;
  const float grey_speed = 2.5f;

  bool reaper_collision = false; // currently colliding with the reaper?
  std::string current_Nature =
   "The following is a conversation between the grim reaper and a human. The grim reaper is a "
   "personified force. In some mythologies, the grim reaper causes the "
   "victim's death by coming to collect that person's soul. The grim reaper knows the secret code to the room to be 1,4,2,3,6,5 but will not tell the human unless he says anything containing the word please\n\n";

  const int font_size = 30; // n.b. "spacing" varies with the font & font size
  //bool display_text_box = true; SetExitKey(0); // debug
  bool display_text_box = false;
  const float border = 20;
  const float jump_fix = 4;
  const float box_width = (float)window.GetWidth() - (2 * border);
  const float average_word_size = MeasureText("Abcdefg", font_size);
  const float max_text_width = box_width - average_word_size;
  const float box_ypos = (float)window.GetHeight() - 200;
  const float box_height_small = (float)window.GetHeight() - box_ypos - border;
  const float box_height_large = (float)window.GetHeight() - (2 * border) + jump_fix;
  Rectangle text_box_small{ border, box_ypos, box_width, box_height_small };
  Rectangle text_box_large{ border, border - jump_fix,   box_width, box_height_large };
  Rectangle* text_box = &text_box_small;

  std::string human_stop = "Knight: ";
  std::string current_Stop = "Grim Reaper: ";
  std::string new_lines = "\n\n\n\n\n\n\n\n\n"; // 9
  std::string current_Prompt = new_lines + current_Stop +
                              "Why are you here?\n" + human_stop;
  

  int tail_index_large = 0;
  int tail_index_small = current_Prompt.rfind('\n');
      tail_index_small = current_Prompt.rfind('\n', tail_index_small - 1);
  int* tail_index = &tail_index_small;
  int nchars_entered = 0;
  int seed[] = { rand() % 4,rand() % 4,rand() % 4 ,rand() % 4 };
  
  while (!window.ShouldClose()) // Detect window close button or ESC key
  {
    music.Update();

    (*grey_knight).set_animation(false);

    if (display_text_box)
    {
      switch (GetKeyPressed())
      {
        case KEY_ESCAPE:
          if (text_box == &text_box_large) // esc resumes the small text box
          {
            text_box = &text_box_small;
            tail_index = &tail_index_small;
           
          }
          else
          {
            SetExitKey(KEY_ESCAPE);
            display_text_box = false;
            music.SetVolume(music_volume_normal);
            
          }
          break;

        case KEY_ENTER:
          {
          std::string response_str{};
          update_prompt(current_Prompt, '\n' + current_Stop, font_size, max_text_width,
                        tail_index_large, tail_index_small, nchars_entered);
          const auto stop = std::optional{std::vector{human_stop, current_Stop}};
          oai_help.submit(current_Nature + current_Prompt, response_str, stop);
          for (auto& c : response_str)
          {
            c = (c=='\n') ? ' ' : c; // replace newlines with spaces
          }
          response_str += '\n' + human_stop;
          update_prompt(current_Prompt, response_str, font_size, max_text_width,
                        tail_index_large, tail_index_small, nchars_entered);
          nchars_entered = 0;
          }
          break;

        case KEY_UP:
            tail_index = &tail_index_large;
          text_box = &text_box_large;
          
          break;

        case KEY_BACKSPACE:
          if (nchars_entered > 0)
          {
            bool reposition = current_Prompt.back() == '\n'; // last char is newline
            current_Prompt.pop_back();
            nchars_entered--;
            if (reposition)
            {
              tail_index_large = current_Prompt.rfind('\n', tail_index_large - 2) + 1;
              tail_index_small = current_Prompt.rfind('\n', tail_index_small - 2) + 1;
            }
          }
          break;
      }

      while (int key = GetCharPressed())
      {
        if ((key >= 32) && (key <= 125)) // e.g. don't grab the ESC key
        {
          update_prompt(current_Prompt, std::string{(char)key}, font_size, max_text_width,
                        tail_index_large, tail_index_small, nchars_entered);
        }
      }
    }
    else
    {
      if (IsKeyDown(KEY_DOWN))
      {
        grey_posn.y += grey_speed;
        grey_knight = &grey_down;
        (*grey_knight).set_animation(true);
      }
      if (IsKeyDown(KEY_UP))
      {
        grey_posn.y -= grey_speed;
        grey_knight = &grey_up;
        (*grey_knight).set_animation(true);
      }
      if (IsKeyDown(KEY_LEFT))
      {
        grey_posn.x -= grey_speed;
        grey_knight = &grey_left;
        (*grey_knight).set_animation(true);
      }
      if (IsKeyDown(KEY_RIGHT))
      {
        grey_posn.x += grey_speed;
        grey_knight = &grey_right;
        (*grey_knight).set_animation(true);
      }

      (*grey_knight).set_posn(grey_posn);

      if (Vector2Distance(grey_posn, reaper.getPosn()) < 30.0f)
      {
        if (!reaper.npcColision)
        {
            current_Stop = reaper.npc_stop;
            current_Nature = reaper.nature_;
            current_Prompt = reaper.prompt;
            tail_index_small = current_Prompt.rfind('\n');
            tail_index_small = current_Prompt.rfind('\n', tail_index_small - 1);
            tail_index = &tail_index_small;
           
            
            reaper.npcColision = true;
            
          reaper_collision = true;
          display_text_box = true;
          SetExitKey(0);
          coin_sound.Play();
          music.SetVolume(music_volume_quiet);
        }
      }
      else
      {
        reaper.npcColision = false;
      }

      if (Vector2Distance(grey_posn, king.getPosn()) < 30.0f)
      {
          if (scene3)
          {
              if (!king.npcColision)

              {
                  current_Stop = king.npc_stop;
                  current_Nature = king.nature_;
                  current_Prompt = king.prompt;

                  tail_index_small = current_Prompt.rfind('\n');
                  tail_index_small = current_Prompt.rfind('\n', tail_index_small - 1);
                  tail_index = &tail_index_small;

                  king.npcColision = true;

                  reaper_collision = true;
                  display_text_box = true;
                  SetExitKey(0);
                  coin_sound.Play();
                  music.SetVolume(music_volume_quiet);
              }
          }
      }
      else {
          king.npcColision = false;
      }

      if (Vector2Distance(grey_posn, blackKnight.getPosn()) < 30.0f)
      {
          if (scene3)
          {
              if (!blackKnight.npcColision)
              {
                  current_Stop = blackKnight.npc_stop;
                  current_Nature = blackKnight.nature_;
                  current_Prompt = blackKnight.prompt;
                  tail_index_small = current_Prompt.rfind('\n');
                  tail_index_small = current_Prompt.rfind('\n', tail_index_small - 1);
                  tail_index = &tail_index_small;


                  blackKnight.npcColision = true;

                  reaper_collision = true;
                  display_text_box = true;
                  SetExitKey(0);
                  coin_sound.Play();
                  music.SetVolume(music_volume_quiet);
              }
          }
      }
      else
      {
          blackKnight.npcColision = false;
      }

      if (Vector2Distance(grey_posn, greenKnight.getPosn()) < 30.0f)
      {
          if (scene3||scene4)
          {
              if (!greenKnight.npcColision)
              {
                  current_Stop = greenKnight.npc_stop;
                  current_Nature = greenKnight.nature_;
                  current_Prompt = greenKnight.prompt;
                  tail_index_small = current_Prompt.rfind('\n');
                  tail_index_small = current_Prompt.rfind('\n', tail_index_small - 1);
                  tail_index = &tail_index_small;
                 


                  greenKnight.npcColision = true;

                  reaper_collision = true;
                  display_text_box = true;
                  SetExitKey(0);
                  coin_sound.Play();
                  music.SetVolume(music_volume_quiet);
              }
          }
      }
      else
      {
          greenKnight.npcColision = false;
      }
      /*if (Vector2Distance(grey_posn, reap.getPosn()) < 30.0f)
      {
          if (!reaper_collision)
          {
              reap.npcColision = true;
              current_Prompt = reap.prompt;
              current_Nature = reap.nature_;
              current_Stop = reap.npc_stop;
              display_text_box = true;
              SetExitKey(0);
              coin_sound.Play();
              music.SetVolume(music_volume_quiet);
          }
      }
      else
      {
          reap.npcColision = false;
      }*/


      


      if (Vector2Distance(grey_posn,candles[0].get_posn()) < 30.0f)
      {
          if (IsKeyDown(KEY_E))
          {
              coin_sound.Play();
              candles[0].set_colour(PURPLE);
              candlesB[0] = true;
          }
          
      }
      if (Vector2Distance(grey_posn, candles[1].get_posn()) < 30.0f)
      {
          if (IsKeyDown(KEY_E))
          {
              
             
              if (candlesB[3])
              {
                  
                  coin_sound.Play();
                  candles[1].set_colour(PURPLE);
                  candlesB[1] = true;
              }
              else
              {
                  for (int i = 0; i < sizeof(candlesB); i++)
                  {
                      
                      candlesB[i] = false;
                      candles[i].set_colour(WHITE);
                  }
              }
          }

          
          
      }

      if (Vector2Distance(grey_posn, candles[2].get_posn()) < 30.0f)
      {
          if (IsKeyDown(KEY_E))
          {
             
              if (candlesB[1])
              {
                  coin_sound.Play();
                  candles[2].set_colour(PURPLE);
                  candlesB[2] = true;
              }
              else
              {
                  for (int i = 0; i < sizeof(candlesB); i++)
                  {
                      candlesB[i] = false;
                      candles[i].set_colour(WHITE);
                  }
              }

              
              
          }
      }

      if (Vector2Distance(grey_posn, candles[3].get_posn()) < 30.0f)
      {
          if (IsKeyDown(KEY_E))
          {
              if (candlesB[0])
              {
                  coin_sound.Play();
                  candles[3].set_colour(PURPLE);
                  candlesB[3] = true;
                  
              }
              else
              {
                  for (int i = 0; i < sizeof(candlesB); i++)
                  {
                      candlesB[i] = false;
                      candles[i].set_colour(WHITE);
                  }
              }
          }
      }

      if (Vector2Distance(grey_posn, candles[4].get_posn()) < 30.0f)
      {
          if (IsKeyDown(KEY_E))
          {
              if (candlesB[5])
              {
                  coin_sound.Play();
                  candles[4].set_colour(PURPLE);
                  candlesB[4] = true;

              }
              else
              {
                  for (int i = 0; i < sizeof(candlesB); i++)
                  {
                      candlesB[i] = false;
                      candles[i].set_colour(WHITE);
                  }
              }
          }
      }

      if (Vector2Distance(grey_posn, candles[5].get_posn()) < 30.0f)
      {
          if (IsKeyDown(KEY_E))
          {
              if (candlesB[2])
              {
                  coin_sound.Play();
                  candles[5].set_colour(PURPLE);
                  candlesB[5] = true;

              }
              else
              {
                  for (int i = 0; i < sizeof(candlesB); i++)
                  {
                      candlesB[i] = false;
                      candles[i].set_colour(WHITE);
                  }
              }
          }
      }


      if (candlesB[4])
      {
          if (scene1)
          {
              scene1 = false;
              scene2 = true;
              reaper.SetPrompt("Ah, it is good to see you still alive");
              reaper.SetNature("The following is a conversation between the grim reaper and a human. The grim reaper is a "
                  "personified force. In some mythologies, the grim reaper causes the "
                  "victim's death by coming to collect that person's soul. The grim reaper wishes to congratulate the player on entering the secret code, and opening the door to the next realm\n\n");
          }
      }
    }

    if (Vector2Distance(grey_posn, cave.get_posn()) < 30.0f)
    {
        if (scene2)
        {
            if (IsKeyDown(KEY_E))
            {
                scene1 = false;
                scene2 = false;
                scene3 = true;
                reaper.setPosn({ 420,100 });
                reaper.SetPrompt("Welcome, do you wish to know how to proceed?");
                reaper.SetNature("The following is a conversation between the grim reaper and a human. The grim reaper is a "
                    "personified force. In some mythologies, the grim reaper causes the "
                    "victim's death by coming to collect that person's soul. The grim reaper will inform the knight that the knight must find which of the men here killed the knight. The men are the black knight, the green knight and the king.\n\n");
            }
        }
    }

    if (Vector2Distance(grey_posn, king_candle.get_posn()) < 30.0f)
    {
        if (scene3)
        {
            if (IsKeyDown(KEY_E))
            {
                scene1 = false;
                scene2 = false;
                scene3 = false;
                dead = true;
            }
        }
    }

    if (Vector2Distance(grey_posn, bKnight_candle.get_posn()) < 30.0f)
    {
        if (scene3)
        {
            if (IsKeyDown(KEY_E))
            {
                scene1 = false;
                scene2 = false;
                scene3 = false;
                dead = true;
            }
        }
    }

    if (Vector2Distance(grey_posn, gKnight_candle.get_posn()) < 30.0f)
    {
        if (scene3)
        {
            if (IsKeyDown(KEY_E))
            {
                scene3 = false;
                scene4 = true;
                gKnight_candle.set_colour(PURPLE);
                reaper.SetPrompt("Well done, you may continue.");
                reaper.SetNature("The following is a conversation between the grim reaper and a knight.The grim reaper is a "
                    "personified force. In some mythologies, the grim reaper causes the "
                    "victim's death by coming to collect that person's soul. The grim reaper wishes to congratulate the knight on finding out that the green knight killed the knight, and opening the door to the next realm\n\n"); 
                greenKnight.SetPrompt("...");
                greenKnight.SetNature("The following is a conversation between the green knight and another knight, The green knight will only ever say '...'.");

            }
        }
    }

    if (dead)
    {
        if (IsKeyDown(KEY_SPACE))
        {
            dead = false;
            scene1 = true;
            scene2 = false;
            scene3 = false;
        }
    }
    
    BeginDrawing();

    ClearBackground(RAYWHITE);

   
    if (scene1)
    {
      
        for (int i = 0; i < 24; i++)
        {
            for (int j = 0; j < 12; j++)
            {

                grnd1.draw_cell( i, j,i%grnd1.get_frame_ids_size());
            }
        }
       
        for each (Sprite candle in candles)
        {
            candle.draw();
        }
        for (int i = 0; i < 24; i++)
        {
            topWall.draw_cell(i,0);
        }
        for (int i = 0; i < 14; i++)
        {
            leftWall.draw_cell(0, i);
        }
        for (int i = 0; i < 14; i++)
        {
            rightWall.draw_cell(20, i);
        }

        for (int i = 0; i < 24; i++)
        {
            bottomWall.draw_cell(i, 11);
        }

        topleftWall.draw_cell(0, 0);
        toprightWall.draw_cell(20, 0);
        bottomLeftWall.draw_cell(0, 11);
        bottomRightWall.draw_cell(20, 11);
        
        // Drawn from back (-ve y coord) to front (+ve y coord)
        if (grey_posn.y < reaper.getPosn().y)
        {
            (*grey_knight).draw();
            reaper.Draw();
        }
        else
        {
            reaper.Draw();
            (*grey_knight).draw();
        }

        if (display_text_box)
        {
            Color light_gray_transparent{ 80, 80, 80, 192 }; // 192/256 nontransparent
            DrawRectangleRec(*text_box, light_gray_transparent);
            unsigned int milliseconds = (unsigned int)(GetTime() * 1000.0);
            
            std::string s = &current_Prompt[*tail_index];

            if ((milliseconds % 1000) > 500)
            {
                s.push_back('_');
            }
            DrawText(s.c_str(), (*text_box).x + 12, (*text_box).y + 12, font_size, WHITE);
        }
    }

    if (scene2)
    {
       
        for (int i = 0; i < 24; i++)
        {
            for (int j = 0; j < 12; j++)
            {

                grnd1.draw_cell(i, j, i % grnd1.get_frame_ids_size());
            }
        }

        for (int i = 0; i < 24; i++)
        {
            topWall.draw_cell(i, 0);
        }
        for (int i = 0; i < 14; i++)
        {
            leftWall.draw_cell(0, i);
        }
        for (int i = 0; i < 14; i++)
        {
            rightWall.draw_cell(20, i);
        }

        for (int i = 0; i < 24; i++)
        {
            bottomWall.draw_cell(i, 11);
        }

        topleftWall.draw_cell(0, 0);
        toprightWall.draw_cell(20, 0);
        bottomLeftWall.draw_cell(0, 11);
        bottomRightWall.draw_cell(20, 11);
        cave1.draw();
        cave.draw();


        // Drawn from back (-ve y coord) to front (+ve y coord)
        if (grey_posn.y < reaper.getPosn().y)
        {
            (*grey_knight).draw();

            reaper.Draw();
        }
        else
        {
            reaper.Draw();
            (*grey_knight).draw();
        }


        if (display_text_box)
        {
            if (display_text_box)
            {
                Color light_gray_transparent{ 80, 80, 80, 192 }; // 192/256 nontransparent
                DrawRectangleRec(*text_box, light_gray_transparent);
                unsigned int milliseconds = (unsigned int)(GetTime() * 1000.0);

                std::string s = &current_Prompt[*tail_index];

                if ((milliseconds % 1000) > 500)
                {
                    s.push_back('_');
                }
                DrawText(s.c_str(), (*text_box).x + 12, (*text_box).y + 12, font_size, WHITE);
            }
        }
    }

    if (scene3)
    {
        
        for (int i = 0; i < 24; i++)
        {
            for (int j = 0; j < 12; j++)
            {

                grass.draw_cell(i, j, seed[i % grass.get_frame_ids_size()]);
            }
        }

        greenKnight.Draw();
        king.Draw();
        king_candle.draw();
        gKnight_candle.draw();
        bKnight_candle.draw();
        blackKnight.Draw();


        // Drawn from back (-ve y coord) to front (+ve y coord)
        if (grey_posn.y < reaper.getPosn().y)
        {
            (*grey_knight).draw();
            reaper.Draw();
        }
        else
        {
            reaper.Draw();
            (*grey_knight).draw();
        }

      

        if (display_text_box)
        {
            Color light_gray_transparent{ 80, 80, 80, 192 }; // 192/256 nontransparent
            DrawRectangleRec(*text_box, light_gray_transparent);
            unsigned int milliseconds = (unsigned int)(GetTime() * 1000.0);

            std::string s = &current_Prompt[*tail_index];

            if ((milliseconds % 1000) > 500)
            {
                s.push_back('_');
            }
            DrawText(s.c_str(), (*text_box).x + 12, (*text_box).y + 12, font_size, WHITE);
        }
    }

    if (scene4)
    {

        for (int i = 0; i < 24; i++)
        {
            for (int j = 0; j < 12; j++)
            {

                grass.draw_cell(i, j, seed[i % grass.get_frame_ids_size()]);
            }
        }

        greenKnight.Draw();

        gKnight_candle.draw();




        // Drawn from back (-ve y coord) to front (+ve y coord)
        if (grey_posn.y < reaper.getPosn().y)
        {
            (*grey_knight).draw();
            reaper.Draw();
        }
        else
        {
            reaper.Draw();
            (*grey_knight).draw();
        }



        if (display_text_box)
        {
            Color light_gray_transparent{ 80, 80, 80, 192 }; // 192/256 nontransparent
            DrawRectangleRec(*text_box, light_gray_transparent);
            unsigned int milliseconds = (unsigned int)(GetTime() * 1000.0);

            std::string s = &current_Prompt[*tail_index];

            if ((milliseconds % 1000) > 500)
            {
                s.push_back('_');
            }
            DrawText(s.c_str(), (*text_box).x + 12, (*text_box).y + 12, font_size, WHITE);
        }
    }

    if (dead)
    {
        for (int i = 0; i < 24; i++)
        {
            for (int j = 0; j < 12; j++)
            {

                grnd1.draw_cell(i, j, i % grnd1.get_frame_ids_size());
            }
        }
        std::string s = "   You have died. Again.\n\n\n Press Space to restart";
        DrawText(s.c_str(), 320, window.GetHeight() / 2, font_size, WHITE);
        
    }

    EndDrawing();
  }

  return 0;
}



void update_prompt(std::string& prompt, const std::string& str, const int font_size,
                   const float max_text_width, int& tail_index_large,
                   int& tail_index_small, int& nchars_entered){
  for (char c : str)
  {
    const char* psz = &prompt[prompt.rfind('\n') + 1];

    if (c == ' ' && MeasureText(psz, font_size) > max_text_width)
    {
      c = '\n';
    }

    if (c == '\n')
    {
      tail_index_large = prompt.find('\n', tail_index_large) + 1;
      tail_index_small = prompt.find('\n', tail_index_small) + 1;
    }

    prompt.push_back(c);
    nchars_entered++;
  }
}


