#pragma once

#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
	Reset(4);
}

FBullCowGame::~FBullCowGame()
{
	return;
}

void FBullCowGame::Reset(int32 WordLength)
{
	HiddenWord = GetHiddenWordByLength(WordLength);
	CurrentTry = 1;
	bGameIsWon = false;

	return;
}

// All words to guess should be isograms, don't fuck this up.
FString FBullCowGame::GetHiddenWordByLength(int32 ValidWordLength) const {
	TMap<int32, FString> HiddenWordsMap;
	HiddenWordsMap[2] = "we";
	HiddenWordsMap[3] = "are";
	HiddenWordsMap[4] = "cows";
	HiddenWordsMap[5] = "match";
	HiddenWordsMap[6] = "quartz";
	HiddenWordsMap[7] = "program";

	return HiddenWordsMap[ValidWordLength];
}

bool FBullCowGame::CheckValidWordLength(int32 WordLength) {
	if (GetHiddenWordByLength(WordLength) == "") {
		return false;
	}
	else {
		return true;
	}
}

// receives a VALID guess, incriments turn, and returns count
BullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	CurrentTry++;
	BullCowCount BullCowCount;
	int32 WordLength = HiddenWord.length();// assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 i = 0; i < WordLength; i++)
	{
		// compare letters against the guess
		for (int32 j = 0; j < WordLength; j++)
		{
			if (Guess[i] == HiddenWord[j])
			{
				if (i == j) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
				break;
			}
		}
	}
	// Set if it match all the letters in the correct place to win
	bGameIsWon = BullCowCount.Bulls == GetHiddenLength();
	return BullCowCount;
}

void FBullCowGame::Play()
{
}

void FBullCowGame::Finish()
{
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (isUnique(Guess) == false) {
		return EGuessStatus::NOT_ISOGRAM;
	}
	else if (Guess.length() != GetHiddenLength()) {
		return EGuessStatus::WRONG_LENGTH;
	}
	else if (hasNumber(Guess)) {
		return EGuessStatus::ERROR_NUMBER;
	}
	else if (hasSpecialChar(Guess)) {
		return EGuessStatus::CHARACTER_NOT_VALID;
	}
	else {
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::hasSpecialChar(FString Guess) const {
	std::smatch match;
	std::regex regx("([^A-z 0-9])+");
	if (std::regex_search(Guess, match, regx) && match.size() > 0)
	{
		return true;
	}
	else {
		return false;
	}
}

bool FBullCowGame::hasNumber(FString Guess) const {
	std::smatch match;
	std::regex regx("([0 - 9])");
	if (std::regex_search(Guess, match, regx) && match.size() > 0)
	{
		return true;
	}
	else {
		return false;
	}
}

bool FBullCowGame::isUnique(FString Guess) const {
	std::sort(Guess.begin(), Guess.end());
	bool uniqueness = std::unique(Guess.begin(), Guess.end()) == Guess.end();
	return uniqueness;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return CurrentTry;
}

int32 FBullCowGame::GetHiddenLength() const
{
	return HiddenWord.length();
}

int32 FBullCowGame::GetMaxTries() const
{
	return 2 + GetHiddenLength() / 2;
}