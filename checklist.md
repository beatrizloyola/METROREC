# Checklist — Sincronização do Metrô (Implementação 4)

## Bloco 1 — Projeto da solução

- [x] Definir o estado em `struct station`:
  - [x] `mutex`
  - [x] `waiting` (passageiros esperando)
  - [x] `free_seats` (assentos livres do carro atual)
  - [x] `boarding` (passageiros que passaram o wait mas ainda não chamaram `on_board`)
  - [x] `car_present` (carro na estação)
- [x] Definir 2 ou 3 variáveis de condição: `car_arrived`, `all_boarded` (2 bastam; `passenger_boarded` não foi necessária)
- [x] Definir regras das funções
  - [x] `station_wait_for_car` bloqueia enquanto `!car_present || free_seats == 0`; ao acordar, faz `free_seats--` e `boarding++` (reserva o assento)
  - [x] `station_load_car` retorna imediato se `count == 0` ou `waiting == 0`; senão faz `broadcast` e espera até `(free_seats == 0 || waiting == 0) && boarding == 0`
  - [x] `station_on_board` faz `boarding--` e dá `signal` quando chega a 0
- [x] Decidir como contar `waiting` e como evitar que um passageiro novo chegue com o carro já cheio (`waiting++` ao entrar; o `while` com `free_seats == 0` segura quem chega com carro cheio)

## Bloco 2 — Implementação

- [x] Criar `sync_car.h` (struct, protótipos, include guards)
- [x] Criar `sync_car.c` com `#include "sync_car.h"`
- [x] Implementar `station_init` (`pthread_mutex_init` e `pthread_cond_init`)
- [x] Implementar `station_wait_for_car` com `while` no `cond_wait` (nunca `if`, por causa de wakeups espúrios)
- [x] Implementar `station_load_car`
- [x] Implementar `station_on_board`
- [X] Criar o `Makefile` com alvos `all`, `clean` e `sync_car` (`-Wall -Wextra -pthread`), compilando `sync_car.c` + `sync_car-runner.c`
- [X] Primeira compilação sem warnings

## Bloco 3 — Testes e depuração

- [X] Lembrar de iniciar `script -a evidencias.log` antes de compilar/testar
- [X] Rodar o runner e registrar a saída ("Looks good!")
- [X] Rodar o runner em loop (50 a 200 execuções) para pegar race condition, deadlock e wakeup perdido
- [ ] Testar casos limite:
  - [ ] `count = 0`
  - [ ] sem passageiros
  - [ ] passageiros > assentos
  - [ ] assentos > passageiros
- [ ] Testar caso inválido (ex.: `count` negativo), decidir o comportamento e documentar (sugestão: tratar `count <= 0` como `count == 0`)
- [X] Rodar com `-fsanitize=thread`
- [X] Rodar com `valgrind --tool=helgrind`
- [X] Confirmar ausência de busy-wait (CPU ociosa durante a espera)
- [X] Confirmar que existe um único mutex por `struct station`
- [ ] Confirmar que não há semáforos nem outras primitivas além das permitidas
- [ ] Anotar cada tentativa no diário (estratégia, resultado, hipótese, horário, evidência)
- [X] Print do bug mais relevante
- [X] Print do teste passando

## Bloco 4 — Documentação

- [ ] README:
  - [ ] descrição de cada arquivo `.c`/`.h`
  - [ ] como compilar
  - [ ] como executar
  - [ ] como testar
  - [ ] SO usado (`uname -a`, `gcc --version`)
- [ ] Relatório em PDF (formato do Guia de Relatórios):
  - [ ] 1. Objetivo (3–5 linhas)
  - [ ] 2. Checklist de requisitos (status + como testar)
  - [ ] 3. Como reproduzir (comandos reais e copiáveis)
  - [ ] 4. Arquitetura (arquivos, responsabilidades, decisões técnicas)
  - [ ] 5. Estratégias e diário de desenvolvimento (5.1 e 5.2, ordem cronológica batendo com `evidencias.log`)
  - [ ] 6. Evidências (log + prints)
  - [ ] 7. Uso de IA (preencher mesmo que seja "não utilizei")
  - [ ] 8. Reflexão final (5–8 linhas)
  - [ ] 9. Checklist final de entrega
  - [ ] 10. "Se eu tivesse mais 2 horas" (5–10 linhas)
- [ ] Incluir dificuldades e o que não foi implementado, com justificativa
- [ ] Conferir que prints, log e relato não se contradizem
- [ ] Remover frases genéricas ou vazias

## Bloco 5 — Empacotamento e entrega

- [ ] Validar a compilação do zero: `make clean && make && ./sync_car`
- [ ] Encerrar o `script` (`exit`) e conferir que `evidencias.log` está em `blgv/`
- [ ] Gerar o tar: `cd .. && tar -cf blgv.tar blgv/`
- [ ] Testar a extração e a compilação a partir do tar:
  ```
  mkdir /tmp/check && tar -xf blgv.tar -C /tmp/check && cd /tmp/check/blgv && make && ./sync_car
  ```
- [ ] Conferir o conteúdo do `.tar`:
  - [ ] código (`sync_car.c`, `sync_car.h`, runner)
  - [ ] README
  - [ ] Makefile
  - [ ] `evidencias.log`
- [ ] Nomear o relatório `blgv.pdf` e colocar uma cópia no repositório
- [ ] Push no GitHub com README e PDF
- [ ] Enviar no Classroom: `blgv.pdf` + `blgv.tar` + link do GitHub
- [ ] Conferir nomes: diretório `blgv/`, `blgv.tar`, `blgv.pdf`

## Checklist final do guia (seção 9)

- [ ] Compilei do zero seguindo só o que está no relatório
- [ ] Rodei os testes e `evidencias.log` foi gerado
- [ ] Tenho prints obrigatórios
- [ ] Testei pelo menos um caso limite e um caso inválido
- [ ] Preenchi a seção de uso de IA
- [ ] Revisei o relatório e removi frases genéricas / vazias
