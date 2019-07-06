# Trabalho de FSO
Hugo Alves dos Santos Barbosa - 15/0036884  
Josué Nascimento da Silva - 15/0038933

## Protocolo implementado:
- O protocolo foi implementado de acordo com o que foi especificado, no qual a mensagem deve ser enviada na forma _DE:PARA:MENSAGEM_.  
- Para o receptor a mensagem é mostrada como _DE: MENSAGEM_.
- Ao apertar _ctrl + c_ é mostrada um aviso que para encerrar o programa é necessário digitar _sair_. Ao sair a fila de mensagens é apagada.
- Quando a fila não existe é mostrado _UNKNOWUSER PARA_.
- Caso não for possível enviar uma mensagem são feitas três tentativas e caso nenhuma dê certo é mostrado _ERRO DE:PARA:MENSAGEM_.
- Foi implementado o comando _list_.
- Foi implementado o broadcast, sendo que para o(s) receptor(es) a mensagem é mostrada como _Broadcast de DE: MENSAGEM_.
- O programa inibe a criação de um usuário com o nome _all_.

## Problemas conhecidos:
- Na tentativa de inibir que a pessoa que enviou um broadcast também recebesse a mensagem, a feature de broadcast ficou instável. Ele entra na condição de uma das filas estar cheia e tenta fazer as três tentativas, sendo que a mensagem não chega para uma das filas abertas. Ao tirar essa restrição o broadcast funciona para todos.
- Não foi feita a verificação se uma fila já existe antes de criar uma nova.
- Caso seja digitado algo que não seja o padrão da mensagem e os comandos de listar e sair o programa quebra.
- Ao testar no prestígio não conseguimos escrever nas filas que estavam abertas no momento, só receber mensagens. Localmente funciona corretamente.
- O broadcast não cria outras threads para enviar as mensagens para as filas abertas, por isso caso haja _n_ filas e uma delas esteja cheia, entra na condição de tentar reenviar três vezes, travando o envio das outras durante esse tempo.

## Dificuldades de implementação:
- Implementar toda a parte do broadcast.
- Diferenciar o que é mensagem a ser enviada e os comandos de listar e sair.
