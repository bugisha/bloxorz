#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef enum meni { GLAVNI, MENI1, KRAJ, IGRA }menu;

typedef struct gr {
	int i, j;
	struct gr* next;
}Graf;

typedef struct {
	int i, j;
}Index;

typedef struct {
	int starti, startj;
	int endi, endj;
	int m, n;
}Info;

typedef struct {
	int i[2], j[2];
	int stanje;
	int potez;
}Stanje;

void clean() {
	for (int i = 0; i < 50; i++) printf("\n");
}

void push(int *top, Stanje* s, int size, Stanje val) {
	if (*top >= size-1) {
		printf("TEST: Stack full.\n");
		//return s;
	}
	else {
		*top = *top + 1;
		s[*top] = val;
	}
	//return s;
}

Stanje pop(int *top, Stanje* s) {
	Stanje old;
	old.i[0] = 2;
	old.j[0] = 2;
	old.i[1] = -1;
	old.j[1] = -1;
	old.stanje = 1;
	if (*top == -1) {
		printf("TEST: Stack empty.\n");
	}
	else {
		old = s[*top];
		(*top)--;
		return old;
	}
	return old;
}

int stack_empty(int top) {
	if (top == -1) {
		return 1;
	}
	else {
		return 0;
	}
}

void DFS(Graf ** G, Info stats,int glcnt) {
	int m = stats.m;
	int n = stats.n;
	Stanje s[400];

	int visit1[400], visit2[400], visit3[400];
	int level[3][400];
	char potezi[400];
	for (int i = 0; i < 400; i++) {
		visit1[i] = 0;
		visit2[i] = 0;
		visit3[i] = 0;
		for (int j = 0; j < 3; j++) {
			level[j][i] = 0;
		}
		potezi[i] = '-';
	}
	Stanje v,u;
	Graf* tmp;
	v.i[0] = stats.starti;
	v.j[0] = stats.startj;
	v.i[1] = -1;
	v.j[1] = -1;
	v.stanje = 1;
	int top = -1;
	char potez = '-';
	Stanje prevs[400];
	int cnt = 0;
	push(&top, s, 400, v);
	int dif = 0,id=0;
	Stanje old;
	while (stack_empty(top) == 0 && visit1[n*(stats.endi)+stats.endj] == 0) {
		old = v;
		v = pop(&top, s);
		prevs[id] = v;
		//if(old.i[0] )
		//old = prevs[id];
		dif = level[v.stanje - 1][n * (v.i[0]) + v.j[0]] - level[old.stanje - 1][n * (old.i[0]) + old.j[0]] -1;
		if (dif < 0) {
			id += dif;
			old = prevs[id-1];
			if (old.stanje == 1 && v.stanje == 2) {
				if (old.j[0] < v.j[0]) v.potez = 'd';
				else v.potez = 'a';
			}
			else if (old.stanje == 1 && v.stanje == 3) {
				if (old.i[0] > v.i[0]) v.potez = 'w';
				else v.potez = 's';
			}
			else if (old.stanje == 2 && v.stanje == 2) {
				if (v.i[0] < old.i[0]) v.potez = 'w';
				else v.potez = 's';
			}
			else if (old.stanje == 2 && v.stanje == 1) {
				if (v.j[0] > old.j[0]) v.potez = 'd';
				else v.potez = 'a';
			}
			else if (old.stanje == 3 && v.stanje == 1) {
				if (v.i[0] < old.i[0]) v.potez = 'w';
				else v.potez = 's';
			}
			else if (old.stanje == 3 && v.stanje == 3) {
				if (v.j[0] > old.j[0]) v.potez = 'd';
				else v.potez = 'a';
			}
			//if (cnt >= 0) {
				//potezi[cnt++] = v.potez;
			//}
		}	
		/*if (v.i[0] <0 || v.j[0] <0|| v.i[1] <0 && v.i[1] !=-1 && v.j[1] != -1 || v.j[1]<0 && v.i[1] != -1 && v.j[1] != -1 || v.i[0] >= m || v.j[0] >=n || v.i[1] >= m ||  v.j[1] >= n || !G[v.i[0] * n + v.j[0]] || !G[v.i[1] * n + v.j[1]] && v.i[1] != -1 && v.j[1] != -1) {
			cnt--;
			continue;
		}//*/
		if (v.stanje == 1 && !visit1[n * (v.i[0]) + v.j[0]] || v.stanje == 2 && (!visit2[n * (v.i[1]) + v.j[1]] || !visit2[n * (v.i[0]) + v.j[0]]) || v.stanje == 3 && (!visit3[n * (v.i[1]) + v.j[1]] || !visit3[n * (v.i[0]) + v.j[0]])) {
			if (dif < 0 && cnt >0) {
				cnt += dif;
			}
			//printf("POP:[ %d %d | %d %d ] dif = %d | cnt = %d | id = %d, %c \n", v.i[0], v.j[0], v.i[1], v.j[1], dif, cnt, id, prevs[id].potez);
			if (cnt >= 0) {
				potezi[cnt++] = v.potez;
				id++;
			}
			if(v.stanje == 1) visit1[n * (v.i[0]) + v.j[0]] = 1;
			else if (v.stanje == 2) {
				visit2[n * (v.i[0]) + v.j[0]] = 1;
				visit2[n * (v.i[1]) + v.j[1]] = 1;
			}
			else if (v.stanje == 3) {
				visit3[n * (v.i[0]) + v.j[0]] = 1;
				visit3[n * (v.i[1]) + v.j[1]] = 1;
			}
			for (tmp=G[n * (v.i[0]) + v.j[0]]; tmp; tmp = tmp->next) {
				if (v.stanje == 1) {
					if (v.i[0] == tmp->i) {
						if (v.j[0] < tmp->j) {
							u.i[0] = tmp->i;
							u.i[1] = tmp->i;
							u.j[0] = tmp->j;
							u.j[1] = tmp->j + 1;
							u.stanje = 2;
							u.potez = 'd';
						}
						else if (v.j[0] > tmp->j) {
							u.i[0] = tmp->i;
							u.i[1] = tmp->i;
							u.j[0] = tmp->j;
							u.j[1] = tmp->j - 1;
							u.stanje = 2;//horizontalno
							u.potez = 'a';
						}
					}
					else if (v.j[0] == tmp->j) {
						if (v.i[0] < tmp->i) {
							u.j[0] = tmp->j;
							u.j[1] = tmp->j;
							u.i[0] = tmp->i;
							u.i[1] = tmp->i + 1;
							u.stanje = 3;//vertikalno
							u.potez = 's';
						}
						else if (v.i[0] > tmp->i) {
							u.j[0] = tmp->j;
							u.j[1] = tmp->j;
							u.i[0] = tmp->i;
							u.i[1] = tmp->i - 1;
							u.stanje = 3;
							u.potez = 'w';
						}
					}
				}
				else if (v.stanje == 2) {
					if (v.i[0] == tmp->i) {
						u.stanje = 1;
						u.i[0] = tmp->i;
						u.i[1] = -1;
						u.j[1] = -1;
						if (v.j[0] < tmp->j) {
							if (v.j[0] < v.j[1]) {
								u.j[0] = v.j[0] + 2;
							}
							else {
								u.j[0] = v.j[0] + 1;
							}
							u.potez = 'd';
						}
						else if (v.j[0] > tmp->j) {
							if (v.j[0] < v.j[1]) {
								u.j[0] = v.j[0] - 1;
							}
							else {
								u.j[0] = v.j[0] - 2;
							}
							u.potez = 'a';
						}
					}
					else if(v.j[0] == tmp->j) {
						if (tmp->i > v.i[0]) u.potez = 's';
						else u.potez = 'w';
						u.i[0] = tmp->i;
						u.i[1] = tmp->i;
						u.j[0] = v.j[0];
						u.j[1] = v.j[1];
						u.stanje = 2;
					}
				}
				else if (v.stanje == 3) {
					if (v.j[0] == tmp->j) {
						u.stanje = 1;
						u.j[0] = tmp->j;
						u.j[1] = -1;
						u.i[1] = -1;
						if (v.i[0] < tmp->i) {
							if (v.i[0] < v.i[1]) {
								u.i[0] = v.i[0] + 2;
							}
							else {
								u.i[0] = v.i[0] + 1;
							}
							u.potez = 's';
						}
						else if (v.i[0] > tmp->i) {
							if (v.i[0] < v.i[1]) {
								u.i[0] = v.i[0] - 1;
							}
							else {
								u.i[0] = v.i[0] - 2;
							}
							u.potez = 'w';
						}
					}
					else if (v.i[0] == tmp->i) {
						if(tmp ->j > v.j[0]) u.potez = 'd';
						else u.potez = 'a';
						u.j[0] = tmp->j;
						u.j[1] = tmp->j;
						u.i[0] = v.i[0];
						u.i[1] = v.i[1];
						u.stanje = 3;
					}
				}
				if (!G[n * (u.i[0]) + u.j[0]] || (u.stanje == 2 || u.stanje == 3) && !G[n * (u.i[1]) + u.j[1]]) {
					continue;
				}
				if (u.stanje == 1 && !visit1[n * (u.i[0]) + u.j[0]] || u.stanje == 2 && (!visit2[n * (u.i[1]) + u.j[1]] || !visit2[n * (u.i[0]) + u.j[0]]) || u.stanje == 3 && (!visit3[n * (u.i[1]) + u.j[1]] || !visit3[n * (u.i[0]) + u.j[0]])) {
					level[u.stanje - 1][n * (u.i[0]) + u.j[0]] = level[v.stanje - 1][n * (v.i[0]) + v.j[0]] + 1;
					push(&top, s, 400, u);
				}
			}
		}
	}
	printf("\nHINT: ");
	if (cnt <= 0) printf("Nema resenja.");
	for (int k = 1; k < cnt;k++) {
		if (k -1) printf("->");
		if(k == glcnt+1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		printf("%c", potezi[k]);
		if(k == glcnt+1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	//*glcnt = *glcnt + 1;
}

Graf** loadGraph(Info stats,char ** map) {
	Graf** G = NULL,**tmp = NULL,*data=NULL;
	int m = stats.m;
	int n = stats.n;
	int i = 0, j = 0,cnt=0;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			tmp = realloc(G, (cnt + 1) * sizeof(Graf*));
			if (!tmp) perror(NULL), exit(1);
			else G = tmp;
			int local=0;
			Graf* last = NULL;
			G[cnt] = NULL;
			if (map[i][j] == 'o' || map[i][j] == 'S' || map[i][j] == 'T') {
				if (i >= 1) {
					if (map[i - 1][j] == 'o' || map[i-1][j] == 'S' || map[i-1][j] == 'T') {
						data = malloc(sizeof(Graf));
						data->next = NULL;
						if (last == NULL) G[cnt] = data;
						else last->next = data;
						last = data;
						data->i = i - 1;
						data->j = j;
					}
				}
				if (j >= 1) {
					if (map[i][j - 1] == 'o' || map[i][j-1] == 'S' || map[i][j-1] == 'T') {
						data = malloc(sizeof(Graf));
						data->next = NULL;
						if (last == NULL) G[cnt] = data;
						else last->next = data;
						last = data;
						data->i = i;
						data->j = j - 1;
					}
				}
				if (j < n - 1) {
					if (map[i][j + 1] == 'o' || map[i][j+1] == 'S' || map[i][j+1] == 'T') {
						data = malloc(sizeof(Graf));
						data->next = NULL;
						if (last == NULL) G[cnt] = data;
						else last->next = data;
						last = data;
						data->i = i;
						data->j = j + 1;
					}
				}
				if (i < m - 1) {
					if (map[i + 1][j] == 'o' || map[i+1][j] == 'S' || map[i+1][j] == 'T') {
						data = malloc(sizeof(Graf));
						data->next = NULL;
						if (last == NULL) G[cnt] = data;
						else last->next = data;
						last = data;
						data->i = i + 1;
						data->j = j;
					}
				}
				//printf("%d\n", cnt);
			}
			cnt++;
		}
	}
	return G;
}

void printGraph(Graf** G, Info stats) {
	Graf* tmp;
	for (int i = 0; i < (stats.m)*(stats.n); i++) {
		tmp = G[i];
		if (tmp == NULL) printf("NULL");
		else {
			for (; tmp; tmp = tmp->next) {
				printf("%d,%d|", tmp->i, tmp->j);
			}
		}
		putchar('\n');
	}
}

char** readMap(Info* stats) {
	char** map = NULL, ** tika = NULL, * temp;
	int i = 0, j = 0;
	FILE* dat = fopen("map1a.txt", "r");
	signed char c;
	int oldj = 0;
	int end = 0;
	int cnt = 0;
	while (end == 0) {
		j = 0;
		tika = realloc(map, (i + 1) * sizeof(Graf*));
		if (!tika) perror(NULL), exit(1);
		else map = tika;
		map[i] = NULL;
		while ((c = fgetc(dat)) != '\n') {
			if (c == EOF) {
				end = 1;
				break;
			}
			else if (c == 'o' || c == '-' || c == 'S' || c == 'T') {
				temp = realloc(map[i], (j + 1) * sizeof(char));
				if (!temp) {
					perror(NULL);
					exit(1);
				}
				else map[i] = temp;
				map[i][j] = c;
			}
			else if (c != EOF) {
				printf("KARAKTER %c je INVALIDAN\n", c);
				printf("ERROR: Greska u mapi (map.txt sadrzi nedozvoljene karaktere).\n");
				end = 1;
				printf("ERROR: Ucitavanje prekinuto!\n");
				for (int k = 0; k < i; k++) free(map[k]);
				free(map);
				map = NULL;
			}
			if (c == 'S') {
				(*stats).starti = i;
				(*stats).startj = j;
			}
			if (c == 'T') {
				(*stats).endi = i;
				(*stats).endj = j;
			}
			j++;
		}
		oldj = j;
		i++;
	}
	(*stats).m = i;
	(*stats).n = oldj;
	fclose(dat);
	return map;
}

Index* createIndexArr(Info stats) {
	int cnt = 0;
	int m = stats.m;
	int n = stats.n;
	Index* arr;
	arr = malloc(m * n * sizeof(Index));
	for (int i = 0; i < stats.m; i++) {
		for (int j = 0; j < stats.n; j++) {
			arr[cnt].i = i;
			arr[cnt].j = j;
			cnt++;
		}
	}
	return arr;
}

void dodajGranu(Graf** G, Info stats, int x, int y,int x1,int y1) {
	int n = stats.n;
	int m = stats.m;
	Graf* data;
	int cnt = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (i == x && j == y) {
				data = malloc(sizeof(Graf));
				data->next = G[cnt];
				G[cnt] = data;
				data->i = x1;
				data->j = y1;
			}
			else if (i == x1 && j == y1) {
				data = malloc(sizeof(Graf));
				data->next = G[cnt];
				G[cnt] = data;
				data->i = x;
				data->j = y;
			}
			cnt++;
		}
	}
}

void addOneField(Graf * *G, char ** map, Info stats, int x, int y) {
	Graf* tmp = G[x];
	int end = 0;
	if (x >= stats.m || x < 0 || y >= stats.n || y < 0) {
		printf("ERROR: Pogresan unos.\n");
		end = 1;
	}
	if (map[x][y] == 'o') {
		printf("ERROR: Cvor vec postoji.\n");
		end = 1;
	}
	tmp = G[x];
	Graf* last = NULL;
	int cnt = 0;
	if (end == 0) {
		for (int i = 0; i < stats.m; i++) {
			for (int j = 0; j < stats.n; j++) {
				if (i == x && j == y) break;
				cnt++;
			}
		}
		if (x >= 1 && map[x-1][y] == 'o') {
			dodajGranu(G, stats, x, y, x - 1, y);
		}
		if (y >= 1 && map[x][y-1] == 'o') {
			dodajGranu(G, stats, x, y, x, y - 1);
		}
		if (x < stats.m - 1 && map[x +1][y] == 'o') {
			dodajGranu(G, stats, x, y, x + 1, y);
		}
		if (y < stats.n - 1 && map[x][y+1] == 'o') {
			dodajGranu(G, stats, x, y, x, y + 1);
		}
		map[x][y] = 'o';
		printf("SUCCESS: Uspesna izmena!\n");
	}
}
//SUTRA : ODRADI OBRISI GRANU I ODRADI REMOVE ONE ZA BRISANJE I TO JE TO 
// I ALGORITAM SMISLI NA FAKSU ZA ONO SRANJE
void obrisiGranu(Graf** G, Info stats, int x, int y, int x1, int y1) {
	int n = stats.n;
	int m = stats.m;
	Graf* last=NULL;
	Graf* tmp;
	int cnt = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (i == x && j == y) {
				for (tmp = G[cnt]; tmp->i != x1 && tmp->j != y1; tmp = tmp->next) {
					last = tmp;
				}
				if (last == NULL) G[cnt] = G[cnt]->next;
				else last->next = tmp->next;
				free(tmp);
			}
			else if (i == x1 && j == y1) {
				for (tmp = G[cnt]; tmp->i != x && tmp->j != y; tmp = tmp->next) {
					last = tmp;
				}
				if (last == NULL) G[cnt] = G[cnt]->next;
				else last->next = tmp->next;
				free(tmp);
			}
			cnt++;
		}
	}
}

void removeOneField(Graf** G, char** map, Info stats, int x, int y) {
	Graf* tmp = G[x];
	int end = 0;
	if (x >= stats.m || x < 0 || y >= stats.n || y < 0) {
		printf("ERROR: Pogresan unos.\n");
		end = 1;
	}
	if (map[x][y] == '-') {
		printf("ERROR: Cvor ne postoji.\n");
		end = 1;
	}
	tmp = G[x];
	Graf* last = NULL;
	int cnt = 0;
	if (end == 0) {
		for (int i = 0; i < stats.m; i++) {
			for (int j = 0; j < stats.n; j++) {
				if (i == x && j == y) break;
				cnt++;
			}
		}
		if (x >= 1 && map[x - 1][y] == 'o') {
			obrisiGranu(G, stats, x, y, x - 1, y);
		}
		if (y >= 1 && map[x][y - 1] == 'o') {
			obrisiGranu(G, stats, x, y, x, y - 1);
		}
		if (x < stats.m - 1 && map[x + 1][y] == 'o') {
			obrisiGranu(G, stats, x, y, x + 1, y);
		}
		if (y < stats.n - 1 && map[x][y + 1] == 'o') {
			obrisiGranu(G, stats, x, y, x, y + 1);
		}
		map[x][y] = '-';
		printf("SUCCESS: Uspesna izmena!\n");
	}
}



void printMap(char ** map, Info stats) {
	//printf("DIM = %d %d\n", stats.m, stats.n);
	for (int i = 0; i < stats.m; i++) {
		for (int j = 0; j < stats.n; j++) {
			putchar(map[i][j]);
		}
		putchar('\n');
	}
}

void printMapPlaying(char * *G, Info stats, int x1, int y1, int x2, int y2) {
	//printf("DIM = %d %d\n", stats.m, stats.n);
	for (int i = 0; i < stats.m; i++) {
		printf("\r");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
		for (int j = 0; j < stats.n; j++) {
			if (i == x1 && j == y1 || i == x2 && j == y2) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 28);
				putchar('x');
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
			}
			else if (stats.endi == i && stats.endj == j) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 29);
				putchar('K');
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
			}
			else putchar(G[i][j]);
			//reset();
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		putchar('\n');
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}


int main(int argc, char* argv[]) {
	///////////////PROMENLJIVE//////////////////
	Index* indeks;
	char** map = NULL;
	menu meni = GLAVNI;
	int glopcija, opcija;
	Graf** G = NULL;
	Info stats;
	int nazad = 0;
	Stanje player;
	int izgubio = 0, pobeda = 0;
	int brkoraka = 0;
	int glcnt = 0;
	//char potezi[100];
	////////////////////////////////////////////
	while (meni != KRAJ) {
		if (meni == GLAVNI) {
			clean();
			printf("----------------[BLOXORZ]----------------\n");
			printf("1) Kreiraj mapu\n");
			printf("2) Igraj\n");
			printf("0) IZLAZ\n");
			printf("-----------------------------------------\n");
			scanf("%d", &glopcija);
			clean();
			if (glopcija == 1) {
				meni = MENI1;
			}
			else if (glopcija == 2) {
				meni = IGRA;
			}
			else if (glopcija == 0) {
				printf("Da li ste sigurni da zelite da izadjete?\n");
				printf("1) Da.\n");
				printf("2) Ne.\n");
				printf("Izbor: ");
				int mini;
				scanf("%d", &mini);
				if (mini == 1) {
					break;
				}
				else if (mini == 2) {
					continue;
				}
			}
			else {
				printf("ERROR: Pogresan unos!\n");
			}
		}
		else if (meni == MENI1) {
			clean();
			printf("-------------[KREIRANJE MAPE]-------------\n");
			printf("1) Ucitaj mapu iz fajla [map.txt]\n");
			printf("2) Dodaj plocu na poziciju\n");
			printf("3) Ukloni plocu sa pozicije\n");
			printf("4) Pregled mape\n");
			printf("0) NAZAD\n");
			printf("------------------------------------------\n");
			printf("Izbor :");
			scanf("%d", &opcija);
			clean();
			if (opcija == 1) {
				clean();
				if (!map) {
					map = readMap(&stats);
					G = loadGraph(stats, map);
					//printGraph(G, stats);
					indeks = createIndexArr(stats);
					printf("[PREGLED MAPE]\n");
					printMap(map, stats);
					printf("SUCCESS: Uspesno ucitavanje!\n");
				}
				else printf("ERROR: Mapa vec ucitana.");
				while (nazad != 1) {
					printf("\n1) Nazad\nIzbor:");
					scanf("%d", &nazad);
				}
				nazad = 0;
				meni = MENI1;
			}
			else if (opcija == 2) {
				clean();
				int x = 0, y = 0;
				printf("[DODAVANJE POLJA]\n");
				printMap(map, stats);
				printf("Unesite polje koje zelite da dodate\n");
				printf("Format( i j ) = ");
				scanf("%d %d", &x, &y);
				addOneField(G, map,stats, x, y);
				//printList(G, stats);
				while (nazad != 1) {
					printf("\n1) Nazad\nIzbor:");
					scanf("%d", &nazad);
				}
				nazad = 0;
				meni = MENI1;
			}
			else if (opcija == 3) {
				clean();
				int x = 0, y = 0;
				printf("[BRISANJE POLJA]\n");
				printMap(map, stats);
				printf("Unesite polje koje zelite da obrisete\n");
				printf("Format( i j ) = ");
				scanf("%d %d", &x, &y);
				removeOneField(G,map, stats, x, y);
				while (nazad != 1) {
					printf("\n1) Nazad\nIzbor:");
					scanf("%d", &nazad);
				}
				nazad = 0;
				meni = MENI1;
			}
			else if (opcija == 4) {
				clean();
				if (!map) printf("ERROR: Mapa nije ucitana.\n");
				else {
					printf("[PREGLED MAPE]\n");
					printMap(map, stats);
				}
				while (nazad != 1) {
					printf("\n1) Nazad\nIzbor:");
					scanf("%d", &nazad);
				}
				nazad = 0;
				meni = MENI1;
			}
			else if (opcija == 0) {
				meni = GLAVNI;
			}
		}
		else if (meni == IGRA) {
			//int izgubio = 0;
			glcnt = 0;
			if (!G) {
				clean();
				meni = GLAVNI;
				printf("ERROR: Mapa nije ucitana.\n");
				while (nazad != 1) {
					printf("\n1) Nazad\nIzbor:");
					scanf("%d", &nazad);
				}
				nazad = 0;
			}
			else {
				clean();
				int nepoznat = 0;
				//char *potezi;
				//DFS(G, stats);
				int hint = 0;
				char potez = -1;
				//for (int k = 0; k < stats.m * stats.n; k++) printf("%c -> ", potezi[k]);
				if (pobeda == 1) {
					printf("[POBEDA]\nCestitamo, uspeli ste da predjete ovaj nivo!!!\n Broj koraka: %d\n", brkoraka);
					izgubio = 0;
					pobeda = 0;
					printf("1) Nazad u meni.\n2) Probaj opet.\n");
					while (izgubio != 1 && izgubio != 2) {
						printf("Izbor: ");
						scanf("%d", &izgubio);
					}
					if (izgubio == 1) meni = GLAVNI, izgubio = 0,pobeda = 0;
					else if (izgubio == 2) meni = IGRA, izgubio = 0,pobeda = 0;
				}
				else if (potez == 0 || izgubio == 1) {
					clean();
					printf("[PORAZ]\n");
					izgubio = 0;
					printf("1) Nazad u meni.\n2) Probaj opet.\n");
					while (izgubio != 1 && izgubio != 2) {
						printf("Izbor: ");
						scanf("%d", &izgubio);
					}
					if (izgubio == 1) meni = GLAVNI, izgubio = 0,pobeda =0;
					else if (izgubio == 2) meni = IGRA, izgubio = 0,pobeda = 0;
				}
				else if (izgubio == 0) {
					brkoraka = 0;
					player.i[0] = stats.starti;
					player.j[0] = stats.startj;
					player.i[1] = -1;
					player.j[1] = -1;
					potez = 'a';
					player.stanje = 1;
					while (potez != 0 && pobeda != 1 && izgubio != 1) {
						if (nepoznat == 0) {
							clean();
							printf("[IGRA]\n");
							printMapPlaying(map, stats, player.i[0], player.j[0], player.i[1], player.j[1]);
							printf("Broj koraka: %d\nk) Predaj se.\nw,a,s,d) Pomeranje\nh) Hint toggle\n\n", brkoraka);
							if (hint == 1) {
								DFS(G, stats, glcnt++);
							}
							printf("\nPotez: ");
						}
						else nepoznat = 0;
						scanf("%c", &potez);
						if (potez == 'w' || potez == 'W') {
							brkoraka++;
							if (player.stanje == 1) {
								player.i[1] = player.i[0] - 2;
								player.j[1] = player.j[0];
								player.j[0] = player.j[0];
								player.i[0] = player.i[0] - 1;
								player.stanje = 2;
							}
							else if (player.stanje == 2) {
								if (player.i[0] == player.i[1]) {
									player.i[1] = player.i[1] - 1;
									player.j[1] = player.j[1];
									player.j[0] = player.j[0];
									player.i[0] = player.i[0] - 1;
									player.stanje = 2;
								}
								else if (player.j[0] == player.j[1]) {
									if (player.i[0] > player.i[1]) {
										player.i[0] = player.i[0] - 2;
									}
									else {
										player.i[0] = player.i[1] - 2;
									}
									player.i[1] = -1;
									player.j[1] = -1;
									player.j[0] = player.j[0];
									player.stanje = 1;
								}
							}
						}
						else if (potez == 'a' || potez == 'A') {
							brkoraka++;
							if (player.stanje == 1) {
								player.i[1] = player.i[0];
								player.j[1] = player.j[0] - 2;
								player.j[0] = player.j[0] - 1;
								player.i[0] = player.i[0];
								player.stanje = 2;
							}
							else if (player.stanje == 2) {
								if (player.i[0] == player.i[1]) {
									if (player.j[0] > player.j[1]) {
										player.j[0] = player.j[0] - 2;
									}
									else {
										player.j[0] = player.j[1] - 2;
									}
									player.i[1] = -1;
									player.j[1] = -1;
									player.i[0] = player.i[0];
									player.stanje = 1;
								}
								else if (player.j[0] == player.j[1]) {
									player.i[1] = player.i[1];
									player.j[1] = player.j[1] - 1;
									player.j[0] = player.j[0] - 1;
									player.i[0] = player.i[0];
									player.stanje = 2;
								}
							}
						}
						else if (potez == 's' || potez == 'S') {
							brkoraka++;
							if (player.stanje == 1) {
								player.i[1] = player.i[0] + 2;
								player.j[1] = player.j[0];
								player.j[0] = player.j[0];
								player.i[0] = player.i[0] + 1;
								player.stanje = 2;
							}
							else if (player.stanje == 2) {
								if (player.i[0] == player.i[1]) {
									player.i[1] = player.i[1] + 1;
									player.j[1] = player.j[1];
									player.j[0] = player.j[0];
									player.i[0] = player.i[0] + 1;
									player.stanje = 2;
								}
								else if (player.j[0] == player.j[1]) {
									if (player.i[0] < player.i[1]) {
										player.i[0] = player.i[0] + 2;
									}
									else {
										player.i[0] = player.i[1] + 2;
									}
									player.i[1] = -1;
									player.j[1] = -1;
									player.j[0] = player.j[0];
									player.stanje = 1;
								}
							}
						}
						else if (potez == 'd' || potez == 'D') {
							brkoraka++;
							if (player.stanje == 1) {
								player.i[1] = player.i[0];
								player.j[1] = player.j[0] + 2;
								player.j[0] = player.j[0] + 1;
								player.i[0] = player.i[0];
								player.stanje = 2;
							}
							else if (player.stanje == 2) {
								if (player.i[0] == player.i[1]) {
									if (player.j[0] < player.j[1]) {
										player.j[0] = player.j[0] + 2;;
									}
									else {
										player.j[0] = player.j[1] + 2;;
									}
									player.i[1] = -1;
									player.j[1] = -1;
									player.i[0] = player.i[0];
									player.stanje = 1;
								}
								else if (player.j[0] == player.j[1]) {
									player.i[1] = player.i[1];
									player.j[1] = player.j[1] + 1;
									player.j[0] = player.j[0] + 1;
									player.i[0] = player.i[0];
									player.stanje = 2;
								}
							}
						}
						else if (potez == 'k') {
							meni = IGRA;
							potez = 0;
							izgubio = 1;
							break;
						}
						else if (potez == 'h') {
							if (hint == 0)hint = 1;
							else hint = 0;
						}
						else {
							//printf("ERROR: Nepoznat potez\n");
							nepoznat = 1;
						}
						if (G[player.i[0] * (stats.n) + player.j[0]] == NULL || player.i[1] != -1 && player.j[1] != -1 && G[player.i[1]*(stats.n)+player.j[1]] == NULL) {
							izgubio = 1, potez = 0;
						}
						else if (player.i[0] == stats.endi && player.j[0] == stats.endj && player.i[1] == -1 && player.j[1] == -1) {
							pobeda = 1;
							potez = 0;
						}
					}
				}
			}
		}
	}
	return 0;
}