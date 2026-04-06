#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include <termios.h>
#include <semaphore.h>

using namespace std;

sem_t mutex;

//dimensions of board game
const int length = 20;
const int height = 10;

//game board 2d array
char tab[height][length];

//points game
int pontos = 1;
//max points game
int max_p = length * height;

//movement operations
int dir[] = {0,1};
int esq[] = {0,-1};
int up[] = {-1,0};
int down[] = {1,0};

//control end game
bool game_end = false;

//movement direction
int mov[] = {0,0};

//Snake
vector <pair<int, int>> s;

//function read char input without needing to press enter
char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

//verify snake position
int check(pair<int,int> pos){
  if(pos.first >= height || pos.first < 0 || pos.second >= length || pos.second < 0 ){
    return 0;
  }

  if(tab[pos.first][pos.second] == '#'){
    return 0;
  }

  return 1;
}

//generate random food in game board
void comida(){
  int e1;
  int e2;
  do{
    e1 = rand()%height;
    e2 = rand()%length;

    if(tab[e1][e2] != '#' && tab[e1][e2] != 'c'){
      break;
    }

  }while(true);
  tab[e1][e2] = 'c';

}

//change movement direction pattern snake
void next_pos(char e){
  if(e == 'w'){
    if(mov[0] !=  1)  memcpy(mov, up, sizeof mov);
  }else if(e == 's'){
    if(mov[0] !=  -1) memcpy(mov, down, sizeof mov);
  }else if(e == 'a'){
    if(mov[1] !=  1)  memcpy(mov, esq, sizeof mov);
  }else if(e == 'd'){
    if(mov[1] !=  -1)  memcpy(mov, dir, sizeof mov);
  }
}

//change snake position in game board 
int move(){
  pair<int,int> next_pos = make_pair(s[0].first+mov[0], s[0].second+mov[1]);

  if(!check(next_pos)){
    return -1;
  }

  pair<int,int> aux = s.back();

  s.insert(s.begin(), next_pos);

  if(tab[next_pos.first][next_pos.second] != 'c'){
    tab[aux.first][aux.second] = ' ';
    s.pop_back();
  }else{
    pontos++;
    if(pontos == max_p){
      game_end = true;
    }
    comida();
  }

  tab[next_pos.first][next_pos.second] = '#';
  return 1;
}

//impress the game board
void imprimir(){
  cout << '|';
  for(int j = 0; j < length; j++){
    cout << '-';
  }
  cout << "|" << endl;
  for(int i = 0; i < height; i++){
    cout << '|';
    for(int j = 0; j < length; j++){
      cout << tab[i][j];
    }
    cout <<'|'<< endl;
  }
  cout << '|';
  for(int j = 0; j < length; j++){
    cout << '-';
  }
  cout << "|" << endl;
}

//initialize game-board, variables...
void start(){
  sem_init(&mutex, 0, 1);

  system("clear");

  memset(tab,' ', sizeof tab);

  tab[int(height/2)][int(length/2)] = '#';

  s.insert(s.begin(), make_pair(int(height/2),int(length/2)));

  char read;
  cout << "Digite (W A S D) + ENTER, para começar\n";

  imprimir();
  //Initial direction of snake
  read = getchar();
  next_pos(read);

  comida();
}

//Read direction and set it
void *read(void *ptr){
  char read;
  while(!game_end){
    usleep(150000);
    read = getch();
		sem_wait(&mutex);
    next_pos(read);
		sem_post(&mutex);
  }
  pthread_exit(NULL);
}

//Movement function snake
void *movimenta(void *ptr){
  while(!game_end){
    usleep(150000);
		sem_wait(&mutex);
	  if(move() == -1){
      game_end = true;
    } 
		sem_post(&mutex);
  }
  pthread_exit(NULL);
}

//loop impress game board
void *imprime(void *ptr){
  while(!game_end){
    system("clear");
    imprimir();
    usleep(100000);
  }
  pthread_exit(NULL);
}

pthread_t t1;
pthread_t t2;
pthread_t t3;

int main(){
  start();
  pthread_create(&t1, NULL, read, NULL);
  pthread_create(&t2, NULL, movimenta, NULL);
  pthread_create(&t3, NULL, imprime, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);

  system("clear");
  cout << "PONTOS: " << pontos << endl;
  if(pontos == max_p){
    cout << "Vitória" << endl;
  }else{
    cout << "Derrota" << endl;
  }

  return 0;
}
