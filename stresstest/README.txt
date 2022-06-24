FAQ:
1) QUE NÚMEROS SÃO ESSES NA MINHA TELA?
Cada número que o stressTest imprime é um caso de teste que o seu programa passou.

2) COMO EU PARO, ESTÁ RODANDO A MUITO TEMPO?
Control-C no Linux, não sei mexer em nada além de Linux.

3) QUE ARQUIVOS SÃO ESSES QUE O PROGRAMA CRIOU?
O que termina em in é o último caso de teste, os que terminam em "out" e "out2" são o resultado dos programas nesse caso de teste. Se der errado em algum momento vai dar pra ver em que caso deu errado nesses arquivos.

# Comandos para rodar o stresstest (só sei mexer com Linux :)
chmod +x bruto
chmod +x gen
chmod +x stressTest
bash stressTest bruto nomedoseuexecutavel gen

# O que isso tudo faz:
'gen' gera casos aleatórios de tamanho 10x10 com 100 mesas, e probabilidade de 50% de uma posição ser um '#', e 50% de ser um '.'; a seed é especificada como argumento da linha de comando.

'bruto' resolve o problema de forma bem lenta, O(k*(n*m)²)

'stressTest' recebe como argumento o executável bruto, o seu executável, e o executável gerador de casos aleatórios, e fica gerando infintos casos de teste. Se em algum sua saída der diferente do bruto, ele para e fala onde deu diferente.


É útil pra saber qual caso tá dando errado, já que o juiz online n mostra =D
