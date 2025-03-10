#include <SFML/Graphics.hpp>
#include <string.h>
int main()
{
    sf::RenderWindow window(sf::VideoMode(1940, 1000), "The Labyrinth of Cards");
    
	
	//==========================
    //Section-1 Global Variables
    //==========================
    
    
    int selectionIndex1=0;
    int selectionIndex2=0;
    int GState=0;
    int PGState=0;
    int TGstate=0;
    int LoadTime=2.0f;
    //unordered_map<int,string> gamestates={{0,"MainMenu"},{1,"Menu"},{2,"Rules"},{3,"Controles"},{4,"Controles"},{5,"Start Game"}};
    
    
    //==========================================
    //Section-2 Highlights for Specific Objects.
    //==========================================
    
    
    // Selection highlight
    sf::RectangleShape selectStart(sf::Vector2f(250.f,75.f));
    selectStart.setFillColor(sf::Color::Black);
    selectStart.setPosition(1200,500);
    
    // Selection highlight
    sf::RectangleShape selectMenu(sf::Vector2f(260.f,75.f));
    selectMenu.setFillColor(sf::Color::Black);
    selectMenu.setPosition(1200,600);
    
    // Selection highlight
	sf::RectangleShape selectExits(sf::Vector2f(190.f,75.f));
    selectExits.setFillColor(sf::Color::Black);
    selectExits.setPosition(1200,700);    
    
    // Selection highlight
	sf::RectangleShape selectRule(sf::Vector2f(260.f,75.f));
    selectRule.setFillColor(sf::Color::Black);
    selectRule.setPosition(500,500);
    
    // Selection highlight
	sf::RectangleShape selectCtrl(sf::Vector2f(390.f,75.f));
    selectCtrl.setFillColor(sf::Color::Black);
    selectCtrl.setPosition(500,700);
    
    
    //=====================================================
    //Section-3: Loading Fonts,Textures and other resources
    //=====================================================
    
    
    //Font for writing on the menu
    sf::Font font;
    if(!font.loadFromFile("GAMER.otf")){
    	return -1;
	}
    
    //LoadingScreen Timer
    sf::Clock timer;
    
    // Load Background Texture
    sf::Texture backgroundT;
    if (!backgroundT.loadFromFile("MainMenu.png")) {
        return -1; // Exit if the file is not found
    }
    
    // Change Screen
    sf::RectangleShape loadingScreen(sf::Vector2f(1940.f,1000.f));
    loadingScreen.setFillColor(sf::Color(77,73,158));
    loadingScreen.setPosition(0,0);
    
    
    
    
	//========================================
	//Section-4: Making The Main Menu Objects.
	//========================================
	
	
	sf::Text Load;
    Load.setFont(font);
    Load.setPosition(570,500);
    Load.setFillColor(sf::Color::Yellow);
    Load.setOutlineColor(sf::Color::Black);
    Load.setOutlineThickness(4);
    Load.setString("Loading....Please Wait.");
    Load.setCharacterSize(72);
    
    
	
	//All the texts for start page.
	//welcome to...
	sf::Text welcome;
	
	welcome.setFont(font);
	welcome.setString(L"welcome \n       to:");
	welcome.setCharacterSize(48);
	welcome.setOutlineColor(sf::Color::Black);
	welcome.setOutlineThickness(4);
	welcome.setFillColor(sf::Color::Yellow);
	welcome.setPosition(1370,200);
	//title text "The Labirynth of Cards"
	sf::Text titletxt;
	
	titletxt.setFont(font);
	titletxt.setString(L"The Labyrinth of \n            Cards");
	titletxt.setCharacterSize(72);
	titletxt.setOutlineColor(sf::Color::Black);
	titletxt.setOutlineThickness(4);
	titletxt.setFillColor(sf::Color::Yellow);
	titletxt.setPosition(1150,300);
	
	// "Start"
	sf::Text start_txt;
	
	start_txt.setFont(font);
	start_txt.setString(L"> Start");
	start_txt.setCharacterSize(62);
	start_txt.setOutlineColor(sf::Color::Black);
	start_txt.setOutlineThickness(4);
	start_txt.setFillColor(sf::Color::Yellow);
	start_txt.setPosition(1200,500);
	
	//title text "Menu"
	sf::Text menu_txt;
	
	menu_txt.setFont(font);
	menu_txt.setString(L"> Menu");
	menu_txt.setOutlineColor(sf::Color::Black);
	menu_txt.setOutlineThickness(4);
	menu_txt.setCharacterSize(62);
	menu_txt.setFillColor(sf::Color::Yellow);
	menu_txt.setPosition(1200,600);
	
	//title text "Exit"
	sf::Text exit_txt;
	
	exit_txt.setFont(font);
	exit_txt.setString(L"> Exit");
	exit_txt.setOutlineColor(sf::Color::Black);
	exit_txt.setOutlineThickness(4);
	exit_txt.setCharacterSize(62);
	exit_txt.setFillColor(sf::Color::Yellow);
	exit_txt.setPosition(1200,700);
	
    // Create Sprite for Background
    sf::Sprite backgroundS;
    backgroundS.setTexture(backgroundT);
    
    //======================================================
    //Section-5: Making The "Menu"
    //======================================================
    
    
    //The Escape Button
    
    sf::Text Back_txt;
    Back_txt.setFont(font);
    Back_txt.setPosition(50,50);
    Back_txt.setFillColor(sf::Color::White);
    Back_txt.setString("Press {<-} to go Back");
    Back_txt.setCharacterSize(20);
    
    
    //other menu options
    sf::Text Rule_txt;
    Rule_txt.setFont(font);
    Rule_txt.setString(L"> Rules");
	Rule_txt.setCharacterSize(62);
	Rule_txt.setFillColor(sf::Color::Yellow);
	Rule_txt.setPosition(500,500);
    
    
    sf::Text Ctrl_txt;
    Ctrl_txt.setFont(font);
    Ctrl_txt.setString(L"> Controls");
	Ctrl_txt.setCharacterSize(62);
	Ctrl_txt.setFillColor(sf::Color::Yellow);
	Ctrl_txt.setPosition(500,700);
    
    //Highlights for the "Menu" Options.
    
    
    
    //====================
    //Section-6: Game Loop
    //====================


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
			window.close();
			}
			if(GState==0){
				if(event.type==sf::Event::KeyPressed){
					if(event.key.code==sf::Keyboard::W){
						selectionIndex1=(selectionIndex1==0)?2:selectionIndex1-1;
					}
					if(event.key.code==sf::Keyboard::S){
						selectionIndex1=(selectionIndex1==2)?0:selectionIndex1+1;
					}
					if(event.key.code==sf::Keyboard::Return){
						if(selectionIndex1==0){
							
						}
						if(selectionIndex1==1){
							GState=1;
							continue;
						}
						if(selectionIndex1==2){
							window.close();
						}
					}
				}
			}
			if(GState==1){
				if(event.type==sf::Event::KeyPressed){
					if(event.key.code==sf::Keyboard::W){
						selectionIndex2=(selectionIndex2==0)?1:0;
					}
					if(event.key.code==sf::Keyboard::S){
						selectionIndex2=(selectionIndex2==1)?0:1;
					}
					if(event.key.code==sf::Keyboard::Return){
						if(selectionIndex2==0){
							GState=2;
						}
						if(selectionIndex2==1){
							GState=3;
						}
						if(selectionIndex2==2){
							window.close();
						}
					}
					if(event.key.code==sf::Keyboard::BackSpace){
						GState=0;
					}
				}				
			}
			if(GState==2){
				
			}
			if(GState==3){
				
			}
        }

        window.clear();                // Clear the screen
        
//        window.draw(shape);            // Draw red circle

        if(GState==0){
        	selectMenu.setFillColor(sf::Color::Black);
        	window.draw(backgroundS);      // Draw background
        	window.draw(welcome);
        	window.draw(titletxt);
        	if(selectionIndex1==0){
        		window.draw(selectStart);
			}
        	else if(selectionIndex1==1){
        		window.draw(selectMenu);
			}
			else if(selectionIndex1==2){
        		window.draw(selectExits);
			}
			window.draw(start_txt);
        	window.draw(menu_txt);
        	window.draw(exit_txt);
		}
		else if(GState==1){
			window.clear(sf::Color(77,73,158));
			selectMenu.setFillColor(sf::Color::White);
			
			
			window.draw(titletxt);
			window.draw(Back_txt);
			window.draw(selectMenu);
			window.draw(menu_txt);
			
			if(selectionIndex2==0){
				window.draw(selectRule);
			}
			else{
				window.draw(selectCtrl);
			}
			window.draw(Rule_txt);
			window.draw(Ctrl_txt);
		}
		
		else if(GState==2){
			if(TGstate==0) PGState=1;
			
		}
		else if(GState==3){
			if(TGstate==0) PGState=1;
			
		}
		else if(GState==4){
			if(TGstate==0) PGState=0;
			
			
		}
		else if(GState==5){
			if(TGstate==0) PGState=0;
			window.close();//Placeholder for now.
		}
        
        
        
		window.display();              // Update the window
    }

    return 0;
}

