import java.util.Random;

public class Dice {


public static void main(String[] args){


Random rand = new Random();
int min = 1;
int max = 6;
int loop = 0;
int diceRollOne = 0;
int diceRollTwo = 0;
int diceTotal = 0;
int prevDiceTotal =0;
int BigLoop = 0;
double WinLoss = 0;
double TotalLoop = 15000;
double OnlyWins = 0;


while(BigLoop < TotalLoop){


diceRollOne = rand.nextInt(max - min + 1) + min;
diceRollTwo = rand.nextInt(max - min + 1) + min;
diceTotal = diceRollOne + diceRollTwo;

System.out.println("Dice Roll 1: " + diceRollOne);
System.out.println("Dice Roll 2: " + diceRollTwo);
System.out.println("Dice Total: " + diceTotal);
System.out.println("previous total: " + prevDiceTotal);

if(diceTotal == prevDiceTotal){
	System.out.println("You Win! The previous two rolls were the same");
	WinLoss = WinLoss + 1;
	OnlyWins = OnlyWins + 1;
								}

if(diceRollOne == diceRollTwo){
	System.out.println("Numbers Match, YOU GET NOTHING, YOU LOSE, GOOD DAY SIR!");
	WinLoss = WinLoss + 1;

								}
prevDiceTotal = diceTotal;
BigLoop++;
						}
double Average = (TotalLoop / WinLoss);
System.out.println("The total number of Win Losses over 15000: " + WinLoss);
System.out.println("The Average number of Rolls to Win or Lose = " + Average);
double AverageWins = (OnlyWins / TotalLoop);
System.out.println("The total number of Wins over 15000: " + OnlyWins);
System.out.println("The Average number of Rolls to Win  = " + AverageWins);

}

}