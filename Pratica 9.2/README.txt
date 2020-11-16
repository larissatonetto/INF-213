Etapa 1:

Input     | Tempo
11        | 0m0,005s
12        | 0m0,007s
13        | 0m0,006s
14        | 0m0,022s
15        | 0m0,015s
16        | 0m2,407s
17        | 0m0,049s
18        | 43m52,749s
19        | 0m0,230s

As chamadas de pop() percorrem a lista atéchegar em top(), já que não é guardado um ponteiro para o elemento de maior prioridade

Etapa 3:
Mediana
Input     | Tempo
1         | 0m0,021s
2         | 0m0,043s
3         | 0m0,068s
4         | 0m0,521s
5         | 0m0,813s
6         | 0m1,450s

MedianaLenta
Input     | Tempo
1         | 0m0,199s
2         | 0m0,559s
3         | 0m1,917s

A implementação de MedianaLenta tem complexidade O(N log N) (complexidade de sort() do C++)
A implementação Mediana tem complexidade O(log N) (complexidade de insere())

Etapa 4:
No caso 1 a busca em profundidade é mais rápida (0m0,734s x 0m3,918s)
No caso 2 a busca em profundidade é mais rápida (0m1,214s x 0m23,799s)
No caso 3 a busca em profundidade é mais rápida (0m11,509s x 0m20,641s)
No caso 4 a busca em largura é mais rápida (0m6,658s x 0m6,439s)
No caso 5 a busca em profundidade é mais rápida (2m44,770s x 2m59,921s)