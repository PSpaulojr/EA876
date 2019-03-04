
/* Demonstracao de maquina de estados */

#include <stdio.h>

/* Maquina de estados:
 * Detecta se existe ao menos um numero inteiro na linha inserida */

int eh_digito(char c)
{
  if ((c >= '0') && (c <= '9')) return 1;
  else return 0;
}

typedef struct {
  int estado_atual;
} fsm, *Fsm; /* fsm = finite state machine */

int opera_fsm(void *this_fsm, char entrada) {
  Fsm maquina = (Fsm) this_fsm;

  switch (maquina->estado_atual) {
    case 0:
      if (eh_digito(entrada)) {
        maquina->estado_atual = 1;
      }
      else maquina->estado_atual = 0;
      break;

    case 1:
      if (!eh_digito(entrada)) {
        maquina->estado_atual = 0;
      }
      else maquina->estado_atual = 2;
      break;

      case 2:
        if (!eh_digito(entrada)){
          maquina->estado_atual = 0;
        }
        else maquina->estado_atual = 2;
  }
  return (maquina->estado_atual);
}

int main() {
  char buffer_in[100];
  int pointer;
  int achei_inteiro;
  char c;

  for (int i=0; i<100; i++) buffer_in[i] = '\0';

  pointer = 0;
  do {
    c=getchar();
    buffer_in[pointer++] = c;
  } while (c != '\n');

  fsm maquina;
  maquina.estado_atual = 0;

  pointer = 0;
  achei_inteiro = 0;
  while (buffer_in[pointer] != '\n') {
    opera_fsm((void*) (&maquina), buffer_in[pointer]);
    if (maquina.estado_atual == 1) achei_inteiro = 1;
    printf("Entrada: %c\tEstado: %d\n", buffer_in[pointer], maquina.estado_atual);
    pointer++;
  }

  if (achei_inteiro == 1) printf("ACEITAR\n");
  else printf("REJEITAR\n");

  return 0;
}
