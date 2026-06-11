#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

typedef struct {
    char palavra[50];
    char tema[30];
    char dica[100];
} Palavra;

int vitorias = 0, derrotas = 0;

void getConsoleSize(int *largura, int *altura) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *largura = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *altura  = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void printCentralizado(const char *linha) {
    int largura, altura;
    getConsoleSize(&largura, &altura);

    int esp = (largura - strlen(linha)) / 2;
    if (esp < 0) esp = 0;

    for (int i = 0; i < esp; i++) printf(" ");
    printf("%s\n", linha);
}

void printInline(const char *linha) {
    int largura, altura;
    getConsoleSize(&largura, &altura);

    int esp = (largura - strlen(linha)) / 2;
    if (esp < 0) esp = 0;

    for (int i = 0; i < esp; i++) printf(" ");
    printf("%s", linha);
}

void centralizarVertical(int linhas) {
    int largura, altura;
    getConsoleSize(&largura, &altura);

    int topo = (altura - linhas) / 2;
    if (topo < 0) topo = 0;

    for (int i = 0; i < topo; i++) printf("\n");
}

void getForcaLinha(int erros, int linha, char *out) {
    const char *estados[7][6] = {
        {" +-----+ ", " |     | ", " |       ", " |       ", " |       ", " |       "},
        {" +-----+ ", " |     | ", " |     O ", " |       ", " |       ", " |       "},
        {" +-----+ ", " |     | ", " |     O ", " |     | ", " |       ", " |       "},
        {" +-----+ ", " |     | ", " |     O ", " |    /| ", " |       ", " |       "},
        {" +-----+ ", " |     | ", " |     O ", " |    /|\\", " |       ", " |       "},
        {" +-----+ ", " |     | ", " |     O ", " |    /|\\", " |    /  ", " |       "},
        {" +-----+ ", " |     | ", " |     O ", " |    /|\\", " |    / \\", " |       "}
    };
    strcpy(out, estados[erros][linha]);
}

int menu() {
    const char *opcoes[] = {"Jogar", "Cadastrar", "Sair"};
    int escolha = 0;

    while (1) {
        system("cls");
        centralizarVertical(10);

        printCentralizado("===== JOGO DA FORCA =====\n");

        for (int i = 0; i < 3; i++) {
            char linha[50];
            sprintf(linha, (i == escolha) ? " > %s" : "   %s", opcoes[i]);
            printCentralizado(linha);
        }

        printf("\n");
        printCentralizado("Use seta pra cima e a seta pra baixo para mover e ENTER para selecionar");

        int tecla = getch();

        if (tecla == 224) {
            tecla = getch();
            if (tecla == 72) escolha--;
            if (tecla == 80) escolha++;
        }

        if (escolha < 0) escolha = 2;
        if (escolha > 2) escolha = 0;

        if (tecla == 13) return escolha;
    }
}

void embaralhar(Palavra **banco, int n) {
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        Palavra *temp = banco[i];
        banco[i] = banco[j];
        banco[j] = temp;
    }
}

void jogar(Palavra *p) {
    int tentativas = 6;
    int tamanho = strlen(p->palavra);

    char descoberta[50];
    char usadas[27] = "";
    int usadasCount = 0;

    for (int i = 0; i < tamanho; i++)
        descoberta[i] = '_';
    descoberta[tamanho] = '\0';

    while (tentativas > 0) {
        system("cls");
        centralizarVertical(15);

        char linhaForca[20];
        char linha[200];

        printCentralizado("+----------------------+------------------------------+");

        for (int i = 0; i < 6; i++) {
            getForcaLinha(6 - tentativas, i, linhaForca);

            if (i == 0)
                sprintf(linha, "| %s | Tema: %-22s |", linhaForca, p->tema);
            else if (i == 1)
                sprintf(linha, "| %s | Dica: %-22s |", linhaForca, p->dica);
            else if (i == 2)
                sprintf(linha, "| %s | Palavra: %-19s |", linhaForca, descoberta);
            else if (i == 3)
                sprintf(linha, "| %s | Tentativas: %-16d |", linhaForca, tentativas);
            else if (i == 4)
                sprintf(linha, "| %s | Erradas: %-18s |", linhaForca, usadas[0] ? usadas : "-");
            else
                sprintf(linha, "| %s | %-28s |", linhaForca, "");

            printCentralizado(linha);
        }

        printCentralizado("+----------------------+------------------------------+\n");

        printInline("Digite uma letra: ");

        char letra;
        scanf(" %c", &letra);

        if (strchr(usadas, letra) || strchr(descoberta, letra)) {
            printCentralizado("Letra repetida!");
            Sleep(800);
            continue;
        }

        int acertou = 0;

        for (int i = 0; i < tamanho; i++) {
            if (p->palavra[i] == letra) {
                descoberta[i] = letra;
                acertou = 1;
            }
        }

        if (!acertou) {
            if (usadasCount < 25) {
                usadas[usadasCount++] = letra;
                usadas[usadasCount] = '\0';
            }
            tentativas--;
        }

        if (strcmp(descoberta, p->palavra) == 0) {
            vitorias++;
            printCentralizado("VOCE GANHOU!");
            Sleep(1000);
            return;
        }
    }

    derrotas++;
    printCentralizado("VOCE PERDEU!");
    printCentralizado(p->palavra);
    Sleep(1200);
}

void cadastrar(const char *arq) {
    FILE *f = fopen(arq, "a");

    Palavra p;
    printf("Palavra: "); scanf("%s", p.palavra);
    printf("Tema: "); scanf(" %[^\n]", p.tema);
    printf("Dica: "); scanf(" %[^\n]", p.dica);

    fprintf(f, "%s|%s|%s\n", p.palavra, p.tema, p.dica);
    fclose(f);

    printf("Cadastrado!\n");
    system("pause");
}

Palavra** carregar_banco(const char *arq, int *n) {
    FILE *arquivo = fopen(arq, "r");
    if (!arquivo) return NULL;

    Palavra **banco = NULL;
    char linha[256];
    *n = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        banco = (Palavra**) realloc(banco, (*n + 1) * sizeof(Palavra*));
        banco[*n] = (Palavra*) malloc(sizeof(Palavra));

        sscanf(linha, "%49[^|]|%29[^|]|%99[^|\n]",
               banco[*n]->palavra,
               banco[*n]->tema,
               banco[*n]->dica);

        (*n)++;
    }

    fclose(arquivo);
    return banco;
}

int main() {
    srand(time(NULL)); // ?? ESSENCIAL PRA ALEATORIEDADE

    while (1) {
        int op = menu();

        if (op == 0) {
            int n;
            Palavra **banco = carregar_banco("banco.txt", &n);

            if (!banco || n == 0) {
                printf("Banco vazio!\n");
                system("pause");
                continue;
            }

            embaralhar(banco, n); // ?? embaralha tudo

            jogar(banco[0]); // pega a primeira já embaralhada

            for (int i = 0; i < n; i++)
                free(banco[i]);
            free(banco);
        }

        if (op == 1) cadastrar("banco.txt");
        if (op == 2) break;
    }

    system("cls");
    printCentralizado("===== PLACAR =====");

    char placar[100];
    sprintf(placar, "Vitorias: %d | Derrotas: %d", vitorias, derrotas);
    printCentralizado(placar);

    system("pause");
    return 0;
}
