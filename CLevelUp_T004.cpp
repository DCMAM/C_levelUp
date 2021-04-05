#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define max_string 32
#define max_row 13
#define max_col 26
#define max_food 6
#define max_list 50
#define max_string_length 32

char map[max_row][max_col];
int food_cordinate[max_food][2];
int player_row;
int player_col;
int total_food = 0;
int point=0;

void print_menu_3(){
	printf("How to Play\n");
	printf("===================================\n");
	printf("1. Player can use W(up), A(left), S(down), D(right) to move.\n");
	printf("2. There are 5 foods in the map, the position is randomed.\n");
	printf("3. You have to eat all the food in the map.\n\n");
}

void print_menu_2(){
	printf("Scoreboard Menu\n");
	printf("===============\n");
	printf("1. View Scoreboard\n");
	printf("2. Search Username\n");
	printf("3. Exit\n");
	printf("Choose: ");
}

void print_menu(){
	printf("Welcome To Hunger Bunny Sweety\n");
	printf("==============================\n");
	printf("1. Play\n");
	printf("2. Scoreboard\n");
	printf("3. How to Play\n");
	printf("4. Exit\n");
	printf("Choose: ");
}

void load_map(){
	FILE *fp = fopen("Map.txt", "r+");
	
	if(! fp ){
		printf("File not found\n");
	}
	else{
		int x=0;
	    while (1) {
	    	if(feof(fp)) break;
			fscanf(fp, "%[^\n]", map[x]); fgetc(fp);
			x++;
	    }
	}
}

void print_map(){
	printf("Food: %-4d Score: %-10d\n", total_food, point);
	for(int i=0; i<max_row; i++){
		for(int j=0; j<max_col; j++){
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

void generate_food(){
	for(int x=0; x<total_food;){	
		while(1){
			int random_row = rand()%max_row;	
			int random_col = rand()%max_col;
			if(map[random_row][random_col] != '#' && map[random_row][random_col] != 'P'
			&& map[random_row][random_col] != 'O'){
				map[random_row][random_col] = 'O';
				food_cordinate[x][0] = random_row;
				food_cordinate[x][1] = random_col;
				x++;
				break;
			}
		}
	}
}

char get_input(){
	char ch=0;
	if(kbhit()) {
		ch = getch();
	}
	return ch;
}

void update_player(char ch){
	if(ch == 'd' && map[player_row][player_col + 1] != '#'){
		map[player_row][player_col] = ' ';
		player_col++;
		if(map[player_row][player_col] == 'O'){
			total_food--;
			point = point + (1000 + (rand()%1000)) ;
		}
		map[player_row][player_col] = 'P';
	}
	else if(ch == 's' && map[player_row+1][player_col] != '#'){
		map[player_row][player_col] = ' ';
		player_row++;
		if(map[player_row][player_col] == 'O'){
			total_food--;
			point = point + (1000 + (rand()%1000)) ;
		}
		map[player_row][player_col] = 'P';
	}
	else if(ch == 'a' && map[player_row][player_col-1] != '#' ){
		map[player_row][player_col] = ' ';
		player_col--;
		if(map[player_row][player_col] == 'O'){
			total_food--;
			point = point + (1000 + (rand()%1000)) ;
		}
		map[player_row][player_col] = 'P';
	}
	else if(ch == 'w' && map[player_row-1][player_col] != '#' ){
		map[player_row][player_col] = ' ';
		player_row--;
		if(map[player_row][player_col] == 'O'){
			total_food--;
			point = point + (1000 + (rand()%1000)) ;
		}
		map[player_row][player_col] = 'P';
	}	
}

void print_all(){
	char line[max_list][100];
	char name[max_list][100];
	char point[max_list][50];
	
	FILE *fp = fopen("Scoreboard.txt", "r+");
	if(! fp ){
		printf("Creating File..\n");
//		fopen("Scoreboard.txt", "w");
//		return;
	}
	
	int x=0;
    while (1) {
    	if(feof(fp)) break;
		fscanf(fp, "%[^\n]", line[x]); 
		fgetc(fp);
		char *p = strtok(line[x], "#");
		int z=0;
	    while(p != NULL){
	    	if(z%4 == 0) strcpy(name[x], p);
	    	if(z%4 == 1) strcpy(point[x], p);
	        p = strtok (NULL, "#");
	        z++;
		}
		x++;
    }
	    
	printf("==============================================================\n");
	printf("%| %-4s | %-32s | %-16s |\n", "No.", "Name", "Point");
	printf("==============================================================\n");
	for(int i=0; i<x-1; i++){
		printf("| %-4d | %-32s | %-16s |\n", i+1, name[i], point[i]);
	}
	printf("==============================================================\n");
}

void search(char name_[100]){
	char line[max_list][100];
	char name[max_list][100];
	char point[max_list][50];
	
	FILE *fp = fopen("Scoreboard.txt", "r+");
	if(! fp ){
		printf("Creating File..\n");
//		fopen("Scoreboard.txt", "w");
		return;
	}
	
	int x=0;
    while (1) {
    	if(feof(fp)) break;
		fscanf(fp, "%[^\n]", line[x]); 
		fgetc(fp);
		char *p = strtok(line[x], "#");
		int z=0;
	    while(p != NULL){
	    	if(z%4 == 0) strcpy(name[x], p);
	    	if(z%4 == 1) strcpy(point[x], p);
	        p = strtok (NULL, "#");
	        z++;
		}
		x++;
    }
	    
	printf("=======================================================\n");
	printf("| %-48s    |\n", "Your Search Data");
	printf("=======================================================\n");
	int flag_ = 0;
	for(int i=0; i<x; i++){
		if(strcmp(name[i], name_) == 0) {
			printf("| %-32s | %-16s |\n", name[i], point[i]);
			flag_ = 1;
		}
	}
	if (flag_ == 0){
		printf("| No data found!                                      |\n");
	}
	printf("=======================================================\n");
}

int is_unique(char name_[100]){
	char line[max_list][100];
	char name[max_list][100];
	char point[max_list][50];
	
	FILE *fp = fopen("Scoreboard.txt", "r+");
	if(! fp ){
		return 0;
//		printf("Creating File..\n");
//		fopen("Scoreboard.txt", "w");
	}
	
	int x=0;
    while (1) {
    	if(feof(fp)) break;
		fscanf(fp, "%[^\n]", line[x]); 
		fgetc(fp);
		char *p = strtok(line[x], "#");
		int z=0;
	    while(p != NULL){
	    	if(z%4 == 0) strcpy(name[x], p);
	    	if(z%4 == 1) strcpy(point[x], p);
	        p = strtok (NULL, "#");
	        z++;
		}
		x++;
    }
	    
	for(int i=0; i<x; i++){
		if(strcmp(name[i], name_) == 0) return 0;
	}
	return 1;
}

void add_user(char user[max_string_length], long score){
	FILE *fp = fopen("Scoreboard.txt", "a+");
	fprintf(fp, "%s#%d\n", user, score);
}

int main(){
	srand(time(NULL));
	do{
		print_menu();
		int menu =0;
		scanf("%d", &menu);
		if(menu == 1){
			char name[max_string];
			do{
				printf("Fill Your Username: ");
				scanf("%s", &name);
				if(is_unique(name) == 1) break;
			}while(1);
			
			load_map();
			map[1][1] = 'P';
			player_row = 1;
			player_col = 1;
			total_food = 5;
			generate_food();
			do{
				if(total_food == 0) {
					printf("Your score is %d\n", point);
					add_user(name, point);
					system("pause");
					break;
				}
				print_map();
				char ch = get_input();
				update_player(ch);
				Sleep(100);
				system("cls");
			}while(1);
		}
		else if(menu == 2){
			do{
				system("cls");
				int menu_2;
				print_menu_2();
				scanf("%d", &menu_2);
				if(menu_2 == 1){
					print_all();
				}
				else if(menu_2 == 2){
					char name[32];
					printf("Search Your Username: ");
					scanf("%s", &name);
					search(name);
				}
				else if (menu_2 == 3){
					break;
				}
				system("pause");
			} while(1);
		}
		else if(menu == 3){
			system("cls");
			print_menu_3();
			system("pause");
		}
		else if(menu == 4){
			break;
		}
		else{
			
		}
		system("cls");
	}while(1);
	return 0;
}
