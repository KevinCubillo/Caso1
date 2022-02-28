#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include<unordered_set>
#define SIZE 5
#define SIZE2 6

using namespace std;


/*
Instituto Tecnológico de Costa Rica
Análisis de Algoritmos

Prof. Rodrigo Núñez, Caso #1 - 5%
Estudiante: Kevin Josué Cubillo Chacón
*/


//PRIMERA PARTE

//// Compare The Triplets

/*Version ineficiente:
  Con un for se recorren los dos vectores y se va preguntando cual
  elemento es mayor, y de este modo ir sumando los resultados de Alice y Bob.
*/
vector<int> compareTriplets(vector<int> a, vector<int> b){
    vector<int> result = {0,0};
    for (int i = 0; i<3; i++){ // 3 sumas, // 4 comparaciones
       if(a[i] > b[i]){ // 3 compraciones
           result[0]+=1;
       }
       if (a[i] < b[i]) { //3 comparaciones
           result[1]+=1; // hasta 6 posibles sumas, contando las del acceso a la posiciones del arreglo
       }
    }
    return result;
} //total 10 comparaciones y 9 sumas


/*Version eficiente:
  Obtiene el resultado al comparar los 3 elementos de cada arreglo y sumar 1 si es mayor o 0 si no.
  Se puede observar que esta version tiene 6 comparaciones y 6 sumas, mientras que la anterior tiene
  10 comparciones y hasta 9 posibles sumas, por lo que es mejor.
*/
vector<int> compareTriplets2(vector<int> a, vector<int> b){
    vector<int> result = {0,0};
    result[0] = (a[0] > b[0])*1 + (a[1] > b[1])*1 + (a[2] > b[2])*1; //3 compraciones y 3 sumas
    result[1] = (b[0] > a[0])*1 + (b[1] > a[1])*1 +( b[2] > a[2])*1; //3 comparaciones y 3 sumas

    return result;
    //total 6 comparaciones y 6 sumas
}


//// Time Conversion

/*Version ineficiente:
4 comparaciones,6 sumas explicitas. Además de las operaciones internas
del to_string, stoi y substr.
*/

string timeConversion(string s){

    int hora = stoi(s.substr(0,2)); //extrae el int de la hora
    string result = s.substr(2,6); // crea un nuevo string con los minutos y segundos que no cambian

    if (s[8] == 'A'){ // Pregunta si es AM
        if (hora == 12){ //Si la hora es 12, agrega 00 al string de resultado
           result = "00"+result;

        }else{
            result = to_string(hora)+result; // convierte la hora a string y la concatena al resultado
        }
        if (hora<10){ //Agrega un 0 al inicio en caso de que la hora sea de un digito
            result = "0"+result;
        }

    }else if (hora != 12){ //hace el ajuste si PM
            result = to_string(hora+12)+result;
          }
          else{
            result = "12"+result;
        }
    return result;
}


/*Version eficiente:

   Esta version posee unicamente 2 comparaciones y no necesita de funciones como el
   to_string, stoi o substr, que internamente realizan muchos calculos. Además hace un
   mejor uso de la memoria, ya que no necesita de otro string para el resultado, si no
   que hace los cambios en el mismo string que recibe por parámetro.
*/
string timeConversion2(string s) {
    int hora = stoi(s.substr(0,2));

    if (s[8] == 'A'){ //comprueba si es AM
       hora = hora%12; //El modulo ayuda a que si es 12 se cambie a 0
    }
    else if (hora != 12){ //Si es PM suma 12 a la hora
        hora+=12;
    }

    s[0] = hora/10+'0'; //Reemplaza la hora en el string original
    s[1] = hora%10+'0';

    s.pop_back(); //Elimina el A o P
    s.pop_back(); //Elimina la M

    return s;
}



//// Subarray Division

/*Version ineficiente:
Utiliza dos for anidados para buscar todos los numeros
consecutivos que sumandos den "d".
*/

int birthday(vector<int> s, int d, int m){
    int result = 0;
    int sum;
    for (int i = 0; i<SIZE+1-m; i++){//limitamos el area de busqueda para que no se salga del rango de los m consecutivos.
        sum = 0;
        for(int j = 0; j<m; j++){
            sum+=s[i+j];//sumamos los m consecutivos
        }
        if (sum == d){ //comprobamos si la suma es valida
            result++;
        }
    }
    return result;
}

/*Version eficiente:
Utiliza un unico for que realiza la suma de todos los elementos, luego
al final de cada iteracion hace el ajuste para que queden solo los "m" consecutivos.
Esta version es mejor ya que reduce la cantidad de operaciones aritmeticas,
asi como el problema del doble for y las comparaciones que conlleva.
*/

int birthday2(vector<int> s, int d, int m){
    int result, sum = 0;
    for (int i = 0; i<SIZE2; i++){
        sum += s[i];
        if (i >= m-1){
            if (sum == d){
                 result += 1;
            }
            sum -= s[i-(m-1)];
        }
    }
    return result;
}



//SEGUNDA PARTE


//// The minion game

string minion_game(string word){

    int len = word.length();
    int kevinScore, stuartScore = 0;

    for (int i = 0; i<len; i++){ //se recorre el string

        if (word[i] == 'A' || word[i] == 'E' || word[i] == 'I' || word[i] == 'O' || word[i] == 'U'){ //Comprueba si el caracter es vocal
            kevinScore += len-i; //Le suma a Kevin la cantidad de substrings que inician con esa vocal.
        }
        else{
            stuartScore += len-i; //Le suma a Stuart la cantidad de substrings que inician con esa consonante.
        }
    }
    //Comprueba quien gano, o si es empate y retorna el resultado en el formato solicitado.
    if (kevinScore > stuartScore){
        return "Kevin " + to_string(kevinScore);
    }
    else if (stuartScore > kevinScore){
        return "Stuart "+ to_string(stuartScore);
    }
    else{
        return "Draw";
    }

}


//// Cipher

string cipher(int k, int n, string s){

    int aux[n]; //arreglo auxiliar
    int res[n]; //arreglo del resultado

    string result;
    result.resize(n); //defino el tam del string result

    res[0] = aux[0];
    result[0] = res[0]+48;

    for(int i = 0; i < n; i++){
        aux[i] = (int)s[i]%48;
        if(i<k){
             res[i] = aux[i]^aux[i-1]; //Hago el Xor con el anterior
             result[i] = res[i]+48; //hago la conversion a ascci y lo inserto en string.
        }
        else{
            res[i] = aux[i]^aux[i-1]^res[i-k];
            result[i] = res[i]+48;
        }

    }
    return result;
}

//// Pairs

int pairs(int k, vector<int> numbers){

    unordered_set<int> hash; //utilizo  unordered_set como una tabla hash
    int count = 0;

    for (int element : numbers){ //recorro el vector

        if (hash.find(element - k) != hash.end()) { //pregunto si la resta del elemento - k esta en la hash.
            count++;
        }

        if (hash.find(element + k) != hash.end()) { //pregunto si la suma del elemento + k esta en la hash.
           count++;
        }

        hash.insert(element); // inseto el el numero en la tabla para ser consultado despues.
    }

return count;

}


int main(){
    vector<int> result1 = compareTriplets({5,6,7},{3,6,10});
    vector<int> result2 = compareTriplets2({5,6,7},{3,6,10});
    cout<<"1. Compare The Triplets: \n\nPRUEBA 1\nInput:\n5 6 7\n3 6 10\n";
    cout<<"Output1: "<<result1[0]<<" "<<result1[1]<<endl;
    cout<<"Output2: "<<result2[0]<<" "<<result2[1]<<endl;
    result1 = compareTriplets({41,17,9},{32,1,4});
    result2 = compareTriplets2({41,17,9},{32,1,4});
    cout<<"\nPRUEBA 2: \nInput:\n41 17 9\n32 1 4\n";
    cout<<"Output1: "<<result1[0]<<" "<<result1[1]<<endl;
    cout<<"Output2: "<<result2[0]<<" "<<result2[1]<<endl;


    cout<<"\n2. Time Conversion: \n\nPRUEBA 1\nInput: 05:08:47PM\n";
    cout<<"Output1: "<<timeConversion("05:08:47PM")<<endl;
    cout<<"Output2: "<<timeConversion2("05:08:47PM")<<endl;
    cout<<"\nPRUEBA 2\nInput: 12:15:47AM\n";
    cout<<"Output1: "<<timeConversion("12:15:47AM")<<endl;
    cout<<"Output2: "<<timeConversion2("12:15:47AM")<<endl;

    cout<<"\n3. Subarray Division: \n\nPRUEBA 1\nInput:\n5\n1 2 1 3 2\n3 2\n";
    cout<<"Output1: "<<birthday({1,2,1,3,2}, 3,2)<<endl;
    cout<<"Output2: "<<birthday2({1,2,1,3,2}, 3,2)<<endl;
    cout<<"\nPRUEBA 2\nInput:\n6\n1 1 1 1 1 1\n3 2\n";
    cout<<"Output1: "<<birthday({1,1,1,1,1}, 3,2)<<endl;
    cout<<"Output2: "<<birthday2({1,1,1,1,1}, 3,2)<<endl;
    cout<<"\n4. The Minion Game: \n\nPRUEBA 1\nInput:BANANA \n";
    cout<<"Output: "<<minion_game("BANANA")<<endl;
    cout<<"\nPRUEBA 2\nInput: TRANSFORMER \n";
    cout<<"Output: "<<minion_game("TRANSFORMER")<<endl;

    cout<<"\n5. Cipher: \n\nPRUEBA 1\nInput:\n7 4\n1110100110\n";
    cout<<"Output: "<<cipher(7,4,"1110100110")<<endl;
    cout<<"\nPRUEBA 2\nInput:\n6 2\n1110001\n";
    cout<<"Output: "<<cipher(6,2,"1110001")<<endl;

    cout<<"\n6. Pairs: \n\nPRUEBA 1\nInput:\n5 2\n1 5 3 4 2\n";
    cout<<"Output: "<<pairs(2,{1,5,3,4,2})<<endl;
    cout<<"\nPRUEBA 2\nInput:\n6 3\n12 5 2 13 4 1\n";
    cout<<"Output: "<<pairs(3,{12,5,2,13,4,1})<<endl;

    return 0;
}



