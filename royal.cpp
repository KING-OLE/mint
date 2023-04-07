#include <iostream>
using std::cout;
using std::endl;

#include <random>

#include <vector>
using std::vector;

void showCards(vector<vector<int>> &s) {
  char suit = '-';
  int  sint = 0;
  int  card = 0;
  int  staz = 0;

  for (int i=0; i<40; i++) {
    if (i%8==0) { cout << endl; }
    staz=s[i].size();
    if (staz>0) {
      sint = (s[i][0]%52)/13;
      if (sint==0) { suit='d'; }
      if (sint==1) { suit='h'; }
      if (sint==2) { suit='c'; }
      if (sint==3) { suit='s'; }
      card=(s[i][0]%13)+1;
      if (card<10) { cout << " "; }
      cout << card << suit << " ";
    } else {
      cout << "--- ";
    }
  }
  cout << endl << endl;
}

void moveAces(vector<vector<int>> &s) {
  for (int i=0; i<32; i++) {
    if (s[i].size()==0) { continue; }
    if (s[i][s[i].size()-1]%13==0) {
      //cout << "Found at " << i << endl;
      for (int a=32; a<40; a++) {
        if (s[a].size()==0) {
          s[a].push_back(s[i][s[i].size()-1]);
          s[i].erase(s[i].begin()+s[i].size()-1);
          break;
        }
      }
    }
  }
}

void moveRootCards(vector<vector<int>> &s) {
  int row=0;
  int rootCard=0;
  bool changes=true;
  while (changes) {
    changes=false;
    for (int i=0; i<24; i++) {
      if (s[i].size()!=0) { continue; }
      // stack empty
      row=i/8;
      rootCard=row+1;
      for (int j=31; j>0; j--) {
        if (j/8==row) { continue; }   // same row, skip
        if (s[j][s[j].size()-1]%13==rootCard) {
          cout << "root card " << rootCard << " found at " << j << endl;
          s[i].push_back(s[j][s[j].size()-1]);
          s[j].erase(s[j].end()-1);
          changes=true;
          break;
        }
      }
    }
  }
}


int main() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> d8(0.0,7.99);
  std::uniform_real_distribution<double> d104(0.0,103.99);
  int n8=0;
  int n104=0;
  vector<int> fixedCards;            // fixed 2 decks of cards
  vector<int> cards;                 // temp cards to insert into deck
  vector<int> deck;                  // deck of cards to draw from
  vector<vector<int>> stack {
    {}, {}, {}, {}, {}, {}, {}, {},  // stacks of 2/5/8/11
    {}, {}, {}, {}, {}, {}, {}, {},  // stacks of 3/6/9/12
    {}, {}, {}, {}, {}, {}, {}, {},  // stacks of 4/7/10/13
    {}, {}, {}, {}, {}, {}, {}, {},  // stacks of useable cards
    {}, {}, {}, {}, {}, {}, {}, {}   // stacks of aces
  };

  // populate fixed cards

  for (int i=0; i<104; i++) {
    fixedCards.push_back(i);
  }

  // copy to cards

  cards=fixedCards;

  // shuffle deck

  while (deck.size()<104) {
    n104=d104(mt);
    if (cards[n104]!=999) {
      deck.push_back(cards[n104]);
      cards[n104]=999;
    }
  }

  // pick random 2, 3 and 4 for first card in first 3 rows

  for (int i=0; i<104; i++) {
    if (deck[i]%13==1) {
      stack[0].push_back(deck[i]);
      deck.erase(deck.begin()+i);
      break;
    }
  }
  for (int i=0; i<103; i++) {
    if (deck[i]%13==2) {
      stack[8].push_back(deck[i]);
      deck.erase(deck.begin()+i);
      break;
    }
  }
  for (int i=0; i<102; i++) {
    if (deck[i]%13==3) {
      stack[16].push_back(deck[i]);
      deck.erase(deck.begin()+i);
      break;
    }
  }

  showCards(stack);

  for (int r=0; r<3; r++) {
    for (int c=1; c<8; c++) {
      stack[(r*8)+c].push_back(deck[0]);
      deck.erase(deck.begin());
    }
  }

  for (int c=0; c<8; c++) {
    stack[(3*8)+c].push_back(deck[0]);
    deck.erase(deck.begin());
  }

  showCards(stack);

  moveAces(stack);

  showCards(stack);

  moveRootCards(stack);

  showCards(stack);


  return 0;

}
