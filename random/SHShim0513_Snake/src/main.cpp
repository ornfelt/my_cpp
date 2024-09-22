#include "GameCtrl.h"

char title[16][30]=
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,0,1,0,0,0,1,0,0,1,1,0,0,0,1,0,0,1,0,1,1,1,1,1,0},
	{0,1,0,0,0,0,0,1,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0},
	{0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,0,0,1,1,1,1,1,0},
	{0,0,0,0,0,1,0,1,0,0,1,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0},
	{0,1,1,1,1,1,0,1,0,0,0,1,0,1,0,0,1,0,0,1,0,0,1,0,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0},
	{0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,1,1,0,0,0,1,1,0,0,1,0,0,0,0,0},
	{0,0,1,0,0,1,1,0,0,1,1,1,1,0,0,1,0,1,0,1,0,1,0,0,1,1,1,1,1,0},
	{0,0,1,1,1,1,1,0,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

};

int main() {
	
	int menu = 0;
	
	for(int x=0;x<16;x++){
		printf("\t");
		for(int y=0;y<30;y++){
			if(title[x][y] == 1){
				printf("��");
			}
			if(title[x][y] == 0){
				printf("��");
			}
		}
		printf("\n");
	}

	printf("\n");
	printf("\t\t\t\t<MENU>\n");
	printf("\t\t\t     1.Snake Game(Manual Mode)\n");
	printf("\t\t\t     2.See How to find Shortest Path\n");
	printf("\t\t\t     3.See How to find Longest Path\n");
	printf("\t\t\t     4.AI Hamiltonian Cycle\n");
	printf("\t\t\t     5.AI Graph Search\n");
	printf("\t\t\t     6.Exit\n");
	printf("\t\t\t     =>Input Menu Number : ");
	scanf("%d",&menu);
	
	auto game = GameCtrl::getInstance(0);
	
	// Set FPS. Default is 60.0
	game->setFPS(60.0);	

    	// Set the interval time between each snake's movement. Default is 30 ms.
	// To play classic snake game, set to 150 ms is perfect.
 	game->setMoveInterval(150);
  
        // Set whether to record the snake's movements to file. Default is true.
        // The movements will be written to a file named "movements.txt".
        game->setRecordMovements(true);

    	// Set map's size(including boundaries). Default is 10*10. Minimum is 5*5.
    	game->setMapRow(10);
	game->setMapCol(10);

	if(menu==1){ //Snake Game

    		// Set whether to enable the snake AI. Default is true.
    		game->setEnableAI(false);

    		// Set whether to use a hamiltonian cycle to guide the AI. Default is true.
    		game->setEnableHamilton(true);

    		// Set whether to run the test program. Default is false.
    		// You can select different testing methods by modifying GameCtrl::test().
    		game->setRunTest(false);
	}

	else if(menu==2){ //Shortest Path

	    	game->setEnableAI(false);
	    	game->setEnableHamilton(true);
	    	game->setRunTest(true);

    		game->setMapRow(20);
		game->setMapCol(20);
	}
	else if(menu==3){ //Longest Path

		auto game = GameCtrl::getInstance(1);
	
	    	game->setEnableAI(false);
            	game->setEnableHamilton(true);
	    	game->setRunTest(true);

    		game->setMapRow(20);
		game->setMapCol(20);
	}
	else if(menu==4){ //Hamiltonian Cycle

	    	game->setEnableAI(true);
 	    	game->setEnableHamilton(true);
   	    	game->setRunTest(false);
	}
	else if(menu==5){ //AI

	    	game->setEnableAI(true);
	    	game->setEnableHamilton(false);
	    	game->setRunTest(false);
	}
	else 
	    	return 0;

    	return game->run();
}
