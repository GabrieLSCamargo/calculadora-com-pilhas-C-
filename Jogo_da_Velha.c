// GABRIEL LUCAS DA SILVA CAMARGO

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "tela.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

// struct das coordenadas de um ponto
typedef struct 
{
  float x;
  float y;
} ponto;

//struct que gaurda dois pontos de um quadrado ou retângulo
typedef struct
{
  ponto cse; // canto superior esquerdo 
  ponto cid; // canto inferior direito
} quadrado;

//struct de um círculo
typedef struct 
{
  ponto meio; // ponto central
  float raio; // raio do círculo
}circulo;

// struct para conferir as casas do tabuleiro
typedef struct 
{
  int lin;
  int col;
}casa_tab;

// função para desenhar mouse
void mouse()
{
  circulo mouse ={{tela_rato_x(), tela_rato_y()} , {7}};
  tela_circulo(mouse.meio.x, mouse.meio.y, mouse.raio, 2, preto, preto);
}

// função para conferir vitória
bool vitoria (char tab[3][3])
{

  for(int i=0; i<3; i++){  // confere as possibilidades de vitória vertical
    if(tab[i][0] == tab[i][1] && tab[i][0] == tab[i][2] && tab[i][0] != ' ' ) 
      return true;
  }
  for(int j=0; j<3; j++){ // confere as possibilidades de vitória horizontal
    if(tab[0][j] == tab[1][j] && tab[0][j] == tab[2][j] && tab[0][j] != ' ')
      return true;
  }
  if(tab[0][0] == tab[1][1] && tab[0][0] == tab[2][2] && tab[0][0] != ' ') // confere a diagonal principal
    return true;
  if(tab[0][2] == tab[1][1] && tab[0][2] == tab[2][0] && tab[0][2] != ' ') // confere a diagonal secundária
    return true;
  return false;
}

// função para conferir empate
bool velha(int cont, char tab[3][3])
{
  if(!vitoria(tab) && cont == 9)
    return true;
  else
    return false;
}

// função para desenhar X ou O de cores diferentes
void desenha(char tab[3][3])
{
  int co;
  char letra[1];
  for (int i=0; i<3; i++)
  {
    for (int j=0; j<3; j++)
    {
      letra[0] = tab[i][j];
      if(letra[0] == 'O')
        co = tela_cria_cor(0.1219, 0.916, 0.964); // desenha O de azul
      else if(letra[0] == 'X')
        co = tela_cria_cor(0.224, 0.704, 0); // desenha X de verde
      else
        co = transparente;
      if(i==0 && j==0)
        tela_texto(330, 180, 80, co, letra);
      else if( i==1 && j==0)
        tela_texto(450, 180, 80, co, letra);
      else if(i==2 && j==0)
        tela_texto(570, 180, 80, co, letra);
      else if(i==0 && j==1)
        tela_texto(330, 300, 80, co, letra);
      else if(i==1 && j==1)
        tela_texto(450, 300, 80, co, letra);
      else if(i==2 && j==1)
        tela_texto(570, 300, 80, co, letra);
      else if(i==0 && j==2)
        tela_texto(330, 420, 80, co, letra);
      else if(i==1 && j==2)
        tela_texto(450, 420, 80, co, letra);
      else if(i==2 && j==2)
        tela_texto(570, 420, 80, co, letra);
    }
  }
}

// troca a vez de quem joaga
void jogada_vez (char *vez)
{
  if(*vez == 'X')
    *vez = 'O';
  else
    *vez = 'X';
}

// confere se houve clique na em algum botão
bool confere_clique(quadrado q)
{
  if( tela_rato_x_clique() > q.cse.x && tela_rato_x_clique() < q.cid.x && tela_rato_y_clique() > q.cse.y && tela_rato_y_clique() < q.cid.y)
    return true;
  else  
    return false; 
}

// confere se a jogada é válida, se sim ela é realizada
bool jogada (char tab[3][3], char *vez)
{
  casa_tab casa = {{-1} , {-1}};

  for (int i=0; i<3; i++)
  {
    if(tela_rato_x_clique() > 270 + 120 * i && tela_rato_x_clique() < 270+120*(i+1))
    {
      casa.lin = i; 
      for(int j=0; j<3; j++)
      {
        if(tela_rato_y_clique() > 120 + 120 * j && tela_rato_y_clique() < 120 + 120 * (j+1))
        {
          casa.col = j; 
            if(tab[casa.lin][casa.col]==' ')
            {
              if(*vez == 'X')
                tab[casa.lin][casa.col] = 'X';
              else
                tab[casa.lin][casa.col] = 'O';
              jogada_vez(&*vez);
              return true;
            }
        }
      }
    }
  }
  return false;
}
 
 // desenha o tabuleiro
void tabuleiro (char tab[3][3], int co)
{ 
  quadrado q1 = {{0,0} , {900,600}};
  quadrado q2 = {{270,120} , {630,480}};
  tela_retangulo(q1.cse.x, q1.cse.y, q1.cid.x, q1.cid.y, 2, preto, co);
  tela_retangulo(q2.cse.x, q2.cse.y, q2.cid.x, q2.cid.y, 2, preto, branco);
  tela_linha(390, 120, 390, 480, 5, co);
  tela_linha(510, 120, 510, 480, 5, co);
  tela_linha(270, 240, 630, 240, 5, co);
  tela_linha(270, 360, 630, 360, 5, co);
  desenha(tab);
}
// retorna resutado de quem ganhou, se houve desistência ou empate
int resultado(bool flag, char vez, bool empate)
{
  if(flag){
    jogada_vez(&vez);
    if(vez == 'O')
      return 4; // se o desistênte for O retorna X como vencedor
    else if(vez == 'X')
      return 3; // se o desistênte for X retorna O como vencedor
  }
  else if(empate)
    return 0; // retorna empate
  else if(vez == 'O')
    return 2; // retorna O como vencedor
  else if(vez == 'X')
    return 1; // retorna X como vencedor
  return 5;
}

// confere se um jogador desistiu
bool desistir(int co, char *vez)
{
  quadrado des = {{30, 275} , {240, 325}};
  tela_retangulo(des.cse.x, des.cse.y, des.cid.x, des.cid.y, 2, preto, co);
  tela_texto(135, 300, 40, branco, "DESISTIR");
  if(confere_clique(des)){
    jogada_vez(&*vez);
    return true;
  }
  return false;
} 

// desenha o tabuleiro final
bool desenha_final (char tab[3][3], char vez, int cont)
{
  quadrado voltar = {{30, 275} , {240, 325}};
  if(cont == 9 ){
    tabuleiro(tab, tela_cria_cor(0.564, 0.544, 0.6));
    tela_texto(450, 60, 60, preto, "EMPATE");
  }
  else if(vez == 'X'){
    tabuleiro(tab, tela_cria_cor(0.224, 0.704, 0));
    tela_texto(450, 60, 60, preto, "O VENCEDOR É  X");
  }
  else if(vez == 'O'){
    tabuleiro(tab, tela_cria_cor(0.121, 0.916, 0.964));
    tela_texto(450, 60, 60, preto, "O VENCEDOR É  O");
  }
  tela_retangulo(voltar.cse.x, voltar.cse.y, voltar.cid.x, voltar.cid.y, 2, preto, tela_cria_cor(0.999, 0.444, 0.584));
  tela_texto(135, 300, 40, preto, "VOLTAR");
  if(tela_rato_clicado() && confere_clique(voltar))
    return true;
  else
    return false;
}

// informa o jogador da vez
void quem_joga (char vez)
{
  if(vez == 'X')
    tela_texto(450, 60, 60, preto, "VEZ DE  X");
  else
    tela_texto(450, 60, 60, preto, "VEZ DE  O");

}

// realiza uma partida
int partida(char *vez)
{
  int cont=0;
  bool fim = true, flag = false, empate = false;
  char tab[3][3] = {{' ', ' ', ' '},{' ', ' ', ' '},{' ', ' ', ' '}};

  while(fim)
  {
    tabuleiro(tab, tela_cria_cor(0.724, 0.524, 0.564));
    quem_joga(*vez);
    if(tela_rato_clicado){
      if(desistir(tela_cria_cor(0.808, 0.412, 0.008), &*vez)){
        flag = true;
        break; // caso um jogador desista encerra a repetição
      }
    }
    if(tela_rato_clicado()){
      if(jogada(tab, &*vez))
        cont++; // contador de jogadas realizadas
    }
    if(vitoria(tab)){
      jogada_vez(vez);
      break; // se houver vitória encerra a repetição
    }
    if(cont == 9){
      empate = true;
      break; // se o contador chegar a 9 encerra a repetição
    }
    mouse();
    tela_atualiza();
  }
  while (true)
  {
    if(desenha_final(tab, *vez, cont)){
      return resultado(flag, *vez, empate);
      fim = false;
      break;
    }
    mouse();
    tela_atualiza();
  }
}

// escreve o placar
void int_char(int placar[2][3], char numero[2])
{
  for(int i=0; i<2; i++)
  {
    for(int j=0; j<3; j++)
    {
      if(i==1 && j == 2)
        break;
      sprintf(numero,"%d", placar[i][j]);
      tela_texto(405+90*j , 300+120*i, 60, preto, numero);
    }
  }
}

// desenha o placar
void plac(char numero[2], int placar[2][3])
{
 int co = tela_cria_cor(0.28, 0.272, 0.716);
  quadrado q1 = {{0,0} , {900,600}};
  quadrado q2 = {{270,120} , {630,480}};
  quadrado q3 = {{360,240} , {630, 480}};
  tela_retangulo(q1.cse.x, q1.cse.y, q1.cid.x, q1.cid.y, 2, preto, co);
  tela_retangulo(q2.cse.x, q2.cse.y, q2.cid.x, q2.cid.y, 2, co, tela_cria_cor(0.6, 0.6, 0.6));
  tela_retangulo(q3.cse.x, q3.cse.y, q3.cid.x, q3.cid.y, 2, co, branco);
  tela_linha(360, 120, 360, 480, 5, co);
  tela_linha(450, 120, 450, 570, 5, co);
  tela_linha(540, 120, 540, 480, 5, co);
  tela_linha(270, 240, 630, 240, 5, co);
  tela_linha(270, 360, 630, 360, 5, co);
  tela_texto(315, 300, 60, preto, "X");
  tela_texto(315, 420, 60, preto, "O");
  tela_texto(405, 180, 60, preto, "V");
  tela_texto(495, 180, 60, preto, "D");
  tela_texto(585, 180, 60, preto, "E");
  int_char(placar, numero);

}

// desenha os botões na tela do placar
int botoes()
{
   int co = tela_cria_cor(0.28, 0.272, 0.716);
  quadrado q3 = {{270,510} , {450,570}};
  quadrado q4 = {{450,510} , {630,570}};
  tela_retangulo(q3.cse.x, q3.cse.y, q3.cid.x, q3.cid.y, 2, co, rosa);
  tela_retangulo(q4.cse.x, q4.cse.y, q4.cid.x, q4.cid.y, 2, co, verde);
  tela_texto(360, 540, 40, preto, "SAIR");
  tela_texto(540, 540, 40, preto, "JOGAR");
  if(tela_rato_clicado())
  {
    if(confere_clique(q3))
      tela_fim();
    else if(confere_clique(q4))
      return 1;
    else
      return 2;
  }
  return 0;
}

//atualiza placar
void atualiza_placar(int i, int placar[2][3])
{
  if(i == 0){
    placar[0][2] += 1;
  } else if( i == 1){
    placar[0][0] += 1;
  }else if(i == 2){
    placar[1][0] += 1;
  }else if(i ==3){
    placar[0][1] += 1;
    placar[1][0] += 1;
  }else if(i == 4)
    placar[0][0] += 1;
}

// escolhe quem começa a partida
char rodada_da_vez(bool primeira_rodada, char *vez, int i)
{
  int turno;
  if(primeira_rodada){
    turno = rand()%2;
    if(turno%2==0)
      return *vez = 'X';
    else
      return *vez = 'O';
  }else if(i==0){
    if(*vez == 'X')
      return *vez =='O';
    else
      return *vez == 'X';  
  }else if(i == 3)
      return *vez = 'O';
    else if(i == 4){
      if(*vez == 'X')
        return *vez = 'O';
      else
        return *vez ='X';
    }
  else if (i == 1){
    return *vez = 'X';
  }else{
    return *vez = 'O';
  }
}

int main()
{
  int placar [2][3]={{0,0,0},{0,0,0}}, i, play = 2;
  char vez = ' ';
  static char numero[2];
  bool primeira_rodada = true, inicio = true;
  srand(time (NULL));
  tela_inicio(900,600 , "VELHA");
  quadrado q1 = {{0,0} , {900,600}}; // quadrado fundo 
  quadrado q2 = {{375, 275} , {525, 325}}; // quadrado botão

  //desenha a tela inicial
  do{
    tela_retangulo(q1.cse.x, q1.cse.y, q1.cid.x, q1.cid.y, 2, preto, tela_cria_cor(0.28, 0.272, 0.716));
    tela_retangulo(q2.cse.x, q2.cse.y, q2.cid.x, q2.cid.y, 2, preto, vermelho);
    tela_texto(450, 300, 35, preto, "JOGAR");
    mouse();
    if(tela_rato_clicado()){
     if(confere_clique(q2))
        inicio = false;
    }
    tela_atualiza();
  }while(inicio);
  
  // tela da partida e tela do placar
  while(true)
  {
    inicio =false;
    rodada_da_vez(primeira_rodada, &vez, i);

    // repetição da partida
    while (true){
      i = partida(&vez);
      break;
    }
    primeira_rodada = false;
    atualiza_placar(i, placar);

    // repetição da tela do placar
    while(true)
    { 
      plac(numero, placar);
      play = botoes();
      if(play == 1)
        break;
      mouse();
      tela_atualiza();
    }
  }
  tela_fim();
}