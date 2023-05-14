/* Written by: Alex Greenwood, with help from Caliana, and Emma
 * purpose: Game of craps
 * Input: wagers
 * Outputs: results, and bank
 */

// use this for files fout.open("crapsgame.txt", fstream::app);



#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <ctime>
using namespace std;



void dice_roll(int& dice1, int& dice2 );
void wagering(int&bet, int&bank, int& remainder);
void pre_game(int& GN);
void seeds(int& seed);
void instructions();
void lose();
void win();
void clear_game();
void PS_Header();
void PS_save(int bank,int PN);
//void no_wager();
//void wager_poss();


int main()
{
    //this is all set up
    int dice1, dice2, seed, GN, sum, point,roll, bet, bank, remainder,j,PN,ans;

    cout<<"Do you have the service code? Press 1 for yes, 2 for no."<<endl;
    cin>>j;

    if(j!=64528) {
        clear_game();       //reset current game

        // PS_Header();        //creating a header to past results

        ofstream fout;
        fout.open("ScoreBoard.txt", fstream::app);           //header and set up for current game page
        fout << "--------The Game of Craps--------" << endl;

        instructions();                     //Game instructions
        pre_game(GN);                   //Selecting number of games
        seeds(seed);                   //input seed
        srand(seed + time(NULL));    //randomizes the seed even more so user cant just reuse the same seed number
        bank = 1000;                       // initialize the bank amount

        while (GN > 0 && bank >
                         0)         // this is loop runs till the player has played all games, or if the person has no money left in their bank
        {
            //betting
            wagering(bet, bank, remainder);     // this is the waging and how it works



            //this is first roll
            dice_roll(dice1, dice2);        //dice roll
            point = dice1 + dice2;                  //add up point
            cout << "Dice 1   " << "  dice 2 " << endl;
            cout << dice1 << "       +        " << dice2 << "    =    " << point << endl;

            //this is a file output
            fout << "Dice 1   " << "  dice 2 " << endl;
            fout << dice1 << "       +        " << dice2 << "    =    " << point << endl;

            //check outcome of first roll
            if (point == 7 || point == 11) {
                win();
                bank = remainder + (3 * bet);
            } else if (point == 2 || point == 3 || point == 12) {
                lose();
            } else {
                //state point
                cout << endl;
                cout << " Your point to hit is: " << point << endl;
                cout << endl;

                //this is for a file output
                fout << endl;
                fout << " Your point to hit is: " << point << endl;
                fout << endl;

                //second roll
                dice_roll(dice1, dice2);
                sum = dice1 + dice2;
                cout << dice1 << "       +        " << dice2 << "    =    " << sum << endl;

                //this is a file output
                fout << dice1 << "       +        " << dice2 << "    =    " << sum << endl;

                //a thing that was needed to make my code work
                roll = sum;

                //all needed rolls after 2nd to determine win or loss
                while (roll != 7 && roll != point) {
                    dice_roll(dice1, dice2);
                    roll = dice1 + dice2;

                    cout << dice1 << "       +        " << dice2 << "    =    " << roll << endl;

                    //this is a file output
                    fout << dice1 << "       +        " << dice2 << "    =    " << roll << endl;
                }
                if (roll == 7) {
                    lose();
                } else if (roll == point) {
                    win();
                    bank = remainder + (2 * bet);
                }
            }

            //making sure the number of games played is correct
            GN--;
        }


        cout << "Here is what you have left." << endl;
        cout << "Bank: $" << bank << endl;

        //this is for file output
        fout << "Here is what you have left." << endl;
        fout << "Bank: $" << bank << endl;

        cout<<"Your Games have ended."<<endl;
        cout<<endl;

        fout<<"Your Games have ended."<<endl;
        fout<<endl;

        cout << "Would you like your remainder in the bank to be recorded? Type 1 for yes, and 2 for no." << endl;
        cin>>ans;

        fout << "Would you like our remainder in the bank to be recorded? Type 1 for yes, and 2 for no." << endl;

        while(ans<1 || ans>2)
        {
            cout<<"Please enter a valid answer."<<endl;
            cin>>ans;

            fout<<"Please enter a valid answer."<<endl;
            fout<<ans;
        }
        if(ans==1)
        {
            cout<<"Pick a 3 digit number that is not previously in the score sheet for your player number."<<endl;
            cin>>PN;

            fout<<"Pick a 3 digit number that is not previously in the score sheet for your player number."<<endl;
            fout<<PN;


            PS_save(bank, PN);
        }
        else if(ans==2)
        {
            cout<<"Ok, have a nice day:)"<<endl;

            fout<<"Ok, have a nice day:)"<<endl;
        }


    }
    else if (j==64528)
    {
        PS_Header();
    }

    return 0;


}

/*-----------------------------------------------------------------------------------------------*/

//dice roller
void dice_roll(int& dice1, int& dice2)
{
        dice1=(rand()%6)+1;
        dice2=(rand()%6)+1;
}

/*-----------------------------------------------------------------------------------------------*/

//These are the rules and instructions, You are given the choice of having the rules displayed
void instructions()
{

    int ans;

    ofstream fout;
    fout.open("crapsgame.txt", fstream::app);

  cout<< "You are about to play a game of craps."<<endl;
  cout<<" you will start with a bank of $1000, and it ill ask you what you would like to wager."<<endl;
  cout<<" Would you like the rules? Input 1 for yes, 2 for no"<<endl;
  cin>>ans;

  //this is for file output
  fout<< "You are about to play a game of craps."<<endl;
  fout<<" you will start with a bank of $1000, and it will ask you what you would like to wager."<<endl;
  fout<<" Would you like the rules? Input 1 for yes, 2 for no."<<endl;

  while (ans < 1 || ans > 2 )
  {
      cout<<" Would you like the rules? Input 1 for yes, 2 for no."<<endl;
      cin>>ans;

      //this is for file output
      fout<<" Would you like the rules? Input 1 for yes, 2 for no."<<endl;

  }
  if(ans==1)
  {
      fout<<"Yes"<<endl;
      fout<<endl;

      cout<<" The way that the game of craps is played is you roll two dice."<<endl;
      cout<<" Or in the case of this simulator, it will roll for you."<<endl;
      cout<<" If the two dice add up to 7 or 11, on your first turn, you automatically win that game."<<endl;
      cout<<" If the two dice add up to 2,3, or 12, on your first turn, you lose that game."<<endl;
      cout<<" If the two dice add up to 4, 5, 6, 8, 9, or 10, you get a point."<<endl;
      cout<<" In order to get another point, and win the game, you must roll the same sum number of the two dice."<<endl;
      cout<<" If you roll a 7 at any time you automatically lose the game."<<endl;
      cout<<" After your first turn, all other numbers are safe and you can roll again, but you do not get a point."<< endl;
      cout<<endl;
      cout<<" For wagers, if you win, by making your point, you will get 2 times your wager back."<<endl;
      cout<<" This means if you wager $100 of your $1000, you will get $200 back meaning you now have $1100."<<endl;
      cout<<" I have decided to be nice to you today, if you win on the first roll, you wil 3 times your wager back."<<endl;
      cout<<endl;
      cout<<" Now that you know the rules: "<<endl;

      //this is for file output
      fout<<" The way that the game of craps is played is you roll two dice."<<endl;
      fout<<" Or in the case of this simulator, it will roll for you."<<endl;
      fout<<" If the two dice add up to 7 or 11, on your first turn, you automatically win that game."<<endl;
      fout<<" If the two dice add up to 2,3, or 12, on your first turn, you lose that game."<<endl;
      fout<<" If the two dice add up to 4, 5, 6, 8, 9, or 10, you get a point."<<endl;
      fout<<" In order to get another point, and win the game, you must roll the same sum number of the two dice."<<endl;
      fout<<" If you roll a 7 at any time you automatically lose the game."<<endl;
      fout<<" After your first turn, all other numbers are safe and you can roll again, but you do not get a point."<< endl;
      fout<<endl;
      fout<<" For wagers, if you win, you will make your point you will get 2 times your wager back."<<endl;
      fout<<" This means if you wager $100 of your $1000, you will get $200 back meaning you now have $1100."<<endl;
      fout<<" I have decided to be nice to you today, if you win on the first roll, you wil 3 times your wager back."<<endl;
      fout<<endl;
      fout<<" Now that you know the rules: "<<endl;
      fout<<endl;
  }
  else if (ans==2)
  {
      fout<<"No"<<endl;
      fout<<endl;

      cout<<" Ok enjoy your time playing!"<<endl;
      cout<<endl;

      //this is for file output
      fout<<" Ok enjoy your time playing!"<<endl;
      fout<<endl;
  }
}

/*-----------------------------------------------------------------------------------------------*/

//This is all the pre-game stuff needed
void pre_game(int& GN)
{

    ofstream fout;
    fout.open("crapsgame.txt", fstream::app);


    cout << " How many games would you like to play? Pick any number between 5 and 20." << endl;
    cin >> GN;

    //this is for file output
    fout << " How many games would you like to play? Pick any number between 5 and 20." << endl;
    fout<< GN<<endl;

    while (GN < 5 || GN > 20) {
        cout << "Please enter how many games would you like to play? It must be any number between 5 and 20." << endl;
        cin >> GN;

        //this is for file output
        fout << "Please enter how many games would you like to play? It must be any number between 5 and 20." << endl;
        fout<<GN<<endl;
    }
    cout << " Ok so you are going to play " << GN << " games." << endl;

    //this is for file output
    fout<<endl;
    fout << " Ok so you would like to play " << GN << " games." << endl;
    fout<<endl;


}

/*-----------------------------------------------------------------------------------------------*/

void seeds(int& seed)
{
    ofstream fout;
    fout.open("crapsgame.txt", fstream::app);

    cout<<"Now can you please pick a random seed number."<<endl;
    cin>>seed;
    cout<<"Thank you for picking a random see number, your games are now starting."<<endl;

    //this is for file output
    fout<<"Now can you please pick a random seed number."<<endl;
    fout<<seed<<endl;
    fout<<"Thank you for picking a random see number, your games are now starting."<<endl;
    fout<<endl;
}

/*-----------------------------------------------------------------------------------------------*/

//this is to tell people they lost
void lose()
{
    ofstream fout;
    fout.open("crapsgame.txt", fstream::app);

    cout<<"You lose, better luck next game!"<<endl;
    cout<<endl;
    cout<<endl;

    //this is for file output
    fout<<"You lose, better luck next game!"<<endl;
    fout<<endl;
    fout<<endl;
}

/*-----------------------------------------------------------------------------------------------*/

//this is to tell people that they won
void win()
{
    ofstream fout;
    fout.open("crapsgame.txt", fstream::app);

    cout<<"Congrats you won the game!"<<endl;
    cout<<endl;
    cout<<endl;

    //this is for file output
    fout<<"Congrats you won the game!"<<endl;
    fout<<endl;
    fout<<endl;
}

/*-----------------------------------------------------------------------------------------------*/

//this is the betting
void wagering(int& bet,int& bank, int& remainder)
{
    int ans;

    ofstream fout;
    fout.open("crapsgame.txt", fstream::app);

        cout << "You currently have $" << bank << " in you bank!" << endl;
        cout << "How much would you like to wager?" << endl;
        cin >> bet;
        cout << endl;

        //this is for file output
        fout << "You currently have $" << bank << " in you bank!" << endl;
        fout << "How much would you like to wager?" << endl;
        fout << bet;
        fout << endl;

        while ((bank - bet) < 0 || bet < 0) {
            if ((bank - bet) < 0) {
                cout << "You do not have enough money in your bank currently, please lower your wager" << endl;
                cin >> bet;
                cout << endl;
                cout << endl;

                //this is for file output
                fout << "You do not have enough money in your bank currently, please lower your wager" << endl;
                fout << bet;
                fout << endl;
                fout << endl;
            }
            if (bet < 0) {
                cout << "You cannot wager a negative amount, please enter a positive wager." << endl;
                cin >> bet;
                cout << endl;
                cout << endl;

                //this is for file output
                fout << "You cannot wager a negative amount, please enter a positive wager." << endl;
                fout << bet;
                fout << endl;
                fout << endl;
            }
        }

        cout << "You would like to wager $" << bet << ", is this correct. Type 1 for yes, 2 for No" << endl;
        cin >> ans;
        cout << endl;

        //this is for file output
        fout << "You would like to wager $" << bet << ", is this correct. Type 1 for yes, 2 for No" << endl;

        while (ans < 1 || ans > 2) {

            cout << "Unrecognized answer, please select 1 for yes, or 2 for no." << endl;
            cin >> ans;
            cout << endl;

            //this is for file output
            fout << "Unrecognized answer, please select 1 for yes, or 2 for no." << endl;
            fout << ans;
            fout << endl;
        }
        if (ans == 1) {
            fout << "Yes" << endl;
            fout << endl;

            remainder = bank - bet;
            cout << "Great, time to start your game." << endl;
            cout << "Your remaining balance in you bank is $" << remainder << ", and your current wager is $" << bet
                 << "." << endl;
            cout << endl;

            //this is for file output
            fout << "Great, time to start your game." << endl;
            fout << "Your remaining balance in you bank is $" << remainder << ", and your current wager is $" << bet
                 << "." << endl;
            fout << endl;

        } else if (ans == 2) {
            fout << "No" << endl;
            fout << endl;

            cout
                    << "If it is not the right amount, what is. As a heads up you cannot change your wager for this game after you enter the new amount"
                    << endl;
            cin >> bet;
            cout << endl;

            //this is for file output
            fout
                    << "If it is not the right amount, what is. As a heads up you cannot change your wager for this game after you enter the new amount"
                    << endl;
            fout << "$"<<bet<<endl;
            fout << endl;

            while ((bank - bet) < 0 || bet < 0) {
                if ((bank - bet) < 0) {
                    cout << "You do not have enough money in your bank currently, please lower your wager" << endl;
                    cin >> bet;
                    cout << endl;
                    cout << endl;

                    //this is for file output
                    fout << "You do not have enough money in your bank currently, please lower your wager" << endl;
                    fout << "$"<<bet<<endl;
                    fout << endl;
                    fout << endl;
                }
                if (bet < 0) {
                    cout << "You cannot wager a negative amount, please enter a positive wager." << endl;
                    cin >> bet;
                    cout << endl;
                    cout << endl;

                    //this is for file output
                    fout << "You cannot wager a negative amount, please enter a positive wager." << endl;
                    fout << "$"<<bet<<endl;
                    fout << endl;
                    fout << endl;
                }
            }
            remainder = bank - bet;
            cout << "Okay, your final wager this game is $" << bet << ", and the remainder in your bank is $"
                 << remainder << endl;
            cout << endl;

            //this is for file output
            fout << "Okay, your final wager this game is $" << bet << ", and the remainder in your bank is $"
                 << remainder << endl;
            fout << endl;
        }
        bank = remainder;

        cout << "Wager: $" << bet << endl;
        cout << "Bank: $" << bank << endl;

        //this is for file output
        fout << "Wager: $" << bet << endl;
        fout << "Bank: $" << bank << endl;



}

/*-----------------------------------------------------------------------------------------------*/

void clear_game()
{
    ofstream fout;
    fout.open("crapsgame.txt");

    fout<<endl;
}

/*-----------------------------------------------------------------------------------------------*/

void PS_Header()
{
    ofstream f;
    f.open("PastScores.txt");
    f<<"----------Past Scores----------"<<endl;
    f<<"Player #"<<"    "<<"Bank remainder"<<"\t"<<"Time"<<endl;
}

/*-----------------------------------------------------------------------------------------------*/

void PS_save(int bank, int PN)
{

    ofstream f;
    ifstream fi;
    fi.open("PastScores.txt");
    f.open("PastScores.txt",fstream::app);


    auto start = chrono::system_clock::now();

    // Some computation here
    auto end = chrono::system_clock::now();

    chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = std::chrono::system_clock::to_time_t(end);

    f<<PN<<"         "<<bank<<"\t"<<"\t"<<ctime(&end_time)<<endl;


}



// this was an effort at trying to make wagering an option instead of mandatory

/*void no_wager()
{
    ofstream fout;
    fout.open("crapsgame.txt", fstream::app);

    fout<<"No."<<endl;

    cout<<"Okay, sounds good, enjoy the game."<<endl;

    fout<<"Okay, sounds good, enjoy the game."<<endl;
}

void wager_poss()
{
    int ans2, bet, bank, remainder;

    ofstream fout;
    fout.open("crapsgame.txt", fstream::app);

    cout<<"Would you like to play and wager in this game? Input 1 for yes, 2 for no."<<endl;
    cin>>ans2;

    fout<<"Would you like to play and wager in this game? Input 1 for yes, 2 for no."<<endl;

    while(ans2<1 || ans2>2)
    {
        cout<<"You need to answer with the number 1 or 2!"<<endl;
        cout<<"Would you like to play and wager in this game? Input 1 for yes, 2 for no."<<endl;
        cin>>ans2;
    }
    if(ans2==1)
    {
        fout << "Yes" << endl;
        fout << endl;

        bank=1000;

        wagering(bet, bank, remainder);
    }
    else if (ans2==2)
    {
        fout<<"No."<<endl;
        no_wager();
    }
}

*/