#include <iostream>
#include <ncurses.h>
#include <unistd.h>

class NcursesGame{
private:
	char roll_bar[5];
	int center_x;
	int center_y;
	int in_key;
	int center_cnt;
	int cur_x;
	int cur_y;
	int cur_rad;

public:
	NcursesGame();
	~NcursesGame();

	void move_curses();
	void disp_curses();
	void proc_game();
	void key_input();
};

NcursesGame::NcursesGame(){
	initscr();
	curs_set(0);
	cbreak();
	noecho();
	leaveok(stdscr, TRUE);
	
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	bkgd(COLOR_PAIR(1));
	
	center_x = COLS / 2;
	center_y = LINES / 2;
	cur_x = center_x + 10;
	cur_y = center_y;
	cur_rad = center_cnt = 0;
	strcpy(roll_bar, "|\\-/");

	timeout(0);
	keypad(stdscr, TRUE);
}

NcursesGame::~NcursesGame(){
	endwin();
}

void NcursesGame::key_input(){
	in_key = getch();
}

void NcursesGame::move_curses(){
	if(in_key != -1){
		if(in_key == KEY_LEFT){
			if(cur_rad < 90) cur_x -= 2, cur_y--;
			else if(cur_rad < 180) cur_x -= 2, cur_y++;
			else if(cur_rad < 270) cur_x += 2, cur_y++;
			else if(cur_rad < 360) cur_x += 2, cur_y--;

			cur_rad += 18;
		}else if(in_key == KEY_RIGHT){
			if(cur_rad == 0 || cur_rad > 270) cur_x -= 2, cur_y++;
			else if(cur_rad > 180) cur_x -= 2, cur_y--;
			else if(cur_rad > 90) cur_x += 2, cur_y--;
			else if(cur_rad > 0) cur_x += 2, cur_y++;
		
			cur_rad -= 18;
		}
		if(cur_rad >= 360) cur_rad -= 360;
		else if(cur_rad < 0) cur_rad += 360;
	}

	center_cnt++;
	move(cur_y, cur_x);
}

void NcursesGame::disp_curses(){
	printw("o");
	mvprintw(center_y, center_x, "%c", roll_bar[center_cnt%4]);
	mvprintw(0, 0, "%d:%d", cur_x, cur_y);
	mvprintw(1, 0, "%d", center_cnt);
}

void NcursesGame::proc_game(){
	while(key_input(), in_key != 'q' && in_key != 'Q'){
		erase();

		move_curses();
		disp_curses();

		refresh();
		usleep(70000);
		//sleep(0);
	}
}

int main(){
	/*
	initscr();
	curs_set(0);
	cbreak();
	
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	bkgd(COLOR_PAIR(1));

	char roll_bar[] = "|\\-/";
	const int center_y = LINES / 2, center_x = COLS / 2;
	int key, cur_x = center_x, cur_y = center_y - 5, i = 0;

	timeout(0);
	while(key = getch(), key != 'q' && key != 'Q'){
		erase();

		if(i >= 20) i = 0;
		if(i >= 0 && i < 5) cur_x -= 2, cur_y++;
		else if(i >= 5 && i < 10) cur_x += 2, cur_y++;
		else if(i >= 10 && i < 15) cur_x += 2, cur_y--;
		else if(i >= 15 && i < 20) cur_x -= 2, cur_y--;

		move(cur_y, cur_x);
		printw("o");
		mvprintw(center_y, center_x, "%c", roll_bar[i%4]);
		mvprintw(0, 0, "%d:%d", LINES, COLS);
		mvprintw(1, 0, "%d:%d", center_x, center_y);
		mvprintw(2, 0, "%d:%d", cur_x, cur_y);
		
		refresh();
		i++;
		usleep(100000);
	}
	
	endwin();
	*/

	NcursesGame game;
	game.proc_game();

	return 0;
}
