/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include <regex>
#include "FBullCowGame.h"

// This make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void Intro();
void PlayGame();
void PrintGameSummary();
bool AskToPlayAgain();
FText GetValidGuess();
int32 GetValidWordLength();
void PrintGuess(FText Guess);

FBullCowGame BCGame;

int main() {
	bool bPlayAgain = false;
	do {
		Intro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0; // exit app.
}

// loop continually until the user gives a valid guess
FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::INVALID;
	FText Guess = "";
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter a " << BCGame.GetHiddenLength() << " letter word. \n\n";
			break;
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "Please use an isograme word. Isograms doesn't repeat any letter. \n\n";
			break;
		case EGuessStatus::ERROR_NUMBER:
			std::cout << "We don't use numbers. Enter a word without any number. \n\n";
			break;
		case EGuessStatus::CHARACTER_NOT_VALID:
			std::cout << "No special characters are allow. Enter a simple word Jezz!. \n\n";
			break;
		default:
			// Assume we have a valid guess.
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PrintGuess(FText Guess) {
	std::cout << "You had enter the word: " << Guess << std::endl;
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	int32 ValidLWordLength = GetValidWordLength();
	BCGame.Reset(ValidLWordLength);

	int32 MaxTries = BCGame.GetMaxTries();
	// Loop to ask and print a guess a number of time
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() < MaxTries)
	{
		FText Guess = GetValidGuess();
		BullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "YEY! You WON. \n";
	}
	else {
	}
	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play a game [Y/N]? ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (toupper(Response[0]) == 'Y');
}

int32 GetValidWordLength() {
	int32 length = 0;
	while (!BCGame.CheckValidWordLength(length)) {

		std::cout << "Select a length word number from 2 to 6: ";
		FText Response = "";
		std::getline(std::cin, Response);
		std::regex regx("([0-9])+");
		std::smatch filter;
		std::regex_search(Response, filter, regx);
		length = std::stoi(filter[0]);
	}

	return length;
}

void Intro() {
	// introduce the game
	std::cout << "\n\nWelcome to Bulls and Cows\n";
	std::cout << "	                                                          >*" << std::endl;
	std::cout << "                                                   #      >*" << std::endl;
	std::cout << "                                                   #  ###>***~~~~~|" << std::endl;
	std::cout << "                                                   ####  *****^^^#" << std::endl;
	std::cout << "                                              _____/       *#####" << std::endl;
	std::cout << "                                             // ^^^#   \// \// #" << std::endl;
	std::cout << "                                            ##^^###         |" << std::endl;
	std::cout << "                                             ### ##*        *" << std::endl;
	std::cout << " \\                                ********~~|_____>         *" << std::endl;
	std::cout << " \\|_                    _______************        #>>***    ***" << std::endl;
	std::cout << " \\ \\|_              __/     *************        ## >>>*  *****" << std::endl;
	std::cout << " |___  |_____      /         ***********       ##>### ^^^^^^^^^^" << std::endl;
	std::cout << "    |____    \\__/           **********       >>>>## ^<^^^^^@^^^^^" << std::endl;
	std::cout << "        #          ***      ********      **>>>># ^<^^@^^^@^^^^^" << std::endl;
	std::cout << "          #      ***********    ******     *>>>## ^<<^^^^^^^^<<<" << std::endl;
	std::cout << "          #      ***********    ******    **>>>## ^<<<<^^^<<<<<" << std::endl;
	std::cout << "         #        *********      ****   ***>>>#### ^<<<<<<<<<" << std::endl;
	std::cout << "         #         **********          ****>>>###### <<<<<" << std::endl;
	std::cout << "         ##        **********          ****>>>>##      ##" << std::endl;
	std::cout << "         ##         **  ***             ****>>>>        #     ##XXX" << std::endl;
	std::cout << "         ##**                            *******         ##>>>>#XX" << std::endl;
	std::cout << "          >>*                             ******         #######XXX" << std::endl;
	std::cout << "          >>*****                           ***         ##__" << std::endl;
	std::cout << "           >>*****   **** ***               **    *****     \\__" << std::endl;
	std::cout << "           >># **    *********              *********>>>#      XXX" << std::endl;
	std::cout << "           ##        *********              *******>>>>>##     XXX" << std::endl;
	std::cout << "        |~~           ********                 *>>>>> >#######XXX" << std::endl;
	std::cout << "    X~~~~ ###          *********          ######>          >>>XXXX" << std::endl;
	std::cout << "  XXX  #>>>##          ********>>##  #######" << std::endl;
	std::cout << "   XXX#>      #   ##>>>>>>>>>>>>>###UUUUU^^" << std::endl;
	std::cout << "   XXX        #  ####>>>>>>>>>>UUUUUUUUU^^" << std::endl;
	std::cout << "              #  >>           UUUUUU^^^<()" << std::endl;
	std::cout << "             #  >              U()^<()  ()" << std::endl;
	std::cout << "           *#  *>               ()  ()" << std::endl;
	std::cout << "          **** #" << std::endl;
	std::cout << "            ***" << std::endl;
	std::cout << "            **" << std::endl;
	std::cout << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}