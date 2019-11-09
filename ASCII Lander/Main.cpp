#include<Windows.h>

//DEFINES
#define WIDTH 150
#define HEIGHT 40

//Console Paramenters
#pragma region Console Buffer Params

//Window size Coordinate, be sure to start at zero
SMALL_RECT windowsize{ 0, 0, WIDTH - 1, HEIGHT - 1 };

// A COORD struct for specifying the console screen buffer
COORD bufferSize = { WIDTH, HEIGHT };
CONSOLE_SCREEN_BUFFER_INFO SBInfo;

// Setting up different variable for passing to WriteConsoleOutput
COORD characterBufferSize = { WIDTH, HEIGHT };
COORD charaterPosition = { 0, 0 };
SMALL_RECT ConsoleWriteArea = { 0, 0, WIDTH - 1, HEIGHT - 1 };

//A CHAR_INFO structure containing data about our frame data
CHAR_INFO consoleBuffer[WIDTH * HEIGHT];

//Initialise Handles
HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE rHnd = GetStdHandle(STD_INPUT_HANDLE);
#pragma endregion

//GAME
const unsigned char characterToPrint = 219;


int main() {
	//Set the console title
	SetConsoleTitle("Title of my console window");

	//
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	//Sets the size and position of the screen Bufer window
	SetConsoleWindowInfo(wHnd, TRUE, &windowsize);

	bool exitGame = false;
	while (!exitGame) {
		if (GetAsyncKeyState(VK_ESCAPE)) //Checking to see if player has pressed escaped, if yes game exits
		{
			exitGame = true;
		}

		for (int y = 0; y < HEIGHT; ++y)
		{

			for (int x = 0; x < WIDTH; ++x)
			{
				
				consoleBuffer[x + WIDTH * y].Char.AsciiChar = characterToPrint;
				//Printing our character from the line above and giving it a random color, line below.
				consoleBuffer[x + WIDTH * y].Attributes = rand() % 256;
			}
		}

		WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, charaterPosition, &ConsoleWriteArea);
	}


	return 0;
}
