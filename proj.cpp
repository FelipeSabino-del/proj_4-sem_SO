/* 
    NOME: Felipe Sabino
    TIA:32242638
    TURMA: 04N12
    NOME: Nicolas Rondon
    TIA:32235208
*/
#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da lista
typedef struct Node {
  int arrival_time;  // Momento em que a pessoa chegou
  int direction;     // Direção que a pessoa quer ir (0 ou 1)
  struct Node *next; // Próximo nó na lista
} Node;

// Função para criar um novo nó
Node *createNode(int arrival_time, int direction) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->arrival_time = arrival_time;
  newNode->direction = direction;
  newNode->next = NULL;
  return newNode;
}

// Função para inserir um novo nó no final da lista
void insertEnd(Node **head, Node *new_person) {
  if (*head == NULL) {
    *head = new_person;
  } else {
    Node *temp = *head;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = new_person;
  }
}

// Função principal que simula a escada rolante
int simularEscadaRolante(Node *head, int duration) {
  int current_time = 0;
  int last_exit_time = 0;
  int current_direction = -1; // -1 indica que a escada está livre

  while (head != NULL && current_time <= duration) {
    Node *current_person = head;

    if (current_direction != -1 && current_time == last_exit_time)
    {
        current_direction = -1;
    }


    // Verificar se a pessoa pode entrar na escada
    if (current_person->arrival_time <= current_time) {
      // Verificar se a escada está livre ou se a pessoa pode entrar na direção da escada
      if (current_direction == -1 || current_person->direction == current_direction) {
        printf("Pessoa entrou na escada no momento %d\n", current_person->arrival_time);
        last_exit_time = current_person->arrival_time + 10; // Atualizar o último momento de saída
        head = current_person->next;
        current_direction = current_person->direction; // Atualizar a direção da escada
      } else {
        // A pessoa deve esperar até que a escada esteja livre na direção desejada
        printf("Aguardando pessoa no momento %d\n", current_time);
        current_person->arrival_time = last_exit_time; // Incrementar o tempo de chegada da pessoa que está esperando
        continue; // Continue para a próxima iteração do loop
      }
    } else {
      // A pessoa ainda não pode entrar, aguarde um momento
      printf("Aguardando pessoa no momento %d\n", current_time);
    }

    current_time++; // Incrementa o tempo, mas não atualiza o último momento de saída
  }

  return last_exit_time;
}

// Função principal
int main() {
  Node *head = NULL; // Inicializar a lista vazia

  int num_people;
  printf("Informe o número de pessoas: ");
  scanf("%d", &num_people);

  for (int i = 0; i < num_people; i++) {
    int arrival_time, direction;
    printf("Informe a hora de chegada e a direção para a pessoa %d: ", i + 1);
    scanf("%d %d", &arrival_time, &direction);
    Node *new_person = createNode(arrival_time, direction);
    insertEnd(&head, new_person);
  }

  // Simular a escada rolante
  int last_exit_time =
      simularEscadaRolante(head, 100); // Duração total da simulação

  // Imprimir o momento em que a última pessoa saiu
  printf("O último momento de saída foi %d\n", last_exit_time);

  // Liberar a memória ao final do programa
  while (head != NULL) {
    Node *temp = head;
    head = head->next;
    free(temp);
  }

  return 0;
}


