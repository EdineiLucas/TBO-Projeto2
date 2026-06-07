#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ostream>

using namespace std;

vector <int> calculaLPS (const string &padrao){
    int m = padrao.length();
    vector <int> lps(m,0);
    int tamanho = 0;
    int i = 1;

    while (i < m){
        if(padrao[i] == padrao[tamanho]){
            tamanho ++;
            lps[i] = tamanho;
            i++;
        }else{
            if(tamanho != 0){
                tamanho = lps[tamanho -1];
            }else{
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

void buscaKMP(const string& texto, const string& palavra){
    int n = texto.length();
    int m = palavra.length();

    if(m == 0 || n == 0){
        cout << "Texto ou palavra para busca zerada" << endl;
        return;
    }

    vector <int> lps = calculaLPS(palavra);
    int i = 0, j = 0;

    bool encontrou  = false;
    int contadorOcorrencias = 0;

    while(i < n){
        if(palavra[j] == texto[i]){
            j++;
            i++;
        }

        if(j == m){
            contadorOcorrencias++;
            cout << "Ocorrencias: " << contadorOcorrencias << " |Palavra encontrada no indice: " << (i - j) << endl;
            encontrou = true;
            j = lps [j - 1];
        }else if(i < n && palavra[j] != texto[i]){
            if(j != 0){
                j = lps[j-1];
            }else{
                i++;
            }
        }
    }

    if(!encontrou){
        cout << "Palavra nao encontrada" << endl;
    }
}

int main (){

    ifstream arquivoDicionario("Fonte de dados/dicionario.txt");
    stringstream dicionario;
    string palavraBusca;

    if(!arquivoDicionario.is_open()){
        cout << "Arquivo de cinema nao aberto" << endl;
        return 1;
    }

    dicionario << arquivoDicionario.rdbuf();
    arquivoDicionario.close();

    string textocompleto = dicionario.str();

    cout << "Digite o que deseja buscas" << endl;
    cin >> palavraBusca;

    cout << " --- Busca KMP ---" << endl;
    buscaKMP(textocompleto, palavraBusca);


    cout << "Rodou";
    return 0;
}