#include <iostream>
#include <array>
#include <numeric>
#include <algorithm>

using namespace std;

class Creature
{
  enum Abilities
  {
    strength,
    agility,
    intelligence,
    count // here the value of count is 3, we can use it count the length of enum
  };
  array<int, count> abilities;

public:
  int getStrength() const { return abilities[strength]; }
  void setStrength(int value) { abilities[strength] = value; }

  int getAgility() const { return abilities[agility]; }
  void setAgility(int value) { abilities[agility] = value; }

  int getIntelligence() const { return abilities[intelligence]; }
  void setIntelligence(int value) { abilities[intelligence] = value; }

  int sum() const
  {
    return accumulate(abilities.begin(), abilities.end(), 0);
  }

  double average() const { return sum() / (double)count; }

  int max() const { return *max_element(abilities.begin(), abilities.end()); }
};

int main()
{
  return 0;
}
