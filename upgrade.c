/*
    melhoria 

        um usuario que cria demanda para cpu, quando um usuário cria um processo, este precisa ser armazenado na
        MEMORIA, encontrar um espaço disponivel (armazenar esse espaço inicio e tamanho), então cobre com ums 
        nesse espaco. 
            AQUI ENTRA O SWAPER: se não houver espaço, de acordo com a estrutura proposta, o SWAPER retira uma
            pagina da memória, e a move para o disco, junto com os dados que ela referenciava.

        um escalonador que escalona os processos para o consumo na cpu

        a cpu consome um processo

        um swapper tabalha na MEMORIA (com o algoritmo especifico) movendo paginas para o DISCO (swap)
        a memoria tem um espaco de memoria no qual os processos e as paginas podem ser armazenadas
        o disco tambem tem um espaco no qual os processos e paginas podem ser movidos para ele.

        
        a memoria e o disco podem ser vetores, pois são estáticos, e nunca vão crescer.

        a cpu (consumer), usuario (producer, para o escalonador [fila de chamadas]) e escalonador de processos (consumer para o usuario,
        mas é producer para a CPU), podem ser threads
*/ 