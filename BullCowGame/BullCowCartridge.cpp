// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetUpGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{   
    if(bGameOver){
        ClearScreen();
        SetUpGame();
    }
    else
    {
        VerifyGuess(Input);
    }
}

void UBullCowCartridge::SetUpGame()
{
    PrintLine( TEXT( "wellcome to Bull And Cow" ));

    HiddenWord = WordList[FMath::RandRange(1,WordList.Num()-1)];
    Lives = 5;
    bGameOver = false;

    PrintLine(TEXT("HiddenWord debug : %s"),*HiddenWord);

    PrintLine( TEXT( "\nGuess %i letter word..!"), HiddenWord.Len());
    PrintLine(TEXT("You Have %i Tries to do that"), Lives);
    PrintLine( TEXT( "\nType Your Guess.\npress Enter Button to Continue....!" ));
   
}

void UBullCowCartridge::EndGame()
{
    PrintLine(TEXT("The hidden word  is %s"), *HiddenWord);
    bGameOver = true;
    PrintLine(TEXT("Press Enter To Play Again..!"));
}

bool UBullCowCartridge::IsIsogram(const FString& Input) const
{
    /*
        i = 0  => j=,1,2,3,4
        i = 1  => j=2,3,4
        i = 2  => j=3,4
        i = 3  => j=4
    */
    int32 i,j;

    for(i = 0; i<Input.Len()-1; i++){
        for(j =i+1;j<Input.Len();j++){
            if(Input[i]==Input[j]){
                return false;
            }
        }

    }
    return true;

}

void UBullCowCartridge::VerifyGuess(const FString& Guess)
{
    //check length is corrct
    if(HiddenWord.Len() != Guess.Len()){
        PrintLine(TEXT("Guess %i letter word..!"), HiddenWord.Len());
        return;
    }

    //check Isogram
    if(!IsIsogram(Guess)){
        PrintLine(TEXT("Word is Not An Isogram"));
        return;
    }

   
    //check corrctGuess
    if(Guess == HiddenWord)
    {
        ClearScreen();
        PrintLine (TEXT("you guessed the correct word..!\n Congatulation..!"));
        EndGame();
        return;
    }


    //wrong Guess
    if(Lives>1){
        PrintLine(TEXT("your Guess is wrong"));
       FBullCowCount BullCow = GetBullcow(Guess);
        
        PrintLine(TEXT("You have %i Bulls and %i Cows"),BullCow.Bulls,BullCow.Cows);
        --Lives;
        PrintLine(TEXT("try again You Have %i Tries"), Lives);

        return;
    }


    //EndGAme
    if(Lives<=1)
    {   
        ClearScreen();
        PrintLine(TEXT("may be Try Again Later..!"));
        EndGame();
        
        return;
    }
            
        
}

FBullCowCount UBullCowCartridge::GetBullcow(const FString& Guess) const
{
    FBullCowCount Count;

    for(int32 GuessIndex = 0;GuessIndex<Guess.Len();GuessIndex++)
    {
        if(Guess[GuessIndex]==HiddenWord[GuessIndex])
        {
            ++Count.Bulls;
            continue;
        }
        for(int32 CowIndex = 0;CowIndex<Guess.Len();CowIndex++)
        {
           if(Guess[GuessIndex]==HiddenWord[CowIndex])
           {
               ++Count.Cows;
           }
        }
    }
    return Count;

}