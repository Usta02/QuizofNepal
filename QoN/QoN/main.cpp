#include <iostream>
#include <SFML/Graphics.hpp>
#include "defination.hpp"
#include <SFML/Audio.hpp>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

sf::Vector2f setSize(float width, float height, sf::Texture tempTexture);
float get_center_x(float);
float get_center_y(float);
bool release = true;


int main()
{

/********************** Declaring database Variables ***************************/
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

/********************** Open database ***************************/
   rc = sqlite3_open("quiz.db", &db);
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }

/********************** Query to database ***************************/
   sql = "SELECT * from quiz WHERE type='text'";
  // sql = "INSERT INTO quiz (Question,opt1,opt2,opt3,opt4,answer,type,sector) "  \
 "VALUES ('National bird of nbdsfbdepal', 'cfbdbfdow', 'bdbfddog','bdbfcat', 'rupeegdge', 'rupeesdf', 'text', 'Nandgnfdture');";
   rc = sqlite3_exec(db, sql, callback,0, &zErrMsg);  // Callback function gets the values returned by query
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      std::cout<<"Operation done successfully\n"<<std::endl;
   }
   sqlite3_close(db);

//sql = "INSERT INTO quiz (Question,opt1,opt2,opt3,opt4,answer,type,sector) "  \
 "VALUES ('National bird of nepal', 'cow', 'dog',' cat', 'rupee', 'rupee', 'text', 'Nature');




/******************* Declaing Variables *************************************************************/
    sf::SoundBuffer mouse_buffer;
	sf::Sound smouse;
    sf::Texture welcomeTexture,flagTexture;
    sf::Sprite welcomeSprite,flagSprite;
    sf::Text start;
    sf::Font font,font1;
    sf::Clock clock;
    sf::Music bg_music;


/******************* Loading Resource Files *************************************************************/
    bg_music.openFromFile("res/background.wav");
    mouse_buffer.loadFromFile("res/mouseclick.wav");
    font1.loadFromFile("res/times.ttf");
    font.loadFromFile("res/dominojack.otf");
    flagTexture.loadFromFile("res/flag.png");
    welcomeTexture.loadFromFile("res/menu.jpg");


/******************* On Window Launch *************************************************************/
    smouse.setBuffer(mouse_buffer);
	smouse.setVolume(50);
	bg_music.play();
	bg_music.setLoop(true);
	bg_music.setVolume(10);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE ,sf::Style::Close | sf::Style::Titlebar);
    while(window.isOpen()){
        goto STARTUP_LAUNCHER;
        break;
    }

/******************* Initial 3 Seconds Display Screen *************************************************************/

    STARTUP_LAUNCHER:{
        while(window.isOpen()) {
                sf::Event evnt;
                while(window.pollEvent(evnt)){
                    if(evnt.type==sf::Event::Closed) window.close();
                }
                window.clear();
                start.setFont(font1);
                start.setCharacterSize(80);
                start.setColor(sf::Color::Red);
                start.setString("Quiz of Nepal (QoN) \n\n"
                                "Project By: \n\n"
                                "Usta Adhikari \nAnurupa Dhamala \nKiran Neupane \nPrabhat Neupane");
                start.setPosition(get_center_x(start.getGlobalBounds().width), get_center_y(start.getGlobalBounds().height));
                window.draw(start);
                window.display();

                if(clock.getElapsedTime().asSeconds() > 3 ) {
                    goto START_MAIN_WINDOW;
                    break;
                }
            }
    }

/******************* Home Window Display Screen *************************************************************/

    START_MAIN_WINDOW:{
        /********** Drawing Home Background ************/
        welcomeSprite.setTexture(welcomeTexture);
        welcomeSprite.setPosition(0,0);
        sf::Vector2f scaleWelcome = setSize(1024,1024,welcomeTexture);
        welcomeSprite.setScale(scaleWelcome);
        window.draw(welcomeSprite);
        /********** Drawing Title ************/

		sf::Text title("Quiz Of Nepal", font, 95);
		title.setStyle(sf::Text::Bold);
		title.setColor(sf::Color::Red);
		title.setPosition(get_center_x(title.getGlobalBounds().width), 30);
		window.draw(title);
        /********** Drawing Control Buttons ************/
        std::string str[] = { "New game", "High score", "About", "Exit" };
		sf::Text buttons[4];
		int i;
		for (i = 0; i < 4; i++)
		{
			buttons[i].setFont(font);
			buttons[i].setCharacterSize(50);
			buttons[i].setString(str[i]);
			buttons[i].setColor(sf::Color(128, 128, 0));
			buttons[i].setPosition(SCREEN_WIDTH-450, 450 + i * 60);
			window.draw(buttons[i]);

		}

        while(window.isOpen()) {
            sf::Event evnt;
            while(window.pollEvent(evnt)){
                if(evnt.type==sf::Event::Closed) window.close();

                if(evnt.type==sf::Event::MouseButtonPressed){
                    smouse.play();
                    if(release && (buttons[3].getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))) {
                        window.close();
                    }
                    if(release && (buttons[0].getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))) {
                        goto START_NEW_GAME;
                    }



                    release=false;
                }



                if(evnt.type==sf::Event::MouseButtonReleased) release=true;
            }

                window.clear();
                /********** Mouse Over Button Effect ************/

                if(buttons[0].getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)) {
                    buttons[0].setColor(sf::Color::Blue);
                }else{
                    buttons[0].setColor(sf::Color(128, 128, 0));
                }
                if(buttons[1].getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)) {
                    buttons[1].setColor(sf::Color::Blue);
                }
                else{
                    buttons[1].setColor(sf::Color(128, 128, 0));
                }
                if(buttons[2].getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)) {
                    buttons[2].setColor(sf::Color::Blue);
                }else{
                    buttons[2].setColor(sf::Color(128, 128, 0));
                }
                if(buttons[3].getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)) {
                    buttons[3].setColor(sf::Color::Blue);
                }else{
                    buttons[3].setColor(sf::Color(128, 128, 0));
                }

                window.draw(welcomeSprite);
                window.draw(title);
                window.draw(buttons[0]);
                window.draw(buttons[1]);
                window.draw(buttons[2]);
                window.draw(buttons[3]);
                /********** Display Window ************/

                window.display();
        }
    }

    START_NEW_GAME:{
        sf::Texture btn;
        btn.loadFromFile("res/qstn_box.png");
        sf::Sprite btn2_sprite,btn1_sprite,btn3_sprite,btn4_sprite,btnq_sprite;
        sf::Vector2f scale_btn = setSize((SCREEN_WIDTH/2)-50,100,btn);
        sf::Vector2f scale_btnq = setSize((SCREEN_WIDTH)-50,400,btn);

        btnq_sprite.setTexture(btn);
        btnq_sprite.setPosition(1.5*25,SCREEN_HEIGHT-750);
        btnq_sprite.setScale(scale_btnq);
        window.draw(btnq_sprite);

        btn1_sprite.setTexture(btn);
        btn1_sprite.setPosition(1.5*25,SCREEN_HEIGHT-300);
        btn1_sprite.setScale(scale_btn);
        window.draw(btn1_sprite);

        btn2_sprite.setTexture(btn);
        btn2_sprite.setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT-300);
        btn2_sprite.setScale(scale_btn);
        window.draw(btn2_sprite);

        btn3_sprite.setTexture(btn);
        btn3_sprite.setPosition(1.5*25,SCREEN_HEIGHT-200);
        btn3_sprite.setScale(scale_btn);
        window.draw(btn3_sprite);

        btn4_sprite.setTexture(btn);
        btn4_sprite.setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT-200);
        btn4_sprite.setScale(scale_btn);
        window.draw(btn4_sprite);



         while(window.isOpen()) {
                sf::Event evnt;
                while(window.pollEvent(evnt)){
                    if(evnt.type==sf::Event::Closed) window.close();
                }
                window.clear();
                window.draw(btnq_sprite);
                window.draw(btn1_sprite);
                window.draw(btn2_sprite);
                window.draw(btn3_sprite);
                window.draw(btn4_sprite);
                window.display();
            }
    }

    return 0;
}

/******************* Width, Height To Scale Convertor *************************************************************/

sf::Vector2f setSize(float width, float height, sf::Texture tempTexture) {
    sf::Vector2u size = tempTexture.getSize();
    float scaleX = ((float) width/size.x );
    float scaleY = ((float) height/size.y );

    sf::Vector2f scale;
    scale.x = scaleX;
    scale.y = scaleY;

    return scale;
}

/******************* Getting Center of X-Y axis (i.e Width,Height) *************************************************************/

float get_center_x(float params){
    return (SCREEN_WIDTH/2)-(params/2);
}
float get_center_y(float params){
    return (SCREEN_HEIGHT/2)-(params/2);
}
