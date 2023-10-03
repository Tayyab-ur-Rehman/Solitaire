#pragma once
#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include <windows.h>
#include <windows.h>
#include <Windows.h>
#include <conio.h>
#include"st.h"
#include"qu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;




struct Position
{
	int ri, ci;
};
Position MouseClick(RenderWindow& window) {


	Position raw{ -1,-1 };
	Event event;
	while (window.waitEvent(event)) {
		switch (event.type) {
		case Event::Closed:
			window.close();
			exit(0);
			break;
		case Event::MouseButtonReleased:
			if (event.mouseButton.button == Mouse::Left) {
				raw.ri = event.mouseButton.y;
				raw.ci = event.mouseButton.x;
				return raw;
			}
			break;
		default:
			break;
		}
	}
	return raw;
}
#define        BLACK                   0
#define        BLUE                    1
#define        GREEN                   2
#define        CYAN                    3   
#define        RED                     4
#define        MAGENTA                 5
#define        BROWN                   6 
#define        LIGHTGRAY               7 
#define        DARKGRAY                8 
#define        LIGHTBLUE               9
#define        LIGHTGREEN             10
#define        LIGHTCYAN              11
#define        LIGHTRED               12
#define        LIGHTMAGENTA           13
#define        YELLOW                 14
#define        WHITE                  15

void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}


class card_game
{
	vector<MyStack<card>>slot;// d c h s
	vector<MyStack<card>>main;
	TQueue<TQueue<card>> pick;
	int no_cards = 52;
	int score = 0;
	int state = 0;
	char slot_d[4]{ 'd','c','h','s' };
	sf::Texture cardTextures[52];
	sf::Sprite cardSprites[52];
	std::string suits[4] = {"hearts", "diamonds", "clubs", "spades"};
	std::string ranks[13] = { "ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king" };

	
public:
	card_game( int level = 2, bool f = false)
	{
		if (!(level >= 1 && level <= 3))
			level = 3;

		vector<card>A;
		for (int c = 1; c < 5; c++) {

			for (int i = 1; i <= 13; i++)
			{
				card a;
				switch (c)
				{
				case 1:
				{
					a.colour = 'r';
					a.type = 'h';
					break;
				}
				case 2:
				{
					a.colour = 'r';
					a.type = 'd';
					break;
				}
				case 3:
				{
					a.colour = 'b';
					a.type = 'c';
					break;
				}
				case 4:
				{
					a.colour = 'b';
					a.type = 's';
				}
				}
				a.card_num = i;
				A.push_back(a);
			}
		}
		//Shuffle is to me done
		for (int i = 0; i < 200; i++)
		{
			int ind1 = rand() % 52;
			int ind2 = rand() % 52;
			swap(A[ind1], A[ind2]);


		}
		//main slot is done 1 2 3 4 5 6 7 
		for (int i = 0; i < 7; i++) {
			MyStack<card> B(13, i);
			for (int j = 0; j <= i; j++)
			{
				B.push(A[A.size() - 1]); A.pop_back();
				//single_card_p(B.top()); cout << " ";
			}
			main.push_back(B);
		}
		// pick is to be done
		while (A.size() != 0)
		{
			TQueue<card> T;
			for (int i = 0; i < level; i++)
			{

				T.Enqueue(A[A.size() - 1]);
				A.pop_back();
			}
			pick.Enqueue(T);
			cout << endl;
		}
		//this->print_sl();
		for (int i = 0; i < 4; i++)
		{
			MyStack<card>A;
			slot.push_back(A);
		}
		
		for (int suitIndex = 0; suitIndex < 4; suitIndex++) {
			for (int rankIndex = 0; rankIndex < 13; rankIndex++) {
				std::string filename = ranks[rankIndex] + "_of_" + suits[suitIndex] + ".png";

				if (!cardTextures[suitIndex * 13 + rankIndex].loadFromFile(filename)) {
					// Handle loading error
					cout << "can not load";
				}

				cardSprites[suitIndex * 13 + rankIndex].setTexture(cardTextures[suitIndex * 13 + rankIndex]);
			}
		}
	}
	card_game(const card_game& A)
	{
		slot = A.slot;
		main = A.main;
		pick = A.pick;

	}
	void rotate_pick()
	{
		TQueue <card> c = pick.Front();
		pick.Dequeue();
		pick.Enqueue(c);
	}
	void play()
	{
		RenderWindow window(sf::VideoMode(1200, 700), "SFML works!");
		window.clear(); bool m = false; Music c; 
		while (1)
		{
			if (m)
			{
				  c.openFromFile("mi.ogg");
				 c.play();
			}

			//this->print();
			this->PRINT(window);
			char s, d;
			/*
			cout << " source ,,, destination main (m),slot(s),pick(p)\n";
			do {
				cin >> s;
				if (s != 'n') {
					cin >> d;
				}
				else
				{
					d = 's';
				}

			} while (!(s == 'n' || ((s == 'p' || s == 'm' || s == 's' ) && (d == 'm' || d == 's'))));
			 m=move(s, d);*/
			m=move2(window);
			if(!m)
			cout << "nothing\n";
		}
	}
	bool can_palce_pickTomain(int c)
	{
		if (pick.size_() != 0) {
			card to_place = this->pick[0].Front();
			if (main[c].size_() > 0)
			{
				if (main[c].top().card_num - 1 == to_place.card_num && main[c].top().colour != to_place.colour)
				{
					return true;
				}
			}
			else
			{
				if (to_place.card_num == 13)
					return true;
			}
		}
		return false;
	}
	bool can_place_1c_main(card to_place, int c)
	{
		if (main[c].top().card_num - 1 == to_place.card_num && main[c].top().colour != to_place.colour)
			return true;
		return false;

	}
	bool can_place_toslot(card to_place)
	{
		if (pick.size_() != 0) {
			//card to_place = this->pick[0].Front();
			int slot_ind = to_place.slot_num();
			if (slot[slot_ind].size_() == 0 && to_place.card_num == 1)
				return true;
			else if (slot[slot_ind].top().card_num == to_place.card_num - 1)
				return true;
		}
		return false;
	}
	void place_pickTomain(int col)
	{
		card to_place = pick[0].Front();
		//cout << pick[0].size;
		
		cout << pick[0].size;

		main[col].push(to_place);
		TQueue <card> c = pick.Front();
		pick.Dequeue();
		c.Dequeue();
		if (c.size_() != 0)
			pick.Enqueue(c);
	}
	void place_pickToslot()
	{
		card to_place = pick[0].Front();
		int slot_ind = to_place.slot_num();
		pick[0].Dequeue();

		slot[slot_ind].push(to_place);
		TQueue <card> c = pick.Front();
		pick.Dequeue();
		if (c.size_() != 0)
			pick.Enqueue(c);
	}
	void mainToSlot(int col)
	{
		card A = main[col].top();
		main[col].pop();
		int num = A.slot_num();
		slot[num].push(A);
		if (main[col].size == main[col].hidden)
		{
			main[col].hidden--;
		}
	}
	void slotTomain(int sl_num, int col)
	{
		card a = slot[sl_num].top();
		slot[sl_num].pop();
		main[col].push(a);

	}
	void mouse_to_ch(int r,int c)
	{
		char s, d;
		int ri, ci;
		ri = (r - 197);
		int ind_sl;
		ci = (c - 200)/98;
		if (ci == -1 && r < 220)
		{
			s = 'p';
		}
		else if (ci == -1 && r >600)
		{
			s = 'n'; d = 'n';
		}
		else if (r<126 && ci>=3 &&  ci<=6)
		{
			s = 's';
			ind_sl = ci - 3;
		}
		else if((ci >= 0 && ci <= 6))
		{ 
			int var = this->main[ci].size_();
			ri /= 50;
		}
		


	}
	bool move(char s, char d = ' ')
	{
		bool m = false;
		if (s == 'p' && d == 'm')
		{
			cout << "destination col ...";
			int col; cin >> col;
			col--;
			if (col >= 0 && col <= 6)
				if (can_palce_pickTomain(col))
				{
					place_pickTomain(col);
					m = true;
					score += 5;
				}
		}
		else if (s == 's' && d == 'm')
		{
			cout << "destination col ...";
			int col; cin >> col;
			col--;
			if (col >= 0 && col <= 6)
			{
				int sl_num;
				cout << "slot no 1...4"; cin >> sl_num; sl_num--;
				if (sl_num >= 0 && sl_num <= 3)
				{
					card a = slot[sl_num].top();
					if (can_place_1c_main(a, col))
					{
						m = true; score -= 5;
						slotTomain(sl_num, col);
					}
				}
			}
		}
		else if (s == 'p' && d == 's')
		{
			card to_place = this->pick[0].Front();
			if (can_place_toslot(to_place))
			{
				m = true; score += 10;
				place_pickToslot();
			}
		}
		else if (s == 'm' && d == 'm')
		{
			int col1, col2; int no_cards_toPlace;
			cout << "col 1= ";
			do {
				cin >> col1; col1--;
			} while (col1 > 6 || col1 < 0);
			cout << "no. cards ="; cin >> no_cards_toPlace;

			if ((main[col1].size - main[col1].hidden) >= no_cards_toPlace && no_cards_toPlace <= main[col1].size_())
			{
				MyStack<card> A(no_cards);
				for (int i = 0; i < no_cards_toPlace; i++) {
					A.push(main[col1].top());
					main[col1].pop();
				}
				do {
					cout << "col2= "; cin >> col2; col2--;
				} while (col2 > 6 || col2 < 0);

				if (main[col2].size != 0) {
					if (main[col2].top().card_num - 1 == A.top().card_num && (main[col2].top().colour != A.top().colour))
					{
						while (A.size != 0) {
							card o = A.top();
							A.pop();
							main[col2].push(o);
							m = true;
							score += 5;

						}
					}
					else
					{
						while (A.size != 0) {
							card o = A.top();
							A.pop();
							main[col1].push(o);
						}
					}
				}
				else
				{
					if (A.top().card_num == 13)
					{
						m = true;

						while (A.size != 0) {
							card o = A.top();
							A.pop();
							main[col2].push(o); score += 5;
						}
					}
					else
					{
						while (A.size != 0) {
							card o = A.top();
							A.pop();
							main[col1].push(o);

						}
					}
				}
			}
			check_m(col2);
			check_m(col1);
		}
		else if (s == 'm' && d == 's')
		{
			cout << "destination col ...";
			int col; cin >> col;
			col--;
			if (col >= 0 && col <= 6)
			{
				card to_place = main[col].top();
				if (can_place_toslot(to_place))
				{
					mainToSlot(col); score += 10;
				}
			}

		}
		else if (s == 'n')
		{
			rotate_pick(); m = true;
		}
		return m;
	}
	bool move2(RenderWindow & window)
	{

		char s = 'k';char  d; int m_in_col, col_index_r, slot_number;
		int r, c,ri,ci;
		Position a = MouseClick(window);
		r = a.ri; c = a.ci;
		{
			ri = (r - 197);
			ci = (c - 200) / 98;
			if (ci == -1 && r < 220)
			{
				s = 'p';
			}
			else if (ci == -1 && r > 600)
			{
				s = 'n'; d = 'n';
			}
			else if (r < 126 && ci >= 3 && ci <= 6)
			{
				s = 's';
				slot_number = ci - 3;
			}
			else if ((ci >= 0 && ci <= 6))
			{
				int var = this->main[ci].size_();
				ri /= 50;
				s = 'm';
				m_in_col = ci;
				col_index_r = ri;

			}
		}
		bool m = false;
		bool find = false;
		if (s == 'p' || s == 's' || s == 'n' || s == 'm')
		{
			if (s == 'p')
			{
				{
					Position a2 = MouseClick(window);
					int c2 = a2.ci;
					int r2 = a2.ri;
					int ri2 = (r2 - 197);
					int ci2 = (c2 - 200) / 98;
					if ((ci2 >= 0 && ci2 <= 6) && r2 > 200)
					{
						int var = this->main[ci2].size_();
						ri2 /= 50;
						d = 'm';
						m_in_col = ci2;
						col_index_r = ri2;
						find = true;
					}
					else if (r2 < 126 && ci2 >= 3 && ci2 <= 6)
					{
						d = 's';
						slot_number = ci - 3;
						find = true;
					}


				}
				if (find) {
					if (d == 'm') {
						int col; col = m_in_col;
						if (col >= 0 && col <= 6)
							if (can_palce_pickTomain(col))
							{
								place_pickTomain(col);
								m = true;
								score += 5;
							}
					}
					if (d == 's')
					{

						card to_place = this->pick[0].Front();
						if (can_place_toslot(to_place))
						{
							m = true; score += 10;
							place_pickToslot();
						}
					}
				}
			}
			else if (s == 's')
			{
				bool find = false;
				int col;
				{
					Position a2 = MouseClick(window);
					int c2 = a2.ci;
					int r2 = a2.ri;
					int ri2 = (r2 - 197);
					int ci2 = (c2 - 200) / 98;
					if ((ci2 >= 0 && ci2 <= 6))
					{
						int var = this->main[ci2].size_();
						ri2 /= 50;
						d = 'm';
						m_in_col = ci2;
						col = m_in_col;
						col_index_r = ri2;
						find = true;
					}
					if ((ci2 >= 0 && ci2 <= 6))
					{
						int var = this->main[ci2].size_();
						ri2 /= 50;
						d = 'm';
						m_in_col = ci2;
						col = m_in_col;
						col_index_r = ri2;
						find = true;
					}
				}
				if (find)
					if (col >= 0 && col <= 6)
					{
						int sl_num;
						sl_num = slot_number;
						if (sl_num >= 0 && sl_num <= 3)
						{
							card a = slot[sl_num].top();
							if (can_place_1c_main(a, col))
							{
								m = true; score -= 5;
								slotTomain(sl_num, col);
							}
						}
					}
			}
			else if (s == 'm')
			{
				int m_in_col2;
				{
					Position a2 = MouseClick(window);
					int c2 = a2.ci;
					int r2 = a2.ri;
					int ri2 = (r2 - 197);
					int ci2 = (c2 - 200) / 98;
					if ((ci2 >= 0 && ci2 <= 6) && r2 > 200)
					{
						int var = this->main[ci2].size_();
						ri2 /= 50;
						d = 'm';
						m_in_col2 = ci2;
						find = true;
					}
					else if (r2 < 126 && ci2 >= 3 && ci2 <= 6)
					{
						d = 's';
						slot_number = ci - 3;
						find = true;
					}
				}
				if (find) {
					if (d == 's')
					{

						int col;
						col = m_in_col;
						if (col >= 0 && col <= 6)
						{
							card to_place = main[col].top();
							if (can_place_toslot(to_place))
							{
								mainToSlot(col); score += 10;
							}
						}
					}
					if (d == 'm') {
						int col1, col2; int no_cards_toPlace;
						cout << "col 1= ";
						col1 = m_in_col;
						if (col1 > 6 || col1 < 0)
							return false;
						cout << "no. cards ="; no_cards_toPlace= main[col1].size - col_index_r;
						if (no_cards_toPlace <= 0)
							return false;
						if ((main[col1].size - main[col1].hidden) >= no_cards_toPlace && no_cards_toPlace <= main[col1].size_())
						{
							MyStack<card> A(no_cards);
							for (int i = 0; i < no_cards_toPlace; i++) {
								A.push(main[col1].top());
								main[col1].pop();
							}
							
							cout << "col2= "; col2 = m_in_col2;
							if (col2 > 6 || col2 < 0) {
								while (A.size != 0)
								{
									card o = A.top();
									A.pop();
									main[col1].push(o);
								}
								return false;
							}

							if (main[col2].size != 0) {
								if (main[col2].top().card_num - 1 == A.top().card_num && (main[col2].top().colour != A.top().colour))
								{
									while (A.size != 0) {
										card o = A.top();
										A.pop();
										main[col2].push(o);
										m = true;
										score += 5;

									}
								}
								else
								{
									while (A.size != 0) {
										card o = A.top();
										A.pop();
										main[col1].push(o);
									}
								}
							}
							else
							{
								if (A.top().card_num == 13)
								{
									m = true;

									while (A.size != 0) {
										card o = A.top();
										A.pop();
										main[col2].push(o); score += 5;
									}
								}
								else
								{
									while (A.size != 0) {
										card o = A.top();
										A.pop();
										main[col1].push(o);

									}
								}
							}
						}
						check_m(col2);
						check_m(col1);
					}
				}
			}
			else if (s == 'n')
			{
				rotate_pick(); m = true;
			}
		}
		return m;
	}
	void single_card_p(card now, bool show = 1)
	{
		if (show) {
			if (now.colour == 'r')
			{
				SetClr(RED);
			}
			else
			{
				SetClr(15);

			}
			if (now.card_num >= 2 && now.card_num <= 10)
				cout << now.card_num;
			else
			{
				if (now.card_num == 1)
					cout << "A";
				else if (now.card_num == 11)
					cout << "J";
				else if (now.card_num == 12)
					cout << "Q";
				else if (now.card_num == 13)
					cout << "K";
				else
					cout << "N";
			}

			if (now.type == 'h')
				cout << " Heart ";
			else if (now.type == 'c')
				cout << " Club ";
			else if (now.type == 'd')
				cout << " Diamond ";
			else
				cout << " Spades ";

		}
		else
		{
			SetClr(DARKGRAY);
			cout << "CARD";
		}
		SetClr(15);
	}
	void print1()
	{
		if (pick.size_() != 0) {
			TQueue <card> now_q = pick.Front();
			for (int i = 0; i < now_q.size_(); i++)
			{
				card now = now_q[i];

				gotoRowCol(10 * i, 0);
				this->single_card_p(now);
				now_q.Dequeue();



			}
		}
		//it print's  pick queue
		for (int i = 0; i < 4; i++)
		{
			gotoRowCol(0, (10 * i) + 200);
			if (!slot.size() || !slot[i].size_())
				cout << "empty";
			else
				this->single_card_p(this->slot[i].top());

		}
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; main[i].size_() > j; j++)
			{
				gotoRowCol(400 + (j * 10), 400 + (i * 50));

				single_card_p(main[i].ptr[j]);

			}
		}
	}
	void print()
	{
		cout << this->score << endl;
		if (pick.size_() != 0) {
			TQueue <card> now_q = pick.Front();
			for (int i = now_q.size_() - 1; i > -1; i--)
			{
				card now = now_q[i];

				this->single_card_p(now);
				cout << endl;

			}
		}
		cout << endl;
		//it print's  pick queue
		cout << "                             ";
		for (int i = 0; i < 4; i++)
		{
			gotoRowCol(0, (10 * i) + 200);
			if (!slot.size() || !slot[i].size_())
				cout << "empty";
			else
				this->single_card_p(this->slot[i].top());
			cout << "     ";
		}
		cout << "\n main 1...7\n";
		for (int i = 0; i < 7; i++)
		{

			for (int j = 0; main[i].size_() > j; j++)
			{
				bool sh = false;
				if (j > main[i].hidden - 1)
					sh = 1;
				this->single_card_p(main[i].ptr[j], sh); cout << "    ";
			}
			cout << endl;
		}
	}
	void print_sl()
	{
		if (pick.size_() != 0) {
			for (int i = 0; i < pick.size_(); i++)
			{
				cout << "\n" << i << "\n";
				TQueue <card> now_q = pick[i];
				for (int j = 0; j < pick[i].size; j++)
				{
					card now = now_q[j];

					this->single_card_p(now);
					if (i != now_q.size_() - 1)
						cout << endl;

				}
				cout << endl;
			}
		}
	}
	int index_sp(card a)
	{
		int b;
		if (a.type == 'h')
			b = 0;
		if (a.type == 'd')
			b = 1;
		if (a.type == 'c')
			b = 2;
		if (a.type == 's')
			b = 3;
		return ((13 * b) + a.card_num-1);
	}
	void PRINT(RenderWindow & window)
	{
		window.clear();
		Texture tem1; tem1.loadFromFile("b1.png");
		Sprite si(tem1);
		si.setScale(0.172,0.347);
		si.setPosition(0,0);
		window.draw(si);

		string a = to_string(this->score);;
		string So = "Score "; So = So + a;

		Font font; font.loadFromFile("letters.ttf");
	    Text text; text.setFont(font); text.setCharacterSize(20); text.setFillColor(Color::White); text.setString(So);
	    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	    text.setPosition(1070.f, 600.f);
	    window.draw(text); 
		
		if (pick.size_() != 0) {
			if (pick.size_() != 0) {
				TQueue <card> now_q = pick.Front(); int p = 0;
				for (int i = now_q.size_() - 1; i > -1; i--)
				{
					card now = now_q[i];

					int ind = index_sp(now);
					cardSprites[ind].setPosition(0, 0 + (p * 40));
					cardSprites[ind].setScale(0.2, 0.2);
					window.draw(cardSprites[ind]);
					p++;
				}
			}
			Texture tem; tem.loadFromFile("e.png");
			Sprite s(tem);
			s.setScale(0.16f, 0.11f);
			s.setPosition(0 , 605);
			window.draw(s);
		}

		for (int i = 0; i < 4; i++)
		{
			gotoRowCol(0, (10 * i) + 200);
			if (!slot.size() || !slot[i].size_())
			{
				Texture tem; tem.loadFromFile("e.png");
				Sprite s(tem);
				s.setScale(0.16f, 0.16f);
				s.setPosition(500 + (i * 100), 5);
				window.draw(s);
			}
			else{
				int ind = index_sp(this->slot[i].top());
				cardSprites[ind].setScale(0.2, 0.2);
				cardSprites[ind].setPosition(500 + (i * 100), 5);
				window.draw(cardSprites[ind]);

	     	}
		}

			for (int i = 0; i < 7; i++)
			{
				if (main[i].size != 0) {
					for (int j = 0; main[i].size_() > j; j++)
					{

						bool sh = false;
						if (j > main[i].hidden - 1)
							sh = 1;
						card aa = main[i].ptr[j];
						int ind = index_sp(aa);
						if (sh == 1)
						{
							cardSprites[ind].setScale(0.18f, 0.18f);
							cardSprites[ind].setPosition(200 + (i * 100), 200 + (j * 50));
							window.draw(cardSprites[ind]);

						}
						else
						{
							Texture t; t.loadFromFile("oc.png");
							Sprite s(t);
							s.setScale(0.16f, 0.16f);
							s.setPosition(200 + (i * 100), 200 + (j * 50));
							window.draw(s);
						}
					}
				}
				else
				{
					Texture t; t.loadFromFile("e.png");
					Sprite s(t);
					s.setScale(0.17f, 0.17f);
					s.setPosition(200 + (i * 150), 200 );
					window.draw(s);
				}
			}

			window.display();
			
	
	}
	void check_m(int col)
	{

		if (main[col].hidden == main[col].size)
		{
			main[col].hidden--;
		}
	}

};

