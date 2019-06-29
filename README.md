# Trabalho LFA – Simulador de AutômatoFinito Determinístico
## Universidade tecnologica federal do para

 1. - O  arquivo  TXTque  representa  o  autômato  deve  seguir  o  formato  de  texto especificado a seguir.
    **1.1** O alfabeto do autômato é fixo: Σ = {0, 1}.  
    **1.2** A primeira linha contéma cadeia de teste.  
    **1.3** A  segunda  linha contémo  nome  dos  estados.  O  primeiro  estado  da segunda linha é o estado inicial. Nomes de estados tem no mínimo 1 e no máximo  dois  caracteres  e  são  separados  por  um  ou mais  espaços.  O simulador  deve  ser  genérico  e  permitir  qualquer  número  de  estados, respeitando no mínimo um estado.  
    **1.4** A  terceira  linha contémos  estados  finais.  Se  for  vazia,  significa  que  o autômato não tem estados de aceitação.  
    **1.5** A  quarta  linha  e  as  seguintes contéma  tabela  de  transição.  O  primeiro elemento da linha é o nome do estado. O segundo elemento da linha é a transição  para  o  símbolo  0.  O  terceiro  elemento da  linha  é  a  transição para o símbolo 1. Use o hífen (“-”) para denotar transição inexistente.  
  2. - Exemplos de entradas (do arquivo):  
    **2.1** Exemplo 1:  
          - cadeias terminadas em 1.  
          00101  
          q0 q1  
          q1  
          q0 q0 q1  
          q1 q0 q1   
          
          
O simulador de autômato é programado na linguagem de programação C++, fora utilizado estruturas de grafos, ponteiros interligando uma estrutura de dados definia no algoritimo, para simular os estados que o autômato pode ter, ainda temos, nessa estrutura de dados, dois valores boleanos para dizer se o estado é final e/ou inicial, dentro desta ainda temos a definição da gramática, que conforme a proposta do enunciado do trabalho é uma gramática fixa, onde o alfabeto é Σ = {0, 1}. Segue o trecho de código que define um estado:

typedef struct estado {
    string nome;
    struct estado *_0;
    struct estado *_1;
    bool inicial;
    bool final;
}Q;

A primeira fase do algoritmo é a leitura do arquivo de texto para criação das malhas do grafo, se o arquivo segue as regras definidas pelo software, este será interpretado de maneira correta! Caso contrário o software irá falhar! Considerando o êxito na leitura, o software irá ter um array cujo seus elementos são os N estados lidos no arquivo informado pelo usuário. A próxima fase será fazer a ligação dos ponteiros, ou seja “nesse estado atual se eu ver 1 o que eu faço?”. Para tal o algoritmo irá percorrer este array, e como informado no arquivo de texto, vamos criar referenciar os ponteiros do estado, tanto o ‘0’ quanto o ‘1’, caso não haja estado definido o ponteriro será nullptr, ou seja, um estado não definido, sem transição. Segue o código que realiza essa tarefa:

for (int i = 3; i < linha.size(); i++) // a parir da 3 linha temos as definições de transições dos estados!
    {
        vector<string> estado_transicao = explode(linha[i], ' ');
        for (int j = 0; j < estados.size(); j++)
        {
            if (estados[j].nome == estado_transicao[0])
            {
                for (int k = 0; k < estados.size(); k++)
                {
                    if (estados[k].nome == estado_transicao[1])
                        estados[j]._0 = &estados[k];
                    if (estados[k].nome == estado_transicao[2])
                        estados[j]._1 = &estados[k];
                }
            }
        }
    }

O primeiro laço de repetição percorre todos os estado para cada estado ele irá alocar a referencia do estado que há transição, o nome do estado é utilizado para isso! O segundo laço de repetição irá buscar dentre todos os estados aquele que o estado do laço anterior tem referencia, inclusive pode ser o mesmo, por isso voltamos ao inicio e vamos até o fim! Ao final o grafo estará completo e podemos navegar por ele, a partir do estado inicial e ver se paramos em um estado final ao término do processamento de uma palavra, segue o código final que faz tal procedimento:

/*
     * VERIFICANDO SE A CADEIA INFORMADA NO ARQUIVO PERETENCE A LINGUAGEM DEFINIDA NO AUTOMATO
    */
    bool aceito = false;
    Q *atual = &estados[0];
    int count = 0;
    cout << "W: " << palavra << endl;
    /* enquanto houver transicoes p/ outros estados OU enquanto nao processar toda a cadeia de caracteres */
    while (atual != nullptr && count < palavra.size())
    {
        cout << "delta(" << atual->nome << ", " << palavra[count] << ") = ";
        if (palavra[count++] == '1')
            atual = atual->_1;
        else
            atual = atual->_0;
        if (atual != nullptr)
        {
            cout << atual->nome << endl;
        }
        else {
            cout << "-";
            break;
        }
        if (atual->final)
            aceito = true;
        else {
            aceito = false;
        }
        /*
         * se processamos toda a cadeia e estamos no estado final
         * entao aceita a palavra
         */
        if (palavra.size() == count && aceito ){
            cout << endl << "Aceito a palavra" << endl;
            break;
        }
    }
    if (!aceito || palavra.size() != count)
        cout << endl << "Rejeito a palavra" << endl;  
        
@autor *lucasdsl*
