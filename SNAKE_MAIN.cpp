// Main File
#include <iostream>
#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "SNAKE_DDA.cpp"
#include "SNAKE_POLY_FILL.cpp"

using namespace std;

void fillBlack(short int, short int, short int);
void drawBoundaries();
void my_cpy(char *, char *);

typedef struct snake Snake;

struct snake{
	short int x, y;
	Snake *next, *prev;
};

void addNode(Snake **head, int x, int y){
	Snake *n;
	n = new Snake;
	n->x = x, n->y = y;
	n->next = NULL, n->prev = NULL;
	if(!(*head)){
		*head = n;
	}
	else{
		n->next = (*head);
		(*head)->prev = n;
		*head = n;
	}
}

void deallocList(Snake **head){
	Snake *t = *head, *f;
	while(t){
		f = t->next;
		delete t;
		t = f;
	}
	*head = NULL;
}

class Game{
	short int init_x, init_y, x_inc, y_inc, box_size, score, speed, level;
	short int food_color, head_color;
	short int maxX, maxY;
    time_t begin_t;
    Snake *head;
	public:
	Game(int init_x, int init_y, int box_size){
		this->init_x = init_x;
		this->init_y = init_y;
		this->box_size = box_size;
		head = NULL;
		x_inc = box_size, y_inc = box_size;
		level = 1;
		score = 0;
		speed = 100;
		maxX = getmaxx();
		maxY = getmaxy();
		food_color = 10;
		head_color = RED;
	}
	~Game(){
	    // Deallocated the complete list from the heap after
	    // game is over or completed or terminated using ESC button.
        deallocList(&head);
	}
	void displayDetails();
	void level_screen();
	void win_screen();
	void game_over();
	void get_time(short int, short int, short int);
	short int my_rng(short int, short int);
	void startGame();
};

inline void Game::displayDetails(){
    short int t1, t2;
    char str[10], *ptr;
	ptr = str;
    setcolor(10);
    settextstyle(3, 0, 1);
	my_cpy(str, "Score: ");
	if(score > 9){
        t1 = score;
        t2 = score % 10;
        score /= 10;
        str[7] = 48+score;
        str[8] = 48+t2;
        str[9] = '\0';
        score = t1;
	}
	else{
        str[7] = 48+score;
        str[8] = '\0';
	}
    outtextxy(5, 0, ptr);
    my_cpy(str, "Level: ");
	str[7] = 48+level;
	str[8] = '\0';
    outtextxy(580, 0, ptr);
}

void Game::level_screen(){
	short int i;
	char str[10], *ptr;
    ptr = str;

	my_cpy(str, "Level ");

	str[6] = 48+level;
	str[7] = '\0';
	cleardevice();

	setcolor(RED);
	settextstyle(4, 0, 3);
	outtextxy(240, 160, "Up Next");

	setcolor(WHITE);
	settextstyle(3, 0, 20);
	outtextxy(110, 200, ptr);

	my_cpy(str, ".");

	for(i = 0; i<5; i++){
		if(i % 2 == 0)
			setcolor(RED);
		else
			setcolor(BLACK);
		outtextxy(490, 200, ptr);
		delay(700);
	}
	food_color = my_rng(0, 15);
    if(level == 2){
        head_color = 3;
    }
    if(level == 3){
        head_color = GREEN;
    }
    if(level == 4){
        head_color = BLUE;
    }
    if(level == 5){
        head_color = RED;
        food_color = YELLOW;
    }

	cleardevice();
	drawBoundaries();
}

void Game::win_screen(){
	short int i = 0, t1, t2;
	char str[10], *ptr;
	ptr = str;
	cleardevice();
	get_time(100, WHITE, 2);

	setcolor(GREEN);
	settextstyle(3, 0, 10);
	outtextxy(130, 180, "Winner");

	setcolor(RED);
	settextstyle(3, 0, 2);
	outtextxy(210, 400, "Press any key to continue.");
	my_cpy(str, "Score: ");
	if(score > 9){
        t1 = score;
        t2 = score % 10;
        score /= 10;
        str[7] = 48+score;
        str[8] = 48+t2;
        str[9] = '\0';
        score = t1;
	}
	else{
        str[7] = 48+score;
        str[8] = '\0';
	}
	setcolor(WHITE);
	outtextxy(70, 100, ptr);
    my_cpy(str, "Level: ");
	str[7] = 48+level;
	str[8] = '\0';
	outtextxy(500, 100, ptr);
	my_cpy(str, "!");

    settextstyle(3, 0, 10);
	while(1){
        if(kbhit()){
            getch();
            cleardevice();
            return;
        }
		if(i % 2 == 0)
			setcolor(GREEN);
		else
			setcolor(BLACK);

		outtextxy(460, 180, ptr);
		delay(700);
		i++;
	}
}

void Game::game_over(){
	short int i = 0, t1, t2;
	char str[10], *ptr;
	ptr = str;
	cleardevice();
	get_time(100, WHITE, 2);

	setcolor(RED);
	settextstyle(3, 0, 9);
	outtextxy(70, 180, "Game Over");
	settextstyle(3, 0, 2);
	outtextxy(210, 400, "Press any key to continue.");
	my_cpy(str, "Score: ");
	if(score > 9){
        t1 = score;
        t2 = score % 10;
        score /= 10;
        str[7] = 48+score;
        str[8] = 48+t2;
        str[9] = '\0';
        score = t1;
	}
	else{
        str[7] = 48+score;
        str[8] = '\0';
	}

	setcolor(WHITE);
	outtextxy(70, 100, ptr);
    my_cpy(str, "Level: ");
	str[7] = 48+level;
	str[8] = '\0';

	outtextxy(500, 100, ptr);
	my_cpy(str, ".");

    settextstyle(3, 0, 9);
	while(1){
        if(kbhit()){
            getch();
            cleardevice();
            return;
        }
		if(i % 2 == 0)
			setcolor(RED);
		else
			setcolor(BLACK);
		outtextxy(550, 180, ptr);
		delay(700);
		i++;
	}
}

inline void Game::get_time(short int y, short int color, short int font_size){
    char str[10], *ptr;
	ptr = str;
	setcolor(color);
	settextstyle(3, 0, font_size);
	outtextxy(220, y, "Time: ");
    time_t end_t = clock();
    int mins, secs, temp = 0, t1, t2;
    if(end_t - begin_t > 59999){
        mins = (int)((end_t - begin_t) / 60000);
        secs = (int)((end_t-begin_t)/(double)CLK_TCK) % 60;
        if(mins > 9){
            t1 = mins;
            t2 = mins % 10;
            mins /= 10;
            str[0] = 48+mins;
            str[1] = 48+t2;
            str[2] = '\0';
        }
        else{
            str[0] = 48+mins;
            str[1] = '\0';
        }

        outtextxy(280, y, ptr);
        outtextxy(300, y, " mins");

        if(secs > 9){
            t1 = secs;
            t2 = secs % 10;

            while(secs){
                temp = secs % 10;
                secs /= 10;
            }
            secs = temp;
            str[0] = 48+secs;
            str[1] = 48+t2;
            str[2] = '\0';
        }
        else{
            str[0] = 48+secs;
            str[1] = ' ';
            str[2] = ' ';
            str[3] = '\0';
        }
        outtextxy(360, y, ptr);
        outtextxy(380, y, " secs");
    }

    else{
        mins = 0;
        secs = (end_t-begin_t)/(double)CLK_TCK;
        str[0] = 48+mins;
        str[1] = '\0';
        outtextxy(280, y, ptr);
        outtextxy(300, y, " mins");
        if(secs > 9){
            t1 = secs;
            t2 = secs % 10;
            secs /= 10;
            str[0] = 48+secs;
            str[1] = 48+t2;
            str[2] = '\0';
        }
        else{
            str[0] = 48+secs;
            str[1] = '\0';
        }
        outtextxy(360, y, ptr);
        outtextxy(380, y, " secs");
    }
}

inline short int Game::my_rng(short int lower, short int upper){
	return ((rand() % (upper-lower+1))+lower);
}

void Game::startGame(){
	char k = 77;
	short int x = init_x, y = init_y, p, q, temp, i = 0;
	y_inc = 0;
	Snake *t;
    // Initialing the snake with 5 nodes.
	addNode(&head, x, y);
	addNode(&head, x+x_inc, y);
	addNode(&head, x+2*x_inc, y);
	addNode(&head, x+3*x_inc, y);
	addNode(&head, x+4*x_inc, y);
	// -- Initialing the snake with 5 nodes.

	// Randomly generating the food on the map
	p = my_rng(box_size, maxX - box_size);
	temp = p%20;
	p = p - temp; // To ensure that the food generated matches the grid line with the snake.
	q = my_rng(20+box_size, maxY - box_size);
	temp = q%20;
	q = q - temp; // To ensure that the food generated matches the grid line with the snake.
	if(p<=1)
		p = box_size;
	else if(p>=639)
		p = 640 - box_size;
	if(q<=20)
		q = 20 + box_size;
	else if(q>=479)
		q = 480 - box_size;
	drawSquare(p, q, WHITE, box_size);
	fillPoly(p, q, food_color, BLACK);
	//drawSquare(p, q, WHITE, box_size);
	// -- Randomly generating the food on the map

	displayDetails();
	begin_t = clock(); // Starting the timer.
	// Main Loop, run till ESC is pressed, or game over, or game completed.
	while(k != 27){
        // Displaying time on top of the screen continuously.
		get_time(0, 10, 1);
		// If key is pressed.
		if(kbhit()){
            k = getch();
			if(k == 72 && y_inc != box_size){
				// UP
				x_inc = 0;
				y_inc = -box_size;
			}
			else if(k == 77 && x_inc != -box_size){
				// RIGHT
				x_inc = box_size;
				y_inc = 0;
			}
			else if(k == 80 && y_inc != -box_size){
				// DOWN
				x_inc = 0;
				y_inc = box_size;
			}
			else if(k == 75 && x_inc != box_size){
				// LEFT
				x_inc = -box_size;
				y_inc = 0;
			}
		}
        // -- If key is pressed.
		else{
			while(head->next){
				head = head->next;
			}
			while(head->prev){
				head->x = head->prev->x;
				head->y = head->prev->y;
				head = head->prev;
			}
			// Get next coordinate based on arrow key pressed
			head->x += x_inc;
			head->y += y_inc;

			// Check if snake's head crosses the boundaries
			if(head->x > maxX || head->x < 0){
				game_over();
				return;
			}
			else if(head->y > maxY || head->y < 20){
				game_over();
				return;
			}
			// -- Check if snake's head crosses the boundaries

			// Draw the complete Snake
			t = head;
			drawSquare(t->x, t->y, WHITE, box_size);
			fillPoly(t->x, t->y, head_color, BLACK);
			drawSquare(t->x, t->y, WHITE, box_size);
			t = t->next;
			while(t->next){
				drawSquare(t->x, t->y, head_color, box_size);
				fillPoly(t->x, t->y, WHITE, BLACK);
				drawSquare(t->x, t->y, head_color, box_size);
				t = t->next;
			}
			delay(speed);
			fillBlack(t->x, t->y, box_size);
			fillBlack(head->x, head->y, box_size);
			// -- Draw the complete Snake
		}
        // Check if snake's head hits it's own body.
        t = head->next;
        while(t){
            if(head->x == t->x && head->y == t->y){
                game_over();
                return;
            }
            t = t->next;
        }
        // -- Check if snake's head hits it's own body.

        // If snake eats the food.
        if(head->x == p && head->y == q){
            short int flag = 0;
            score++;
            if(score % 5 == 0){
                level++;
                if(level == 6){
                    level--;
                    win_screen();
                    return;
                }
                speed -= 20;
                level_screen();
            }
            displayDetails();
            fillBlack(p, q, box_size);
            addNode(&head, head->x+x_inc, head->y+y_inc);
            t = head;

            // Loop for not generating food under the snake's body.
            while(t){
                if(flag == 0){
                    p = my_rng(box_size, maxX - box_size);
                    temp = p%20;
                    p = p - temp;
                    q = my_rng(20+box_size, maxY - box_size);
                    temp = q%20;
                    q = q - temp;
                    if(p<=1)
                        p = box_size;
                    else if(p>=639)
                        p = 640 - box_size;
                    if(q<=20)
                        q = 20 + box_size;
                    else if(q>=479)
                        q = 480 - box_size;
                    flag = 1;
                }

                if(t->x == p && t->y == q){
                    t = head;
                    flag = 0;
                    continue;
                }
                t = t->next;
            }
            // -- Loop for not generating food under the snake's body.
            drawSquare(p, q, WHITE, box_size);
            fillPoly(p, q, food_color, BLACK);
            //drawSquare(p, q, WHITE, box_size);
        }
        // -- If snake eats the food.
	}
}

// Helper Functions
void fillBlack(short int ox, short int oy, short int b_size){
	short int bs = b_size/2, i, j, x, y;
	x = ox-bs, y = oy-bs;
	for(i = x; i<=ox+bs; i++){
		for(j = y; j<=oy+bs; j++){
			putpixel(i, j, BLACK);
		}
	}
}

void drawBoundaries(){
	dda(0, 20, 639, 20, RED);
	dda(639, 20, 639, 479, RED);
	dda(639, 479, 0, 479, RED);
	dda(0, 479, 0, 20, RED);
}

// String copy function
void my_cpy(char *str, char *ptr){
	while(*ptr != '\0'){
		*str = *ptr;
		str++;
		ptr++;
	}
	*str = '\0';
}
// -- Helper Functions

void show_instructions(){
    short int k;
    cleardevice();
	setcolor(YELLOW);
	settextstyle(8, 0, 6);
	outtextxy(130, 40, "Instructions");

	setcolor(RED);
	settextstyle(8, 0, 1);
	outtextxy(200, 100, "Press ESC to go back.");

	setcolor(WHITE);
	settextstyle(3, 0, 2);
	outtextxy(70, 140, "1. Use arrow keys to move the snake around the map.");

	setcolor(WHITE);
	settextstyle(3, 0, 2);
	outtextxy(70, 180, "2. Eat the food placed randomly on the map to grow in size.");

	setcolor(WHITE);
	settextstyle(3, 0, 2);
	outtextxy(70, 220, "3. The Score increases as you eat food.");

	setcolor(WHITE);
	settextstyle(3, 0, 2);
	outtextxy(70, 260, "4. Every 5 points scored the level increases,");

    setcolor(WHITE);
	settextstyle(3, 0, 2);
	outtextxy(90, 285, "speed of the snake will also increase with every level.");

	setcolor(WHITE);
	settextstyle(3, 0, 2);
	outtextxy(70, 320, "5. If the snake hits it's own body, Game Over.");

	setcolor(WHITE);
	settextstyle(3, 0, 2);
	outtextxy(70, 360, "6. If the snake hits the boundaries of the map, Game Over.");

	setcolor(GREEN);
	settextstyle(3, 0, 2);
	outtextxy(170, 410, "Complete Level 5 to win the Game!!");

	while(1){
		if(kbhit()){
			k = getch();
			if(k == 27){
                return;
			}
		}
	}
}

short int menu(){
	short int k, i = 0;
	cleardevice();
	setcolor(10);
	settextstyle(8, 0, 8);
	outtextxy(70, 50, "Snake Game");
	setcolor(YELLOW);
	settextstyle(3, 0, 4);
	outtextxy(270, 140, "in C++");
	setcolor(10);
	settextstyle(3, 0, 1);
	outtextxy(180, 400, "Use Up & Down Keys to select an option.");
	while(1){
		if(kbhit()){
			k = getch();
			if(k == 13){
				break;
			}
			if(k == 72){
				i--;
				i = i<0?2:i;
			}
			if(k == 80){
				i++;
				i = i>2?0:i;
			}
		}
		if(i == 0){
			setcolor(RED);
			settextstyle(8, 0, 4);
			outtextxy(220, 220, "Start Game");
			setcolor(WHITE);
			settextstyle(8, 0, 4);
			outtextxy(200, 270, "Instructions");
			setcolor(WHITE);
			settextstyle(8, 0, 4);
			outtextxy(280, 320, "Exit");
		}
		if(i == 1){
			setcolor(WHITE);
			settextstyle(8, 0, 4);
			outtextxy(220, 220, "Start Game");
			setcolor(RED);
			settextstyle(8, 0, 4);
			outtextxy(200, 270, "Instructions");
			setcolor(WHITE);
			settextstyle(8, 0, 4);
			outtextxy(280, 320, "Exit");
		}
		if(i == 2){
			setcolor(WHITE);
			settextstyle(8, 0, 4);
			outtextxy(220, 220, "Start Game");
			setcolor(WHITE);
			settextstyle(8, 0, 4);
			outtextxy(200, 270, "Instructions");
			setcolor(RED);
			settextstyle(8, 0, 4);
			outtextxy(280, 320, "Exit");
		}
		delay(5);
	}
	if(i == 0){
		return 0;
	}
	if(i == 1){
        show_instructions();
	}
	if(i == 2){
		closegraph();
		exit(0);
	}
	return 1;
}

void Stealth()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth,0);
}

int main(){
	// Initializing the game window in the center of the screen, no matter what the resolution is.
	short int ch, x = 640 / 2, y = 480 / 2;
	DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
	DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
	initwindow(640, 480, "Snake Game", screenWidth/2 - x, screenHeight/2 - y);
	// -- Initializing the game window in the center of the screen, no matter what the resolution is.
	Stealth();
	while(1){
		ch = menu();
		if(ch == 0){
			cleardevice();
			drawBoundaries();
			Game *obj = new Game(100, 240, 10);
			obj->startGame();
			delete obj;
			cleardevice();
		}
	}
}
