#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <list>
#include <unordered_set>

using namespace std;

class Card {
public:
    string name;
    int value;
    string suit;

    Card(int x, string s, string n) : value(x), suit(s), name(n) {}

    void printCard() const {
    	if(suit=="Weapon"){
    		cout << suit << '\n';
		}
		else{
			cout << name << " of " << suit << '\n';
		}
        
    }

    bool operator==(const Card& other) const {
        return name == other.name && suit == other.suit;
    }

    // Required for unordered_set to work with Card objects
    struct Hash {
        size_t operator()(const Card& c) const {
            return hash<string>()(c.name) ^ hash<string>()(c.suit);
        }
    };
};

class Deck {
public:
    vector<Card> cards;
    list<Card> pile;

    Deck() {
        string suits[] = {"Heart", "Demon", "Weapon", "Devil"};
        string names[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        int values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

        for (const string& suit : suits) {
            for (int i = 0; i < 13; i++) {
                cards.emplace_back(values[i], suit, names[i]);
            }
        }
        cards.emplace_back(100, "Joker", "Heath");
        cards.emplace_back(100, "Joker", "Jared");
    }

    void shuffleDeck() {
        random_device rd;
        mt19937 g(rd());
        shuffle(cards.begin(), cards.end(), g);
    }

    void setDeck() {
        for (const auto& card : cards) {
            pile.push_back(card);
        }
    }

    Card dealCard() {
        if (pile.empty()) {
            cout << "The deck is finished.\n";
            return Card(0, "", ""); // Return a default card if deck is empty
        }
        Card top = pile.back();
        pile.pop_back();
        return top;
    }

    void addCardToDeck(const Card& c) {
        pile.push_front(c); // Add card back to deck
    }
};

class Player {
public:
    int h; // Health
    int w; // Weapon (strength)
    int score;

    Player() : h(20), w(0), score(0) {}
};

class Level {
public:
    Deck new_Deck;
    Player p;
    unordered_set<Card, Card::Hash> visited, discarded;

    Level() {
    	cout<<"Rules: \nYou need to find Joker to win this game.\nIf you reach joker with 0 score, you lose.\nIf you use weapon to kill a weaker monster, your weapon will detoriate to value of that monster.\nIf you use weapon on a superior monster, weapon will remain unaffected, but your health will diminish.\nHearts heal you to maximum of 20.\nWeapons and hearts have values from 2-14.\nThere are 2 monsters for every value, but only one heart and weapon for each.\nGOOD LUCK!";    	
        cout << endl <<endl<< "Let us BEGIN!" << endl;
        new_Deck.shuffleDeck();
        new_Deck.setDeck();
    }

    void choiceloop() {
        while (p.h > 0) { // Game continues as long as the player is alive
            vector<Card> room;
            room.push_back(new_Deck.dealCard());
            room.push_back(new_Deck.dealCard());
            room.push_back(new_Deck.dealCard());
            room.push_back(new_Deck.dealCard());

            // Display the room cards
            cout << "The room contains the following cards:\n";
            for (int i = 0; i < room.size(); ++i) {
                cout << i + 1 << ". ";
                room[i].printCard();
            }
            cout << "Choose a card to deal with (1-4), or enter 0 to run away: \n\n";

            int choice;
            cin >> choice;

            if (choice == 0) {
                // Player decides to run, take damage from the weakest monster
                
                // Add the cards back to the deck after running
                
                int min_dam=15;
                for(auto& c:room){
                	if(c.suit=="Devil" || c.suit=="Demon"){
                		min_dam=min(min_dam,c.value);
					}
				}
				cout << "\nYou chose to run. Taking damage from the weakest monster...\n";
				p.h-=min_dam;
				cout<<"\n"<<"Health:"<<p.h<< " | Weapon: " <<p.w<< " | Score: " <<p.score<<"\n"<<"\n";
                
                for (auto& c : room) {
                    new_Deck.addCardToDeck(c);
                    new_Deck.shuffleDeck();
                }
                room.clear(); // Reset the room for the next round
                cout << "Loading Next Room...\n";
                continue; // Proceed to the next iteration of the loop
            } else if (choice >= 1 && choice <= 4) {
                Card chosenCard = room[choice - 1];
                // Handle the card choice logic (e.g., if it's a weapon, monster, etc.)
                cout << "You chose to deal with the " << chosenCard.name << " of " << chosenCard.suit << ".\n";
                // Add your logic here to handle combat, health, etc.
                if (chosenCard.suit == "Joker" && p.score!=0){
                cout << "You Win!\nGame Over.\n";
                break;
            }
				else if(chosenCard.suit=="Heart"){
                	if(20<=p.h+chosenCard.value){
                		p.h=20;
                		cout<<"Full health achieved.";
					}
					else{
						p.h+=chosenCard.value;
						cout<<"Healed using: "<<chosenCard.name<< " of " <<chosenCard.suit<<"\n";
					}
					cout<<"\n"<<"Health:"<<p.h<< " | Weapon: " <<p.w<< " | Score: " <<p.score<<"\n"<<"\n";
				}
				if(chosenCard.suit=="Weapon"){
				p.w=chosenCard.value;
				cout<<"Equipped:"<<chosenCard.name<< " of " <<chosenCard.suit<<"\n";
				cout<<"\n"<<"Health:"<<p.h<< " | Weapon: " <<p.w<< " | Score: " <<p.score<<"\n"<<"\n";
				}
				if(chosenCard.suit=="Demon" || chosenCard.suit=="Devil"){
				cout << "Fighting the Monster: "<<chosenCard.name<<" of "<<chosenCard.suit<<"\n";
				if (p.w < chosenCard.value) {
					int loss = chosenCard.value - p.w;
					p.h = p.h-loss;
				} 
				else if(p.w==chosenCard.value){
					p.w--;
				}
				else if(p.w>chosenCard.value){
					p.w=chosenCard.value;
				}
				p.score+=chosenCard.value;
				cout<<"\n"<<"Health:"<<p.h<< " | Weapon: " <<p.w<< " | Score: " <<p.score<<"\n"<<"\n";
				}
				for(int i=0;i<4;i++){
					if(room[i]==chosenCard){
						discarded.insert(chosenCard);
						continue;
					}
					new_Deck.addCardToDeck(room[i]);
				}
				new_Deck.shuffleDeck();
				room.clear();
				if (p.h <= 0) {
				cout << "You have died! Game Over.\n";
                break;
				}
				cout << "Loading Next Room...\n";
				continue;
            }

            // Check if the player is alive
            if (p.h <= 0) {
                cout << "You have died! Game Over.\n";
                break;
            }
            
        }
    }
};

int main() {
    Level level1;
    level1.choiceloop();
    return 0;
}
