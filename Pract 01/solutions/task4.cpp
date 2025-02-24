#include <iostream>

enum class Drink
{
	Whiskey = 1, // 2**0
	Vodka = 2, // 2**1
	Cola = 4, // 2**2
	Fanta = 8, // 2**3
	Water = 16, // 2**4
	Wine = 32, // 2**5
	Rum = 64, // 2**6
	Juice = 128 // 2**7
};

bool isDrinkFavorable(unsigned favorabilityMask, Drink drink)
{
	return favorabilityMask & (unsigned)drink;
}

void makeDrinkFavorable(unsigned& favorabilityMask, Drink drink)
{
	favorabilityMask |= (unsigned)drink;
}

void makeDrinkUnfavorable(unsigned& favorabilityMask, Drink drink)
{
	favorabilityMask &= ~(unsigned)drink;
}

void printName(Drink drink)
{
	switch (drink)
	{
		case Drink::Whiskey:
			std::cout << "Whiskey";
			break;
		case Drink::Vodka:
			std::cout << "Vodka";
			break;
		case Drink::Cola:
			std::cout << "Cola";
			break;
		case Drink::Fanta:
			std::cout << "Fanta";
			break;
		case Drink::Water:
			std::cout << "Water";
			break;
		case Drink::Wine:
			std::cout << "Wine";
			break;
		case Drink::Rum:
			std::cout << "Rum";
			break;
		case Drink::Juice:
			std::cout << "Juice";
			break;
	}
}

void printAllFavorableDrinks(unsigned favorabilityMask)
{
	Drink drinks[] = { Drink::Whiskey, Drink::Vodka, Drink::Cola, Drink::Fanta,
					   Drink::Water, Drink::Wine, Drink::Rum, Drink::Juice };
	size_t drinksCount = 8;

	for (size_t i = 0; i < drinksCount; i++)
	{
		if (isDrinkFavorable(favorabilityMask, drinks[i]))
		{
			printName(drinks[i]);
			std::cout << std::endl;
		}
	}
}

int main()
{
	unsigned mask = 0;

	makeDrinkFavorable(mask, Drink::Whiskey);
	makeDrinkFavorable(mask, Drink::Vodka);
	makeDrinkFavorable(mask, Drink::Rum);

	printAllFavorableDrinks(mask);
	std::cout << std::endl;

	makeDrinkUnfavorable(mask, Drink::Rum);
	printAllFavorableDrinks(mask);
}
