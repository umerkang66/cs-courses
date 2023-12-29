#include <iostream>
using namespace std;

int main()
{
	int length = 10;
	string items[length] = {"Chicken Biryani", "Kabab Masala", "Chicken Manchurian", "Chicken Leg Piece", "Chapli Kabab + Naan", "Pizza", "Grill Sandwich", "Shawarma", "Fries", "Tea"};
	int prices[length] = {140, 120, 140, 130, 90, 450, 140, 120, 50, 40};
	int userPurchasedItems[length];
	// entering default values in the userPurchasedItems;
	for (int i = 0; i < length; i++)
	{
		userPurchasedItems[i] = -1;
	}

	cout << "Menu item:                  Price (Rs.)" << endl;
	for (int i = 0; i < length; i++)
	{
		string spacedItem = items[i];
		int itemLength = items[i].length();
		int howManySpaces = i == length - 1 ? 24 : 25;
		for (int i = itemLength; i < howManySpaces; i++)
		{
			spacedItem += " ";
		}
		cout << i + 1 << ": " << spacedItem << ": " << prices[i] << " Rs." << endl;
	}
	cout << endl;

	char purchaseFurther;
	int whichItem;

	cout << "Enter item no. to purchase: ";
	cin >> whichItem;
	while (whichItem < 1 || whichItem > 10)
	{
		cout << "Please enter no. between 1 and 10: ";
		cin >> whichItem;
	}

	// store the quantity in array at the index, and that index should also point to the item and price in other two arrays
	cout << "How many items (quantity): ";
	cin >> userPurchasedItems[whichItem - 1];

	cout << "Do you want to purchase further? (y/n): ";
	cin >> purchaseFurther;

	while (purchaseFurther != 'n' && purchaseFurther != 'N')
	{
		cout << "Enter item no. to purchase: ";
		cin >> whichItem;
		while (whichItem < 1 || whichItem > 10)
		{
			cout << "Please enter no. between 1 and 10: ";
			cin >> whichItem;
		}

		// store the quantity in array at the index, and that index should also point to the item and price in other two arrays
		cout << "How many items (quantity): ";
		cin >> userPurchasedItems[whichItem - 1];

		cout << "Do you want to purchase further? (y/n): ";
		cin >> purchaseFurther;
	}

	int totalAmount = 0;
	int orderNo = 1;
	cout << endl;
	cout << "Order No.     Item                     Quantity     Price" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (userPurchasedItems[i] != -1)
		{
			totalAmount += prices[i] * userPurchasedItems[i];

			string spacedItem = items[i];
			int itemLength = items[i].length();
			int howManySpaces = orderNo == length ? 24 : 25;
			for (int i = itemLength; i < howManySpaces; i++)
			{
				spacedItem += " ";
			}
			cout << orderNo << "             " << spacedItem << userPurchasedItems[i] << "            " << prices[i] * userPurchasedItems[i] << " Rs." << endl;
			orderNo++;
		}
	}

	cout << endl;

	float tax = ((float)totalAmount) * 5.0 / 100.0;
	float amountDue = totalAmount + tax;
	float discount = totalAmount <= 1000 ? 0 : ((float)totalAmount) * 10.0 / 100.0;

	cout << "Total Amount:    " << totalAmount << " Rs." << endl;
	cout << "Tax (5%):        " << tax << " Rs." << endl;
	cout << "Amount Due:      " << amountDue << " Rs." << endl;
	cout << "Discount:        " << discount << " Rs." << endl;
	cout << "Net Total:       " << amountDue - discount << " Rs." << endl;

	cout << endl;
	cout << "Thank you for purchasing. Have a nice day." << endl;
	return 0;
}
