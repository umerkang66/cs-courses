#include <iostream>
using namespace std;

class Shop
{
private:
    int itemId[100];
    int itemPrice[100];
    int counter;

public:
    void initCounter(void) { counter = 0; }
    void setPrice(void);
    void displayPrice(void);
};

void Shop::setPrice(void)
{
    cout << "Enter itemId of your item: ";
    cin >> itemId[counter];
    cout << "Enter itemPrice of your item: ";
    cin >> itemPrice[counter];
    counter++;
}

void Shop::displayPrice(void)
{
    for (int i = 0; i < counter; i++)
    {
        cout << "Id: " << itemId[i] << "    price: " << itemPrice[i] << endl;
    }
}

int main(int argc, char const *argv[])
{
    Shop shop;
    shop.initCounter();
    for (int i = 1; i <= 3; i++)
    {
        shop.setPrice();
    }
    shop.displayPrice();
    return 0;
}
