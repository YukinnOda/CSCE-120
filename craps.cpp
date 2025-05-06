
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout, std::cin, std::endl;

int rollDice();		
int doGame(int, int);

int main()
{
  int seed;
  cin >> seed;
  srand(seed); 
  int wallet = 1000;
  bool gameOver = false;

  while (!gameOver) {
	  cout << "Enter amount to bet. You have $" << wallet << endl;
	  int bet;
	  cin >> bet;
	  if (bet <= 0) {
		  cout << "Bet must be positive." << endl;
    }
	  else if (bet > wallet) {
		  cout << "You don't have that much money." << endl;
    }
	  else {
      wallet = doGame(bet,wallet);
    }
	  if (wallet <= 0)
	  {
		  cout << "You are penniless. Thanks for playing." << endl;
		  gameOver = true;
	  }
	  else {
		  cout << "Play again? (y/n)" << endl;
    }
		char c;
		cin >> c;
		if (c == 'n') {
			gameOver = true;
      cout << "You ended the game with $" << wallet << endl;
    }
  }

}     

int rollDice()
{
	return (rand() % 6 + rand() % 6 + 2);
}

int doGame(int bet, int wallet) {
    int roll = rollDice();
    cout << "You rolled " << roll << endl;
    switch (roll)
    {
        case 7:
        case 11:
            cout << "You win!" << endl;
            wallet += bet;
            break;
        case 2:
        case 3:
        case 12:
            cout << "You lose." << endl;
            wallet -= bet;
            break;
        default:
            int point = roll;
            cout << "The point is " << point << endl;
            do
            {
                roll = rollDice();
                cout << "You rolled " << roll << endl;
                if (roll == 7)
                {
                  cout << "You lose." << endl;
                  wallet -= bet;
                  break;
                }
                else if (roll == point)
                {
                  cout << "That matches the point!" << " You win!" << endl;
                  wallet += bet;
                  break;
                }
            } while ((roll != 7) || (roll != point));
    }
    return wallet;
}
   