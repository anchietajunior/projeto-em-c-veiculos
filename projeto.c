#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define MAX_STRING 50

typedef struct {
    char modelo[MAX_STRING];
    char marca[MAX_STRING];
    int anoFabricacao;
    char cor[MAX_STRING];
    char combustivel[MAX_STRING];
    int status; // 0 = Vendido, 1 = Em estoque
} Veiculo;

// Estrutura do nó da fila
typedef struct Node {
    Veiculo veiculo;
    struct Node* proximo;
} Node;

// Estrutura da fila
typedef struct {
    Node* inicio;
    Node* fim;
} Fila;

// Função para criar uma nova fila
Fila* criarFila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    if (fila != NULL) {
        fila->inicio = NULL;
        fila->fim = NULL;
    }
    return fila;
}

// Função para inserir um veículo na fila
void inserirNaFila(Fila* fila, Veiculo veiculo) {
    Node* novo = (Node*)malloc(sizeof(Node));
    if (novo != NULL) {
        novo->veiculo = veiculo;
        novo->proximo = NULL;
        
        if (fila->fim == NULL) {
            fila->inicio = novo;
            fila->fim = novo;
        } else {
            fila->fim->proximo = novo;
            fila->fim = novo;
        }
    }
}

// Função para liberar a memória da fila
void liberarFila(Fila* fila) {
    Node* atual = fila->inicio;
    while (atual != NULL) {
        Node* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(fila);
}

void listarVeiculos() {
    FILE* arquivo;
    Fila* fila = criarFila();
    char linha[MAX_STRING];
    Veiculo veiculo;
    int contador = 0;
    
    arquivo = fopen("veiculos.txt", "r");
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo!\n");
        system("pause");
        system("cls");
        return;
    }
    
    printf("\n=== Veículos Cadastrados ===\n");
    
    // Verificar se o arquivo está vazio
    fseek(arquivo, 0, SEEK_END);
    if (ftell(arquivo) == 0) {
        printf("\nO arquivo está vazio!\n");
        fclose(arquivo);
        liberarFila(fila);
        system("pause");
        system("cls");
        return;
    }
    rewind(arquivo);
    
    int veiculoAtual = 0;
    
    while (fgets(linha, MAX_STRING, arquivo) != NULL) {
        if (strstr(linha, "=== VEÍCULO ===") != NULL) {
            veiculoAtual = 1;
            continue;
        }
        
        if (veiculoAtual) {
            if (strstr(linha, "Modelo:") != NULL) {
                sscanf(linha, "Modelo: %[^\n]", veiculo.modelo);
            }
            else if (strstr(linha, "Marca:") != NULL) {
                sscanf(linha, "Marca: %[^\n]", veiculo.marca);
            }
            else if (strstr(linha, "Ano:") != NULL) {
                sscanf(linha, "Ano: %d", &veiculo.anoFabricacao);
            }
            else if (strstr(linha, "Cor:") != NULL) {
                sscanf(linha, "Cor: %[^\n]", veiculo.cor);
            }
            else if (strstr(linha, "Combustível:") != NULL) {
                sscanf(linha, "Combustível: %[^\n]", veiculo.combustivel);
            }
            else if (strstr(linha, "Status:") != NULL) {
                char statusStr[MAX_STRING];
                sscanf(linha, "Status: %[^\n]", statusStr);
                veiculo.status = (strcmp(statusStr, "Em estoque") == 0) ? 1 : 0;
                
                // Quando temos todos os dados do veículo, inserimos na fila
                inserirNaFila(fila, veiculo);
                contador++;
                
                veiculoAtual = 0;
            }
        }
    }
    
    fclose(arquivo);
    
    // Listar os veículos da fila
    if (contador == 0) {
        printf("\nNenhum veículo cadastrado!\n");
    } else {
        Node* atual = fila->inicio;
        int i = 1;
        
        while (atual != NULL) {
            printf("\nVeículo %d:\n", i++);
            printf("Modelo: %s\n", atual->veiculo.modelo);
            printf("Marca: %s\n", atual->veiculo.marca);
            printf("Ano: %d\n", atual->veiculo.anoFabricacao);
            printf("Cor: %s\n", atual->veiculo.cor);
            printf("Combustível: %s\n", atual->veiculo.combustivel);
            printf("Status: %s\n", atual->veiculo.status == 1 ? "Em estoque" : "Vendido");
            printf("-------------------\n");
            
            atual = atual->proximo;
        }
        
        printf("\nTotal de veículos: %d\n", contador);
    }
    
    liberarFila(fila);
    system("pause");
    system("cls");
}

void cadastrarVeiculo() {
    Veiculo veiculo;
    FILE *arquivo;
    
    printf("\n=== Cadastro de Veículo ===\n");
    
    // Limpar o buffer do teclado
    fflush(stdin);
    
    printf("Modelo: ");
    fgets(veiculo.modelo, MAX_STRING, stdin);
    veiculo.modelo[strcspn(veiculo.modelo, "\n")] = 0;
    
    printf("Marca: ");
    fgets(veiculo.marca, MAX_STRING, stdin);
    veiculo.marca[strcspn(veiculo.marca, "\n")] = 0;
    
    printf("Ano de Fabricação: ");
    scanf("%d", &veiculo.anoFabricacao);
    fflush(stdin);
    
    printf("Cor: ");
    fgets(veiculo.cor, MAX_STRING, stdin);
    veiculo.cor[strcspn(veiculo.cor, "\n")] = 0;
    
    printf("Combustível: ");
    fgets(veiculo.combustivel, MAX_STRING, stdin);
    veiculo.combustivel[strcspn(veiculo.combustivel, "\n")] = 0;
    
    printf("Status (0 = Vendido, 1 = Em estoque): ");
    scanf("%d", &veiculo.status);
    
    // Validar o status
    while (veiculo.status != 0 && veiculo.status != 1) {
        printf("Status inválido! Digite 0 para Vendido ou 1 para Em estoque: ");
        scanf("%d", &veiculo.status);
    }
    
    // Abrir arquivo para escrita (append)
    arquivo = fopen("veiculos.txt", "a");
    
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo!\n");
        system("pause");
        system("cls");
        return;
    }
    
    // Escrever os dados no arquivo com uma formatação clara
    fprintf(arquivo, "=== VEÍCULO ===\n");
    fprintf(arquivo, "Modelo: %s\n", veiculo.modelo);
    fprintf(arquivo, "Marca: %s\n", veiculo.marca);
    fprintf(arquivo, "Ano: %d\n", veiculo.anoFabricacao);
    fprintf(arquivo, "Cor: %s\n", veiculo.cor);
    fprintf(arquivo, "Combustível: %s\n", veiculo.combustivel);
    fprintf(arquivo, "Status: %s\n", veiculo.status == 1 ? "Em estoque" : "Vendido");
    fprintf(arquivo, "================\n\n");
    
    // Verificar se houve erro na escrita
    if (ferror(arquivo)) {
        printf("\nErro ao escrever no arquivo!\n");
        fclose(arquivo);
        system("pause");
        system("cls");
        return;
    }
    
    fclose(arquivo);
    
    printf("\nVeículo cadastrado com sucesso!\n");
    printf("Dados salvos no arquivo veiculos.txt\n");
    system("pause");
    system("cls");
}

void buscarVeiculo() {
    FILE* arquivo;
    Fila* fila = criarFila();
    char linha[MAX_STRING];
    Veiculo veiculo;
    char modeloBusca[MAX_STRING];
    int contador = 0;
    
    printf("\n=== Buscar Veículo ===\n");
    
    // Limpar o buffer do teclado
    fflush(stdin);
    
    printf("Digite o modelo do veículo que deseja buscar: ");
    fgets(modeloBusca, MAX_STRING, stdin);
    modeloBusca[strcspn(modeloBusca, "\n")] = 0;
    
    arquivo = fopen("veiculos.txt", "r");
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo!\n");
        system("pause");
        system("cls");
        return;
    }
    
    printf("\n=== Resultados da Busca ===\n");
    
    int veiculoAtual = 0;
    
    while (fgets(linha, MAX_STRING, arquivo) != NULL) {
        if (strstr(linha, "=== VEÍCULO ===") != NULL) {
            veiculoAtual = 1;
            continue;
        }
        
        if (veiculoAtual) {
            if (strstr(linha, "Modelo:") != NULL) {
                sscanf(linha, "Modelo: %[^\n]", veiculo.modelo);
            }
            else if (strstr(linha, "Marca:") != NULL) {
                sscanf(linha, "Marca: %[^\n]", veiculo.marca);
            }
            else if (strstr(linha, "Ano:") != NULL) {
                sscanf(linha, "Ano: %d", &veiculo.anoFabricacao);
            }
            else if (strstr(linha, "Cor:") != NULL) {
                sscanf(linha, "Cor: %[^\n]", veiculo.cor);
            }
            else if (strstr(linha, "Combustível:") != NULL) {
                sscanf(linha, "Combustível: %[^\n]", veiculo.combustivel);
            }
            else if (strstr(linha, "Status:") != NULL) {
                char statusStr[MAX_STRING];
                sscanf(linha, "Status: %[^\n]", statusStr);
                veiculo.status = (strcmp(statusStr, "Em estoque") == 0) ? 1 : 0;
                
                // Verificar se o modelo corresponde à busca
                if (strcmp(veiculo.modelo, modeloBusca) == 0) {
                    // Inserir o veículo na fila
                    inserirNaFila(fila, veiculo);
                    contador++;
                }
                
                veiculoAtual = 0;
            }
        }
    }
    
    fclose(arquivo);
    
    // Exibir os resultados
    if (contador == 0) {
        printf("\nNenhum veículo encontrado com o modelo '%s'!\n", modeloBusca);
    } else {
        Node* atual = fila->inicio;
        int i = 1;
        
        printf("\nForam encontrados %d veículo(s) com o modelo '%s':\n", contador, modeloBusca);
        
        while (atual != NULL) {
            printf("\nVeículo %d:\n", i++);
            printf("Modelo: %s\n", atual->veiculo.modelo);
            printf("Marca: %s\n", atual->veiculo.marca);
            printf("Ano: %d\n", atual->veiculo.anoFabricacao);
            printf("Cor: %s\n", atual->veiculo.cor);
            printf("Combustível: %s\n", atual->veiculo.combustivel);
            printf("Status: %s\n", atual->veiculo.status == 1 ? "Em estoque" : "Vendido");
            printf("-------------------\n");
            
            atual = atual->proximo;
        }
    }
    
    liberarFila(fila);
    system("pause");
    system("cls");
}

int main() {
    // Configurar o console para suportar caracteres UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    int opcao;

    do {
        printf("\n==== Anchieta Veículos ====\n");
        printf("1 - Listar veículos no estoque\n");
        printf("2 - Cadastrar novo veículo\n");
        printf("3 - Buscar veículo\n");
        printf("4 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarVeiculos();
                break;
            case 2:
                cadastrarVeiculo();
                break;
            case 3:
                buscarVeiculo();
                break;
            case 4:
                printf("-> Saindo do sistema. Até logo!\n");
                break;
            default:
                printf("-> Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 4);

    return 0;
}

