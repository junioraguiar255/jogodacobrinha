#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 20; //blocos
const int height = 20; //blocos
int x, y, fruitX, fruitY,score; //posição
int tailX[100],tailY[100]; //coordenadas da cauda
int nTail; //cumprimento da cauda
enum eDirecton{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;

void Setup() //configuração inicial
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw(){ //desenho da tela
    system("cls");
    for(int i = 0; i < width+2; i++)
        cout<<"#";
    cout << endl;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j<width;j++)
        {
            if(j==0)
                cout << "#";
            if(i == y && j == x)
                cout<< "0";
            else if(i == fruitY && j == fruitX)
                cout<<"F";
            else{
                bool print = false;
                                for (int k = 0; k < nTail; k++)
                                {
                                    if (tailX[k] == j && tailY[k] == i)
                                    {
                                        cout << "o";
                                        print = true;
                                    }
                                }
                                if (!print)
                                    cout << " ";
            }

            if(j == width - 1)
                cout <<"#";
        }
        cout << endl;
    }

    for (int i = 0; i<width+2;i++)
        cout<<"#";
    cout << endl;
    cout << "Score: "<< score << endl;
}

void Input(){ //teclas minusculas
    if(_kbhit()){
        switch(_getch()){
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }

}

void Logic(){ // a logica do movimento

    int prevX = tailX[0]; //coordenada anterior
    int prevY = tailY[0];
    int prev2X, prev2Y;
        tailX[0] = x; //coordenadas da tela
        tailY[0] = y;
        for (int i = 1; i < nTail; i++)
        {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    //if (x > width || x < 0 || y > height || y < 0)//se encostar na parede
        //  gameOver = true;
        if (x >= width) x = 0; else if (x < 0) x = width - 1;
        if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++) // se pegar na cauda
          if (tailX[i] == x && tailY[i] == y)
              gameOver = true;

    if(x == fruitX && y == fruitY){ // se comermos a fruta

        score+=10; // aumentamos o tamanho
    fruitX = rand() % width; // fruta vai para outra coordenada
    fruitY = rand() % height;
    nTail++; //aumentando a cauda
    }
}

int main(){

    Setup();

    while(!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(10); //processo suspenso por um determinado tempo
    }
    return 0;
}
