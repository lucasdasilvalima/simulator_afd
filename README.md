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
@autor *lucasdsl*
