#include <stdlib.h>  // Inclusão da biblioteca padrão para alocação de memória.
#include <stdio.h>   // Inclusão da biblioteca padrão para entrada e saída.
#include <iostream>  // Inclusão da biblioteca de entrada e saída do C++.
#include <string>    // Inclusão da biblioteca de manipulação de strings.

using namespace std; // Usar o namespace padrão para evitar prefixos de nome.

typedef struct pessoa { // Definição da estrutura 'pessoa'.
    int cpf;          // CPF armazenado como um inteiro.
    string nome;     // Nome da pessoa armazenado como uma string.
    int idade;       // Idade da pessoa armazenada como um inteiro.
    struct pessoa *prox; // Ponteiro para a próxima pessoa na lista.
} PESSOA;

typedef struct frasco { // Definição da estrutura 'frasco'.
    int doses;             // Número de doses disponíveis no frasco.
    struct frasco *prox;   // Ponteiro para o próximo frasco na pilha.
} FRASCO;

void imprimeFila(PESSOA *primeiro) { // Função para imprimir a fila de pessoas.
    if (primeiro == NULL) { // Verifica se a fila está vazia.
        cout << "\nFILA VAZIA\n"; // Imprime mensagem de fila vazia.
    } else { // Se a fila não estiver vazia.
        while (primeiro != NULL) { // Enquanto houver pessoas na fila.
            cout << "\nCPF: " << primeiro->cpf << ", Nome: " << primeiro->nome << ", Idade: " << primeiro->idade; // Imprime CPF, nome e idade da pessoa.
            primeiro = primeiro->prox; // Avança para a próxima pessoa na fila.
        }
    }
    cout << "\n"; // Imprime uma nova linha ao final da lista.
}

bool validarCPF(const string &cpf) { // Função para validar o CPF.
    if (cpf.length() != 11) { // Verifica se o CPF tem 11 dígitos.
        return false; // Se não tiver, retorna falso.
    }
    for (size_t i = 0; i < cpf.length(); ++i) { // Percorre cada caractere do CPF.
        if (cpf[i] < '0' || cpf[i] > '9') { // Verifica se o caractere não é um dígito.
            return false; // Se encontrar um caractere inválido, retorna falso.
        }
    }
    return true; // Se o CPF for válido, retorna verdadeiro.
}

int stringParaInt(const string &cpf) { // Função para converter uma string de CPF para um inteiro.
    int valor = 0; // Inicializa a variável que armazenará o valor inteiro.
    for (char c : cpf) { // Para cada caractere na string CPF.
        valor = valor * 10 + (c - '0'); // Converte o caractere para inteiro e atualiza o valor.
    }
    return valor; // Retorna o CPF como um inteiro.
}

void adicionarPessoa(PESSOA **primeiro, PESSOA **ultimo, int cpf, string nome, int idade) { // Função para adicionar uma nova pessoa à fila.
    PESSOA *novaPessoa = (PESSOA *)malloc(sizeof(PESSOA)); // Aloca memória para uma nova pessoa.
    novaPessoa->cpf = cpf; // Define o CPF da nova pessoa.
    novaPessoa->nome = nome; // Define o nome da nova pessoa.
    novaPessoa->idade = idade; // Define a idade da nova pessoa.
    novaPessoa->prox = NULL; // Define o próximo ponteiro como NULL.

    if (*ultimo == NULL) { // Verifica se a fila está vazia.
        *primeiro = novaPessoa; // Se estiver vazia, a nova pessoa é o primeiro.
        *ultimo = novaPessoa; // E também o último.
    } else { // Se a fila não estiver vazia.
        (*ultimo)->prox = novaPessoa; // O próximo do último se torna a nova pessoa.
        *ultimo = novaPessoa; // Atualiza o ponteiro do último para a nova pessoa.
    }
}

PESSOA *removerPessoa(PESSOA **primeiro) { // Função para remover uma pessoa da fila.
    if (*primeiro == NULL) { // Verifica se a fila está vazia.
        cout << "\nFILA VAZIA\n"; // Imprime mensagem de fila vazia.
        return NULL; // Retorna NULL se a fila estiver vazia.
    } else { // Se a fila não estiver vazia.
        PESSOA *aux = *primeiro; // Armazena o primeiro elemento em uma variável auxiliar.
        *primeiro = aux->prox; // Atualiza o primeiro para o próximo elemento.
        return aux; // Retorna a pessoa removida.
    }
}

void empilharFrasco(FRASCO **topo, int doses) { // Função para empilhar um frasco na pilha.
    FRASCO *novoFrasco = (FRASCO *)malloc(sizeof(FRASCO)); // Aloca memória para um novo frasco.
    novoFrasco->doses = doses; // Define o número de doses do novo frasco.
    novoFrasco->prox = *topo; // O próximo do novo frasco é o topo atual da pilha.
    *topo = novoFrasco; // Atualiza o topo para o novo frasco.
}

FRASCO *desempilharFrasco(FRASCO **topo) { // Função para desempilhar um frasco da pilha.
    if (*topo == NULL) { // Verifica se a pilha está vazia.
        return NULL; // Retorna NULL se a pilha estiver vazia.
    } else { // Se a pilha não estiver vazia.
        FRASCO *aux = *topo; // Armazena o topo em uma variável auxiliar.
        *topo = aux->prox; // Atualiza o topo para o próximo frasco.
        return aux; // Retorna o frasco desempilhado.
    }
}

void vacinarPessoas(PESSOA **primeiro, FRASCO **topo, int *totalVacinados) { // Função para vacinar as pessoas da fila.
    while (*topo != NULL && *primeiro != NULL && *totalVacinados < 15) { // Enquanto houver frascos, pessoas na fila e o total vacinado for menor que 15.
        PESSOA *pessoaAtual = removerPessoa(primeiro); // Remove a pessoa da fila.
        if (pessoaAtual != NULL) { // Se a pessoa foi removida com sucesso.
            cout << "\nPessoa vacinada: " << pessoaAtual->nome; // Imprime o nome da pessoa vacinada.
            free(pessoaAtual); // Libera a memória da pessoa.
            (*topo)->doses--; // Decrementa o número de doses do frasco.

            if ((*topo)->doses == 0) { // Se o frasco ficou sem doses.
                FRASCO *frascoAtual = desempilharFrasco(topo); // Desempilha o frasco.
                free(frascoAtual); // Libera a memória do frasco desempilhado.
            }

            (*totalVacinados)++; // Incrementa o total de vacinados.
        }
    }

    if (*totalVacinados >= 15) { // Se o limite diário de vacinas for atingido.
        cout << "\nLimite diário de 15 pessoas vacinadas atingido. Não é possível vacinar mais pessoas."; // Imprime mensagem de limite atingido.
    }
}

int main() { // Função principal do programa.
    PESSOA *primeiro = NULL; // Inicializa o primeiro elemento da fila como NULL.
    PESSOA *ultimo = NULL; // Inicializa o último elemento da fila como NULL.
    FRASCO *topo = NULL; // Inicializa o topo da pilha como NULL.
    int totalVacinados = 0; // Inicializa o contador de vacinados como 0.
    int opcao; // Variável para armazenar a opção do menu.
    string cpfStr, nome; // Variáveis para CPF e nome da pessoa.
    int idade; // Variável para a idade da pessoa.
    string data; // Variável para armazenar a data de vacinação.

    // Empilhar 3 frascos com 5 doses cada.
    for (int i = 0; i < 3; i++) {
        empilharFrasco(&topo, 5); // Empilha um novo frasco na pilha.
    }

    cout << "Digite a data de vacinação (dd/mm/aaaa): "; // Solicita a data de vacinação.
    getline(cin, data); // Lê a data informada.

    do { // Início do loop do menu.
        cout << "\nMenu:"; // Imprime o menu.
        cout << "\nData de vacinação: " << data; // Exibe a data de vacinação.
        cout << "\n1. Adicionar pessoa na fila"; // Opção para adicionar uma pessoa.
        cout << "\n2. Tirar pessoa da fila"; // Opção para remover uma pessoa.
        cout << "\n3. Imprimir os nomes de todo mundo da fila"; // Opção para imprimir a fila.
        cout << "\n4. Vacinar pessoas"; // Opção para vacinar pessoas.
        cout << "\n5. Exibir total de pessoas vacinadas"; // Opção para exibir total de vacinados.
        cout << "\n6. Sair"; // Opção para sair do programa.
        cout << "\nEscolha uma opcao: "; // Solicita ao usuário uma opção.
        cin >> opcao; // Lê a opção escolhida.
        cin.ignore(); // Limpa o buffer de entrada.

        if (opcao == 1) { // Se a opção for 1 (adicionar pessoa).
            do { // Loop para garantir que o CPF seja válido.
                cout << "\nDigite o CPF (11 dígitos): "; // Solicita o CPF.
                getline(cin, cpfStr); // Lê o CPF informado.
                if (!validarCPF(cpfStr)) { // Verifica se o CPF é válido.
                    cout << "CPF inválido! Tente novamente.\n"; // Informa CPF inválido.
                }
            } while (!validarCPF(cpfStr)); // Repete até que um CPF válido seja fornecido.

            int cpf = stringParaInt(cpfStr); // Converte a string CPF para inteiro.

            cout << "Digite o nome: "; // Solicita o nome da pessoa.
            getline(cin, nome); // Lê o nome informado.
            cout << "Digite a idade: "; // Solicita a idade da pessoa.
            cin >> idade; // Lê a idade informada.
            cin.ignore(); // Limpa o buffer de entrada.
            adicionarPessoa(&primeiro, &ultimo, cpf, nome, idade); // Adiciona a pessoa à fila.
        } else if (opcao == 2) { // Se a opção for 2 (remover pessoa).
            PESSOA *pessoaRemovida = removerPessoa(&primeiro); // Remove uma pessoa da fila.
            if (pessoaRemovida != NULL) { // Se uma pessoa foi removida.
                cout << "\nPessoa removida: " << pessoaRemovida->nome; // Imprime o nome da pessoa removida.
                free(pessoaRemovida); // Libera a memória da pessoa removida.
            }
        } else if (opcao == 3) { // Se a opção for 3 (imprimir fila).
            imprimeFila(primeiro); // Chama a função para imprimir a fila de pessoas.
        } else if (opcao == 4) { // Se a opção for 4 (vacinar pessoas).
            vacinarPessoas(&primeiro, &topo, &totalVacinados); // Chama a função para vacinar as pessoas.
        } else if (opcao == 5) { // Se a opção for 5 (exibir total vacinados).
            cout << "\nTotal de pessoas vacinadas: " << totalVacinados; // Imprime o total de vacinados.
        } else if (opcao == 6) { // Se a opção for 6 (sair).
            cout << "\nSaindo...\n"; // Imprime mensagem de saída.
        } else { // Se a opção for inválida.
            cout << "\nOpção invalida!"; // Informa que a opção é inválida.
        }
    } while (opcao != 6); // Continua o loop até que a opção 6 (sair) seja escolhida.

    return 0; // Retorna 0 indicando que o programa terminou com sucesso.
}
