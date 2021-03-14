//Adicionar bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

//MACROS
#define TAMA 12 // tamanho do tabuleio mais 2
#define VIDA 3 // quantidades de vidas iniciais
#define RECURSION_TIME 400 //tempo dado em milisegundos de mostra a recursão da função deixaVisivelRep

int getQuadradosLivres(int flag[][TAMA], char matriz[][TAMA]);

void zerarMatrizVisivel(int flag[][TAMA])
{
    int i,j;
    for(i = 0; i < TAMA; i++)
    {
        for(j = 0; j < TAMA; j++)
        {
            flag[i][j] = 0;
        }
    }
}

//Função Menu decide se vai cria um novo jogo ou carrega um save
void hacker(char matriz[][TAMA])
{
    int i,j;

    printf("\n\n\n\n");
    for(i = 1; i < (TAMA - 1); i++)
    {
        printf("\t");
        for(j = 1; j < (TAMA - 1); j++)
        {
            printf("\t%c",matriz[i][j] );
        }
        printf("\n\n");
    }
}

void menuArquivo(int* novo_jogo,int *vidas, int flag[][TAMA], char matriz[][TAMA])
{
    int num;
    char caminho[400];
    int i, j;
    int opcao;
    int life = *vidas;
    int visivel;

    printf("1 - para comeca um Novo Jogo\n");
    printf("2 - para comeca um Carreagar um tabuleiro: ");
    scanf("%d",&num);
    fflush(stdin);

    switch(num)
    {
    case 1:
        *novo_jogo = 1;
        break;
    case 2:
        {
            FILE * arq = fopen("savegame.txt", "r");

            if(arq != NULL)
            {
                fscanf(arq,"%d",&life);
                *vidas = life;
                fflush(stdin);
                while(fscanf(arq,"%d %d %d %d", &i, &j, &opcao, &visivel) != EOF)
                {
                    i++;
                    j++;
                    flag[i][j] = visivel;
                    if(opcao == 2)
                    {
                        matriz[i][j] = 'T';
                    }
                    else if(opcao == 1)
                    {
                        matriz[i][j] = 'B';
                    }
                    else
                    {
                        matriz[i][j] = '0';
                    }
                }
                *novo_jogo = 0;
                system("pause");
            }
            else
            {
                printf("\nErro ao abrir o arquivo\n");
                *novo_jogo = 1;
            }
            fclose(arq);
            break;
        }

    default:
        break;
    }
}

void salve_game(int* vidas, int flag[][TAMA], char matriz[][TAMA])
{
    FILE * arq = fopen("savegame.txt", "w");
    int i, j,opcao3;

    fprintf(arq, "%d\n",*vidas);
    for(i = 1; i < (TAMA - 1); i++)
    {
        for(j = 1; j < (TAMA - 1); j++)
        {
            if(matriz[i][j] == 'B')
            {
                opcao3 = 1;
            }
            else if(matriz[i][j] == 'T')
            {
                opcao3 = 2;
            }
            else
            {
                opcao3 = 0;
            }
            int aux = flag[i][j];
            fprintf(arq, "%d %d %d %d\n",(i-1), (j-1), opcao3, aux);
        }
    }
    fclose(arq);
}

void zeramatrizI(char matriz[][TAMA])
{
    int i,j;
    for(i=0; i < TAMA; i++)
    {
        for(j=0; j < TAMA; j++)
        {
            matriz[i][j] = 48;
        }
    }
}
//função de Dificuldade
void dificuldade(int* bomb)
{
    int dif;

    printf("\tDificuldade:\n\n");

    printf("\tPara FACIL digite 1\n");
    printf("\tPara MEDIO digite 2\n");
    printf("\tPara DIFICIL digite 3\n");
    printf("\t\nEscolha sua dificuldade: ");
    scanf("%d",&dif);
    fflush(stdin);

    switch(dif)
    {
    case 1:
        *bomb = (TAMA - 2)*(TAMA - 2)*0.25;
        break;
    case 2:
        *bomb = (TAMA - 2)*(TAMA - 2)*0.50;
        break;
    case 3:
        *bomb = (TAMA - 2)*(TAMA - 2)*0.75;
        break;
    default:
        *bomb = 75;
        printf("Numero INVALIDO!!!\n");
        printf("A dificuldade selecionada sera DIFICIL!\n");
    }
}


void colocar_bombas(int bomba, char matriz[][TAMA])
{
    int i,j;

    srand(time(NULL));
    while(bomba != 0)
    {
        i = 1 + rand()%(TAMA - 2);
        j = 1 + rand()%(TAMA - 2);
        if(matriz[i][j] != 'B')
        {
            matriz[i][j] = 'B';
            bomba -= 1;
        }
    }
}

void conta_Bombas_adjacente(char matriz[][TAMA])
{
    int i,j;
    for(i = 1; i< (TAMA - 1); i++)
    {
        for(j = 0; j <(TAMA -1); j++)
        {
            if(matriz[i][j] != 'B' && matriz[i][j] != 'T')
            {
                if(matriz[i-1][j-1] == 'B' || matriz[i-1][j-1] == 'T')
                {
                    matriz[i][j] += 1;
                }
                if(matriz[i-1][j] == 'B' || matriz[i-1][j] == 'T')
                {
                    matriz[i][j] += 1;
                }
                if(matriz[i-1][j+1] == 'B' || matriz[i-1][j+1] == 'T')
                {
                    matriz[i][j] += 1;
                }
                if(matriz[i][j+1] == 'B' || matriz[i][j+1] == 'T')
                {
                    matriz[i][j] += 1;
                }
                if(matriz[i+1][j+1] == 'B' || matriz[i+1][j+1] == 'T')
                {
                    matriz[i][j] += 1;
                }
                if(matriz[i+1][j] == 'B' || matriz[i+1][j] == 'T')
                {
                    matriz[i][j] += 1;
                }
                if(matriz[i+1][j-1] == 'B' || matriz[i+1][j-1] == 'T')
                {
                    matriz[i][j] += 1;
                }
                if(matriz[i][j-1] == 'B' || matriz[i][j-1] == 'T')
                {
                    matriz[i][j] += 1;
                }
            }
        }
    }
}

void printTabuleiro(int* vidas, int* livre, int flag[][TAMA], char matriz[][TAMA])
{
    int i,j;
    char bandeira01 = 'A';
    char bandeira02 = 'A';

    printf("\nQuantidade de Vidas: %d\n",*vidas);
    printf("Quantidades de Quadrados Livres de Bombas: %d",*livre);


    printf("\n\n\t\t\t\t\tTABULEIRO DO CAMPO MINADO: \n\n\n");

    for(i=0; i < (TAMA - 1); i++)
    {
        for(j=0; j < (TAMA - 1); j++)
        {
            if((i != 0) && (j != 0))
            {
                if(flag[i][j])
                {
                    printf("\t%c", matriz[i][j]);
                }
                else
                {
                    printf("\t*");
                }
            }
            else if((i == 0) && (j != 0))
            {
                printf("\t%c",bandeira01);
                bandeira01 += 1;
            }
            else if((j == 0) && (i != 0))
            {
                printf("\t%c",bandeira02);
                bandeira02 += 1;
            }
            else
            {
                printf("\t ");
            }

        }
        printf("\n\n");
    }
}

void deixaVisivel(int x, int y, int flag[][TAMA])
{
    flag[y][x] = 1;
}


void deixaVisivelRep(int x,int y, int flag[][TAMA], char matriz[][TAMA])
{
    if( (x > 0) && (x < (TAMA - 1)) && (y > 0) && (y < (TAMA - 1)) )//VERIFICAR SE A POSIÇÃO EH VALIDA
    {
        if(matriz[y][x] != 'B')
        {
            flag[y][x] = 1;
            int aux = 3, q = 75;
            system("cls");
            printTabuleiro(&aux, &q, flag, matriz);
            printf("\n%d %d\n", x, y);
            Sleep(RECURSION_TIME);
            if(matriz[y][x] == '0')// SE FOR ZERO O CONTEUDO EU CHAMO A RECURSIVIDADE
            {
                if(!(flag[y][x + 1]))//se não estiver visivel eu chamo a recursividade
                {
                    deixaVisivelRep(x + 1, y, flag, matriz);
                }
                if(!(flag[y][x - 1]))
                {
                    deixaVisivelRep(x - 1, y, flag, matriz);
                }
                if(!(flag[y - 1][x]))
                {
                    deixaVisivelRep(x, y - 1, flag, matriz);
                }
                if(!(flag[y + 1][x]))
                {
                    deixaVisivelRep(x, y + 1, flag, matriz);
                }
                //diagonais
                if(!(flag[y - 1][x - 1]))//se não estiver visivel eu chamo a recursividade
                {
                    deixaVisivelRep(x - 1, y - 1, flag, matriz);
                }
                if(!(flag[y - 1][x + 1]))
                {
                    deixaVisivelRep(x + 1, y - 1, flag, matriz);
                }
                if(!(flag[y + 1][x - 1]))
                {
                    deixaVisivelRep(x - 1, y + 1, flag, matriz);
                }
                if(!(flag[y + 1][x + 1]))
                {
                    deixaVisivelRep(x + 1, y + 1, flag, matriz);
                }
            }
        }
    }
}

void zeraPerimetroDaMatrizFlag(int flag[][TAMA])
{
    int i;

    for(i = 0; i < TAMA; i++)
    {
        flag[0][i] = 0;
        flag[TAMA - 1][i] = 0;
        flag[i][0] = 0;
        flag[i][TAMA - 1] = 0;
    }
}

void deixaTudoVisivel(int flag[][TAMA])
{
    int i,j;

    for(i = 1; i < (TAMA - 1); i++)
    {
        for(j = 1; j < (TAMA - 1); j++)
        {
            flag[i][j] = 1;
        }
    }
}

void selecionarCoordenadas(int *vidas, int* bonus, int* livres, int*x, int*y, int* bandeira, int flag[][TAMA], char matriz[][TAMA])
{
    char linha,coluna,flagA = 0;

    do
    {
        if(flagA == 1)
        {
            printf("\n\n\tCOORDENADA INVALIDA!!!\n");
        }
        printf("\tSelecione a linha: ");
        scanf("%c",&linha);
        fflush(stdin);

        printf("\tSelecione a coluna: ");
        scanf("%c",&coluna);
        fflush(stdin);

        flagA = 1;

    }while((linha < 'A') || (linha > 'J') || (coluna < 'A') || (coluna > 'J') || flag[linha][coluna] == 1);

    *x = (int)coluna - 64;
    *y = (int)linha - 64;

    if(*bandeira) // bandeira pra ver se é a primeira jogada
    {
        if(matriz[*y][*x] == 'B')
        {
            *vidas -= 1;
            *bonus = 0;
        }
        else
        {
            *bonus += 1;
            *livres -= 1;
        }
    }
    else
    {
        if(matriz[*y][*x] != 'B')
        {
            *livres -= 1;
            *bandeira = 1;
        }
        else if(matriz[*y][*x] == 'B')
        {
            matriz[*y][*x] = 'T';
        }
    }
}

void bonusBandeira(int* bonus, int flag[][TAMA], char matriz[][TAMA])
{
    int i,j;
    int achou = 0;//achou uma bomba aleatoria pra colocar uma bandeira no jogo

    if(*bonus == 5)
    {
        srand(time(NULL));
        while(achou != 3)
        {
            i = 1 + rand()%10;
            j = 1 + rand()%10;
            if( matriz[i][j] == 'B' && !(flag[i][j]) )
            {
                matriz[i][j] = 'T';//T será a Bandeira
                flag[i][j] = 1;
                achou++ ;
            }
        }
    }
}

int getQuadradosLivres(int flag[][TAMA], char matriz[][TAMA]) {
    int i,j, soma = 0;
    for(i = 1; i < (TAMA - 1); i++) {
        for(j = 1; j < (TAMA - 1); j++) {
            if(flag[i][j]) {
                if(matriz[i][j] != 'B' || matriz[i][j] != 'T') {
                    soma++;
                }
            }
        }
    }
    return soma;
}

int main()
{
    char matriz[TAMA][TAMA];
    int flag[TAMA][TAMA] = {0};
    int vidas = VIDA;
    int bonus = 0;
    int quadrados_livres = (TAMA - 2)*(TAMA - 2);
    int bombs,new_game = 0,i,j;
    int primeira_jogada = 0;
    int x,y;

    //tamanho do jogo

    system("MODE con cols=150 lines=60");
    system("title Tela Full Screen");

    zeramatrizI(matriz);
    menuArquivo(&new_game,&vidas, flag, matriz);

    //Funções de Inicialização do Jogo
    if(new_game)
    {
        dificuldade(&bombs);
        colocar_bombas(bombs, matriz);
        quadrados_livres = quadrados_livres - bombs;
        zerarMatrizVisivel(flag);
        conta_Bombas_adjacente(matriz);
    }
    else
    {
        for(i=1;i<(TAMA - 1);i++)
        {
            for(j=0;j<(TAMA - 1);j++)
            {
                if(matriz[i][j] != 'B' && matriz[i][j] != 'T' && flag[i][j])
                {
                    quadrados_livres--;
                }
            }
        }
    }

    //Funções de Dinamica do Jogo
    zeraPerimetroDaMatrizFlag(flag);
    while(vidas && quadrados_livres)
    {
        printTabuleiro(&vidas,&quadrados_livres, flag, matriz);
        //hacker(matriz);
        selecionarCoordenadas(&vidas,&bonus,&quadrados_livres,&x,&y,&primeira_jogada, flag, matriz);
        bonusBandeira(&bonus, flag, matriz);
        deixaVisivel(x,y, flag);
        deixaVisivelRep(x, y, flag, matriz);
        //zeraPerimetroDaMatrizFlag();
        salve_game(&vidas, flag, matriz);

        system("cls");
    }
    system("cls");
    deixaTudoVisivel(flag);
    printTabuleiro(&vidas,&quadrados_livres, flag, matriz);
    if(vidas > 0)
    {
        printf("\n\n\n\t\t\t YOU WIN!!!!\n\n\n");
        salve_game(&vidas, flag, matriz);
    }
    else
    {
        printf("\n\n\n\t\t\t\tLOSER!!!!!\n\n\n\n\n");
        salve_game(&vidas, flag, matriz);
    }
}
