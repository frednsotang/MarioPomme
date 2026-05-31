#include<stdlib.h>
#include<stdio.h>
#include<iostream>   
#include<stdbool.h>  
#include<vector>
#include<string>
#include<algorithm>  
#include<time.h> 
#include<sstream>
#include "inc/SDL.h"
#include  "inc/SDL_image.h"  
#include "inc/SDL_messagebox.h"


using  namespace   std;   

 
  class  GameOver  
  {
    public :   
    SDL_Surface  *gameover_surf =  NULL;  
    SDL_Texture  *gameover_text  =  NULL;  
    SDL_Rect   game_Over_rect =   {0,0,238,189};    
    const char  *path_src_ressource = "./ressource/img/gameOver.PNG";
    public  :  
        GameOver(SDL_Renderer  *rendu);  
     public :  
       void  drawGameover(SDL_Renderer  *rendu);  
       void  destroyAllTexutre();  
  };  

  GameOver::GameOver(SDL_Renderer  *rendu) 
  {
      this->gameover_surf  =  IMG_Load(this->path_src_ressource);  
      this->gameover_text  =  SDL_CreateTextureFromSurface(rendu ,  this->gameover_surf);  
      if(this->gameover_text  ==  NULL) 
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION , "erreur  %s",IMG_GetError());  
      else  std::cout<< "Fin du  jeu  et  affiche  du   de  la  bande"<<std::endl;  
       
      SDL_FreeSurface(this->gameover_surf);
  }  
  void  GameOver::drawGameover(SDL_Renderer *  rendu)  
  {     
        this->game_Over_rect.x  =   (760/2)  - (this->game_Over_rect.w  /2);  
        this->game_Over_rect.y  =   (550/2)  - (this->game_Over_rect.h / 2);
         SDL_SetRenderTarget(rendu  , this->gameover_text);  
        SDL_RenderCopy(rendu ,this->gameover_text  , NULL ,&this->game_Over_rect);
  }   
  void  GameOver::destroyAllTexutre()   
  {
      SDL_DestroyTexture(this->gameover_text);
  }
  class  Player  
  {
    public :   
      SDL_Surface   *player_surface =  NULL;  
      SDL_Texture   *player_text  =  NULL;   
      SDL_Rect   player_rect  =  { 45 , 345, 67,67};  
      SDL_Rect  player_src    =  {0,0,70,88}; 
      const char  *player_path  =   "./ressource/img/spriteMario.PNG"; 
      int  veloX  =  3; 
       unsigned  int  FrameCount  = 3;
       unsigned  int  FrameStart  = 0; 
       unsigned  int  FrameEnd  = 3;  
       unsigned  int frameRows    = 0; 
       unsigned  int  frameCols   = 0;
       unsigned  int  FrameWidth  = 70; 
       unsigned  int  FrameHeight = 88;
       std::string  animPath =  "r";
       int gameFrame = 0;  
       int  FrameDleay =  7;
     public :  
       Player(SDL_Renderer  *r);  
      public:  
        void  drawPlayer(SDL_Renderer   *rendu); 
        void  MovePlayer(SDL_Event  evt);  
  };  

  Player::Player(SDL_Renderer  *rendu)  
  { 
        
        this->player_surface  =  IMG_Load(this->player_path);  
        this->player_text   =   SDL_CreateTextureFromSurface(rendu ,   this->player_surface);  

        if(this->player_text ==  NULL)  SDL_LogError(SDL_LOG_CATEGORY_APPLICATION ,"erreur %s",IMG_GetError());  
        else  std::cout<< "wouah  Ma jolie image  de Mario  a  ete  chargee  !"<<std::endl; 

        SDL_FreeSurface(this->player_surface); 
  }
   
   void Player::MovePlayer(SDL_Event  evt)  
   {
      if(evt.type ==  SDL_KEYDOWN)  
      {
         if(evt.key.keysym.sym ==  SDLK_LEFT)  
         {
            this->player_rect.x -=  3 * this->veloX *  4; 
            this->animPath = "l";
         }else if(evt.key.keysym.sym ==   SDLK_RIGHT) 
         {
            this->player_rect.x +=  3 * this->veloX  *  4; 
            this->animPath = "r";

         }else  if(evt.key.keysym.sym ==  SDLK_p) 
         {   
             this->animPath = "m";
         }
      }
   }
   void  Player::drawPlayer(SDL_Renderer  *r)  
   {    
       if(this->animPath ==  "r")  
       {
           this->FrameStart++; 
           this->FrameStart %=  this->FrameCount;  

           this->frameCols =  this->FrameStart;

           this->player_src.x = this->frameCols  *  this->player_src.w;  
       }else if(this->animPath ==  "l")  
       {   
          
                    this->FrameEnd--; 

                    if(this->FrameEnd  <=  0)  
                    {
                        this->FrameEnd =  3;
                    }

           this->frameRows  = 1;
           this->frameCols  = this->FrameEnd;  
           this->player_src.x =  this->frameCols   *  this->player_src.w;
           this->player_src.y =  this->frameRows *  (this->player_src.h + 15);  

       }else   if(this->animPath ==  "m")
       {
            this->FrameStart  = 0;  
            this->frameCols  =  0;  
            this->frameRows =  0;  
            
              this->FrameStart++; 
           this->FrameStart %=  this->FrameCount;  

           this->frameCols =  this->FrameStart;

           this->player_src.x = this->frameCols  *  this->player_src.w;   
            this->player_src.y =  this->frameRows *  (this->player_src.h + 15);  
            
       }

      SDL_SetRenderTarget(r,this->player_text);  
      SDL_RenderCopy(r,this->player_text ,&this->player_src,&this->player_rect);  
     
   }   
  class  Apple   
  {
       public  :   
         SDL_Surface  *apple_surface =  NULL;  
         SDL_Texture  *apple_texture = NULL;  
         SDL_Rect  apple_rect  =  {(760/2) - (45/2) ,12,45,45};  
         const char  *path_img_apple =  "./ressource/img/pomme.png";  
         int  veloY  =  3;   
         int levelSpeed =  2;
       public  :   
         Apple(SDL_Renderer *rendu);
        public:  
         void DrawAplle(SDL_Renderer  *rendu); 
         void  MoveApple();   
         void  DestroyTexture();      
  }; 

  Apple::Apple(SDL_Renderer   *rendu) 
  {
        this->apple_surface  =    IMG_Load(this->path_img_apple);  
        this->apple_texture  =    SDL_CreateTextureFromSurface(rendu ,  this->apple_surface);  

        if(this->apple_texture  ==   NULL)   
        {
               SDL_LogError(SDL_LOG_CATEGORY_APPLICATION , "erreur  %s",IMG_GetError()); 
        }else  std::cout<<  "wouah  Ma   jolie  petite  pomme  placee tout en  Haut "<<std::endl;   
      SDL_FreeSurface(this->apple_surface);
  }  
 void  Apple::DrawAplle(SDL_Renderer  *rendu)  
 {
         SDL_SetRenderTarget(rendu ,  this->apple_texture);  
         SDL_RenderCopy(rendu ,this->apple_texture ,NULL ,&this->apple_rect);
 } 

 void  Apple::MoveApple() 
 {   
       
        this->apple_rect.y +=  this->levelSpeed * this->veloY;  
          if(this->apple_rect.y  >=  (550   -  this->apple_rect.h))  
        {
           this->apple_rect.y =  12; 
           this->apple_rect.x =   rand()  %  (760  -  this->apple_rect.w);
        }  

 }  
 
 void  Apple::DestroyTexture()  
 {
      SDL_DestroyTexture(this->apple_texture);
 }

  class  Menu  
  {
      public :   
        SDL_Surface  *btn_surface[2] =  {NULL , NULL};    
        SDL_Texture  *text_btn  =  NULL; 
        SDL_Rect btn_rect =  {0,0,160,80};    
        SDL_Rect mouse_rect = {0,0,12,12};
        const char *path_btn[2] =  
        {
          "./ressource/img/buttonPlay.PNG",  
          "./ressource/img/buttonExit.PNG"
        };
        std::vector<SDL_Rect>button_array;  
        std::vector<SDL_Texture *>button_text;  
        bool  buttonIs_Pressed_play=  false;  
        bool  buttonIs_pressed_Quit =  false;
     public :  
       Menu(SDL_Renderer  *rendu);  
     public :     
      void  CheckHoverCursor(SDL_Event  e);
     void  DrawAllButton(SDL_Renderer *rendu);
     void  DestroyAllTexture(); 
  };  

  Menu::Menu(SDL_Renderer  *rendu) 
  {
     for(int i  =  1;  i  <=2 ;  i+=1)   {
        this->btn_rect.x  =  (760  /  2)  -  (this->btn_rect.w  /2);  
        this->btn_rect.y  =   i  *  this->btn_rect.h + 78;
        this->btn_surface[i-1] =  IMG_Load(this->path_btn[i-1]);  
        
        if(this->btn_surface[i-1]   !=  NULL)  {
             this->text_btn  =   SDL_CreateTextureFromSurface(rendu ,this->btn_surface[i-1]);
             this->button_text.push_back(this->text_btn);   
             std::cout<< "woauh  Mes jolies button  !"<<std::endl;
             SDL_FreeSurface(this->btn_surface[i-1]);
        }   else    
         SDL_LogError(SDL_LOG_CATEGORY_APPLICATION , "erreur  %s",IMG_GetError());   

        this->button_array.push_back(this->btn_rect); 
     }   
  }     
  void Menu::DrawAllButton(SDL_Renderer *rendu) 
  { 
          int i   = 0;
         for(auto  &btn_text  :   this->button_text)  
         {
               SDL_SetRenderTarget(rendu,btn_text);  
               SDL_RenderCopy(rendu,btn_text,NULL,&this->button_array[i]);
               i+=1;
         } 
  }
   void  Menu::DestroyAllTexture()  
   {
       std::for_each(this->button_text.begin() ,  this->button_text.end()  ,  [&](auto  &btn)
       {
           SDL_DestroyTexture(btn);
       });  
   } 
    
   void  Menu::CheckHoverCursor(SDL_Event  e)  
   {
           if(e.type ==  SDL_MOUSEBUTTONDOWN) 
           {  
            mouse_rect.x  =  e.button.x;
            mouse_rect.y  =  e.button.y;   
            int  index_button_array  = 0;
             
         std::for_each(this->button_array.begin() ,  this->button_array.end()  , [&](auto &buttonPress) {
                 switch(index_button_array)  
                 {
                    case  0  :    
                     if(SDL_HasIntersection(&this->mouse_rect , &buttonPress))  this->buttonIs_Pressed_play  =  true;  
                    break;
                    case 1 :    
                      if(SDL_HasIntersection(&this->mouse_rect ,  &buttonPress)) this->buttonIs_pressed_Quit  = true;
                    break;
                 }   
                 index_button_array+=1; 
         });
              
           }
   }

class   Background  
{
     public :  
       SDL_Surface  *background_surf  =  NULL;  
       SDL_Texture   *background_text =  NULL; 
       SDL_Rect  background_rect =  {0,0,760,550};    
       const char  *path_src =  "./ressource/img/background.png";
    public :   
    Background(SDL_Renderer  *r);  
   public :       
      void drawBackground(SDL_Renderer  *r);  
      void DestroyAllRes();   
};   


Background::Background(SDL_Renderer   *r)  
{ 
   
     this->background_surf  =  IMG_Load(this->path_src);  
     this->background_text =  SDL_CreateTextureFromSurface(r ,  this->background_surf);

     if(this->background_text ==  NULL)    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION , "erreur  %s",SDL_GetError());  
     else  std::cout<< "wouah Mon  background  est magnifique  !"<<std::endl; 

     SDL_FreeSurface(this->background_surf);
}  
void  Background::drawBackground(SDL_Renderer  *r)  
{  
      SDL_SetRenderTarget(r,this->background_text); 
      SDL_RenderCopy(r,this->background_text ,NULL , &this->background_rect);
}  
void  Background::DestroyAllRes() 
{
  SDL_DestroyTexture(this->background_text);
}  

class  Window   
{
     public  :   
         SDL_Window  *fenetre = NULL;  
         SDL_Renderer  *rendu =  NULL;   
         SDL_Color     clr_window  =  {255,255,255,255};   
         SDL_Rect   window_rect =  {SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED ,760,550}; 
         SDL_Event event;    
         SDL_Surface  *icon_surf = IMG_Load("./ressource/img/pomme.png");
         bool  running =  true;
         int   delay_time  = 82;   
         const  char *title_window =  "MARIO POMME";  
         enum  State_Game  
         {
              MENU  ,  
              PLAY , 
              END,    
              QUIT
         };
        int stateGame =  0; 
        int levelGame =  1;
    public:    
       Window();  
       ~Window();  
    public:  
       void HandlingInput();  
       void RenderClear(); 
       void RefreshPresentWindow();   
       void DestroyAll();
};  

Window::Window() 
{
   SDL_Init(SDL_INIT_VIDEO);  
   IMG_Init(IMG_INIT_PNG  |  IMG_INIT_JPG); 


   if(SDL_CreateWindowAndRenderer(this->window_rect.w  ,  this->window_rect.h , 0 , &this->fenetre  , &this->rendu)  <  0)   SDL_LogError(SDL_LOG_CATEGORY_APPLICATION , "erreur  %s",SDL_GetError());
   else   std::cout<< "Wouah  Ma  jolie  petite  fenetre"<<std::endl;  

   SDL_SetWindowTitle(this->fenetre  ,this->title_window);   
   SDL_SetWindowIcon(this->fenetre , this->icon_surf);  
}  
Window::~Window()
{   
   IMG_Quit();
   SDL_Quit(); 
}  
void Window::HandlingInput()
{   
     SDL_PollEvent(&this->event);  

     if(this->event.type ==  SDL_QUIT)  { running  =  false; }
   
}  
void Window::RenderClear()
{
    SDL_SetRenderDrawColor(this->rendu  ,  this->clr_window.r  ,  this->clr_window.g  , this->clr_window.b  , this->clr_window.a);
    SDL_RenderClear(this->rendu);
}   
void Window::RefreshPresentWindow()
{    
   SDL_RenderPresent(this->rendu);
   SDL_Delay(this->delay_time); 
}  
void Window::DestroyAll()
{
  SDL_DestroyRenderer(this->rendu);  
  SDL_DestroyWindow(this->fenetre);
}  


int  main(int argc, char *argv[])  
{      
   
      Window  *game  =  new  Window();  
      Background *bg =  new Background(game->rendu);   
      Menu  *menu    =   new Menu(game->rendu);  
      Apple  *apple  =  new Apple(game->rendu);   
      Player  *mario  =  new Player(game->rendu); 
      GameOver *gameover =  new GameOver(game->rendu);
       

       srand((unsigned)time(NULL));    

       bool  collide =  true;
       int  score_game =  0;   
       std::string  text_set ;
       int   currentTime  =  0; 
       int lastTime  =   0;  
       int delays  =  0; 
       int timer =  120; 
       bool  endGame =  false;


       currentTime  =  SDL_GetTicks();


       

       do{
              //  Handling  input 

            game->HandlingInput();

 
           // update    
      
           menu->CheckHoverCursor(game->event);  
           mario->MovePlayer(game->event);   

           lastTime  =  SDL_GetTicks();    

           delays  =   lastTime   -  currentTime;




           if(menu->buttonIs_Pressed_play  ==  true)  
           {
                   game->stateGame  =  game->PLAY; 

           }else if(menu->buttonIs_pressed_Quit  ==  true)  
           {
                  game->stateGame =  game->QUIT;
           }

           //render  clear 

            if(game->stateGame ==  0)   
            {  
            game->RenderClear();    
            bg->drawBackground(game->rendu); 
            menu->DrawAllButton(game->rendu);   
            }else if(game->stateGame  ==  1)  
            {  
            game->RenderClear();    
            bg->drawBackground(game->rendu);  
            mario->drawPlayer(game->rendu); 
            apple->DrawAplle(game->rendu); 
            apple->MoveApple();   
            
            if(SDL_HasIntersection(&mario->player_rect ,  &apple->apple_rect))  
            {
                collide =  true;
            } 

            if(collide)  
           { 
                 score_game+=1;   
                 apple->apple_rect.x  =  rand()  %  (760 - 45); 
                 apple->apple_rect.y  =  0;
                 collide  =  false;
           }  
            
             if(delays  >=  5000)  
            {
                  timer-=1;
            }
              
             if(timer  ==  0)  
             {     
                   endGame  = true; 
                   delays  =  0; 
                   timer  = 0;
             }
              
               text_set   =  " MARIO  POMME  ||  SCORE: " + std::to_string(score_game) +   " timer  : " +   std::to_string(timer);  

               SDL_SetWindowTitle(game->fenetre ,text_set.c_str());  

            }else if(game->stateGame ==  2)  
            {  
               //  this  is End game  
            }else if(game->stateGame ==  3) 
            {  
                  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "FIN  DU  JEU","Voulez-vous  Quittez le  jeu",game->fenetre);  
                  game->running  =  false;
            }
             

            if(endGame)  
            {
            game->RenderClear();    
            bg->drawBackground(game->rendu);  
            gameover->drawGameover(game->rendu);  
            delays  =  0;
            timer  =  0;  
            }


           //  refesh window 

           game->RefreshPresentWindow();
            


     }while(game->running  !=  false);
        
       gameover->destroyAllTexutre();
       apple->DestroyTexture();
       menu->DestroyAllTexture();
       bg->DestroyAllRes();
       game->DestroyAll(); 




       //  destroy all pointeur  
       delete  gameover;
       delete  mario; 
       delete apple;
       delete  bg;
       delete game;
        return  1;  
}