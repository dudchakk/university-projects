#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

class Card
{
  public:
    enum Suit
    {
      HEARTS, 
      DIAMONDS, 
      CLUBS, 
      SPADES 
    };
    enum Rank
    { 
      SIX, 
      SEVEN, 
      EIGHT, 
      NINE, 
      TEN, 
      JACK, 
      QUEEN, 
      KING, 
      ACE 
    };

    Card(): suit(HEARTS), rank(SIX) {}  
    Card(Suit suit, Rank rank): suit(suit), rank(rank) {}

    bool operator<(const Card& other)
    {
      if(other.rank == SIX && rank == ACE) 
      {
        return true;
      }
      if(rank != other.rank)
      {
        return rank < other.rank;
      }
      return suit < other.suit;
    }

    friend ostream& operator<<(ostream& os, const Card& card)
    {
      string suit_names[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
      string rank_names[] = { "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };
      
      os << rank_names[card.rank] << ", " << suit_names[card.suit];
      return os;
    }
  
  private:
    Suit suit;
    Rank rank;
};

class Deck
{
  stack<Card> cards;
  
  public:
    Deck()
    {
      for(int suit = Card::HEARTS; suit <= Card::SPADES; suit++)
      {
        for(int rank = Card::SIX; rank <= Card::ACE; rank++) 
        {
          cards.push(Card(static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank)));
        }
      }
      deck_random_shuffle(cards);
    }

    void deck_random_shuffle(stack<Card>& cards) 
    {
      vector<Card> temp(cards.size());
      
      for(size_t i = 0; i < temp.size(); ++i) 
      {
        temp[i] = cards.top();
        cards.pop();
      }
      random_shuffle(temp.begin(), temp.end());
      for(size_t i = 0; i < temp.size(); ++i)
      {
        cards.push(temp[i]);
      }
    }

    Card draw()
    {
      Card top_card = cards.top();
      cards.pop();
      return top_card;
    }

    void add(const Card& card)
    {
      cards.push(card);
    }

    bool empty() const
    {
      return cards.empty();
    }
};

class Player
{
  string name;
  Deck deck;
  
  public:
    Player(const string& name) : name(name) {}

    void add_card(const Card& card)
    {
      deck.add(card);
    }

    Card draw_card()
    {
      if(deck.empty())
      {
        throw "No cards";
      }
      return deck.draw();
    }

    bool no_cards() const
    {
      return deck.empty();
    }

    friend ostream& operator<<(ostream& os, Player& p)
    {
      os << p.name;
      return os;
    }

    // friend ostream& operator<<(ostream& os, const Player& player)
    // {
    //   os << player.name;
    //   return os;
    // }
};

int main()
{
  Player player1("Player 1");
  Player player2("Player 2");
  Deck deck;
  
  while(!deck.empty())
  {
    player1.add_card(deck.draw());
    player2.add_card(deck.draw());
  }

  while(!player1.no_cards() && !player2.no_cards()) 
  {
    Card card1 = player1.draw_card();
    Card card2 = player2.draw_card();
    
    cout << player1 << " plays " << card1 << endl;
    cout << player2 << " plays " << card2 << endl;

    if(card1 < card2)
    {
      cout << player2 << " wins the round" << endl;
      player2.add_card(card1);
      player2.add_card(card2);
    }
    else if(card2 < card1) 
    {
      cout << player1 << " wins the round" << endl;
      player1.add_card(card1);
      player1.add_card(card2);
    }
    else
    {
      cout << "It's a tie!" << endl;
      
      // War
      vector<Card> pile;
      pile.push_back(card1);
      pile.push_back(card2);

      while(true)
      {
        if(player1.no_cards()) 
        {
          cout << player2 << " wins the game!" << endl;
          return 0;
        }
        else if(player2.no_cards()) 
        {
          cout << player1 << " wins the game!" << endl;
          return 0;
        }

        Card war_card1 = player1.draw_card();
        Card war_card2 = player2.draw_card();

        cout << player1 << " plays " << war_card1 << endl;
        cout << player2 << " plays " << war_card2 << endl;

        pile.push_back(war_card1);
        pile.push_back(war_card2);
        
        if(war_card1 < war_card2)
        {
          cout << player2 << " wins the war!" << endl;
          random_shuffle(pile.begin(), pile.end());
          for(const auto& card : pile) 
          {
            player2.add_card(card);
          }
          break;
        }
        
        else if(war_card2 < war_card1)
        {
          cout << player1 << " wins the war!" << endl;
          random_shuffle(pile.begin(), pile.end());
          for(const auto& card : pile)
          {
            player1.add_card(card);
          }
          break;
        }
        
        else 
        {
          cout << "It's a tie!" << endl;
        }
      }
    }
  }

  if(player1.no_cards())
  {
    cout << player2 << " wins the game!" << endl;
  }
  else 
  {
    cout << player1 << " wins the game!" << endl;
  }

  return 0;
}