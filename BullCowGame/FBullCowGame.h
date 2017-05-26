/*
Game Logic with console interaction
The fun of the game is to guess a word based on a selected word length
*/
#pragma once

#include <string>
#include <algorithm>
#include <regex>
#include <map>

#define TMap std::map
using FString = std::string;
using int32 = int;

struct BullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus
{
	INVALID,
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH,
	ERROR_NUMBER,
	CHARACTER_NOT_VALID
};

class FBullCowGame {
public:
	FBullCowGame();
	~FBullCowGame();

	int32 GetCurrentTry() const;
	int32 GetHiddenLength() const;
	int32 GetMaxTries() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	bool FBullCowGame::CheckValidWordLength(int32 WordLength);

	void Reset(int32);
	BullCowCount SubmitValidGuess(FString);

	//My method that I guess we would use.
	void Play();
	void Finish();

private:
	int32 CurrentTry;
	FString HiddenWord;
	bool bGameIsWon;

	FString GetHiddenWordByLength(int32 WordLength) const;
	bool hasSpecialChar(FString) const;
	bool isUnique(FString) const;
	bool hasNumber(FString) const;
};

