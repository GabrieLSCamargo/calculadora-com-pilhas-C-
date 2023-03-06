#include <iostream>
#include <stack> 
#include <string>
#include <map>
#include <cmath>



template<typename T>
struct Calculadora {

    std::stack<T> operandos;
    std::stack<char> operadores; 
    bool prim_operando = false, prim_operador = false;

    void destroi(void){
        while(operandos.empty() == false)
            operandos.pop();
        while(operadores.empty() == false)
            operadores.pop();
        prim_operador = false; prim_operando = false;
    }

    void operando(int op) {
        if(operadores.size() == 0) prim_operando = true;
        operandos.push(op);
    }

    void operador(char op){
        if(operandos.size() == 0) prim_operador = true;
        operadores.push(op);
    }

    void divisao_multiplicacao(char op)
    {
        int n1, n2;
        n1 = operandos.top();
        operandos.pop();
        n2 = operandos.top();
        operandos.pop();
        operadores.pop();

        if(op == '*') operando(n2*n1);
        if(op == '/') operando(std::round(static_cast<double>(n2)/n1));
        //std::cout << operandos.top() <<std::endl;
    }   

    void operacao (char op, int n1, int n2)
    {
        int n3;
        if(op == '+'){
            if(operadores.empty() == false){

                if(operadores.top() == '-') {
                    n3 = n1-n2;
                    if(n3 <0 ) n3 = n3*(-1);
                    operando(n3);
                }else operando(n2+n1);
            }
            else operando(n2+n1);
        }
        else if(op == '-'){
            operando(n2-n1);
        }else 
        if(op == '*') operando(n2*n1);
        else 
        if(op == '/') operando(std::round(static_cast<double>(n2)/n1));
    }

    void calcula()
    {
        int n1, n2;
        char op;
        while(operadores.empty() == false)
        {   
            if(operadores.top() == '('){
                operadores.pop();
                break;
            }
            //std::cout << operandos.top() << std::endl;

            n1 = operandos.top();
            operandos.pop();
            //std::cout << operandos.top() << std::endl;
            n2 = operandos.top();
            operandos.pop();
            op = operadores.top();
            //std::cout << operadores.top() << std::endl;
            operadores.pop();
            operacao(op, n1, n2);
            //std::cout << operandos.top() << std::endl;
        }
    }

    void negativar()
    {
        int n;
        if(operadores.top() == '-'){
            n = operandos.top();
            operandos.pop();
            operando(n*(-1));
            operadores.pop();
            if(!operadores.empty())
                operador('+');
            else if(!prim_operador)
                operador('+');
        }
    }

    void tratamentos (char op)
    {
        negativar();
        if(op == '*' || op == '/'){
            if(operandos.size()>1)
                divisao_multiplicacao(op);
        }
        else if(op == ')'){
            operadores.pop();
            calcula();
        }
    }

    void empilha(std::string& numeros)
    {
        int i = std::stoi(numeros);
        operando(i);
        //std::cout << operandos.top() << std::endl;
        numeros.clear();
    }

    void le_string(std::string form)
    {
        std::string numeros;
        int i=0;
        while(i<static_cast<int>(form.size()))
        {
            if(form[i] == '+' || form[i] == '-' || form[i] == '*' || form[i] == '/' || form[i] == '(' || form[i] == ')' ){
                if (!numeros.empty()) empilha(numeros);

                if(operadores.empty() == false){
                    tratamentos(operadores.top());
                    if(!operadores.empty())
                    {
                        tratamentos(operadores.top());
                    }
                    operador(form[i]);

                }else operador(form[i]);
                //std::cout << operadores.top() << std::endl;
            }
            else numeros.push_back(form[i]);
            i++;
        }
        if(!numeros.empty())empilha(numeros);
        tratamentos(operadores.top());
    }

    bool confere_pilha(void) {
        if(operandos.empty()) return false;
        if(operandos.size()>1 && operadores.empty()) return false;
        if(prim_operando && operadores.size() >= 1 && operandos.size() <2) return false;
        return true;
    }

    bool recebe_form(std::string form){
        destroi();
        char c = *prev(form.end());
        if(c == '*' || c == '+' || c == '-' || c == '/' || c == '(')
            return false;
        c = *form.begin();
        if(c == '*' || c == '/' || c == '+' || c == ')')
            return false;
        if(c == '-')
            prim_operador = true;
        else 
            prim_operando = true;
        le_string(form);
        return true;
    }

    int resultado(void) {
        if(operandos.empty())
            return static_cast<T>(0);
        return operandos.top();
    }
};

std::string expressao(std::string form)
{
    //std::cout << "inicio " << form << std::endl;
    bool func_valida = true;
    Calculadora <int> c;
    std::string resultado;
    func_valida = c.recebe_form(form);
    if(!func_valida){
    std::cout << "função invalida" << std::endl;
    return form;} 
    if(!c.confere_pilha()){
    std::cout << "função invalida" << std::endl;
    return form;} 
    c.calcula();
    resultado = std::to_string(c.resultado());
    //std::cout << "resultado" << resultado << std::endl;
    return resultado;
}

struct Celula {
  // Seu codigo aqui
  std::string formula;
};

bool operador (char c)
{
    if(c == '*' || c == '+' || c == '-' || c == '/' || c == '(' || c == ')')
        return true;
    else return false;
}

std::string transforma (std::string form ,std::map<std::string,Celula>& celulas)
{
    if(form[0] == '=')
    {
        form.erase(0,1);
        std::string recebe_chave, recebe_form; 
        recebe_form = form;
        int tam =0, inicio_s;
        for(int i = 0; i<static_cast<int>(form.size()); i++)
        {
            if(!isdigit(form[i]) && !operador(form[i]))
            {
                tam=0;
                inicio_s =i;
                while(!operador(form[i]))
                {
                    //if (i + 1 == form.length()) break; 
                    i++;
                    tam++;
                }
                recebe_chave=form.substr(inicio_s,tam);
                if(celulas[recebe_chave].formula[0] == '=')
                    celulas[recebe_chave].formula = transforma(celulas[recebe_chave].formula,celulas);
                //std::cout <<"antes " << recebe_form << std::endl;
                recebe_form.replace(recebe_form.find(recebe_chave), tam, celulas[recebe_chave].formula);
            }
        }
        //std::cout << "depois " << recebe_form << std::endl;
        recebe_form = expressao(recebe_form);
        return recebe_form;
    }
    else 
    {
        //std::cout << "form " << form << std::endl;   
        return form;
    }
}

int main()
{
    std::map<std::string,Celula> celulas;
    std::string posicao, formula;
    while(std::cin >> posicao >> formula)
    {
        celulas[posicao].formula = formula;
    }
    for(auto it= celulas.begin() ; it != celulas.end(); it++)
    {
        it->second.formula = transforma(it->second.formula, celulas);
    }

    for(auto it= celulas.begin(); it != celulas.end(); it++)
        std::cout << it->first << " " << it->second.formula << std::endl;
}