#include<iostream>
#include<cmath>
using namespace std;

// Felipe Freitas Cambra, 2214496
// Guilheme Mathias Tresoldi, 2230061
// Diego Costa Pires, 2235275


//funçao para achar a melhor soluçao de todas as geraçoes, depois do primeiro laço do main
long long int melhorSolucao(char p[][33], int a, int b, int c, int d, int e, int f, long long int melhor){
    long long int solucao = 1;                          //declaraçao da soluçao
    int individuo = 0;                                  //declaraçao do individuo
    int contador = 0;
    if (p[0][0] == '0'){                                //caso individuo positivo
        for(int j = 0; j < 32; j++){
            int valor = p[0][j] - '0';                  //inicializa o valor char como numero inteiro
            individuo = individuo * 2 + valor;          //converte o individuo de binario para decimal
        }
    }if(p[0][0] == '1'){                                //caso individuo negativo
        for (int j = 0; j < 32; j++){
            int valor = p[0][j] - '1';                  //inicializa o valor char como numero inteiro
            if (p[0][j] == 0 - '1'){p[0][j] = '1';}     //corrigi a conversao de complemento de 2 para binario
            individuo = individuo * 2 + valor;          //converte o individuo de binario para decimal
        }
        individuo = individuo + 1;
    }
    //equaçao para calcular a soluçao do melhor individuo
    solucao = pow(individuo, 5) * a + pow(individuo, 4) * b + pow(individuo, 3) * c + pow(individuo, 2) * d + individuo * e + f;

    if(solucao >= 0) {                                  //caso soluçao positiva
        if(abs(solucao) < abs(melhor)){                 //compara os valores absolutos
            melhor = solucao;                           //adiciona a soluçao em melhor
        }
    }
    if(solucao < 0) {                                   //caso solucao negativa
        if (abs(solucao) > abs(melhor)){                //compara valores absolutos
            melhor = solucao;                           //adiciona a soluçao em melhor
        }
    }

    return melhor;
}


// funçao para achar a melhor soluçao de todas as geraçoes, no primeiro laço do main
long long int melhorSolucao0(char p[][33], int a, int b, int c, int d, int e, int f, long long int melhor){
    long long int solucao = 1;                          //declaraçao da soluçao
    int individuo = 0;                                  //declaraçao do individuo

    if (p[0][0] == '0'){                                //caso individuo positivo
        for(int j = 0; j < 32; j++){
            int valor = p[0][j] - '0';                  //inicializa o valor char como numero inteiro
            individuo = individuo * 2 + valor;          //converte o individuo de binario para decimal
        }
    }if(p[0][0] == '1'){                                //caso individuo negativo
        for (int j = 0; j < 32; j++){
            int valor = p[0][j] - '1';                  //inicializa o valor char como numero inteiro
            if (p[0][j] == 0 - '1'){p[0][j] = '1';}     //corrigi a conversao de complemento de 2 para binario
            individuo = individuo * 2 + valor;          //converte o individuo de binario para decimal
        }
        individuo = individuo + 1;
    }
    //equaçao para calcular a soluçao do melhor individuo
    solucao = pow(individuo, 5) * a + pow(individuo, 4) * b + pow(individuo, 3) * c + pow(individuo, 2) * d + individuo * e + f;

    if(abs(solucao) < abs(melhor)){                     //compara os valores absolutos
        melhor = solucao;                               //adiciona a soluçao em melhor
}
    return melhor;
}


//funçao para trocar um "gene" do individuo
void mutacaoPop(char p[][33], int tamanhoPop, int mutacao){
    for (int i = 0; i < tamanhoPop; i++){
        for (int j = 16; j < 32; j++){                      //mutaçao pode ocorrer apenas a partir do gene 16
            float probabilidade = (float)rand() / RAND_MAX; //chance da mutaçao ocorrer
            if (probabilidade < mutacao){
                p[i][j] = (p[i][j] == '0') ? '1' : '0';     //inverte o bit
                break;                                      //interrompe o laço, para ocorrer apenas uma mutaçao
            }
        }
    }
}


//funçao para cruzar os "genes" dos indiduos menos aptos
void cruzaPop(char p[][33], int tamanhoPop, int crossover){
    for (int i = (tamanhoPop - 1) / 2; i <= 32; i = i + 2){     //laço que percorre aproximadamente metade da populaçao
    int pontoCrossover = crossover;                             //define o ponto de crossover

    for (int j = 0; j < pontoCrossover; j++){                   //troca as metades dos "genes" entre as duas linhas
        swap(p[i][j + pontoCrossover], p[i + 1][j]);            //troca a primeira metade com a segunda metade da proxima linha
        swap(p[i + 1][j + pontoCrossover], p[i][j]);            //troca a segunda metade com a primeira da linha anterior
    }
    }
}


//funçao para criar mais individuos
void filtraPop(char p[][33], int tamanhoPop){
    srand(time(0));                                     //gera um seed aleatoria

    //cria novos individuos no lugar da metade mais distante da soluçao
    for(int i = tamanhoPop-1; i >= tamanhoPop/2; i--){
        int sinal = rand() % 2;
        int individuoDec = rand() % 501;                //armazena o numero gerado, interavalo [-500, 500]
        int indice = 31;                                //tamanho do vetor binario de cada individuo

        if (sinal == 0){
        while (individuoDec > 0 && indice >= 0){        //converte o numero decimal para binario
            int bit = individuoDec % 2;                 //pega o resto da divisao por 2 do numero
            p[i][indice] = '0' + bit;                   //atribui o valor a sua posiçao binaria
            individuoDec /= 2;                          //divide o valor decimal por 2, para continuar a conversao
            indice--;                                   //diminui a casa binaria de valor
        }
        while (indice >= 0){                            //completa com zeros ate os 32 bits
            p[i][indice] = '0';                         //atribui o valor a sua posiçao binaria
            indice--;                                   //diminui a casa binaria de valor
        }
}else{ // sinal negativo calcula complemento de 2
    while (individuoDec > 0 && indice >= 0){            //converte o numero decimal para binario
        int bit = individuoDec % 2;                     //pega o resto da divisao por 2 do numero
        if (indice == 31){bit + 1;}                     //soma um no ultimo bit, faz complemento de 2
        p[i][indice] = '1' + bit;                       //atribui o valor a sua posiçao binaria
        if(p[i][indice] == '2'){p[i][indice] = '0';}    //evita de passar do valor da base
        individuoDec /= 2;                              //divide o valor decimal por 2, para continuar a conversao
        indice--;                                       //diminui a casa binaria de valor
    }
    while (indice >= 0){                                //completa com um ate os 32 bits
        p[i][indice] = '1';                             //atribui o valor a sua posiçao binaria
        indice--;                                       //diminui a casa binaria de valor
    }
}
}
}


//funçao para avaliar cada populaçao
void avaliaPop(char p[][33], int tamanhoPop, int a,int b, int c, int d, int e, int f){
    long long int solucao[1001] = {0};                  //declaraçao do vetor das soluçoes

        // laço que calcula a soluçao de cada individuo
        for (int i = 0; i < tamanhoPop; i++){
        solucao[i] = {0};                               //reseta a soluçao a cada ciclo
        int individuo = 0;                              //reseta o valor do individuo a cada ciclo
        if(p[i][0] == '0'){                             //caso individuo positivo
        for(int j = 0; j < 32; j++){
            int valor = p[i][j] - '0';                  //inicializa o valor char como numero inteiro
            individuo = individuo * 2 + valor;          //converte o individuo de binario para decimal
        }
    }if(p[i][0] == '1'){                                //caso individuo negativo
        for (int j = 0; j < 32; j++){
            int valor = p[i][j] - '1';                  //inicializa o valor char como numero inteiro
            if (p[i][j] == 0 - '1'){p[i][j] = '1';}     //corrigi a conversao de complemento de 2 para binario
            individuo = individuo * 2 + valor;          //converte o individuo de binario para decimal
        }
        individuo = individuo + 1;
    }
    //equaçao para testar o individuo
    solucao[i] = pow(individuo, 5) * a + pow(individuo, 4) * b + pow(individuo, 3) * c + pow(individuo, 2) * d + individuo * e + f;
    }
    //laço que ordena a populaçao com base na soluçao do individuo
       for(int a = 0; a < tamanhoPop; a++){
        for(int b = a + 1; b < tamanhoPop; b++){
            for(int c = 0; c < tamanhoPop; c++){
            if(solucao[a] >= 0){                            //selciona numero positivos
                if(solucao[a] > solucao[b]){                //comparaçao entre duas soluçoes
                swap(solucao[a], solucao[b]);               //reordena da menor para a maior soluçao
                swap(p[a], p[b]);                           //reordena do melhor para o pior individuo
            }
                }else{                                      //seleciona numero negativos
                if (solucao[a] < solucao[b]){               // comparaçao entre duas soluçoes
                    swap(solucao[a], solucao[b]);           // reordena da menor para a maior soluçao
                    swap(p[a], p[b]);                       //reordena do melhor para o pior individuo
                }
            }
        }
    }
}
}


//funçao para gerar a primeira populaçao
void gerarPop(char p[][33], int tamanhoPop){
    srand(time(0));                                //sorteia um numero aleatoria

    for(int i = 0; i < tamanhoPop; i++){           //laço para adicionar os individuos na Pop.
    int sinal = rand() % 2;
    int indice = 31;                               //tamanho do vetor binario de cada individuo
    int individuoDec = rand() % 501;               //armazena o numero gerado, intervalo [-500, 500]

    if(sinal == 0){                                //sinal positivo calcula o binario do numero
     while(individuoDec >0 && indice >=0){         //converte o numero decimal para binario
        int bit = individuoDec % 2;                //pega o resto da divisao por 2 do numero
        p[i][indice] = '0' + bit;                  //atribui o valor a sua posiçao binaria
        individuoDec /= 2;                         //divide o valor decimal por 2, para continuar a conversao
        indice--;                                  //diminui a casa binaria de valor
     }
     while(indice>=0){                             //completa com zeros ate os 32 bits
         p[i][indice] = '0';                       //atribui o valor a sua posiçao binaria
         indice--;                                 //diminui a casa binaria de valor
    }
}else {//sinal negativo calcula complemento de 2
    while (individuoDec > 0 && indice >= 0){                        // converte o numero decimal para binario
        int bit = individuoDec % 2;                                 // pega o resto da divisao por 2 do numero
        if (indice == 31) { bit + 1;}                               // soma um no ultimo bit, faz complemento de 2
        p[i][indice] = '1' + bit;                                   // atribui o valor a sua posiçao binaria
        if (p[i][indice] == '2') { p[i][indice] = '0';}             // evita de passar do valor da base
        individuoDec /= 2;                                          // divide o valor decimal por 2, para continuar a conversao
        indice--;                                                   // diminui a casa binaria de valor
    }
    while (indice >= 0){                                            // completa com um ate os 32 bits
        p[i][indice] = '1';                                         // atribui o valor a sua posiçao binaria
        indice--;                                                   // diminui a casa binaria de valor
    }
   }
  }
}


int main(){
    //inicializaçao da variaveis
    char populacao[1001][33];                                //matriz da populaçao, cada linha representa um individuo
    long long int solucao = 61;                              //soluçao do melhor individuo
    long long int melhor = 9223372036854775806;              //melhor soluçao de todas, declaraçao garante o primeiro retorno de solucao
    int tamanhoPop[] = {10,100,1000};                        //vetor com os possiveis tamanhos da populaçao
    int tamanho = 0;                                         //variavel para o tamanho da populaçao
    int crossover = 1;                                       //ponto que realiza a troca de "genes"
    float mutacao = 1.0;                                     //chance de ocorrer mutaçao
    int maxGeracoes = 0;                                     //maximo de tentativas do sistema
    int a = 1, b = 1, c = 1, d = 1, e = 1, f = 1;            //iniciliza as variaveis dos indices da equaçao

    cout << "Algoritmo Genetico:" << endl;
    //entradas do sistema
    cout << "Insira o tamanho da populacao 10, 100 ou 1000 (1, 2, 3), respectivamente: ";
    cin >> tamanho;
    cout << "Taxa de crossover(Recomendado: entre 8 e 12): ";
    cin >> crossover;
    cout << "Taxa de mutacao: ";
    cin >> mutacao;
    cout << "Insira o maximo de geracoes do programa: ";
    cin >> maxGeracoes;
    cout << "Insira os valores de a, b, c, d, e, f: \n";
    cin >> a;cin >> b;cin >> c;cin >> d;cin >> e;cin >> f;
    cout << "Processando..." << endl;

    //gera a primeira geraçao
    gerarPop (populacao, tamanhoPop[tamanho-1]);
    //laço para fazer as geraçoes
    for(int i = 0; i < maxGeracoes; i++){
    //avalia a populaçao
    avaliaPop (populacao, tamanhoPop[tamanho-1],a,b,c,d,e,f);
    //na primeira geraçao usa o valor da variavel "melhor" de dentro do main
    if(i == 0){
    solucao = melhorSolucao0(populacao,a,b,c,d,e,f,melhor);
    melhor = solucao;
        if(solucao == 0){//caso ache a soluçao ideal
            cout << "Melhor solucao encontrada: x = " << solucao << '!' << endl;
            cout << "Na geraçao: " << i <<endl;
        return 0;
        }
}//nas geraçoes posteriores usa o valor "melhor" fornecido por um individuo
    else{
        solucao = melhorSolucao(populacao,a,b,c,d,e,f,melhor);
        melhor = solucao;
        //caso ache a soluçao ideal
        if(solucao == 0){
            cout << "Melhor solucao encontrada: x = " << solucao << '!' << endl;
            cout << "Na geraçao: " << i <<endl;
        return 0;
    }
}
    //seleciona individuos mais aptos
    filtraPop(populacao, tamanhoPop[tamanho-1]);
    //mistura os "genes" entre os individuos
    cruzaPop(populacao, tamanhoPop[tamanho-1], crossover);
    //aplica inversao em um bit do individuo, baseado em uma chance
    mutacaoPop(populacao, tamanhoPop[tamanho-1], mutacao);
    }

    //exibe o resultado final do sistema
    cout << "Melhor solucao encontrada: x = " << solucao << endl;

    return 0;
}

/*Notas:
O algoritmo gera numeros no intervalo [-500, 500],
Entretanto, os cruzamentos e as mutaçoes entre individuos podem ultrapassar esse intervalo.

As mutaçoes ocorrem apenas entre os "genes" 16 e 31, para evitar valores muito distantes do esperado.

O sistema permite qualquer valor de crossover,
Entretanto, alguns valores podem causar problemas, principalmente acima do numero de bits dos individuos.

Ao ultilizar a opçao de 1000 individuos por geraçao, o resultado pode demorar mais que as outras opçoes de geraçao.
*/

/*
Parte destinada a teste do algoritmo:

Teste 1:
"Algoritmo Genetico:
Insira o tamanho da populacao 10, 100 ou 1000 (1, 2, 3), respectivamente: 2
Taxa de crossover(Recomendado: entre 8 e 12): 8
Taxa de mutacao: 50
Insira o maximo de geracoes do programa: 11
Insira os valores de a, b, c, d, e, f:
2
5
4
3
1
6
Melhor solucao encontrada: x = 6"

Teste 2:
"Algoritmo Genetico:
Insira o tamanho da populacao 10, 100 ou 1000 (1, 2, 3), respectivamente: 2
Taxa de crossover(Recomendado: entre 8 e 12): 12
Taxa de mutacao: 5
Insira o maximo de geracoes do programa: 10
Insira os valores de a, b, c, d, e, f:
1
10
12
20
22
120
Melhor solucao encontrada: x = -903588"

Teste 3:
"Algoritmo Genetico:
Insira o tamanho da populacao 10, 100 ou 1000 (1, 2, 3), respectivamente: 3
Taxa de crossover(Recomendado: entre 8 e 12): 29
Taxa de mutacao: 15
Insira o maximo de geracoes do programa: 5
Insira os valores de a, b, c, d, e, f:
1
9
11
7
19
24
Melhor solucao encontrada: x = 9"
*/