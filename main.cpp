#include <iostream>
#include <vector>

using namespace std;

struct estado{
    string nome;
    struct estado *_0;
    struct estado *_1;
    bool inicial;
    bool final;
}typedef Q;

/*
 * create function 'split' in c++ http://www.cplusplus.com/articles/2wA0RXSz/
 */
const vector<string> explode(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}
/* usar o algoritiomo passando um arquivo de texto com as definicoes da gramatica */
int main(int args, char* argv[])
{
    vector<Q> estados;
    FILE *arquivo = nullptr;
    int qtd_estados = 0;
    string texto_arquivo;
    string palavra;
    vector<string> linha;
    vector<string> estado;
    vector<string> estados_finais;
    // Definicao de variaveis

   if (args < 1)
        return 1;

    /*LER O ARQUIVO E ARMAZER INFORMACOES NAS VARIVEIS*/
    arquivo = fopen(argv[1], "r");
    char c[20];
    while (fgets(c, 20, arquivo) != nullptr)
        texto_arquivo += c;
    fclose(arquivo);
    linha = explode(texto_arquivo, '\n');
    palavra = linha[0];
    estado = explode(linha[1], ' ');
    estados_finais = explode(linha[2], ' ');
    qtd_estados = int(estado.size());

    /*
     *  CRIAR UMA LISTA DE ESTADOS, INICIALIZANDO O ESTADO INICIAL
     *  SABE SE QUE O PRIMEIRO ELEMENTO DENTRE OS ESTADOS EH O INICIAL
    */
    for (int i = 0; i < estado.size(); i++)
    {
        Q estado_temporario;
        estado_temporario.nome = estado[i];
        if (i == 0)
            estado_temporario.inicial = true;
        else
            estado_temporario.inicial = false;
        estado_temporario.final = false;
        estado_temporario._0 = estado_temporario._1 = nullptr;
        estados.push_back(estado_temporario);
    }
    /*
     *  DEFININDO TODOS OS ESTADOS FINAIS PARA A LISTA DE AUTOMATO
     */
    for (int i = 0; i < estados_finais.size(); i++)
    {
        for (int j = 0; j < estados.size(); j++)
        {
            if (estados_finais[i] == estados[j].nome)
            {
                estados[j].final = true;
            }
        }
    }
    /*
     * DEFINIDO TODAS AS TRANSICOES ENTRE OS OS ESTADOS DO AUTOMATO;
     * CASO NAO HAJA TRANSICAO, ELA SERA UM nullptr, UMA ABSTRACAO PARA
     * A TRANSICAO INDEFINIDA
    */
    for (int i = 3; i < linha.size(); i++)
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
    return 0;
}
