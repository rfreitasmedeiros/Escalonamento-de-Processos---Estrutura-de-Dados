# SIMULADOR DE ESCALONAMENTO POR PRIORIDADE

### INTEGRANTES: Fernando, Matheus, Rodrigo, Samuel

## 1 - INTRODUÇÃO

O presente trabalho tem como objetivo o desenvolvimento de um simulador de escalonamento de processos utilizando o critério de prioridade, implementado na linguagem C. O projeto foi elaborado no contexto da disciplina de Estrutura de Dados, com a finalidade de aplicar conceitos fundamentais como listas encadeadas, filas e alocação dinâmica de memória em um problema clássico da área de Sistemas Operacionais.

Foram implementados dois algoritmos distintos de escalonamento: prioridade preemptivo e prioridade não preemptivo. Cada algoritmo foi desenvolvido de forma independente, em arquivos separados, permitindo a execução individual e a análise comparativa de seus resultados.

---

## 2 - COMPILAÇÃO E EXECUÇÃO

Para a compilação dos programas é necessário possuir o compilador GCC (GNU Compiler Collection) instalado no sistema.

A compilação do algoritmo de prioridade preemptivo é realizada com o seguinte comando no prompt:

```
gcc prioridade_preemptivo.c -o prioridade_preemptivo
```

A execução ocorre por meio do comando:

```
./prioridade_preemptivo
```

A compilação do algoritmo de prioridade não preemptivo é feita com:

```
gcc prioridade_nao_preemptivo.c -o prioridade_nao_preemptivo
```

E sua execução com:

```
./prioridade_nao_preemptivo
```

Em ambos os casos, o simulador permite a inserção manual dos processos pelo usuário.

---

## 3 - DECISÕES DE PROJETO

A principal estrutura de dados utilizada no projeto é a lista encadeada simples, empregada na implementação das filas de processos. Foram utilizadas três filas principais: fila de entrada, fila de prontos e fila de processos concluídos.

A fila de prontos é mantida ordenada por prioridade, garantindo que o processo com maior prioridade seja selecionado para execução. A utilização de alocação dinâmica de memória permite flexibilidade quanto à quantidade de processos simulados. A escolha por listas encadeadas se justifica pela eficiência nas operações de inserção e remoção, frequentes em algoritmos de escalonamento.

---

## 4 - ALGORITMOS IMPLEMENTADOS

### 4.1 - Prioridade Preemptivo

Neste algoritmo, o processo em execução pode ser interrompido caso um processo de maior prioridade chegue ao sistema. A decisão de escalonamento ocorre a cada unidade de tempo.

### 4.2 - Prioridade Não Preemptivo

Neste algoritmo, o processo selecionado executa até sua finalização, sem interrupções. A prioridade é considerada apenas no momento da escolha do próximo processo.

---

## 5 - CRITÉRIOS DE DESEMPATE (ALGORITMO PREEMPTIVO)

O critério principal de escalonamento é o valor da prioridade, sendo que menores valores indicam maior prioridade. Em caso de empate, utiliza-se como critério de desempate a ordem de chegada à fila de prontos, garantindo previsibilidade e comportamento determinístico.

---

## 6 - CÁLCULO DAS MÉTRICAS

As métricas calculadas para cada processo são:

- Tempo de Término: instante em que o processo finaliza sua execução.
- Turnaround Time (TAT): TAT = Tempo de Término − Tempo de Chegada.
- Waiting Time (WT): WT = Turnaround Time − Tempo de Execução.
- Response Time (RT): RT = Tempo do Primeiro Atendimento − Tempo de Chegada.

As métricas globais do algoritmo incluem as médias dos tempos de espera, turnaround e resposta, além da vazão (Throughput), definida como:

Throughput = Número de Processos / Tempo Total de Execução.

---

## 7 - TABELA COMPARATIVA DE RESULTADOS

| Critério | Prioridade Preemptivo | Prioridade Não Preemptivo |
|--------|----------------------|---------------------------|
| Tempo médio de resposta | Menor | Maior |
| Tempo médio de espera | Moderado | Maior |
| Trocas de contexto | Elevadas | Reduzidas |
| Complexidade | Maior | Menor |
| Risco de starvation | Médio | Alto |

---

## 8 - VISUALIZAÇÃO DE UM EXEMPLO DE EXECUÇÃO

### Comparação entre os algoritmos de prioridade preemptivo e não preemptivo

Para a comparação entre os algoritmos de escalonamento por prioridade preemptivo e não preemptivo, considera-se esse conjunto de processos:

|P1:| chegada = 0 | duração = 5 | prioridade = 2 |
|---|-------------|-------------|----------------|
|P2:| chegada = 1 | duração = 3 | prioridade = 1 |
|P3:| chegada = 2 | duração = 2 | prioridade = 3 |

Adota-se o critério de que **menor valor numérico indica maior prioridade**.

---

#### Execução no algoritmo de prioridade não preemptivo

No escalonamento não preemptivo, o processo selecionado executa até a sua finalização, independentemente da chegada de processos com maior prioridade.

Linha do tempo da CPU:

|Tempo:| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|------|---|---|---|---|---|---|---|---|---|
|CPU:| P1 | P1 | P1 | P1 | P1 | P2 | P2 | P2 | P3 | P3 |

(imagens/naopreemptivo.png)

Nesse cenário, o processo P2, apesar de possuir maior prioridade, aguarda a finalização completa de P1 para ser executado.

---

#### Execução no algoritmo de prioridade preemptivo

No escalonamento preemptivo, sempre que um processo com maior prioridade chega ao sistema, ocorre a interrupção (preempção) do processo em execução.

Linha do tempo da CPU:

|Tempo:| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|------|---|---|---|---|---|---|---|---|---|
|CPU:| P1 | P2 | P2 | P2 | P1 | P1 | P1 | P1 | P3 | P3 |  

(imagens/preemptivo.png)

No tempo 1, o processo P2 chega ao sistema com maior prioridade e preempta o processo P1. Após a conclusão de P2, o processo P1 retoma sua execução.

---

#### Análise comparativa

A comparação entre os dois algoritmos evidencia diferenças significativas no comportamento do sistema:

- **Tempo de resposta**: no algoritmo preemptivo, processos de alta prioridade possuem menor tempo de resposta, pois podem interromper a execução de outros processos.
- **Tempo de espera**: o algoritmo não preemptivo pode aumentar o tempo de espera de processos prioritários, uma vez que não permite interrupções.
- **Previsibilidade**: o algoritmo não preemptivo apresenta execução mais previsível e simples de implementar.
- **Justiça**: o algoritmo preemptivo favorece processos de maior prioridade, podendo causar starvation em processos de baixa prioridade.

Conclui-se que o algoritmo de prioridade preemptivo é mais adequado para sistemas que exigem rápida resposta a processos críticos, enquanto o não preemptivo é indicado para cenários onde a simplicidade e a previsibilidade são mais relevantes.

---

## 9 - CONSIDERAÇÕES FINAIS

O simulador atende aos requisitos propostos, aplicando de forma prática estruturas de dados dinâmicas na implementação de algoritmos de escalonamento. A separação entre versões preemptiva e não preemptiva possibilita uma análise clara das diferenças entre os algoritmos, reforçando a importância da escolha adequada das estruturas de dados e das estratégias de escalonamento.

---
