#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Player {
	string name;
	int score;
	int bid;

	bool operator >(const Player& rhs) {
		return score > rhs.score;
	}

	friend bool operator >(const Player& lhs, const Player& rhs);
};

bool operator >(const Player& lhs, const Player& rhs) {
	return lhs.score > rhs.score;
}

int main() {
	int player_count;

	cout << "Number of players?" << endl;
	cin >> player_count;

	Player p;
	string n;

	vector<Player> players;

	cout << "Enter name of players (in order, startng with dealer): " << endl;
	for(int i = 0; i < player_count; i++) {
		cin >> n;
		p.name = n;
		p.score = 0;
		p.bid = 0;
		players.push_back(p);
	}

	cout << "The players are: ";
	for(auto i : players) {
		cout << i.name << ", ";
	}
	cout << endl;

	vector<int> rounds = {7,6,5,4,3,2,1,1,1,2,3,4,5,6,7};

	int current_index = 0;
	int index;
	int player_bid;
	int total_bid = 0;
	cout << "----------------- Begin Game -----------------" << endl;
	for(auto r : rounds) {
		total_bid = 0;
		cout << "Cards for this round: " << r << endl;
		index = (current_index + 1) % player_count;
		cout << "---------------- Start Biding ----------------" << endl;
		while(index != current_index) {
			cout << "Enter bid for: " << players[index].name << endl;
			cin >> player_bid;
			players[index].bid = player_bid;

			total_bid += player_bid;

			index++;
			index %= player_count;
		}

		cout << "Enter bid for: " << players[index].name;
		if(r - total_bid >= 0) {
			cout << ", cannot be " << (r - total_bid);
		}
		cout << endl;

		cin >> player_bid;

		players[index].bid = player_bid;

		index++;
		index %= player_count;

		cout << "---------------- Enter Tricks ----------------" << endl;
		while(index != current_index) {
			cout << "Enter number of tricks for: " << players[index].name << endl;
			cin >> player_bid;

			if(player_bid == players[index].bid) {
				players[index].score += 10 + player_bid;
			} else {
				players[index].score -= 10;
			}

			index++;
			index %= player_count;
		}
		cout << "Enter number of tricks for: " << players[index].name << endl;
		cin >> player_bid;

		if(player_bid == players[index].bid) {
			players[index].score += 10 + player_bid;
		} else {
			players[index].score -= 10;
		}

		current_index++;
		current_index %= player_count;

		cout << "------------------- Scores -------------------" << endl;
		for(auto i : players) {
			cout << i.name << ": " << i.score << endl;
		}
		cout << "----------------------------------------------" << endl << endl;
	}

	sort(players.begin(), players.end(), greater<Player>());

	cout << "---------------- Final Scores ----------------" << endl;
	for(auto i : players) {
		cout << i.name << ": " << i.score << endl;
	}

	return 0;
}