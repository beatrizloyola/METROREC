# METROREC (`sync_car`)

Solução do problema do carro de metrô com threads POSIX: passageiros chegam à estação e esperam o carro; o carro chega com `count` assentos livres, deixa embarcar no máximo `count` passageiros e só parte quando todos que reservaram assento já sentaram (ou quando não há mais ninguém esperando).

Usa apenas **um mutex** e **duas variáveis de condição** por `struct station`. Sem semáforos, sem busy-wait.

## Arquivos

| Arquivo | Descrição |
|---|---|
| `sync_car.h` | Define `struct station` (mutex, contadores `waiting`, `free_seats`, `boarding`, flag `car_present`, condvars `car_arrived` e `all_boarded`) e os protótipos das 4 funções. |
| `sync_car.c` | Implementação: `station_init`, `station_wait_for_car` (passageiro), `station_load_car` (carro), `station_on_board` (passageiro sentou). |
| `sync_car-runner.c` | Programa de teste fornecido pelo professor (`main`). Cria threads de passageiros e de carro, com timeout via `alarm`, e imprime `Looks good!` se tudo passar. |
| `Makefile` | Alvos `all`, `sync_car` e `clean`. Flags `-Wall -Wextra -pthread`. |
| `evidencias.log` | Sessão de terminal (`script`) com compilação, testes, sanitizers e helgrind. |

## Como compilar

```bash
make
```

Equivale a:

```bash
gcc -Wall -Wextra -pthread -o sync_car sync_car.c sync_car-runner.c
```

Para limpar: `make clean`.

## Como executar

```bash
./sync_car
```

Saída esperada: `Looks good!`

## Como testar

**Repetição (race condition, deadlock, wakeup perdido):**

```bash
ok=0; fail=0
for i in $(seq 1 100); do
    if ./sync_car | grep -q "Looks good"; then ok=$((ok+1)); else fail=$((fail+1)); fi
done
echo "ok=$ok fail=$fail"
```

## Ambiente

```
Linux loyola-dell-g15 7.0.0-28-generic #28~24.04.1-Ubuntu SMP PREEMPT_DYNAMIC Wed Jul  1 15:50:57 UTC 2 x86_64 x86_64 x86_64 GNU/Linux
gcc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
```