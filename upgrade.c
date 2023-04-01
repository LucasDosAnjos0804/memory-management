//              testes
/* FEITO
    fazer o usuário criar jobs;  

*/

/* FAZER
    corrigir vmemory_addin
    corrigir pagetable_map
    implementando o memory manager

*/

//              implementations

/*  FEITO
    joblist to scheduler
    mandar o Job para o escalonador
    corrigir erros de sempre espera
    corrigir erros de sempre sinaliza
    criar thread da CPU
        Fazer a cpu consumir o JOB com base no scheduler
        Fazera cpu requisitar acesso a memoria
        fazer a cpu emitir um free memory para o memory manager
    free memory task
    fazer os logs ficarem mais visualizaveis dividindo-os em categorías de logs
        para cada estrutura e para cada thread:)

*/

/*  FAZENDO 
    criar a thread do swapper
    implementar o algoritmo de swap no SWAPPER
    fazer o swapper pegar os jobs e alocar na memoria
*/

/*  FAZER
    ...
    ...
*/



/*
    melhoria no cenário

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

/*
    melhoria em paginas.h
        paginas referencia endereco de inicio e de fim, tambem pode referencias um Job
        nesse caso fifo seria de fato uma lista duplamente encadeada que refenciaria Nos
        que referenciariam paginas;

        nesse caso um __usuario criaria um Job, ENTAO, o __swaper encontra um espaço disponivel para esse Job na memoria
        com auxilio do enderacento virtual. (errado)

*/