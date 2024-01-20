#include <iostream>
#include <cmath> 
#include <fstream>
#include <sstream>
#define jml_data 13
using namespace std;
const float h = 1.e-6;
float ra; float rb; float rc;
float a; float b; float c;
float da; float db; float dc;
int n=10;
float x[10];

void createX(int realChoice) {
    switch (realChoice) {
        case 1:
            for (int i=0; i<n; i++) {
                x[i] = ra*i + rb;
            }
            break;
        case 2:
            for (int i=0; i<n; i++) {
                x[i] = ra*pow(i,2) + rb*i + rc;
            }
            break;
        case 3:
            for (int i=0; i<n; i++) {
                x[i] = 1/(1+exp(-ra*i+rb));
            }
            break;
        case 4:
            for (int i=0; i<n; i++) {
                x[i] = 2/(1+exp(2*(-ra*i+rb)))-1;
            }
            break;
        case 5:
            for (int i=0; i<n; i++) {
                if (x<0) {
                    x[i] = 0;
                }
                else {
                    x[i] = ra*i+rb;
                }
            }
            break;
        case 6:
            for (int i=0; i<n; i++) {
                cout << "Input data for " << i << ": ";
                cin >> x[i];
            }
            break;
        default:
            for (int i=0; i<n; i++) {
                x[i] = ra*i + rb;
            }
            break;
    }
}

float model_lnr(int i) {
    return a*i + b;
}

float model_sqr(int i) {
    return a*pow(i,2) + b*i + c;
}

float model_sig(int i) {
    return 1/(1+exp(-a*i+b));
}

float model_tanh(int i) {
    return 2/(1+exp(2*(-a*i+b)))-1;
}

float model_reLu(int i) {
    if (x<0) {
        return 0;
    }
    return a*i+b;
}

float obj_func_sqr(int modelChoice) {
    float sum=0;
    
    switch (modelChoice) {
        case 1:
            for (int i = 0; i<n; i++) {
                sum += pow((x[i] - model_lnr(i)), 2);
            }
            break;
        case 2:
            for (int i = 0; i<n; i++) {
                sum += pow((x[i] - model_sqr(i)), 2);
            }
            break;
        case 3:
            for (int i = 0; i<n; i++) {
                sum += pow((x[i] - model_sig(i)), 2);
            }
            break;
        case 4:
            for (int i = 0; i<n; i++) {
                sum += pow((x[i] - model_tanh(i)), 2);
            }
            break;
        case 5:
            for (int i = 0; i<n; i++) {
                sum += pow((x[i] - model_reLu(i)), 2);
            }
            break;
        default:
            for (int i = 0; i<n; i++) {
                sum += pow((x[i] - model_lnr(i)), 2);
            }
            break;
    }
    return(sum/n);
}

float obj_func_abs(int modelChoice) {
    float sum=0;

    switch (modelChoice) {
        case 1:
            for (int i = 0; i<n; i++) {
                sum += fabs(model_lnr(i) - x[i]);
            }
            break;
        case 2:
            for (int i = 0; i<n; i++) {
                sum += fabs(model_sqr(i) - x[i]);
            }
            break;
        case 3:
            for (int i = 0; i<n; i++) {
                sum += fabs(model_sig(i) - x[i]);
            }
            break;
        case 4:
            for (int i = 0; i<n; i++) {
                sum += fabs(model_tanh(i) - x[i]);
            }
            break;
        case 5:
            for (int i = 0; i<n; i++) {
                sum += fabs(model_reLu(i) - x[i]);
            }
            break;
        default:
            for (int i = 0; i<n; i++) {
                sum += fabs(model_lnr(i) - x[i]);
            }
            break;
    }

    return(sum/n);
}

float obj_func_rtSqr(int modelChoice) {
    float sum=0;

    switch (modelChoice) {
        case 1:
            for (int i = 0; i<n; i++) {
                sum += pow((model_lnr(i) - x[i]), 2);
            }
            break;
        case 2:
            for (int i = 0; i<n; i++) {
                sum += pow((model_sqr(i) - x[i]), 2);
            }
            break;
        case 3:
            for (int i = 0; i<n; i++) {
                sum += pow((model_sig(i) - x[i]), 2);
            }
            break;
        case 4:
            for (int i = 0; i<n; i++) {
                sum += pow((model_tanh(i) - x[i]), 2);
            }
            break;
        case 5:
            for (int i = 0; i<n; i++) {
                sum += pow((model_reLu(i) - x[i]), 2);
            }
            break;
        default:
            for (int i = 0; i<n; i++) {
                sum += pow((model_lnr(i) - x[i]), 2);
            }
            break;
    }

    return(sqrt(sum/n));
}

float plot_obj_func(int modelChoice, int functionChoice) {
    int i,j,k;
    float delta=0.1;
    float error;
    float min_a, min_b, min_c, min_error;

    ofstream file_data;
    string filename="";
    filename.append("coefficients.txt");
    file_data.open(filename, ofstream::trunc);
    stringstream output;

    a=-3;
    for (i=0; i<6/delta; i++) {
        b=-3;
        for (j=0; j<6/delta; j++) {
            c=-3;
            for (k=0; k<6/delta; k++) {
                switch (functionChoice) {
                    case 1:
                        error = obj_func_sqr(modelChoice);
                        break;
                    case 2:
                        error = obj_func_abs(modelChoice);
                        break;
                    case 3:
                        error = obj_func_rtSqr(modelChoice);
                        break;
                    default:
                        error = obj_func_sqr(modelChoice);
                        break;
                }   
                if (i==0) {
                    min_error = error;
                    min_a = a;
                    min_b = b;
                    min_c = c;
                }
                else {
                    if (error < min_error) {
                        min_error = error;
                        min_a = a;
                        min_b = b;
                        min_c = c;
                    }
                }
                output << a << "," << b << "," << c << "," << log10(error) << endl;
                c+=delta;
            }
            b+=delta;
        }
        a+=delta;
    }
    file_data << output.str();
    cout << "a = " << min_a << ", b = " << min_b << ", c = " << min_c << ": error = " << min_error << endl;
}

int main() {
    int modelChoice = -1;

    cout << "Pick model: " << endl;
    cout << "1. Linear" << endl;
    cout << "2. Square" << endl;
    cout << "3. Sigmoid" << endl;
    cout << "4. Tanh" << endl;
    cout << "5. ReLu" << endl;
    cout << "Choice: ";
    cin >> modelChoice;

    system("cls");

    int functionChoice = -1;

    cout << "Pick Error Function: " << endl;
    cout << "1. Mean Square" << endl;
    cout << "2. Mean Absolute" << endl;
    cout << "3. Root Mean Square" << endl;
    cout << "Choice: ";
    cin >> functionChoice;

    system("cls");

    int realChoice = -1;

    cout << "Pick Real Model: " << endl;
    cout << "1. Linear: a*x + b" << endl;
    cout << "2. Square: a*x^2 + b*x + c" << endl;
    cout << "3. Sigmoid: 1/(1+e^(-ra*i+rb))" << endl;
    cout << "4. Tanh: 2/(1+e^(2*(-ra*i+rb)))-1" << endl;
    cout << "5. ReLu: 0 or a*x + b" << endl;
    cout << "6. Manual input (x = 0 -> 10)" << endl;
    cout << "Choice: ";
    cin >> realChoice;


    if (realChoice != 6) {
        cout << "Input Coefficients (-3 < n < 3): " << endl;
        cout << "Input a: ";
        cin >> ra;
        cout << "Input b: ";
        cin >> rb;
        if (realChoice == 2) {
            cout << "Input c: ";
            cin >> rc;
        }
    }

    system("cls");

    createX(realChoice);

    plot_obj_func(modelChoice, functionChoice);

    cout << "Done, execture grapher.exe" << endl;

    cin >> n;
}